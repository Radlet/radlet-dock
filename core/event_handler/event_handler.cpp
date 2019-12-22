#include <iostream>

#include <boost/thread/thread.hpp>

#include "event_handler.h"

using namespace std;
using namespace event;

void EventHandler::PushEvent(BaseEvent *ptr, const int &priority) {
  // Method signature to be modified.
  {
    unique_lock<boost::mutex> lock(lock_for_tasks_[priority]);
    tasks_[priority].push_back(ptr);
  }

  Trigger();
}

void EventHandler::AddTask() { cout << "This should be overloaded..."; }

void EventHandler::Trigger() {
  if (running_thread_count_ < allowed_thread_count_) {
    {
      std::unique_lock<boost::mutex> lock(generic_lock_);
      ++running_thread_count_;
      lock.unlock();
    }
    threads_.push_back(
        new std::thread(std::bind(&event::EventHandler::Run, this)));
  }
}

void EventHandler::Run() {
  while (service_up_) {
    for (int priority = PRIORITY_HIGH; priority >= PRIORITY_LOW; priority--) {

      std::unique_lock<boost::mutex> lock(lock_for_tasks_[priority]);
      if (tasks_[priority].empty())
        continue;

      event::BaseEvent *task = (tasks_[priority].front());
      tasks_[priority].pop_front();
      lock.unlock();
      task->execute();
      break;
    }
  }

  ThreadEnded();
}

void EventHandler::ThreadEnded() {
  std::unique_lock<boost::mutex> lock(generic_lock_);
  --running_thread_count_;
}

