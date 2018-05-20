// Eden Yefet 204778294
// Bar Katz 208561357

#ifndef REVERSI_AVAILABLEGAMES_H
#define REVERSI_AVAILABLEGAMES_H

#include <iostream>
#include <vector>
#include <map>

using namespace std;

class AvailableGames {
 private:
  AvailableGames() {}
  AvailableGames(AvailableGames const &);
  void operator=(AvailableGames const &);

 public:
  static vector<string> getList();
  static void add(string game_name, int player_socket);
  static int remove(string game_name);
  static bool exists(string game_name);

};

#endif //REVERSI_AVAILABLEGAMES_H
