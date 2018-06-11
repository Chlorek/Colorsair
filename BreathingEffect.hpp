/* 
 * File:   BreathingEffect.hpp
 * Author: chlorek
 *
 * Created on June 11, 2018, 10:40 AM
 */

#ifndef BREATHINGEFFECT_HPP
#define BREATHINGEFFECT_HPP

#include "LinearEffect.hpp"

namespace colorsair {
    class BreathingEffect : public LinearEffect {
        public:
            BreathingEffect(std::chrono::milliseconds duration, RGB color);
            BreathingEffect(const BreathingEffect& orig);
            virtual ~BreathingEffect();
            
            float tick();
        private:
            RGB color;
    };
}

#endif /* BREATHINGEFFECT_HPP */

