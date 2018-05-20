// Eden Yefet 204778294
// Bar Katz 208561357

#include "../include/RunningGames.h"
#include "../include/Server.h"
#include "../include/CommandManager.h"
#include "../include/AvailableGames.h"

using namespace std;

#define MAX_CONNECTED_CLIENTS 2

Server::Server(int port) : port(port), server_socket(0) {
  cm = new CommandManager(*this);
}

Server::~Server() {
  delete (cm);
}

void Server::start() {

  // Create a socket point
  server_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (server_socket == -1) {
    throw "Error opening socket";
  }

  // Reuse port even if not freed
  int enable = 1;
  if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)
  ) < 0) {
    perror("setsockopt(SO_REUSEADDR) failed");
  }

  // Assign a local address to the socket
  struct sockaddr_in server_address;
  bzero((void *) &server_address, sizeof(server_address));
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = INADDR_ANY;
  server_address.sin_port = htons(static_cast<uint16_t>(port));
  if (bind(server_socket,
           (struct sockaddr *) &server_address,
           sizeof(server_address)) == -1) {
    throw "Error on binding";
  }

  // Start listening to incoming connections
  listen(server_socket, MAX_CONNECTED_CLIENTS);

  pthread_t accept_client_thread_t;
  int accept_client_thread = pthread_create(&accept_client_thread_t, NULL,
                                            acceptClient, this);
  if (accept_client_thread) {
    throw "Error opening thread";
  }
  pthread_t shut_down_thread_t;
  int shut_down_thread = pthread_create(&shut_down_thread_t, NULL,
                                        shutDownServer, this);
  if (shut_down_thread) {
    throw "Error opening thread";
  }

  pthread_join(shut_down_thread_t, NULL);
  pthread_cancel(accept_client_thread_t);
  pthread_join(accept_client_thread_t, NULL);

}

bool Server::play(int client_socket, int rival_socket) {
  char msg[7];
  char dummy[7];

  ssize_t n = read(client_socket, msg, sizeof(msg));
  if (n == -1) {
    throw "Error reading from client";
  }
  n = read(client_socket, dummy, sizeof(dummy));
  if (n == -1) {
    return true;
  }

  n = write(rival_socket, msg, sizeof(msg));
  if (n == -1) {
    throw "Error writing to rival";
  }

  return strcmp(msg, "END") == 0;
}

void Server::run(string game_name,
                 int black_player_socket,
                 int white_player_socket) {

  ssize_t n;
  int status = NO_ERROR;

  if (black_player_socket == -1) {
    availableGame new_game = reEnterName_Join(white_player_socket);

    game_name = new_game.game_name;
    black_player_socket = new_game.player_socket;
  }

  RunningGames::add(game_name, black_player_socket, white_player_socket);

  // write joined game
  n = write(white_player_socket, &status, sizeof(status));
  if (n == -1) {
    throw "Error writing to client";
  }

  cout << "Client: " << white_player_socket << " has joined \"" << game_name
       << "\"" << endl << endl;
  cout << "Game \"" << game_name << "\" has began:\n"
      "   black player: " << black_player_socket << "\n"
           "   white player: " << white_player_socket << endl;

  cout << endl << "#Running games on server: "
       << RunningGames::getList().size() << endl;
  cout << endl << "-----------------------------------" << endl << endl;

  // give clients a color -- change according to client's command
  int color_by_number = 0;

  n = write(black_player_socket, &color_by_number, sizeof(color_by_number));
  if (n == -1) {
    throw "Error writing to client";
  }

  color_by_number = 1;

  n = write(white_player_socket, &color_by_number, sizeof(color_by_number));
  if (n == -1) {
    throw "Error writing to client";
  }

  bool is_game_ended = false;
  int client_socket = black_player_socket;
  int rival_socket = white_player_socket;
  int temp;

  while (!is_game_ended) {
    is_game_ended = play(client_socket, rival_socket);

    // Switches turns
    temp = rival_socket;
    rival_socket = client_socket;
    client_socket = temp;
  }

  RunningGames::remove(game_name);
  close(black_player_socket);
  close(white_player_socket);
}

availableGame Server::reEnterName_Join(int player_socket) {
  char new_game_name[51];
  ssize_t n;
  int status = ERROR;
  int new_player_socket;
  availableGame new_player_game;

  do {

    // write error
    n = write(player_socket, &status, sizeof(status));
    if (n == -1) {
      throw "Error writing to client";
    }

    // enter new game name
    n = read(player_socket, &new_game_name, sizeof(new_game_name));
    if (n == -1) {
      throw "Error writing to client";
    }

    new_player_socket = AvailableGames::remove(new_game_name);

  } while (new_player_socket == -1);

  strcpy(new_player_game.game_name, new_game_name);
  new_player_game.player_socket = new_player_socket;

  return new_player_game;
}

void *Server::acceptClient(void *args) {
  Server *server = reinterpret_cast<Server *>(args);
  cout << "-----------------------------------" << endl << endl;
  while (strcmp(server->shut, "exit") != 0) {
    // Defines the client socket's structures
    struct sockaddr_in player_address;
    socklen_t client_address_len;

    // Accepts client connection
    int player_socket = accept(server->server_socket,
                               (struct sockaddr *) &player_address,
                               &client_address_len);

    if (player_socket == -1) {
      throw "Error on accept";
    }

    cout << "Client: " << player_socket << " was accepted" << endl;
    cout << endl << "-----------------------------------" << endl << endl;

    // handle client -- create thread
    handleArgs handle_args;
    handle_args.command_manager = server->cm;
    handle_args.player_socket = player_socket;
    pthread_t handle_client_thread_t;
    int handle_client_thread = pthread_create(&handle_client_thread_t, NULL,
                                              handleClient,
                                              &handle_args);
    if (handle_client_thread) {
      throw "Error opening thread handle";
    }
    /* opened thread for new client handling -- threads responsibility to
     shut down*/
  }
}

