// Eden Yefet 204778294
// Bar Katz 208561357

#include "../include/CloseCommand.h"
#include "../include/CommandManager.h"
#include "../include/ListGamesCommand.h"
#include "../include/JoinCommand.h"

CommandManager::CommandManager(Server &server) {
  commands_list.insert(pair<string, Command *>("start",
                                               new StartCommand(server)));
  commands_list.insert(pair<string, Command *>("list_games",
                                               new ListGamesCommand(server)));
  commands_list.insert(pair<string, Command *>("join",
                                               new JoinCommand(server)));
  commands_list.insert(pair<string, Command *>("close",
                                               new CloseCommand(server)));
}

CommandManager::~CommandManager() {
  map<string, Command *>::iterator it;
  for (it = commands_list.begin(); it != commands_list.end(); ++it) {
    delete it->second;
  }
}

void CommandManager::executeCommand(char *command_name, vector<string> args,
                                    int player_socket) {

  commands_list.find(command_name)->second->execute(args, player_socket);
}
