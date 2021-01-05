#include "linux_parser.h"

#include <dirent.h>
#include <unistd.h>

#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel;
  string line;
  string version;

  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

/**
 * Read and return the system memory utilization
 *
 * MemFree / MemTotal
 *
 * See: https://stackoverflow.com/a/41251290
 */
float LinuxParser::MemoryUtilization() {
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);

  if (!filestream.is_open()) {
    return 0.0;
  }

  string line;
  string key;
  float mem_total;
  float mem_free;
  float value;

  while (std::getline(filestream, line)) {
    std::replace(line.begin(), line.end(), ':', ' ');
    std::istringstream linestream(line);

    while (linestream >> key >> value) {
      if (key == "MemTotal") {
        mem_total = value;
      } else if (key == "MemFree") {
        mem_free = value;
      }
    }
  }

  return mem_free / mem_total;
}

/**
 * Read and return the system uptime
 */
long LinuxParser::UpTime() {
  string line;
  float uptime;
  float idle_time;

  std::ifstream filestream(kProcDirectory + kUptimeFilename);

  if (!filestream.is_open()) {
    return 0;
  }

  std::getline(filestream, line);
  std::istringstream linestream(line);

  linestream >> uptime >> idle_time;
  return long(uptime);
}

/*
 * Read and return the number of jiffies for the system
 */
long LinuxParser::Jiffies() { return 0; }

/*
 * Read and return the number of active jiffies for a PID
 */
long LinuxParser::ActiveJiffies(int pid [[maybe_unused]]) { return 0; }

/*
 * Read and return the number of active jiffies for the system
 */
long LinuxParser::ActiveJiffies() { return 0; }

/*
 * Read and return the number of idle jiffies for the system
 */
long LinuxParser::IdleJiffies() { return 0; }

/*
 * Read and return CPU utilization
 */
vector<string> LinuxParser::CpuUtilization() { return {}; }

int LinuxParser::TotalProcesses() {
  string line;
  string key;
  int value;
  int total_processes = 0;

  std::ifstream filestream(kProcDirectory + kStatFilename);

  if (!filestream.is_open()) {
    return 0;
  }

  while (std::getline(filestream, line)) {
    std::istringstream linestream(line);

    while (linestream >> key >> value) {
      if (key == "processes") {
        total_processes = value;
        break;
      }
    }
  }

  return total_processes;
}

/*
 * Read and return the number of running processes
 */
int LinuxParser::RunningProcesses() {
  string line;
  string key;
  int running_processes = 0;
  int value;

  std::ifstream filestream(kProcDirectory + kStatFilename);

  if (!filestream.is_open()) {
    return 0;
  }

  while (std::getline(filestream, line)) {
    std::istringstream linestream(line);

    if (linestream >> key >> value) {
      if (key == "procs_running") {
        running_processes = value;
        break;
      }
    }
  }
  return running_processes;
}

/*
 * Read and return the command associated with a process
 */
string LinuxParser::Command(int pid) {
  string line;
  string key;
  string value;

  std::ifstream filestream(LinuxParser::kProcDirectory + to_string(pid) +
                           LinuxParser::kCmdlineFilename);

  if (!filestream.is_open()) {
    return "";
  }

  std::getline(filestream, line);
  return line;
}

/*
 * Read and return the memory used by a process (in MB)
 */
string LinuxParser::Ram(int pid) {
  string line;
  string key;
  string ram = "";
  int value;

  std::ifstream filestream(LinuxParser::kProcDirectory + to_string(pid) +
                           LinuxParser::kStatusFilename);

  if (!filestream.is_open()) {
    return "";
  }

  while (std::getline(filestream, line)) {
    std::replace(line.begin(), line.end(), ':', ' ');

    std::istringstream linestream(line);

    linestream >> key >> value;

    if (key == "VmSize") {
      ram = to_string(value / 1024);
      break;
    }
  }

  return ram;
}

/*
 * Read and return the user ID associated with a process
 */
string LinuxParser::Uid(int pid) {
  string line;
  string key;
  string value = "";

  std::ifstream filestream(LinuxParser::kProcDirectory + to_string(pid) +
                           LinuxParser::kStatusFilename);

  if (!filestream.is_open()) {
    return "";
  }

  while (std::getline(filestream, line)) {
    std::replace(line.begin(), line.end(), ':', ' ');

    std::istringstream linestream(line);

    linestream >> key >> value;

    if (key == "Uid") {
      break;
    }
  }
  return value;
}

/*
 * Read and return the user associated with a process
 */
string LinuxParser::User(int pid) {
  string uid = LinuxParser::Uid(pid);

  string line;
  string username = "";
  string _uid;
  string _x;

  std::ifstream filestream(LinuxParser::kPasswordPath);

  if (!filestream.is_open()) {
    return "";
  }

  while (std::getline(filestream, line)) {
    std::replace(line.begin(), line.end(), ':', ' ');

    std::istringstream linestream(line);

    linestream >> username >> _x >> _uid;

    if (_uid == uid) {
      break;
    }
  }

  return username;
}

/*
 * Read and return the uptime of a process
 */
long LinuxParser::UpTime(int pid) {
  string line;
  string tmp;
  int starttime;

  std::ifstream filestream(LinuxParser::kProcDirectory + to_string(pid) +
                           LinuxParser::kStatFilename);
  if (!filestream.is_open()) {
    return 0;
  }

  std::getline(filestream, line);

  std::istringstream linestream(line);

  for (int i = 1; i < 21; ++i) {
    linestream >> tmp;
  }
  linestream >> starttime;

  return starttime / sysconf(_SC_CLK_TCK);
}

/**
 * Return this process's CPU utilization.
 *
 * See: https://stackoverflow.com/a/16736599
 */
float LinuxParser::CpuUtilization(int pid) {
  string line;
  string tmp;

  int utime;
  int stime;
  int cutime;
  int cstime;
  int starttime;

  std::ifstream filestream(LinuxParser::kProcDirectory + to_string(pid) +
                           LinuxParser::kStatFilename);

  if (!filestream.is_open()) {
    return 0.0;
  }
  std::getline(filestream, line);

  std::istringstream linestream(line);

  int system_uptime;

  system_uptime = LinuxParser::UpTime();

  for (int i = 1; i < 14; ++i) {
    linestream >> tmp;
  }

  linestream >> utime;
  linestream >> stime;
  linestream >> cutime;
  linestream >> cstime;

  for (int i = 17; i < 22; ++i) {
    linestream >> tmp;
  }

  linestream >> starttime;

  int hertz = sysconf(_SC_CLK_TCK);

  int total_time = utime + stime + cutime + cstime;

  int seconds = system_uptime - (starttime / hertz);

  // cpu_usage
  return 100 * ((total_time / hertz) / seconds);
}
