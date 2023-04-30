///////////////////////////////////////////////////////////////////////////////
/// @file menu_item.hpp
///
/// @brief Definition of a menu item.
///////////////////////////////////////////////////////////////////////////////
#ifndef MENU_ITEM_H
#define MENU_ITEM_H

#include <string>

class MenuItem
{
public:
    MenuItem(std::string item_name, std::string item_help_text);
    virtual ~MenuItem();

    virtual bool enter() = 0;
    const std::string name();
    const std::string help();

private:
    std::string m_name;
    std::string m_help;
};

#endif // MENU_ITEM_H
