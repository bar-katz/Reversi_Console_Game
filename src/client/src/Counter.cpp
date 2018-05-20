// Eden Yefet 204778294
// Bar Katz 208561357

#include "../include/Counter.h"

int Counter::getCount() const {
  return count;
}

Counter::Counter() {
  this->count = 0;
}

Counter::Counter(int initial_count) {
  this->count = initial_count;
}

void Counter::increase() {
  this->count++;
}

void Counter::increase(int value) {
  this->count += value;
}

void Counter::decrease(int value) {
  this->count -= value;
}

void Counter::decrease() {
  this->count--;
}
