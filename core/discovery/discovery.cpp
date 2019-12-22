#include "discovery.h"
#include "../event_handler/event_handler.h"

#include <functional>

using namespace event;
using namespace std;
using namespace std::placeholders;
using namespace discovery;

void Device::AddTask(const string &operation_type, const string &arg) {
  // Executing from main thread to be consumed for discovery service.

  if (operation_type == "Add") {
    PushEvent(new Event(bind(&Device::Add, this, arg)));
    return;
  }
/*
  if (operation_type == "Search") {
    PushEvent(bind(&Device::SearchDevices, this, arg));
    return;
  }

  if (operation_type == "Remove") {
    PushEvent(bind(&Device::RemoveDevice, this, arg));
    return;
  }

  if (operation_type == "List") {
    PushEvent(bind(&Device::ListDevices, this, arg));
    return;
  }

  if (operation_type == "Get") {
    PushEvent(bind(&Device::GetDevice, this, arg));
    return;
  }
*/
}

// #TODO: Implement Logic
void Device::Add(const string &arg) {
  // Perform addition operation.
  Notify("Addition Started");
  cout << "Test add.";

}

void Device::SearchDevices(const string &arg) {
}

void Device::RemoveDevice(const string &arg) {
}

void Device::ListDevices(const string &arg) {
}

void Device::GetDevice(const string &arg) {
}

void Device::Notify(const string &arg) {
  cout << arg <<"\n";
}
