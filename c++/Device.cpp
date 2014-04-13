
#include "Device.h"
#include <string>
#include <iostream>


string Device::handleCMD(Interface *fpl,
			 string cmd,
			 vector<string> *args) {
  std::cout << "$$ Device: " << cmd << std::endl;
  
  return "";
}
