#include "discovery.h"
#include "../event_handler/event_handler.h"

#include <fstream>
#include <functional>

using namespace event;
using namespace std;
using namespace std::placeholders;
using namespace discovery;

void Device::AddTask(const string &operation_type, const string &arg) {
  // Executing from main thread to be consumed for discovery service.

  if (operation_type == "Add") {
    BaseEvent *B = new Event(bind(&Device::Add, this, arg));
    PushEvent(B);
    return;
  }

  if (operation_type == "Search") {
    BaseEvent *B = new Event(bind(&Device::SearchDevices, this, arg));
    PushEvent(B);
    return;
  }

  if (operation_type == "Remove") {
    BaseEvent *B = new Event(bind(&Device::RemoveDevice, this, arg));
    PushEvent(B);
    return;
  }

  if (operation_type == "List") {
    BaseEvent *B = new Event(bind(&Device::ListDevices, this, arg));
    PushEvent(B);
    return;
  }

  if (operation_type == "Get") {
    BaseEvent *B = new Event(bind(&Device::GetDevice, this, arg));
    PushEvent(B);
    return;
  }
}

// #TODO: Implement Logic
void Device::Add(const string &arg) {
  // Perform addition operation.
  Notify("Addition Started");
  fstream fs("filex.txt", ios::out);
  fs << "done";
  fs.close();
}

void Device::SearchDevices(const string &arg) {}

void Device::RemoveDevice(const string &arg) {}

void Device::ListDevices(const string &arg) {}

void Device::GetDevice(const string &arg) {}

void Device::Notify(const string &arg) { cout << arg << "\n"; }
