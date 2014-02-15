
#include "PTY_Interface.h"
#include <pty.h>
#include <iostream>
#include <unistd.h>
#include <boost/algorithm/string.hpp>
#include <termios.h>
using namespace boost::algorithm;

static void set_noecho(int fd) { // Turn off Slave echo
  struct termios stermios;

  if (tcgetattr(fd, &stermios) < 0)
    std::cout << "Error tcgetattr()" << std::endl;

  stermios.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL);
  stermios.c_oflag &= ~(ONLCR);
  /* also turn off NL to CR/NL mapping on output */

  if (tcsetattr(fd, TCSANOW, &stermios) < 0)
    std::cout << "Error tcsetattr()" << std::endl;
}

Interface::Interface(Device *default_device,
		     int default_address) {
  char name[40];
  
  this->addr = default_address;
  this->addDevice(default_device, default_address);

  if (openpty(&this->m, &this->s, name, NULL, NULL) < 0)
    std::cerr << "Could not open pty device" << std::endl;
  else {
    set_noecho(this->s);
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
  vector<string> tty_out;
  string tty_full;
  int i;

  this->running = true;
  while (this->running) {
    tty_full = "";
    while (read(this->m, tty_in, readLen) >= readLen) {
      std::cout << tty_in << std::endl;
      tty_full += tty_in;
    }
    tty_full += tty_in;
    i = tty_full.find("\n");
    if ( i != string::npos )
      tty_full = tty_full.substr(0, i);

    tty_out = this->handleInput(tty_full);
    for (std::vector<string>::iterator it = tty_out.begin();
	 it != tty_out.end();
	 it++) {
      write(this->m, it->c_str(), it->length());
    }
  }

  delete[] tty_in;
}

vector<string> Interface::handleInput(string tty_in) {
  vector<string> out;
  Device *dev = NULL;
  vector<string> cmd;
  vector<string> p;
  string first;
  int i;

  trim(tty_in);
  if (tty_in != "" && this->devices.count(this->addr) > 0) {
    dev = this->devices.at(this->addr);
    if (dev == NULL) {
      out.push_back("ERROR! No Device at address: " +
		    to_string(this->addr));
    }

    boost::split(cmd, tty_in, boost::is_any_of(";\n"));
    for (i=0;i<cmd.size();i++) {
      boost::split(p, cmd.at(i), boost::is_any_of(" "));
      first = p.at(0);
      p.erase(p.begin());
      out.push_back(dev->handleCMD(this, first, &p) + "\n");
    }
  }

  out.push_back("");
  return out;
}

void Interface::addDevice(Device *dev, int addr) {
  this->devices.insert( std::pair<int, Device*>(addr, dev));
}

