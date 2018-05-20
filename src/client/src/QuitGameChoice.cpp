//
// Created by Eden Yefet
//

#include "../include/QuitGameChoice.h"

string QuitGameChoice::getTitle() {
  return "Quit";
}

kMenuVal QuitGameChoice::execute() {
  return kQuit;
}

QuitGameChoice::~QuitGameChoice() {

}

QuitGameChoice::QuitGameChoice() {

}
