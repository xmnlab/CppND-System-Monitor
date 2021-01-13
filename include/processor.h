#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();
  long CurrentTotal();
  long CurrentActive();
  long CurrentIdle();

  long PreviousTotal();
  long PreviousIdle();
  long PreviousActive();
  void Update(long idle, long active, long total);

 private:
  long idle_;
  long active_;
  long total_;
};

#endif
