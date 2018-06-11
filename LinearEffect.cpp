/* 
 * File:   LinearEffect.cpp
 * Author: chlorek
 * 
 * Created on June 11, 2018, 12:38 AM
 */

#include "LinearEffect.hpp"

namespace colorsair {
    LinearEffect::LinearEffect(std::chrono::milliseconds duration)
        : Effect(), begin(std::chrono::system_clock::now()), duration(duration) {
    }

    LinearEffect::LinearEffect(const LinearEffect& orig)
        : begin(orig.begin), duration(orig.duration) {
    }
    
    LinearEffect::~LinearEffect() {
    }

    float LinearEffect::tick() {
        auto diff = std::chrono::system_clock::now() - begin;
        if(diff >= duration) {
            begin = std::chrono::system_clock::now();
            diff = duration;
        }
        
        float progress = (float)std::chrono::duration_cast<std::chrono::milliseconds>(diff).count() / duration.count();
        if(progress > 1)
            progress = 1;
        
        return progress;
    }
}