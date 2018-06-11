/* 
 * File:   CyclicColorProvider.cpp
 * Author: chlorek
 * 
 * Created on June 11, 2018, 10:55 AM
 */

#include "CyclicColorProvider.hpp"

namespace colorsair {
    CyclicColorProvider::CyclicColorProvider(std::vector<RGB> colors)
        : colors(colors) {
    }

    CyclicColorProvider::CyclicColorProvider(const CyclicColorProvider& orig)
        : colors(orig.colors) {
    }

    CyclicColorProvider::~CyclicColorProvider() {
    }
    
    RGB CyclicColorProvider::next() {
        if(nextColor == colors.size())
            nextColor = 0;
        return colors.at(nextColor++);
    }
}