
#include "PTY_Interface.h"
#include <pty.h>
#include <iostream>
#include <unistd.h>

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
  
}

string Interface::handleInput(string tty_in) {
  return "Hello";
}

void Interface::addDevice(Device *dev, int addr) {

}

