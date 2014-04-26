#include "MiddleMan.h"
#include <iostream>

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cout << "Usage: " << argv[0] << " <tty device>" << std::endl;
  }
    

  MiddleMan m(argv[1]);
  std::cout << m.getPTY() << std::endl;
  m.run();
  
  return 0;
}
