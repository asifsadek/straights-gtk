#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>

class Observer;

class Subject {
 public:
  virtual ~Subject() = 0;
  void addObserver(Observer *);

 protected:
  void notify();

 private:
  std::vector<Observer *> observers_;
};

#endif
