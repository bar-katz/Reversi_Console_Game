// Eden Yefet 204778294
// Bar Katz 208561357



#include "../include/CloseOtherSocketTask.h"
#include "../include/ShowAvailableGamesTask.h"
#include "../include/CloseSelfSocketTask.h"
#include "../include/LocalVersusRemoteChoice.h"

kMenuVal LocalVersusRemoteChoice::execute() {
  return startSubMenu();
}

string LocalVersusRemoteChoice::getTitle() {
  return "Play Online";
}

LocalVersusRemoteChoice::LocalVersusRemoteChoice(Game *game, int board_size,
                                                 Display *display) {
  cout << "Constructor" << endl;
  this->game = game;
  this->board_size = board_size;
  this->display = display;

  ifstream config("config.txt");
  string ip;
  string port;
  getline(config, ip);
  getline(config, port);

  RemotePlayer *remote_player =
      new RemotePlayer(ip.c_str(), atoi(port.c_str()), display);
  LocalPlayer *localPlayer = new LocalPlayer();
  this->two_players = new TwoPlayers(localPlayer, remote_player);

  sub_menu_items.push_back(new StartNewRemoteGameTask(remote_player));
  sub_menu_items.push_back(new JoinToGameTask(remote_player));
  sub_menu_items.push_back(new ShowAvailableGamesTask(remote_player));
  sub_menu_items.push_back(new CloseOtherSocketTask(remote_player));
  sub_menu_items.push_back(new CloseSocketTask(remote_player));
}

LocalVersusRemoteChoice::~LocalVersusRemoteChoice() {
  delete this->two_players;

  for (vector<MenuItem *>::iterator it = sub_menu_items.begin(); it !=
      sub_menu_items.end(); it++) {
    delete (*it);
  }
  sub_menu_items.clear();
}

kMenuVal LocalVersusRemoteChoice::startSubMenu() {
  kMenuVal menu_value = kContinue;

  while (menu_value == kPlay || menu_value == kContinue) {

    try {
      static_cast<RemotePlayer *>(this->two_players->getP2())->connectToServer();
    } catch (char const *c) {
      cout << c << endl;
      return kContinue;
    }
    display->print(cout << "\n--- Online Menu ---" << endl);
    display->print(cout << "Please choose an option: " << endl);

    for (int i = 0; i < sub_menu_items.size(); i++) {
      display->print(
          cout << i + 1 << ". " << sub_menu_items[i]->getTitle() << endl);
    }

    // Asks the user to choose a command
    int game_mode;
    cin >> game_mode;
    while (cin.fail() || game_mode <= 0 || game_mode > sub_menu_items.size()) {
      cin.clear();
      cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      display->print(cout << "Please enter a valid option." << endl);
      cin >> game_mode;
    }

    menu_value = sub_menu_items[game_mode - 1]->execute();
    if (menu_value == kPlay) {
      game->startNewGame(this->two_players, this->board_size);
    }

  }
  return kContinue;
}
