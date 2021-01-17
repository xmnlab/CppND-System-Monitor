#include "process.h"

#include <unistd.h>

#include <cctype>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"

// for debugging
// #include <glog/logging.h>

using std::string;
using std::to_string;
using std::vector;

/**
 * Return this process's ID
 */
int Process::Pid() {
  return this->pid_;
}
int Process::Pid() const {
  return this->pid_;
};

void Process::UpdateCpuUtilization() {
  long proc_uptime = LinuxParser::UpTime(this->pid_);
  long totaltime = LinuxParser::ActiveJiffies(this->pid_);

  this->utilization_ = float(totaltime) / float(proc_uptime);
}

float Process::CpuUtilization() const {
  return utilization_;
}

/**
 * Return the command that generated this process
 */
string Process::Command() {
  return LinuxParser::Command(this->pid_);
}

/**
 * Return this process's memory utilization
 */
string Process::Ram() {
  return LinuxParser::Ram(this->pid_);
}

/**
 * Return the user (name) that generated this process
 */
string Process::User() {
  return LinuxParser::User(this->pid_);
}

/**
 * Return the age of this process (in seconds)
 */
long int Process::UpTime() {
  return LinuxParser::UpTime(this->pid_);
}

/**
 * Overload the "less than" comparison operator for Process objects
 */
bool Process::operator<(Process const& a) const {
  // using "greater than" operator to show process starting by the
  // one that uses more the cpu.
  return CpuUtilization() > a.CpuUtilization();
}
