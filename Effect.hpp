/* 
 * File:   Effect.hpp
 * Author: chlorek
 *
 * Created on June 10, 2018, 11:15 PM
 */

#ifndef EFFECT_HPP
#define EFFECT_HPP

#include "Types.hpp"

namespace colorsair {
    class Effect {
        public:
            Effect();
            Effect(const Effect& orig);
            virtual ~Effect();
            
            virtual float tick() = 0;
            
            RGB colors[4];
        private:

    };
}

#endif /* EFFECT_HPP */

