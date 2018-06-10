/* 
 * File:   StaticEffect.cpp
 * Author: chlorek
 * 
 * Created on June 10, 2018, 11:33 PM
 */

#include "StaticEffect.hpp"

#include <cstring>

namespace colorsair {
    StaticEffect::StaticEffect(RGB colors[4]) {
        std::memcpy(colors, this->colors, 4);
    }
    
    StaticEffect::StaticEffect(RGB color) {
        std::fill(colors, colors+4, color);
    }

    StaticEffect::StaticEffect(const StaticEffect& orig) {
    }

    StaticEffect::~StaticEffect() {
    }
    
    float StaticEffect::tick() {
        return 1;
    }
}