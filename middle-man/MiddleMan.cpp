
#include "MiddleMan.h"
#include <iostream>
#include <unistd.h>
#include <pty.h>
#include <termios.h>

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

MiddleMan::MiddleMan(const string iotty_name) {
  char name[40];
  
  if (openpty(&this->mPTY, &this->sPTY, name, NULL, NULL) < 0)
    std::cerr << "Could not open pty device" << std::endl;
  else {
    set_noecho(this->sPTY);
    this->ptyname = name;
    this->running = false;
  }
}

MiddleMan::~MiddleMan() {
  close(this->mPTY);
}

string MiddleMan::getPTY() {
  return this->ptyname;
}

void MiddleMan::run(int readLen) {
  char *tty_in = new char[readLen+1];
  string tty_full;
  int i=0;

  this->running = true;
  while (this->running) {
    tty_full = "";
    while ((i=read(this->mPTY, tty_in, readLen)) >= readLen) {
      tty_in[i] = '\0';
      tty_full += tty_in;
    }
    tty_in[i] = '\0';
    tty_full += tty_in;

    this->handleInput(tty_full);
  }

  delete[] tty_in;
}

void MiddleMan::handleInput(string tty_in) {
  std::cout << tty_in << std::endl;
}


