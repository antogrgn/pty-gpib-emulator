
#ifndef DEVICE
#define DEVICE

#include <string>
#include <iostream>

class Device;

#include "PTY_Interface.h"
#include <vector>
using namespace std;

class Device {
 public:
  virtual string handleCMD(Interface *fpl,
			   string cmd,
			   vector<string> *args) {
    return "";
  } /**/
};

#endif
