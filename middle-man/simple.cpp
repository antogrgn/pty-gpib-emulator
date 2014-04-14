#include "MiddleMan.h"
#include <iostream>

int main(int argv, char **argc) {
  MiddleMan m(argc[1]);
  std::cout << m.getPTY() << std::endl;
  m.run();
  
  return 0;
}
