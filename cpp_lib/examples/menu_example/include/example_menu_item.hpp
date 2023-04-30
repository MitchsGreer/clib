///////////////////////////////////////////////////////////////////////////////
/// @file example_menu_item.hpp
///
/// @brief Definition of an example menu item.
///////////////////////////////////////////////////////////////////////////////
#include "menu_item.hpp"


class ExampleMenuItem : public MenuItem
{
public:

    ExampleMenuItem(std::string name, std::string item_help_text): MenuItem(name, item_help_text){}
    ~ExampleMenuItem() {}

    bool enter();

private:
};
