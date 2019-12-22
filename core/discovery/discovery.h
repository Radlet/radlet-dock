#include <string>
#include "../event_handler/event_handler.h"

using namespace std;
namespace discovery {
  class Device;
}

class discovery::Device : public event::EventHandler {
  public:
  void AddTask(const string &operation_type, const string &arg) ;

  void Add(const string &arg);

  void SearchDevices(const string &arg);

  void RemoveDevice(const string &arg);

  void ListDevices(const string &arg);

  void GetDevice(const string &arg);

  void Notify(const string &arg);

};
