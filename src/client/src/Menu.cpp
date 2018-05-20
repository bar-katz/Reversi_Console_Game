// Eden Yefet 204778294
// Bar Katz 208561357


#include "../include/Menu.h"

void *Menu::startMenu() {
  kMenuVal should_continue = kContinue;
  while (should_continue == kContinue || should_continue == kPlay) {
    display->print(cout << "\n--- Main Menu ---" << endl);
    display->print(cout << "Welcome!, please choose an option: " << endl);

    for (int i = 0; i < menu_items.size(); i++) {
      display->print(
          cout << i + 1 << ". " << menu_items[i]->getTitle() << endl);
    }

    // Asks the user to choose a game mode
    int game_mode;
    cin >> game_mode;
    while (cin.fail() || game_mode <= 0 || game_mode > menu_items.size()) {
      cin.clear();
      cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      display->print(cout << "Please enter a valid option." << endl);
      cin >> game_mode;
    }
    should_continue = menu_items[game_mode - 1]->execute();
  }
}

Menu::Menu(string menu_title, Display *display) : game(display) {
  this->display = display;
  this->menu_title.assign(menu_title);

}

void Menu::addMenuItem(MenuItem *menu_item) {
  menu_items.push_back(menu_item);
}

Menu::~Menu() {
}
