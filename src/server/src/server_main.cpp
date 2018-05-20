// Eden Yefet 204778294
// Bar Katz 208561357

#include <cstdlib>
#include <fstream>
#include "../include/Server.h"

int main() {

  // Reads IP from file
  ifstream config("config.txt");
  string line;
  getline(config, line);
  getline(config, line);
  Server s = Server(atoi(line.c_str()));

  try {
    s.start();

  } catch (const char *msg) {
    cout << "Couldn't start server. Reason: " << msg << endl;
    exit(1);
  }
}
