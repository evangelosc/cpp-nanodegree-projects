#include <string>

#include "format.h"
#include <stdio.h>
using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
 std::string theString, theHoursString, theMinutesString, theSecondsString;
 int theHours = seconds/3600;
 int reminder = seconds%3600;
 int theMinutes = reminder/60;
 int theSeconds = reminder%60;
 if (theHours<10){theHoursString = "0"+std::to_string(theHours);}
 else {theHoursString = std::to_string(theHours);}
 if (theMinutes<10){theMinutesString = "0"+std::to_string(theMinutes);}
 else {theMinutesString = std::to_string(theMinutes);}
 if (theSeconds<10){theSecondsString = "0"+std::to_string(theSeconds);}
 else {theSecondsString = std::to_string(theSeconds);}
 theString = theHoursString + ":"+ theMinutesString + ":" + theSecondsString;
 return theString;
}