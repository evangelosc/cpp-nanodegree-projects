#ifndef PROCESS_H
#define PROCESS_H

#include "linux_parser.h"
#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int pid);
  int Pid() const;                         // DONE: See src/process.cpp
  std::string User();                      // DONE: See src/process.cpp
  std::string Command();                   // DONE: See src/process.cpp
  float CpuUtilization() const;            // DONE: See src/process.cpp
  std::string Ram();                       // TODO: See src/process.cpp
  long int UpTime() const;                 // DONE: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp

  // Done: Declare any necessary private members
 private:
  int pid_;
  std::string command_;
  std::string user_;
};

#endif