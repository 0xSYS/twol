#include "tui.hpp"

#include <string>
#include <iostream>
#include <vector>



#include <ftxui/component/captured_mouse.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/table.hpp>
#include <ftxui/dom/node.hpp>
#include <ftxui/screen/color.hpp>











// using namespace ftxui;

// This is a helper function to create a button with a custom style.
// The style is defined by a lambda function that takes an EntryState and
// returns an Element.
// We are using `center` to center the text inside the button, then `border` to
// add a border around the button, and finally `flex` to make the button fill
// the available space.

ftxui::ButtonOption Style() 
{
  auto option = ftxui::ButtonOption::Animated();
  option.transform = [](const ftxui::EntryState& s) 
  {
    auto element = ftxui::text(s.label);
    if (s.focused) 
    {
      element |= ftxui::bold;
    }
    return element | ftxui::center | ftxui::borderEmpty | ftxui::flex;
  };
  return option;
}

// auto screen = ftxui::ScreenInteractive::TerminalOutput();

void tui_main()
{
  std::vector<std::vector<std::string>> pc_list_table =
  {
    {"Name", "MAC Addres", "Brodcast IP", "Power Status"},
    {"[PC_1]", "aa:bb:cc:dd:ee:ff", "192.168.1.83", "Offline"},
    {"Wokspace Computer", "gg:hh:ii:jj:kk:ll", "192.168.1.44", "Online"},
    {"Main Server", "aa:bb:cc:dd:ee:ff", "192.168.1.54", "Online"},
    {"Desktop PC", "aa:bb:cc:dd:ee:ff", "192.168.1.65", "- null -"},
    {"My Laptop", "aa:bb:cc:dd:ee:ff", "192.168.1.89", "Failed"}
  };
  auto screen = ftxui::ScreenInteractive::TerminalOutput();

  int sel_row = 1;

  // Table style configurations
  auto table_rend = ftxui::Renderer([&]{
    auto table = ftxui::Table(pc_list_table);

    // Table decorations
    table.SelectAll().Border(ftxui::DOUBLE);

    table.SelectColumn(0).Border(ftxui::DOUBLE);
    table.SelectColumn(1).Border(ftxui::DOUBLE);
    table.SelectColumn(2).Border(ftxui::DOUBLE);
    table.SelectColumn(3).Border(ftxui::DOUBLE);

    table.SelectRow(0).Decorate(ftxui::bold);
    table.SelectRow(0).SeparatorVertical(ftxui::DOUBLE);
    table.SelectRow(0).Border(ftxui::DOUBLE);

    // Highlight the selected item
    table.SelectRow(sel_row).DecorateCells(bgcolor(ftxui::Color::DodgerBlue1));

    return table.Render() | ftxui::border;                             
  });

  // Handling Keboard events...
  auto k_handle = ftxui::CatchEvent(table_rend, [&](ftxui::Event evt){
    if(evt == ftxui::Event::ArrowUp)
    {
      sel_row = std::max(1, sel_row  -1); // Stops item highlighting from getting out of the number of items in the table.
      return true;
    }
    if(evt == ftxui::Event::ArrowDown)
    {
      sel_row = std::min((int) pc_list_table.size() -1, sel_row + 1); // Aagin the same thing but when the down key action occurs.
      return true;
    }
    return false;                       
  });
	std::vector<std::string> tab_values{
      "Main",
      "Settings",
      "About",
  };
  int tab_selected = 0;
  auto tab_toggle = ftxui::Toggle(&tab_values, &tab_selected);

  std::vector<std::string> tab_1_entries{
      "Forest",
      "Water",
      "I don't know",
  };
  int tab_1_selected = 0;

  std::vector<std::string> tab_2_entries{
      "Hello",
      "Hi",
      "Hay",
  };
  int tab_2_selected = 0;

  std::vector<std::string> tab_3_entries{
      "Table",
      "Nothing",
      "Is",
      "Empty",
  };
  int tab_3_selected = 0;
  int value;
  int row = 0;
  auto button1 = ftxui::Button("Add", [&] { value -= 1; }, Style());
  auto button2 = ftxui::Button("Remove", [&] { value -= 1; }, Style());
  auto quit_btn = ftxui::Button("Quit", [&] {screen.ExitLoopClosure()();}, Style());
  

  auto buttons_container = ftxui::Container::Vertical({
        button1,
        button2,
        quit_btn
    });
  auto tab_content1 = ftxui::Renderer(buttons_container, [&]{
    return ftxui::vbox({
      // buttons_container->Render() | ftxui::center,
      ftxui::hbox({
                ftxui::vbox({
                    button1->Render() | size(ftxui::WIDTH, ftxui::EQUAL, 7) | size(ftxui::HEIGHT, ftxui::EQUAL, 3),
                    ftxui::vbox({}) | size(ftxui::HEIGHT, ftxui::EQUAL, 1),
                    button2->Render() | size(ftxui::WIDTH, ftxui::EQUAL, 7) | size(ftxui::HEIGHT, ftxui::EQUAL, 3),
                    ftxui::vbox({}) | size(ftxui::HEIGHT, ftxui::EQUAL, 1),
                    quit_btn -> Render() | size(ftxui::WIDTH, ftxui::EQUAL, 7) | size(ftxui::HEIGHT, ftxui::EQUAL, 3),
                    k_handle -> Render(),      
                    // Separator for the status bar    
                    ftxui::separator(),
                }) | ftxui::xflex_grow,  // Align the buttons to the left
            }) | ftxui::flex,
      // I accidentally created the status bar XD
      // Awesome :D
      ftxui::hbox({
                ftxui::text("Status: - - - - "),
      }),
    });                   
});
  auto tab_container = ftxui::Container::Tab(
      {
          tab_content1 ,
          ftxui::Radiobox(&tab_2_entries, &tab_2_selected)
      },
      &tab_selected);

  auto container = ftxui::Container::Vertical({
      tab_toggle,
      tab_container,
  });

  auto renderer = Renderer(container, [&] {
    return ftxui::vbox({
               tab_toggle->Render(),
               ftxui::separator(),
               tab_container -> Render(),
           }) |
           ftxui::border;
  });
  screen.Loop(renderer);
}

