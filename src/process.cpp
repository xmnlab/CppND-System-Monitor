#include "process.h"

#include <unistd.h>

#include <cctype>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

/**
 * Return this process's ID
 */
int Process::Pid() { return this->pid_; }
int Process::Pid() const { return this->pid_; };

float Process::CpuUtilization() {
  return LinuxParser::CpuUtilization(this->pid_);
}

/**
 * Return the command that generated this process
 */
string Process::Command() { return LinuxParser::Command(this->pid_); }

/**
 * Return this process's memory utilization
 */
string Process::Ram() { return LinuxParser::Ram(this->pid_); }

/**
 * Return the user (name) that generated this process
 */
string Process::User() { return LinuxParser::User(this->pid_); }

/**
 * Return the age of this process (in seconds)
 */
long int Process::UpTime() { return LinuxParser::UpTime(); }

/**
 * Overload the "less than" comparison operator for Process objects
 */
bool Process::operator<(Process const& a) const {
  float lhs_cpu_usage = LinuxParser::CpuUtilization(Pid());
  float rhs_cpu_usage = LinuxParser::CpuUtilization(a.Pid());

  return lhs_cpu_usage < rhs_cpu_usage;
}
