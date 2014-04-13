

#ifndef MIDDLEMAN
#define MIDDLEMAN

#include <string>

class MiddleMan;

using namespace std;

class MiddleMan {
 private:
  string ttyname;
  int mPTY, sPTY;
  string ptyname;
  bool running;
 public:
  MiddleMan(const string iotty_name);
  ~MiddleMan();

  void run(int readLen=100);

  string getPTY();
  void handleInput(string tty_in);

  string openPTY();
  void closePTY();
};



#endif
