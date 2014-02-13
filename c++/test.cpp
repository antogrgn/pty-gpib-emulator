

#include "PTY_Interface.h"


int main() {
  Interface *inter = new Interface();
  Prologix_GPIB_USB *plg = new Prologix_GPIB_USB();

  inter->printFilename();
  


  delete inter;
  return 0;
}
