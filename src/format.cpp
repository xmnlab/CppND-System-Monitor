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

  string d_display;
  string h_display;
  string m_display;
  string s_display;

  h = seconds / (60 * 60);
  d = h / 24;
  h = h % 24;
  m = (seconds / 60) % 60;
  s = seconds % 60;

  h_display = to_string(h);
  m_display = to_string(m);

  m_display.insert(m_display.begin(), 2 - m_display.length(), '0');

  if (d == 0) {
    s_display = to_string(s);
    s_display.insert(s_display.begin(), 2 - s_display.length(), '0');
    return h_display + 'h' + m_display + 'm' + s_display + 's';
  }

  d_display = to_string(d);
  h_display.insert(h_display.begin(), 2 - h_display.length(), '0');

  return d_display + 'd' + h_display + 'h' + m_display + 'm';
}
