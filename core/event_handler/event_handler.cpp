#include <iostream>

#include <boost/thread/thread.hpp>

#include "event_handler.h"

using namespace std;
using namespace event;

void EventHandler::PushEvent(const BaseEvent* ptr, const int& priority) {
  // Method signature to be modified.
  {
    unique_lock<boost::mutex> lock(lock_for_tasks_[priority]);
    tasks_[priority].push_back(ptr);
  }

  Trigger();
}

void EventHandler::AddTask() {
  cout <<"This should be overloaded...";
}
