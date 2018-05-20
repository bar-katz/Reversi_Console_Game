// Eden Yefet 204778294
// Bar Katz 208561357

#ifndef EX02_REMOTEPLAYER_H
#define EX02_REMOTEPLAYER_H

#include "Player.h"
#include "Board.h"
#include <iostream>
#include <string>
#include <limits>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <cstdlib>
#include <unistd.h>
#include <sstream>
#include "../include/custom_strings.h"

class RemotePlayer : public Player {
 private:
  int client_socket;
  int server_port;
  char server_ip[20];
  Display *display;

 public:
  RemotePlayer(const char *server_ip, int server_port, Display *display);
  void connectToServer();
  void postCommand();
  Coordinate playOneTurn(Board &board_copy,
                         char *message,
                         vector<Move> &available_moves);
  void sendToServer(char msg[62]);
  void setSign(char sign);
  char getSign() const;

  /**
   * Asks the player to choose a new game room name, sends the command to the
   * server and reads back a message, letting the player know if the name is
   * taken. If the name is taken, the player will be asked to enter a new
   * name. Otherwise, a new game room with the name specified will be created.
   */
  void startANewRoom();

  /**
   * Asks the player to enter an existing game room name, sends the command to
   * the server and reads back a message, letting the player know if the game
   * room exists. If the game room doesn't exist, the player will be asked to
   * enter a new name. Otherwise, the player will be joined to the room and
   * the game will start.
   */
  void joinAnExistingRoom();

  void showAvailableRooms();

  bool isCommandValid();
  void endGame();
  void closeSocket();
  void closeOtherSocket();
};

#endif //EX02_REMOTEPLAYER_H