void *Server::handleClient(void *args) {

  handleArgs *handle_args = (handleArgs *) args;
  int player_socket = handle_args->player_socket;

  ssize_t n;

  // read command from client
  char full_command[62];
  n = read(player_socket, &full_command, sizeof(full_command));
  if (n == -1) {
    throw "Error writing to client";
  }

  // cipher command name and arguments
  const char delimiter = ' ';
  char command_name[11];
  vector<string> arguments;
  strcpy(command_name, strtok(full_command, &delimiter));
  if (strcmp(command_name, "play") == 0) {
    int status = ERROR;

    // write error
    n = write(player_socket, &status, sizeof(status));
    if (n == -1) {
      throw "Error writing to client";
    }
    close(player_socket);
    return NULL;
  }
  char *s = strtok(NULL, &delimiter);
  if (s != NULL) {
    arguments.push_back(s);
  }

  // execute command
  handle_args->command_manager->executeCommand(command_name,
                                               arguments,
                                               player_socket);

}

void Server::createNewRoom(string room_name, int player_socket) {

  int status = NO_ERROR;
  char game_name[51];

  strcpy(game_name, room_name.c_str());

  if (AvailableGames::exists(room_name)
      || RunningGames::exists(room_name)) {
    reEnterName_Start(game_name, player_socket);

  }

  AvailableGames::add(game_name, player_socket);

  // write game opened
  ssize_t n = write(player_socket, &status, sizeof(status));
  if (n == -1) {
    throw "Error writing to client";
  }

  cout << "Client: " << player_socket << " has open game: " << room_name
       << endl;
  cout << endl << "#Available games on server: "
       << AvailableGames::getList().size() << endl;
  cout << endl << "-----------------------------------" << endl << endl;
}

void Server::reEnterName_Start(char *game_name, int player_socket) {
  char new_game_name[51];
  ssize_t n;
  int status = ERROR;

  do {

    // write error
    n = write(player_socket, &status, sizeof(status));
    if (n == -1) {
      throw "Error writing to client";
    }

    // enter new game name
    n = read(player_socket, &new_game_name, sizeof(new_game_name));
    if (n == -1) {
      throw "Error writing to client";
    }

  } while (AvailableGames::exists(new_game_name)
      || RunningGames::exists(new_game_name));

  strcpy(game_name, new_game_name);
}

void Server::getAvailableGames(int player_socket) {

  cout << "Client: " << player_socket << " requested the list of available "
      "games" << endl << endl;

  vector<string> available_games = AvailableGames::getList();

  long length = htonl(static_cast<uint32_t>(available_games.size()));

  ssize_t n;
  // Writes size of vector
  n = write(player_socket, &length, sizeof(length));
  if (n == -1) {
    throw "Error writing to client";
  }

  for (int i = 0; i < available_games.size(); i++) {
    length = htonl(static_cast<uint32_t>(available_games[i].length()));
    write(player_socket, &length, sizeof(length));
    write(player_socket,
          available_games[i].data(),
          available_games[i].length());
  }

  close(player_socket);
  cout << "Client: " << player_socket << " disconnected" << endl;
  cout << endl << "-----------------------------------" << endl << endl;
}

void *Server::shutDownServer(void *args) {
  Server *server = reinterpret_cast<Server *>(args);

  do {
    cin >> server->shut;
  } while (strcmp(server->shut, "exit") != 0);

  vector<string> available_games = AvailableGames::getList();
  vector<string> running_games = RunningGames::getList();

  cout << "Server shut down" << endl << endl;

  for (int i = 0; i < available_games.size(); i++) {
    server->closeRoom(available_games[i]);
  }
  for (int i = 0; i < running_games.size(); i++) {
    server->closeRoom(running_games[i]);
  }

  close(server->server_socket);

  return NULL;
}

void Server::closeRoom(string room_name, int player_socket) {
  if (room_name.compare("") != 0) {

    if (player_socket != -1) {
      cout << "Client: " << player_socket << " Closed game: " << room_name
           << endl << endl;
    }
    cout << "Disconnecting all players in game \"" << room_name << "\": "
         << endl;
    if (AvailableGames::exists(room_name)) {
      int game_player_socket = AvailableGames::remove(room_name);

      char disconnected[7] = DISCONNECTED_MESSAGE;

      ssize_t n = write(game_player_socket, disconnected, sizeof(disconnected));
      if (n == -1) {
        throw "Error writing to client";
      }

      close(game_player_socket);
      cout << "   Client: " << game_player_socket << " disconnected" << endl;

    } else if (RunningGames::exists(room_name)) {
      vector<int> players_sockets = RunningGames::remove(room_name);
      char disconnected[7] = DISCONNECTED_MESSAGE;
      ssize_t n;

      for (int i = 0; i < players_sockets.size(); i++) {
        n = write(players_sockets[i], disconnected, sizeof(disconnected));
        if (n == -1) {
          throw "Error writing to client";
        }

        close(players_sockets[i]);
        cout << "   Client: " << players_sockets[i] << " disconnected" << endl;
      }
    }
  }

  if (player_socket != -1) {
    close(player_socket);
    cout << "Client: " << player_socket << " disconnected" << endl;
  }
  cout << endl << "-----------------------------------" << endl << endl;
}


