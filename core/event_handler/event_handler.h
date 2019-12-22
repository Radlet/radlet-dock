#ifndef INCLUDED_EVENT_HANDLER_H_
#define INCLUDED_EVENT_HANDLER_H_

#include <deque>
#include <mutex>

#include "boost/bind.hpp"
#include "boost/fiber/condition_variable.hpp"
#include "boost/thread.hpp"

#include "consts.h"

namespace event {
  class BaseEvent;
  class EventHandler;
  template<typename T>
  class Event;
}
class event::BaseEvent {
  public:

  // To be overloaded by derived class.
  virtual void execute() {}
};
template<typename Call>
class event::Event: public event::BaseEvent {
  Call method_;
public:
  Event(const Call &method):method_(method) {    
  }

  void execute() {
    method_();
  }
};

class event::EventHandler {
  int running_thread_count_;
  int allowed_thread_count_;
  boost::mutex generic_lock_;
  boost::mutex lock_for_tasks_[PRIORITY_COUNT];
  std::deque<const BaseEvent*> tasks_[PRIORITY_COUNT];

public:
  EventHandler(const int &thread_count=1): allowed_thread_count_(thread_count) {}
  virtual void AddTask();

  void PushEvent(const BaseEvent*, const int &priority=PRIORITY_LOW);

  void Trigger() {
    if (running_thread_count_ < allowed_thread_count_) {
     {
      std::unique_lock<boost::mutex> lock(generic_lock_);
      ++running_thread_count_;
     }
      new boost::thread(boost::bind(&event::EventHandler::Run, this));
    }
  }

  void Run() {

    while (true) {
      for (int priority = PRIORITY_HIGH;
             priority >= PRIORITY_LOW; priority--) {

        std::unique_lock<boost::mutex> lock(lock_for_tasks_[priority]);
        if(tasks_[priority].empty())
          continue;
  
        auto task = *(tasks_[priority].front());
        tasks_[priority].pop_front();
        lock.unlock();
        task.execute();
        break;
      }
    }

    ThreadEnded();
  }

  void ThreadEnded() {
    std::unique_lock<boost::mutex> lock(generic_lock_);
    --running_thread_count_;
  }
};

#endif
