// Eden Yefet 204778294
// Bar Katz 208561357

#ifndef REVERSI_JOINCOMMAND_H
#define REVERSI_JOINCOMMAND_H

#include "../include/Command.h"

class Server;

class JoinCommand : public Command {
 private:
  Server &server;

 public:

  JoinCommand(Server &s);
  virtual void execute(vector<string> args, int player_join_socket);
};

#endif //REVERSI_JOINCOMMAND_H
