

#include "Prologix.h"
#include <string>

Prologix_GPIB_USB::Prologix_GPIB_USB() {
  this->addCMD("++ver", &Prologix_GPIB_USB::version);
  //  this->addCMD("++addr", &Prologix_GPIB_USB::addr);
  //  this->addCMD("++kill", &Prologix_GPIB_USB::kill);
}

Prologix_GPIB_USB::~Prologix_GPIB_USB() {

}

string Prologix_GPIB_USB::handleCMD(Interface *fpl,
				    string cmd,
				    vector<string> *args) {
  
}

string Prologix_GPIB_USB::version(Interface *fpl,
				  vector<string> *args) {

}

string Prologix_GPIB_USB::addr(Interface *fpl,
			       vector<string> *args) {

}

string Prologix_GPIB_USB::kill(Interface *fpl,
			       vector<string> *args) {

}


void Prologix_GPIB_USB::addCMD(const char *cmd, handler h) {

}

void Prologix_GPIB_USB::addCMD(string cmd, handler h) {

}