/*
|-------------|
|             |
| FTXUI TESTS |
|             |
|-------------|
*/


// Dev only
#ifdef TUI_TESTS
void tui_tests()
{
  // Table data
    std::vector<std::vector<std::string>> table_data = {
        {"Version", "Marketing name", "Release date", "API level", "Runtime"},
        {"2.3", "Gingerbread", "February 9 2011", "10", "Dalvik 1.4.0"},
        {"4.0", "Ice Cream Sandwich", "October 19 2011", "15", "Dalvik"},
        {"4.1", "Jelly Bean", "July 9 2012", "16", "Dalvik"},
        {"4.2", "Jelly Bean", "November 13 2012", "17", "Dalvik"},
        {"4.3", "Jelly Bean", "July 24 2013", "18", "Dalvik"},
        {"4.4", "KitKat", "October 31 2013", "19", "Dalvik and ART"},
        {"5.0", "Lollipop", "November 3 2014", "21", "ART"},
        {"5.1", "Lollipop", "March 9 2015", "22", "ART"},
        {"6.0", "Marshmallow", "October 5 2015", "23", "ART"},
        {"7.0", "Nougat", "August 22 2016", "24", "ART"},
        {"7.1", "Nougat", "October 4 2016", "25", "ART"},
        {"8.0", "Oreo", "August 21 2017", "26", "ART"},
        {"8.1", "Oreo", "December 5 2017", "27", "ART"},
        {"9", "Pie", "August 6 2018", "28", "ART"},
        {"10", "10", "September 3 2019", "29", "ART"},
        {"11", "11", "September 8 2020", "30", "ART"},
    };
    // State to track selected row
    int selected_row = 1;  // Start with the first row after the header
    auto screen = ScreenInteractive::Fullscreen();
    // Renderer for the table
    auto table_renderer = Renderer([&] {
        auto table = Table(table_data);
        // Decorate the table
        table.SelectAll().Border(DOUBLE);
        table.SelectColumn(0).Border(DOUBLE);
        table.SelectColumn(1).Border(DOUBLE);
        table.SelectColumn(2).Border(DOUBLE);
        table.SelectRow(0).Decorate(bold);
        table.SelectRow(0).SeparatorVertical(DOUBLE);
        table.SelectRow(0).Border(DOUBLE);
        table.SelectColumn(2).DecorateCells(align_right);
        // Highlight the selected row
        table.SelectRow(selected_row).DecorateCells(bgcolor(Color::DodgerBlue1));     
        // Render the table
        return table.Render() | border | vscroll_indicator;
    });
    // Main component for handling keyboard navigation
    auto main_component = CatchEvent(table_renderer, [&](Event event) {
        if (event == Event::ArrowUp) {
            selected_row = std::max(1, selected_row - 1);  // Prevent going above the header row
            return true;
        }
        if (event == Event::ArrowDown) {
            selected_row = std::min((int)table_data.size() - 1, selected_row + 1);  // Prevent overflow
            return true;
        }
        return false;
    });
  // Make the table scrollable
    // auto scrollable_component = Scrollable(main_component);
    // Start the interactive loop
    screen.Loop(main_component);    
}
#endif
