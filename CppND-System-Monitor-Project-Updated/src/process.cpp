#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"
#include "process.h"

using std::string;
using std::to_string;
using std::vector;


// Define the constructor
Process::Process(int pid){
    pid_ = pid;
    command_ = LinuxParser::Command(pid);
    user_ = LinuxParser::User(pid);
}

// DONE: Return this process's ID
int Process::Pid() const { return pid_; }

// DONE: Return this process's CPU utilization
float Process::CpuUtilization() const { // From https://stackoverflow.com/a/16736599
  float totalTime, upTime, secondsOfActive, cpuUtilization;
  totalTime = LinuxParser::ActiveJiffies(pid_);
  upTime = LinuxParser::UpTime();
  secondsOfActive = upTime - (Process::UpTime()/sysconf(_SC_CLK_TCK));
  cpuUtilization = (totalTime/sysconf(_SC_CLK_TCK))/secondsOfActive;
  return cpuUtilization;
}

// DONE: Return the command that generated this process
string Process::Command() { return command_; }

// DONE: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(pid_); }

// DONE: Return the user (name) that generated this process
string Process::User() { return user_; }

// DONE: Return the age of this process (in seconds)
long int Process::UpTime() const { return LinuxParser::UpTime(pid_); }

// TODO: Overload the "less than" comparison operator for Process objects
bool Process::operator<(Process const& a) const {  return CpuUtilization() < a.CpuUtilization(); }
