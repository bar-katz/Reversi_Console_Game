// Eden Yefet 204778294
// Bar Katz 208561357

#include "../include/ListGamesCommand.h"

#include "../include/Server.h"

ListGamesCommand::ListGamesCommand(Server &s) : server(s) {}

void ListGamesCommand::execute(vector<string> args, int player_socket) {
  server.getAvailableGames(player_socket);
}