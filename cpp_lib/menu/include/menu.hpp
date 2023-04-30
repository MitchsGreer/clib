///////////////////////////////////////////////////////////////////////////////
/// @file menu.hpp
///
/// @brief Definition for command line menu.
///////////////////////////////////////////////////////////////////////////////
#ifndef MENU_H
#define MENU_H

#include <vector>
#include <memory>
#include <string>

#include "menu_item.hpp"

class Menu
{
public:
    Menu(std::string menu_name, std::string exit_string = "exit", bool case_sensitive = false);
    ~Menu();

    bool enter();
    bool add_menu_item(std::unique_ptr<MenuItem> &new_menu_item);
    bool remove_menu_item(std::string menu_item_name);

private:

    std::string get_input();
    const std::string help();
    const std::string name();
    const std::vector<std::unique_ptr<MenuItem>>::iterator menu_item_index(std::string menu_item_name);

    std::vector<std::unique_ptr<MenuItem>> m_menu_items;
    std::string m_name;
    bool m_case_sensitive;
    std::string m_exit_string;
};

#endif // MENU_H
