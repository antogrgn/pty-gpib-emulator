
#include "PTY_Interface.h"
#include <pty.h>
#include <iostream>
#include <unistd.h>
#include <boost/algorithm/string.hpp>
using namespace boost::algorithm;

Interface::Interface(Device *default_device,
		     int default_address) {
  char name[40];
  
  this->addr = default_address;
  this->addDevice(default_device, default_address);

  if (openpty(&this->m, &this->s, name, NULL, NULL) < 0)
    std::cerr << "Could not open pty device" << std::endl;
  else {
    this->pname = name;
    this->running = false;
  }
}

Interface::~Interface() {
  close(this->m);
}

string Interface::printFilename() {
  std::cout << this->pname << std::endl;
  return this->pname;
}

void Interface::run(int readLen) {
  char *tty_in = new char[readLen+1];
  string tty_out;

  this->running = true;
  while (this->running) {
    read(this->m, tty_in, readLen);
    tty_out = this->handleInput(tty_in);
    write(this->m, tty_out.c_str(), tty_out.length());
  }

  delete[] tty_in;
}

string Interface::handleInput(string tty_in) {
  string out = "";
  trim(tty_in);
  Device *dev;
  vector<string> cmd;
  vector<string> p;
  string first;
  int i;

  if (tty_in != "" && this->devices.count(this->addr) > 0) {
    dev = this->devices.at(this->addr);
    boost::split(cmd, tty_in, boost::is_any_of(";"));
    for (i=0;i<cmd.size();i++) {
      boost::split(p, cmd.at(i), boost::is_any_of(" "));
      first = p.at(0);
      p.erase(p.begin());
      out += dev->handleCMD(this, first, &p) + "\n";
    }
  }

  return out;
}

void Interface::addDevice(Device *dev, int addr) {
  this->devices.insert( std::pair<int, Device*>(addr, dev));
}

