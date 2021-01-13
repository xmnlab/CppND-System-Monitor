#include "format.h"

#include <iostream>
#include <string>

using std::string;
using std::to_string;

string Format::ElapsedTime(long seconds) {
  long h;
  long d;
  long m;
  long s;

  h = seconds / (60 * 60);
  d = h / 24;
  h = h % 24;
  m = (seconds / 60) % 60;
  s = seconds % 60;

  return to_string(d) + "d" + to_string(h) + "h" + to_string(m) + "m";
}
