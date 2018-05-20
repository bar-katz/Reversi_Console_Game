// Eden Yefet 204778294
// Bar Katz 208561357

#include "../include/CloseCommand.h"

#include "../include/Server.h"

CloseCommand::CloseCommand(Server &s) : server(s) {}

void CloseCommand::execute(vector<string> args, int player_socket) {
  if(!args.empty()) {
    server.closeRoom(args[0], player_socket);
  } else {
    server.closeRoom("", player_socket);
  }
}