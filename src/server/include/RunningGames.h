// Eden Yefet 204778294
// Bar Katz 208561357

#ifndef REVERSI_RUNNINGGAMES_H
#define REVERSI_RUNNINGGAMES_H

#include <iostream>
#include <vector>
#include <map>

using namespace std;

class RunningGames {
 private:
  RunningGames() {}
  RunningGames(RunningGames const &);
  void operator=(RunningGames const &);

 public:
  static vector<string> getList();
  static void add(string game_name, int player1_socket, int player2_socket);
  static vector<int> remove(string game_name);
  static bool exists(string game_name);

};

#endif //REVERSI_RUNNINGGAMES_H
