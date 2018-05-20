// Eden Yefet 204778294
// Bar Katz 208561357

#ifndef REVERSI_COMMAND_H
#define REVERSI_COMMAND_H
#include <string.h>
#include <iostream>
#include <vector>

using namespace std;


class Command {
 public:
  virtual void execute(vector<string> args, int player_socket) = 0;

};

#endif //REVERSI_COMMAND_H
