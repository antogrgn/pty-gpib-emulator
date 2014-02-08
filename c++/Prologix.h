

#ifndef PROLOGIX
#define PROLOGIX

#include "Device.h"
#include <map>
#include "PTY_Interface.h"
#include <vector>
#include <string>
using namespace std;


class Prologix_GPIB_USB : public Device {
 public:
  typedef string (Prologix_GPIB_USB::*handler)(Interface *fpl,
					       vector<string> *args);
  map<string, handler> cmds;
  
  Prologix_GPIB_USB();
  ~Prologix_GPIB_USB();

  string handleCMD(Interface *fpl, string cmd, vector<string> *args);
  string version(Interface *fpl, vector<string> *args);
  string addr(Interface *fpl, vector<string> *args);
  string kill(Interface *fpl, vector<string> *args);

  void addCMD(const char *cmd, handler h);
  void addCMD(string cmd, handler h);
};


#endif
