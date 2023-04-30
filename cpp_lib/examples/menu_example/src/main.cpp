///////////////////////////////////////////////////////////////////////////////
/// @file main.cpp
///
/// @brief Example usage of the menu library.
///////////////////////////////////////////////////////////////////////////////
#include <memory>
#include "menu.hpp"
#include "menu_item.hpp"
#include "example_menu_item.hpp"

///////////////////////////////////////////////////////////////////////////////
/// @brief Main entry point for this application.
///
/// @param argc The number of command line arguments provided ot this
///             application over the command line.
/// @param argv A list of arguments for this command, terminated by nullptr.
///
/// @return 0 If there are no errors, 1 otherwise.
///////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
    Menu main_menu("Example Menu");
    std::unique_ptr<MenuItem> menu_item(new ExampleMenuItem("example", "This is an example menu item."));

    main_menu.add_menu_item(menu_item);

    return !main_menu.enter();
}
