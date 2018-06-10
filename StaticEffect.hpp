/* 
 * File:   StaticEffect.hpp
 * Author: chlorek
 *
 * Created on June 10, 2018, 11:33 PM
 */

#ifndef STATICEFFECT_HPP
#define STATICEFFECT_HPP

#include "Effect.hpp"

#include <algorithm>

namespace colorsair {
    class StaticEffect : public Effect {
        public:
            StaticEffect(RGB colors[4]);
            StaticEffect(RGB color);
            StaticEffect(const StaticEffect& orig);
            virtual ~StaticEffect();
            
            float tick();
        private:

    };
}

#endif /* STATICEFFECT_HPP */

