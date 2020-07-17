#include "processor.h"
#include <iostream>
#include "linux_parser.h"

// DONE: Return the aggregate CPU utilization
float Processor::Utilization() {
  std::string _, user, nice, system, idle, iowait, irq, softirq, steal, line;
  std::ifstream stream(LinuxParser::kProcDirectory + LinuxParser::kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> _ >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal >> _ >> _;
  }

  // Method from https://stackoverflow.com/a/23376195
  int idleTime = std::stoi(idle) + std::stoi(iowait);
  int nonidleTime = std::stoi(user) + std::stoi(nice) + std::stoi(system) + std::stoi(irq) + std::stoi(softirq) + std::stoi(steal);
  float totalTime = idleTime + nonidleTime;
  
  float cpuPercentage = (totalTime - idleTime)/totalTime;
  return cpuPercentage;
}