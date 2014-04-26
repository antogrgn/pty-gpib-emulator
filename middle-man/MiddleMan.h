

#ifndef MIDDLEMAN
#define MIDDLEMAN

#include <string>

class MiddleMan;

using namespace std;

class MiddleMan {
 private:
  string ttyname;
  int mPTY, sPTY;
  int mTTY, sTTY;
  string ptyname;
  bool running;
  int sleep; // Microseconds
  FILE *fout;
 public:
  MiddleMan(const string iotty_name,
	    const string fout_name="out",
	    int sleepTime=200);
  ~MiddleMan();

  void run(int readLen=100);

  string getPTY();
  void handleInput(string input);
  void log(string input, string output,
	   const string format=">> %s\n<< %s\n");

  string openPTY();
  void closePTY();
};



#endif
