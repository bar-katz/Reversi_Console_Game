// Eden Yefet 204778294
// Bar Katz 208561357

#ifndef REVERSI_LISTGAMESCOMMAND_H
#define REVERSI_LISTGAMESCOMMAND_H

#include "../include/Command.h"

class Server;

class ListGamesCommand : public Command {
 private:
  Server &server;

 public:

  ListGamesCommand(Server &s);
  virtual void execute(vector<string> args, int player_socket);
};

#endif //REVERSI_LISTGAMESCOMMAND_H
