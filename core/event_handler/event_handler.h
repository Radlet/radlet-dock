#ifndef INCLUDED_EVENT_HANDLER_H_
#define INCLUDED_EVENT_HANDLER_H_

#include <deque>
#include <mutex>
#include <thread>
#include <vector>

#include "boost/bind.hpp"
#include "boost/fiber/condition_variable.hpp"
#include "boost/thread.hpp"

#include "consts.h"

using namespace std;
namespace event {
class BaseEvent;
class EventHandler;
template <typename T> class Event;
} // namespace event

class event::BaseEvent {
public:
  // To be overloaded by derived class.
  virtual void execute() { std::cout << "wrong" << std::endl; }
};

template <typename Call> class event::Event : public event::BaseEvent {
  Call method_;

public:
  Event(const Call &method) : method_(method) {}

  void execute() { method_(); }
};

class event::EventHandler {
  std::vector<std::thread *> threads_;
  int running_thread_count_;
  bool service_up_;
  int allowed_thread_count_;
  boost::mutex generic_lock_;
  boost::mutex lock_for_tasks_[PRIORITY_COUNT];
  std::deque<BaseEvent *> tasks_[PRIORITY_COUNT];

public:
  EventHandler(const int &thread_count = 1)
      : allowed_thread_count_(thread_count), service_up_(1),
        running_thread_count_(0) {}
  virtual void AddTask();

  void PushEvent(BaseEvent *, const int &priority = PRIORITY_LOW);

  void Trigger();

  void Run();

  void ThreadEnded();

  ~EventHandler() {
    service_up_ = false;
    for (auto &thread_obj : threads_)
      thread_obj->join();
  }
};

#endif
