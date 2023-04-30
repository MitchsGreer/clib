///////////////////////////////////////////////////////////////////////////////
/// @file menu.cpp
///
/// @brief Implementation for command line menu.
///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <algorithm>
#include <vector>
#include <memory>
#include "menu.hpp"
#include "menu_item.hpp"

///////////////////////////////////////////////////////////////////////////////
/// @brief Constructor for MenuItem.
///
/// @param [in] menu_name The name of this menu.
/// @param [in] exit_string The string for the user to input to exit the menu.
///                         Defaults to "exit".
/// @param [in] case_sensitive Flag for case sensitivity for menu item
///                            selection, true for case sensitive, false for
///                            not. Defaults to false.
///////////////////////////////////////////////////////////////////////////////
Menu::Menu(std::string menu_name, std::string exit_string, std::string help_string, bool case_sensitive)
{
    this->m_case_sensitive = case_sensitive;
    this->m_menu_items.clear();
    this->m_name = menu_name;
    this->m_exit_string = exit_string;
    this->m_help_string = help_string;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroyer for Menu.
///////////////////////////////////////////////////////////////////////////////
Menu::~Menu()
{
    /* Does nothing. */
}

///////////////////////////////////////////////////////////////////////////////
/// @brief This is the main loop for the menu, upon user entering the exit
///        string, they will leave this loop.
///
/// @returns True if the menu was exited without error, false otherwise.
///////////////////////////////////////////////////////////////////////////////
bool Menu::enter()
{
    bool success = false;
    std::string input;

    while(true)
    {
        std::cout << std::endl << this->help();
        input = get_input();

        if (input == this->m_exit_string)
        {
            break;
        }
        else if (input == this->m_help_string)
        {
            std::cout << this->long_help();
        }
        else if (this->menu_item_index(input) != this->m_menu_items.end())
        {
            success = (*(*this->menu_item_index(input))).enter();
        }
        else
        {
            std::cout << "Item not recognized: " << input << std::endl;
        }
    }

    return success;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Add a menu item to the menu, the item will not be added if another
///        with the same name exists. The menu owns the pointer once its added.
///
/// @param [in] new_menu_item The menu item to add to the internal menu list.
///
/// @returns True if the menu item was added, false otherwise.
///////////////////////////////////////////////////////////////////////////////
bool Menu::add_menu_item(std::unique_ptr<MenuItem> &new_menu_item)
{
    bool success = false;

    if (this->menu_item_index((*new_menu_item).name()) == this->m_menu_items.end())
    {
        if ((*new_menu_item).name() != this->m_help_string && (*new_menu_item).name() != this->m_exit_string)
        {
            this->m_menu_items.push_back(std::move(new_menu_item));
            success = true;
        }
    }

    return success;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Add a menu item to the menu, the item will not be added if another
///        with the same name exists. The menu owns the pointer once its added.
///
/// @param [in] menu_item_name The name of the menu item to remove from the
///                            list.
///
/// @returns True if the menu item was removed, false otherwise.
///////////////////////////////////////////////////////////////////////////////
bool Menu::remove_menu_item(std::string menu_item_name)
{
    bool success = false;

    if (this->menu_item_index(menu_item_name) != this->m_menu_items.end())
    {
        this->m_menu_items.erase(this->menu_item_index(menu_item_name));
        success = true;
    }

    return success;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Get input from the user and lowercase it if case insensitive.
///
/// @returns The user input string.
///////////////////////////////////////////////////////////////////////////////
std::string Menu::get_input()
{
    std::string user_input;
    std::cin >> user_input;

    if (!this->m_case_sensitive)
    {
        /* Stole this line from https://stackoverflow.com/questions/313970/how-to-convert-an-instance-of-stdstring-to-lower-case */
        std::transform(user_input.begin(), user_input.end(), user_input.begin(), [](unsigned char c){ return std::tolower(c); });
    }

    return user_input;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Builds the help string for this menu.
///
/// @returns The help string for this menu.
///////////////////////////////////////////////////////////////////////////////
const std::string Menu::help()
{
    std::vector<std::string> options_list;
    std::string help_text = "";

    /* Add the starting bit. */
    help_text += this->m_name;
    help_text += " commands: ";

    /* Add the sorted commands. */
    options_list.push_back(this->m_exit_string);
    options_list.push_back(this->m_help_string);

    for(std::vector<std::unique_ptr<MenuItem>>::iterator iter = this->m_menu_items.begin(); iter < this->m_menu_items.end(); iter++)
    {
        options_list.push_back((*(*iter)).name());
    }

    std::sort(options_list.begin(), options_list.end());

    for (std::string menu_item: options_list)
    {
        help_text += menu_item;
        help_text += ", ";
    }

    help_text.erase(help_text.find_last_of(','));

    help_text += "\n";

    return help_text;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Construct long help for all menu options.
///
/// @returns The long help for this menu.
///////////////////////////////////////////////////////////////////////////////
const std::string Menu::long_help()
{
    std::vector<std::string> options_list;
    std::string help_text = "";

    /* Add the starting bit. */
    help_text += "\n";
    help_text += this->m_name;
    help_text += " Help:\n";

    /* Add the sorted commands. */
    options_list.push_back(this->m_exit_string);
    options_list.push_back(this->m_help_string);

    for(std::vector<std::unique_ptr<MenuItem>>::iterator iter = this->m_menu_items.begin(); iter < this->m_menu_items.end(); iter++)
    {
        options_list.push_back((*(*iter)).name());
    }

    std::sort(options_list.begin(), options_list.end());

    for (std::string menu_item: options_list)
    {
        help_text += menu_item;
        help_text += ": ";

        if (menu_item == this->m_exit_string)
        {
            help_text += "Exit this menu.";
        }
        else if (menu_item == this->m_help_string)
        {
            help_text += "Display this help menu.";
        }
        else
        {
            help_text += (*(*this->menu_item_index(menu_item))).help();
        }

        help_text += "\n";
    }

    return help_text;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Getter for Menu name.
///
/// @returns The name of this menu.
///////////////////////////////////////////////////////////////////////////////
const std::string Menu::name()
{
    return this->m_name;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Find the index of the menu item at the given name.
///
/// @param [in] menu_item_name The name of the menu item to search for.
///
/// @returns The index of the menu item if found, -1 otherwise.
///////////////////////////////////////////////////////////////////////////////
const std::vector<std::unique_ptr<MenuItem>>::iterator Menu::menu_item_index(std::string menu_item_name)
{
    std::vector<std::unique_ptr<MenuItem>>::iterator index = this->m_menu_items.end();

    for(std::vector<std::unique_ptr<MenuItem>>::iterator iter = this->m_menu_items.begin(); iter < this->m_menu_items.end(); iter++)
    {
        std::string menu_name = (*(*iter)).name();
        if (!this->m_case_sensitive)
        {
            /* Stole this line from https://stackoverflow.com/questions/313970/how-to-convert-an-instance-of-stdstring-to-lower-case */
            std::transform(menu_name.begin(), menu_name.end(), menu_name.begin(), [](unsigned char c){ return std::tolower(c); });
        }

        if (menu_name == menu_item_name)
        {
            index = iter;
            break;
        }
    }

    return index;
}
