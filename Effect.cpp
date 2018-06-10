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
}