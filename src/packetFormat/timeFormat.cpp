// Paired header
#include "packetFormat/timeFormat.hpp"
// Standard library headers
#include <chrono>   // For chrono time types and fucntions
#include <ctime>    // For calendar and local time structs and functions (std::time_t, std::tm. etc.)
#include <iomanip>  // For i/o manipulation (std::put_time)
#include <sstream>  // For std::ostringstream (streams that read or write to strings)
#include <string>   // To convert to ostringstream to standard C++ string

/*
* std::chrono::system_clock::time_point -> point in time from epoch
* std::chrono::system_clock::to_time_t(timestamp) -> converts timestampe to std::time_t i.e. a calendar time value (note this doesn't preserve microseconds)
* localtime_s(&local_time, &time) -> converts time (calendar time) to local_time (tm struct):
* struct tm {
        int tm_sec;
        int tm_min;
        int tm_hour;
        int tm_mday;
        int tm_mon;
        int tm_year;
        int tm_wday;
        int tm_yday;
        int tm_isdst;
    };
* std::put_time -> a standard-library formatting facility that takes calendar fields and a format string, producing formatted output through a stream
*   %Y: 4-digit year, %m: 2-digit month, %d: 2-digit day
*   %H: 24-hr hour, %M: minute, %S: second
*    
*/
std::string format_time(std::chrono::system_clock::time_point time) {
    // Convert time_point to time_t
    const std::time_t calendar_time { std::chrono::system_clock::to_time_t(time) };
    // Convert time_t to tm struct 
    std::tm local_time {};
    localtime_s(&local_time, &calendar_time);
    // Get string stream from local time
    std::ostringstream time_str;
    time_str << std::put_time(&local_time, "%Y-%m-%d %H:%M:%S");
    // Return converted to string type
    return time_str.str();
}