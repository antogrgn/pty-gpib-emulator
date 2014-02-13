

#include "PTY_Interface.h"
#include "Prologix.h"

int main() {
  Interface *inter = new Interface();
  Prologix_GPIB_USB *plg = new Prologix_GPIB_USB();

  inter->printFilename();
  
  inter->addDevice(plg, 0);

  delete plg;
  delete inter;
  return 0;
}
