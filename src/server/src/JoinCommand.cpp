// Eden Yefet 204778294
// Bar Katz 208561357

#include "../include/RunningGames.h"
#include "../include/JoinCommand.h"
#include "../include/Server.h"
#include "../include/AvailableGames.h"

JoinCommand::JoinCommand(Server &s) : server(s) {}

void JoinCommand::execute(vector<string> args, int player_join_socket) {

  // remove game from available games
  int player_start_socket = AvailableGames::remove(args[0]);

  // execute
  server.run(args[0], player_start_socket, player_join_socket);
}