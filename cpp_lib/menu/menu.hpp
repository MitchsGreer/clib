///////////////////////////////////////////////////////////////////////////////
/// @file menu.hpp
///
/// @brief Template for command line menu.
///////////////////////////////////////////////////////////////////////////////

#include <vector>
#include <memory>
#include <string>

class MenuItem
{
public:
    MenuItem();
    ~MenuItem();

    bool enter() = 0;
    const std::string name();
    const std::string help();

private:
    std::string m_name;
    std::string m_help;
};

class Menu
{
public:
    Menu();
    ~Menu();

    bool enter();
    bool add_menu_item(std::unique_ptr<MenuItem> new_menu_item);
    bool remove_menu_item(std::string menu_item_name);

private:

    std::string get_input();
    bool enter_menu_item();
    std::string help();
    std::string name();

    std::vector<std::unique_ptr<MenuItem>> m_menu_items;
};

