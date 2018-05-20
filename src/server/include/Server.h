// Eden Yefet 204778294
// Bar Katz 208561357

#ifndef EX02_SERVER_H
#define EX02_SERVER_H

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <cstdio>
#include <vector>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <map>

#define NO_ERROR 0
#define ERROR 1

#define DISCONNECTED_MESSAGE "discon"

using namespace std;
class CommandManager;
struct availableGame;

class Server {
 private:
  char shut[10];
  int port;
  int server_socket;
  CommandManager *cm;

  bool play(int client_socket, int rival_socket);
  availableGame reEnterName_Join(int player_socket);
  void reEnterName_Start(char *game_name, int player_socket);
  static void *handleClient(void *args);

 public:
  Server(int port);
  ~Server();
  void start();
  static void *acceptClient(void *args);

  void createNewRoom(string room_name, int player_socket);
  void getAvailableGames(int player_socket);
  void run(string game_name, int black_player_socket, int white_player_socket);
  void closeRoom(string room_name, int player_socket = -1);

  static void *shutDownServer(void *args);

};

struct availableGame {
  char game_name[51];
  int player_socket;
};

struct handleArgs {
  CommandManager *command_manager;
  int player_socket;
};

#endif //EX02_SERVER_H

