// Eden Yefet 204778294
// Bar Katz 208561357

#include "../include/RemotePlayer.h"

RemotePlayer::RemotePlayer(const char *server_ip,
                           int server_port,
                           Display *display) {
  strcpy(this->server_ip, server_ip);
  this->server_port = server_port;
  this->client_socket = 0;
  this->display = display;
  this->type = REMOTE;
}

Coordinate RemotePlayer::playOneTurn(Board &board_copy,
                                     char *message,
                                     vector<Move> &available_moves) {
  int chosen_row;
  int chosen_column;
  ssize_t n = 0;

  char previous_msg[7];
  strcpy(previous_msg, message);

  if (strcmp(message, "") != 0) {
    // Writes an empty move to the server
    n = write(client_socket, message, sizeof(message));
    if (n == -1 || strcmp(message, "End") == 0) {
      return Coordinate(-1, -1);
    }
  }

  cout << "Waiting for other player to make a move..." << endl;

  // Reads rival's move from server
  n = read(client_socket, message, sizeof(message));
  if (n == -1) {
    return Coordinate(-1, -1);
  }

  if (strcmp(message, "discon") == 0) {
    cerr << "Disconnected from server." << endl;
    exit(1);
  }

  if (strcmp(message, "NoMove") == 0) {
    if (strcmp(previous_msg, "NoMove") == 0) {
      strcpy(message, "END");
      n = write(client_socket, message, sizeof(message));
      if (n == -1) {
        throw ERR_CANT_WRITE_TO_SERVER;
      }
    }
    return Coordinate(-1, -1);
  } else {
    chosen_row = atoi(strtok(message, ","));
    chosen_column = atoi(strtok(NULL, ","));
  }

  return Coordinate(chosen_row, chosen_column);
}

char RemotePlayer::getSign() const {
  return this->sign;
}

void RemotePlayer::setSign(char sign) {
  this->sign = sign;
}

void RemotePlayer::connectToServer() {

  // Creates a socket point
  client_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (client_socket == -1) {
    throw ERR_CANT_OPEN_SOCKET;
  }

  // Converts the ip string to a network address
  struct in_addr address;
  if (!inet_aton(server_ip, &address)) {
    throw ERR_CANT_PARSE_IP_ADD;
  }

  // Gets a hostent structure for the given host address
  struct hostent *server;
  server = gethostbyaddr((const void *) &address, sizeof address, AF_INET);
  if (server == NULL) {
    throw ERR_UNREACHABLE_HOST;
  }

  // Creates a structure for the server address
  struct sockaddr_in server_address;
  bzero((char *) &address, sizeof(address));
  server_address.sin_family = AF_INET;
  memcpy((char *) &server_address.sin_addr.s_addr, server->h_addr,
         static_cast<size_t>(server->h_length));

  // Converts values between host and network byte  orders
  server_address.sin_port = htons(static_cast<uint16_t>(server_port));

  // Establishes a connection with the TCP server
  if (connect(client_socket, (struct sockaddr *) &server_address, sizeof
  (server_address)) == -1) {
    throw ERR_CANT_CONNECT_TO_SERVER;
  }
}

void RemotePlayer::sendToServer(char *msg) {
  ssize_t n = 0;
  n = write(client_socket, msg, sizeof(msg) + 2);
  if (n == -1) {
    throw ERR_CANT_WRITE_TO_SERVER;
  }
}

void RemotePlayer::postCommand() {
  // Gets color from server
  int color_by_number;
  ssize_t n = read(client_socket, &color_by_number, sizeof(color_by_number));
  if (n == -1) {
    throw ERR_CANT_READ_FROM_SERVER;
  }

  if (color_by_number == 0) {
    setSign(WHITE);
  } else if (color_by_number == 1) {
    setSign(BLACK);
  } else {
    cerr << "Disconnected from server." << endl;
    exit(1);
  }
}

