// Eden Yefet 204778294
// Bar Katz 208561357

#include "../include/AvailableGames.h"

// Static data members
static map<string, int> games_list;

// global
pthread_mutex_t available_get_list_mutex;
pthread_mutex_t available_add_mutex;
pthread_mutex_t available_remove_mutex;

vector<string> AvailableGames::getList() {
  pthread_mutex_lock(&available_get_list_mutex);
  vector<string> games_names;

  map<string, int>::iterator it;
  for (it = games_list.begin(); it != games_list.end(); ++it) {
    games_names.push_back(it->first);
  }

  pthread_mutex_unlock(&available_get_list_mutex);
  return games_names;
}

void AvailableGames::add(string game_name, int player_socket) {
  pthread_mutex_lock(&available_add_mutex);

  if(games_list.find(game_name) == games_list.end()) {

    games_list.insert(pair<string, int>(game_name, player_socket));
  }

  pthread_mutex_unlock(&available_add_mutex);
}

bool AvailableGames::exists(string game_name) {

  return !(games_list.find(game_name) == games_list.end());
}

int AvailableGames::remove(string game_name) {
  pthread_mutex_lock(&available_remove_mutex);
  map<string, int>::iterator game = games_list.find(game_name);

  int player_socket = -1;

  if(game != games_list.end()) {
    player_socket = game->second;
    games_list.erase(game_name);
  }

  pthread_mutex_unlock(&available_remove_mutex);
  return player_socket;
}
