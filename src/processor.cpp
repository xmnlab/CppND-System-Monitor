#include "processor.h"

#include <iostream>
#include <string>

#include "linux_parser.h"

using std::string;

/**
 * The very first "cpu" line aggregates the numbers in all of the other "cpuN"
 * lines. These numbers identify the amount of time the CPU has spent
 * performing different kinds of work. Time units are in USER_HZ (typically
 * hundredths of a second). The meanings of the columns are as follows, from
 * left to right:
 *
 * user: normal processes executing in user mode
 * nice: niced processes executing in user mode
 * system: processes executing in kernel mode
 * idle: twiddling thumbs
 * iowait: In a word, iowait stands for waiting for I/O to complete. But there
 *      are several problems:
 *        - Cpu will not wait for I/O to complete, iowait is the time that a
 *          task is waiting for I/O to complete. When cpu goes into idle state
 *          for outstanding task io, another task will be scheduled on this
 *          CPU.
 *        - In a multi-core CPU, the task waiting for I/O to complete is not
 *          running on any CPU, so the iowait of each CPU is difficult to
 *          calculate.
 *        - The value of iowait field in /proc/stat will decrease in certain
 *          conditions. So, the iowait is not reliable by reading from
 *          /proc/stat.
 * irq: servicing interrupts
 * softirq: servicing softirqs
 * steal: involuntary wait
 * guest: running a normal guest
 * guest_nice: running a niced guest
 *
 */
float Processor::Utilization() {
  string line;
  string key;

  long usertime = 0;
  long nicetime = 0;
  long systemtime = 0;
  long idletime = 0;
  long iowaittime = 0;
  long irqtime = 0;
  long softirqtime = 0;
  long stealtime = 0;
  long guesttime = 0;
  long guestnicetime = 0;

  std::ifstream filestream(LinuxParser::kProcDirectory +
                           LinuxParser::kStatFilename);

  if (!filestream.is_open()) {
    return 0.0;
  }

  while (std::getline(filestream, line)) {
    std::istringstream linestream(line);

    linestream >> key >> usertime >> nicetime >> systemtime >> idletime >>
        iowaittime >> irqtime >> softirqtime >> stealtime >> guesttime >>
        guestnicetime;

    if (key == "cpu") {
      break;
    }
  }

  // Guest time is already accounted in usertime
  // As you see here, it subtracts guest from user time
  usertime = usertime - guesttime;
  // and guest_nice from nice time
  nicetime = nicetime - guestnicetime;
  // Fields existing on kernels >= 2.6
  // (and RHEL's patched kernel 2.4...)
  // ioWait is added in the idleTime
  unsigned long long int idlealltime = idletime + iowaittime;
  unsigned long long int systemalltime = systemtime + irqtime + softirqtime;
  unsigned long long int virtalltime = guesttime + guestnicetime;
  unsigned long long int totaltime = usertime + nicetime + systemalltime +
                                     idlealltime + stealtime + virtalltime;

  return (totaltime - idlealltime) / totaltime;
}
