

#ifndef PTY_INTERFACE
#define PTY_INTERFACE

#include <string>
#include <map>

class Interface;

#include "Device.h"
using namespace std;

class Interface {
 public:
  map<int, Device*> devices;
  int addr, m, s;
  bool running;
  string pname;

  Interface(Device *default_device=NULL,
	    int default_address=0);
  ~Interface();

  string printFilename();
  void run(int readLen=100);

  string handleInput(string tty_in);
  void addDevice(Device *dev, int addr);

};



#endif
