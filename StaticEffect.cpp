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
        colors[0] = colors[1] = colors[2] = colors[3] = color;
    }

    StaticEffect::StaticEffect(const StaticEffect& orig) {\
        for(int i = 0; i < 4; ++i)
            colors[i] = orig.colors[i];
    }

    StaticEffect::~StaticEffect() {
    }
    
    float StaticEffect::tick() {
        return 1;
    }
}