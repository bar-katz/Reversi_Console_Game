// Eden Yefet 204778294
// Bar Katz 208561357

#include "../include/StartCommand.h"
#include "../include/Server.h"

StartCommand::StartCommand(Server &s) : server(s) {}

void StartCommand::execute(vector<string> args, int player_socket) {

  server.createNewRoom(args.at(0), player_socket);
}
