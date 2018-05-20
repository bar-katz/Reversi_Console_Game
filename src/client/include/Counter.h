// Eden Yefet 204778294
// Bar Katz 208561357

#ifndef EX02_COUNTER_H
#define EX02_COUNTER_H

class Counter {
 private:
  int count;

 public:
  Counter();
  Counter(int initial_count);

  void increase();
  void increase(int value);
  void decrease(int value);
  void decrease();
  int getCount() const;
};

#endif //EX02_COUNTER_H
