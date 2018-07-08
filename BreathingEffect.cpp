/* 
 * File:   BreathingEffect.cpp
 * Author: chlorek
 * 
 * Created on June 11, 2018, 10:40 AM
 */

#include "BreathingEffect.hpp"

namespace colorsair {
    BreathingEffect::BreathingEffect(std::chrono::milliseconds duration, RGB color)
        : LinearEffect(duration), color(color) {
    }

    BreathingEffect::BreathingEffect(const BreathingEffect& orig)
        : LinearEffect(orig), color(orig.color) {
    }

    BreathingEffect::~BreathingEffect() {
    }

    float BreathingEffect::tick() {
        float progress = LinearEffect::tick() * 2;

        if(progress > 1)
            progress = (2.f - progress);

        RGB newColor = {(uint8_t)(color.r * progress), (uint8_t)(color.g * progress), (uint8_t)(color.b * progress)};
        std::fill(&(colors[0]), &(colors[4]), newColor);
        return progress;
    }
}