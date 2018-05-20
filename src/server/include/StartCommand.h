// Eden Yefet 204778294
// Bar Katz 208561357

#ifndef REVERSI_STARTCOMMAND_H
#define REVERSI_STARTCOMMAND_H

#include "../include/Command.h"

class Server;

class StartCommand : public Command {
 private:
  Server &server;

 public:

  StartCommand(Server &s);
  virtual void execute(vector<string> args, int player_socket);
};

#endif //REVERSI_STARTCOMMAND_H

