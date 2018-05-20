// Eden Yefet 204778294
// Bar Katz 208561357

#ifndef REVERSI_COMMANDMANAGER_H
#define REVERSI_COMMANDMANAGER_H

#include <string.h>
#include <iostream>
#include <vector>
#include <map>
#include "StartCommand.h"

using namespace std;

class CommandManager {
 private:
  map<string, Command*> commands_list;

 public:
  CommandManager(Server &server);
  ~CommandManager();
  void executeCommand(char *command_name, vector<string> args, int
  player_socket);
};

#endif //REVERSI_COMMANDMANAGER_H
