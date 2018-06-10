/* 
 * File:   Types.hpp
 * Author: chlorek
 *
 * Created on June 10, 2018, 3:49 PM
 */

#ifndef TYPES_HPP
#define TYPES_HPP

namespace colorsair {
    struct RGB {
        unsigned char r, g, b;
    };
    
    struct WriteResult {
        int result;
        int written;
    };
}

#endif /* TYPES_HPP */

