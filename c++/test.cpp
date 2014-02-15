

#include "PTY_Interface.h"
#include "Prologix.h"
#include <iostream>

#define TEST(A) std::cout << A  << ": " << inter.handleInput(A).at(0) << std::endl;

int main() {
  Prologix_GPIB_USB *plg = new Prologix_GPIB_USB();
  Interface inter(plg);
  vector<string> v;

  inter.printFilename();
  inter.addDevice(plg, 0);

  TEST("++ver");
  TEST("++addr");
  TEST("++addr 2");
  TEST("++addr");
  TEST("++ver");

  inter.printFilename();
  inter.run();

  delete plg;
  return 0;
}
