#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>

#include "linux_parser.h"

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
  string os, kernel, _;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> _ >> kernel;
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

// DONE: Read and return the system memory utilization
// Method from the starting code
float LinuxParser::MemoryUtilization() { 
  string _, memTotal, memFree, line;
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  if (stream.is_open()) {
    // Get Total Memory
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> _ >> memTotal >> _;
    // Get Free Memory
    std::getline(stream, line);
    linestream.str(line);
    linestream.clear();
    linestream >> _ >> memFree >> _;
  }
  // std::cout << memTotal << std::endl;
  // std::cout << memFree << std::endl;
  float memUsed = stof(memTotal) - stof(memFree);
  float pmemUsed = memUsed / stof(memTotal);
  return pmemUsed;
}

// DONE: Read and return the system uptime
// Method from the starting code
long LinuxParser::UpTime() {
  string upTime, _, line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> upTime >> _;
  }
  return stol(upTime);
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// Method from the starting code
long LinuxParser::ActiveJiffies(int pid) {
  string theValue, uTime, sTime, cuTime, csTime, line;
  long totalTime;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      for(int i = 1; i < 14; i++) { linestream >> theValue; }
      linestream >> uTime >> sTime >> cuTime >> csTime;
      totalTime = stol(uTime) + stol(sTime) + stol(cuTime) + stol(csTime);
      return totalTime;
    }
  }
}

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { return {}; }

// DONE: Read and return the total number of processes
// Method from the starting code
int LinuxParser::TotalProcesses() {   
  string line, theKey, theValue;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> theKey >> theValue) {
        if (theKey == "processes") { return stoi(theValue); }
      }
    }
  }
}

// DONE: Read and return the number of running processes
// Method from the starting code
int LinuxParser::RunningProcesses() { 
  string line, theKey, theValue;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> theKey >> theValue) {
        if (theKey == "procs_running") { return stoi(theValue);}
      }
    }
  }
}

// DONE: Read and return the command associated with a process
// Method from the starting code
string LinuxParser::Command(int pid) {
  string line;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kCmdlineFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    return line;
  }
}


// TODO: Read and return the memory used by a process
// Method from the starting code
string LinuxParser::Ram(int pid) {
  string line, theKey, theValue, theRes;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> theKey >> theValue) {
        if (theKey == "VmSize:") { theRes = to_string(stoi(theValue) / 1024); return theRes; }
      }
    }
  }
}

// DONE: Read and return the user ID associated with a process
// Method from the starting code
string LinuxParser::Uid(int pid) {
  string line, theKey, theValue;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> theKey >> theValue) {
        if (theKey == "Uid:") { return theValue; }
      }
    }
  }
}

// DONE: Read and return the user associated with a process
// Method from the starting code
string LinuxParser::User(int pid) {
  string line, theUser, x, theUid;
  string actualUid{LinuxParser::Uid(pid)};
  std::ifstream filestream(kPasswordPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> theUser >> x >> theUid) {
        if (theUid == actualUid) { return theUser; }
      }
    }
  }
}

// TODO: Read and return the uptime of a process
// Method from the starting code
long LinuxParser::UpTime(int pid) {
  string line, theValue;
  long int theRes;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      for(int i = 1; i < 23; i++) { linestream >> theValue;}
      theRes = stol(theValue)/sysconf(_SC_CLK_TCK);
      return theRes;
   }
 }
}