void RemotePlayer::startANewRoom() {
  char msg[62];
  string game_name;
  ostringstream os;
  bool is_valid;
  bool first_try = true;

  display->print(cout << "Please enter a new game room name:" << endl);

  do {
    cin >> game_name;
    std::cin.clear();
    std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (first_try) {
      first_try = false;
      os << "start " << game_name;
      strcpy(msg, os.str().c_str());
    } else {
      strcpy(msg, game_name.c_str());
    }

    // Sends START command
    sendToServer(msg);

    is_valid = isCommandValid();
    if (!is_valid != 0) {
      display->print(cout << "Game room name \"" << game_name << "\" is already"
          " taken.\nPlease enter another name:" << endl);
    }
  } while (!is_valid);

  display->print(cout << "Waiting for another player to join..." << endl);

  postCommand();

}

void RemotePlayer::joinAnExistingRoom() {
  char msg[62];
  string game_name;
  ostringstream os;
  bool is_valid;
  bool first_try = true;

  display->print(cout << "Please enter an existing game room name:" << endl);

  do {
    cin >> game_name;
    std::cin.clear();
    std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (first_try) {
      os << "join " << game_name;
      first_try = false;
      strcpy(msg, os.str().c_str());
    } else {
      strcpy(msg, game_name.c_str());
    }

    // Sends JOIN command
    sendToServer(msg);

    is_valid = isCommandValid();
    if (!is_valid) {
      display->print(cout << "Game room name \"" << game_name << "\" does not"
          " exist.\nPlease enter an existing game room name:" << endl);
    }
  } while (!is_valid);

  postCommand();

}

bool RemotePlayer::isCommandValid() {
  int is_valid;

  ssize_t n = read(client_socket, &is_valid, sizeof(is_valid));
  if (n == -1) {
    throw ERR_CANT_READ_FROM_SERVER;
  }

  return is_valid == 0;
}

void RemotePlayer::showAvailableRooms() {

  char msg[62];
  strcpy(msg, "list_games");
  sendToServer(msg);

  vector<string> available_games;
  long size = 0;
  read(client_socket, &size, sizeof(size));
  size = ntohl(static_cast<uint32_t>(size));

  for (int i = 0; i < size; ++i) {
    string game_room_name;
    long length = 0;

    read(client_socket, &length, sizeof(length));
    length = ntohl(static_cast<uint32_t>(length));

    while (0 < length) {
      char buffer[1024];
      ssize_t cread;
      cread = read(client_socket,
                   buffer,
                   min(static_cast<const size_t &>(sizeof(buffer)),
                       static_cast<const size_t &>(length)));
      game_room_name.append(buffer, static_cast<unsigned long>(cread));
      length -= cread;
    }

    available_games.push_back(game_room_name);
  }
  // Prints available games
  if (available_games.empty()) {
    this->display->print(cout << "No available games to join" << endl);
  } else {
    this->display->print(cout << "Available games to join:" << endl);
    for (vector<string>::iterator it = available_games.begin();
         it != available_games.end(); it++) {
      this->display->print(cout << *it << endl);
    }
    this->display->print(cout << endl);
  }

}

void RemotePlayer::endGame() {
  char message[7];
  strcpy(message, "NoMove");
  ssize_t n;
  n = write(client_socket, message, sizeof(message));
  if (n == -1) {
    throw ERR_CANT_WRITE_TO_SERVER;
  }
  n = write(client_socket, message, sizeof(message));
  if (n == -1) {
    throw ERR_CANT_WRITE_TO_SERVER;
  }
}

void RemotePlayer::closeSocket() {
  char msg[62];
  strcpy(msg, "close");
  sendToServer(msg);
}

void RemotePlayer::closeOtherSocket() {
  char msg[62];
  string game_name;
  ostringstream os;
  bool is_valid;

  display->print(cout << "Please enter an existing game room name to close:" <<
                      endl);

  cin >> game_name;
  std::cin.clear();
  std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
  os << "close " << game_name;
  strcpy(msg, os.str().c_str());

  // Sends CLOSE command
  sendToServer(msg);

  is_valid = isCommandValid();
  if (!is_valid) {
    display->print(cout << "Game room name \"" << game_name << "\" does not"
        " exist." << endl);
  } else {
    display->print(cout << "Game room name \"" << game_name << "\" was "
        "successfully closed" << endl);
  }
}
