/* 
 * File:   LinearEffect.hpp
 * Author: chlorek
 *
 * Created on June 11, 2018, 12:38 AM
 */

#ifndef LINEAREFFECT_HPP
#define LINEAREFFECT_HPP

#include "Effect.hpp"

namespace colorsair {
    class LinearEffect : public Effect {
        public:
            LinearEffect(std::chrono::milliseconds duration);
            LinearEffect(const LinearEffect& orig);
            virtual ~LinearEffect();
            
            float tick();
        protected:
            time_point begin;
            std::chrono::milliseconds duration;
    };
}

#endif /* LINEAREFFECT_HPP */

