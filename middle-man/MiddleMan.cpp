
#include "MiddleMan.h"
#include <iostream>
#include <unistd.h>
#include <pty.h>
#include <termios.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

static void setPort(int fd) {
  /* *** Configure Port *** */
  struct termios tty;
  memset (&tty, 0, sizeof tty);

  /* Error Handling */
  if ( tcgetattr ( fd, &tty ) != 0 ) {
    std::cout << "Error tcgetattr()" << std::endl;
  }

  /* Set Baud Rate */
  cfsetospeed (&tty, B9600);
  cfsetispeed (&tty, B9600);

  /* Setting other Port Stuff */
  tty.c_cflag     &=  ~PARENB;        // Make 8n1
  tty.c_cflag     &=  ~CSTOPB;
  tty.c_cflag     &=  ~CSIZE;
  tty.c_cflag     |=  CS8;
  tty.c_cflag     &=  ~CRTSCTS;       // no flow control
  
  // no signaling chars, no echo, no canonical processing
  tty.c_lflag     =   0; 
  tty.c_oflag     =   0;           // no remapping, no delays
  tty.c_cc[VMIN]      =   0;        // read doesn't block
  // 0.5 seconds read timeout
  tty.c_cc[VTIME]     =   5;

  // turn on READ & ignore ctrl lines
  tty.c_cflag     |=  CREAD | CLOCAL;

  // turn off s/w flow ctrl
  tty.c_iflag     &=  ~(IXON | IXOFF | IXANY);
  tty.c_lflag     &=  ~(ICANON | ECHO | ECHOE | ISIG); // make raw
  tty.c_oflag     &=  ~OPOST;              // make raw

  /* Flush Port, then applies attributes */
  tcflush( fd, TCIFLUSH );

  if ( tcsetattr ( fd, TCSANOW, &tty ) != 0) {
    std::cout << "Error tcsetattr()" << std::endl;
  }
}


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

MiddleMan::MiddleMan(const string tty,
		     const string fout_name,
		     int sleepTime) {
  char name[40];
  
  if (openpty(&this->mPTY, &this->sPTY, name, NULL, NULL) < 0)
    std::cerr << "Could not open pty device" << std::endl;
  else {
    set_noecho(this->sPTY);
    this->ptyname = name;
    this->running = false;
  }

  if ( (this->mTTY = open(tty.c_str(), O_RDWR| O_NONBLOCK)) < 0 ) {
    std::cerr << "Could not open tty device" << std::endl;
  } else {
    this->ttyname = tty;
    setPort(this->mTTY);
  }
  if ( (this->fout = fopen(fout_name.c_str(), "w+")) == NULL )
    std::cout << "Error upon opening the output file" << std::endl;
  this->sleep = sleepTime;
}

MiddleMan::~MiddleMan() {
  close(this->mPTY);
  fclose(this->fout);
}

string MiddleMan::getPTY() {
  return this->ptyname;
}

string readTTY(int master, int readLen=100) {
  char *tty_in = new char[readLen+1];
  string tty_full;
  int i=0;

  tty_full = "";
  while ((i=read(master, tty_in, readLen)) >= readLen) {
    tty_in[i] = '\0';
    tty_full += tty_in;
  }
  tty_in[i] = '\0';
  tty_full += tty_in;
  delete[] tty_in;
  return tty_full;
}

void MiddleMan::run(int readLen) {
  this->running = true;
  while (this->running) {
    this->handleInput(readTTY(this->mPTY, readLen));
  }
}

void MiddleMan::handleInput(string tty_in) {
  string buf;

  write(this->mTTY, tty_in.c_str(), tty_in.size());
  usleep(this->sleep); // microseconds
  buf = readTTY(this->mTTY);
  write(this->mPTY, buf.c_str(), buf.size());
  this->log(tty_in, buf);
}


void MiddleMan::log(string input, string output,
		    const string format) {
  printf(format.c_str(), input.c_str(), output.c_str());
  fprintf(this->fout, format.c_str(), input.c_str(), output.c_str());
  fflush(this->fout);
}

