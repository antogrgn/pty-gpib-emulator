

#include "Prologix.h"
#include <string>
#include <cstdlib>
#include <iostream>


Prologix_GPIB_USB::Prologix_GPIB_USB() {
  this->addCMD("++ver", &Prologix_GPIB_USB::version);
  this->addCMD("++addr", &Prologix_GPIB_USB::addr);
  this->addCMD("++kill", &Prologix_GPIB_USB::kill); 
}

Prologix_GPIB_USB::~Prologix_GPIB_USB() {

}

string Prologix_GPIB_USB::handleCMD(Interface *fpl,
				    string cmd,
				    vector<string> *args) {
  string out = "";
  handler h;

  if (out != "") {
    return out;
  } else if ( this->cmds.count(cmd) > 0 ) {
    h = this->cmds.at(cmd);
    return (this->*h)(fpl, args);
  }

  return "";
}

string Prologix_GPIB_USB::version(Interface *fpl,
				  vector<string> *args) {
  return "Prologix Version 1.1 Simulator (C++)";
}

string Prologix_GPIB_USB::addr(Interface *fpl,
			       vector<string> *args) {
  if (args == NULL || args->size() == 0) {
    return std::to_string(fpl->addr);
  } else {
    fpl->addr = atoi(args->at(0).c_str());
    if ( fpl->devices.count(fpl->addr) == 0 )
      fpl->addDevice(this, fpl->addr);
    return "";
  }
}

string Prologix_GPIB_USB::kill(Interface *fpl,
			       vector<string> *args) {
  fpl->running = false;
  return "";
}


void Prologix_GPIB_USB::addCMD(const char *cmd, handler h) {
  this->cmds.insert( std::pair<string, handler>(cmd, h) );
}

void Prologix_GPIB_USB::addCMD(string cmd, handler h) {
  this->cmds.insert( std::pair<string, handler>(cmd, h) );
}

