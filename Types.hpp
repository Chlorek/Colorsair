/* 
 * File:   Types.hpp
 * Author: chlorek
 *
 * Created on June 10, 2018, 3:49 PM
 */

#ifndef TYPES_HPP
#define TYPES_HPP

#include <cstdint>
#include <chrono>

namespace colorsair {
    struct RGB {
        unsigned char r = 0, g = 0, b = 0;
    };
    
    struct WriteResult {
        int result;
        int written;
    };
    
    /*
     * Duration with milliseconds accuracy
     */
    typedef std::chrono::duration<int, std::chrono::milliseconds> time_duration;
    
    /*
     * System-clock point in time
     */
    typedef std::chrono::time_point<std::chrono::system_clock> time_point;
}

#endif /* TYPES_HPP */

