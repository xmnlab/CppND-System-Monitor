#include "processor.h"

#include <iostream>
#include <string>

#include "linux_parser.h"

using std::string;

/**
 * Return the aggregate CPU utilization
 */
float Processor::Utilization() {
  long total_old;
  long total_new;
  long active_new;
  long idle_old;
  long idle_new;

  total_new = this->CurrentTotal();
  active_new = this->CurrentActive();
  idle_new = this->CurrentIdle();

  total_old = this->PreviousTotal();
  idle_old = this->PreviousIdle();

  this->Update(idle_new, active_new, total_new);

  float total_diff = float(total_new) - float(total_old);
  float idle_diff = float(idle_new) - float(idle_old);
  float utilization = (total_diff - idle_diff) / total_diff;

  return utilization;
}

/**
 * Return the current total of jiffies.
 */
long Processor::CurrentTotal() {
  return LinuxParser::Jiffies();
}

/**
 * Return the current total of active jiffies.
 */
long Processor::CurrentActive() {
  return LinuxParser::ActiveJiffies();
}

/**
 * Return the total of idle jiffies.
 */
long Processor::CurrentIdle() {
  return LinuxParser::IdleJiffies();
}

/**
 * Return the previous total of jiffies.
 */
long Processor::PreviousTotal() {
  return total_;
}

/**
 * Return the previous total of active jiffies.
 */
long Processor::PreviousActive() {
  return active_;
}

/**
 * Return the previous total of idle jiffies.
 */
long Processor::PreviousIdle() {
  return idle_;
}

/**
 * Update the previous information for jiffies (idle, active and total).
 */
void Processor::Update(long idle, long active, long total) {
  this->idle_ = idle;
  this->active_ = active;
  this->total_ = total;
}
