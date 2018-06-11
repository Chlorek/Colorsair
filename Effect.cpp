/* 
 * File:   Effect.cpp
 * Author: chlorek
 * 
 * Created on June 10, 2018, 11:15 PM
 */

#include "Effect.hpp"

#include <cstring>

namespace colorsair {
    Effect::Effect() {
    }

    Effect::Effect(const Effect& orig) {
        std::memcpy(colors, orig.colors, 4);
    }

    Effect::~Effect() {
    }
    
    RGB Effect::lerp(RGB a, RGB b, float weight) {
        return {
                   (uint8_t)(a.r*(1-weight) + b.r*weight),
                   (uint8_t)(a.g*(1-weight) + b.g*weight),
                   (uint8_t)(a.b*(1-weight) + b.b*weight)
               };
    }
}