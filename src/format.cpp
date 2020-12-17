#include "format.h"

#include <string>
#include <iostream>

using std::string;
using std::to_string;

string Format::ElapsedTime(long seconds) {
  string h = std::to_string(seconds / (60 * 60));
  string m = std::to_string((seconds / 60) % 60);
  string s = std::to_string(seconds % 60);

  h.insert(h.begin(), 2 - h.length(), '0');
  m.insert(m.begin(), 2 - m.length(), '0');
  s.insert(s.begin(), 2 - s.length(), '0');

  return h + ':' + m + ':' + s;
}
