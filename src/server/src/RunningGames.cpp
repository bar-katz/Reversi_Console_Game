// Eden Yefet 204778294
// Bar Katz 208561357

#include "../include/RunningGames.h"

// Static data members
static map<string, vector<int> > games_list;

// global
pthread_mutex_t running_get_list_mutex;
pthread_mutex_t running_add_mutex;
pthread_mutex_t running_remove_mutex;

vector<string> RunningGames::getList() {
  pthread_mutex_lock(&running_get_list_mutex);
  vector<string> games_names;

  map<string, vector<int> >::iterator it;
  for (it = games_list.begin(); it != games_list.end(); ++it) {
    games_names.push_back(it->first);
  }

  pthread_mutex_unlock(&running_get_list_mutex);
  return games_names;
}

void RunningGames::add(string game_name,
                       int player1_socket,
                       int player2_socket) {
  pthread_mutex_lock(&running_add_mutex);

  if (games_list.find(game_name) == games_list.end()) {
    vector<int> players;
    players.push_back(player1_socket);
    players.push_back(player2_socket);

    games_list.insert(pair<string, vector<int> >(game_name, players));
  }

  pthread_mutex_unlock(&running_add_mutex);
}

bool RunningGames::exists(string game_name) {
  return !(games_list.find(game_name) == games_list.end());
}

vector<int> RunningGames::remove(string game_name) {
  pthread_mutex_lock(&running_remove_mutex);
  vector<int> players_sockets = games_list.find(game_name)->second;

  games_list.erase(game_name);

  pthread_mutex_unlock(&running_remove_mutex);
  return players_sockets;
}
