// Eden Yefet 204778294
// Bar Katz 208561357

#ifndef REVERSI_CLOSECOMMAND_H
#define REVERSI_CLOSECOMMAND_H

#include "../include/Command.h"

class Server;

class CloseCommand : public Command {
 private:
  Server &server;

 public:

  CloseCommand(Server &s);
  virtual void execute(vector<string> args, int player_socket);
};

#endif //REVERSI_CLOSECOMMAND_H
