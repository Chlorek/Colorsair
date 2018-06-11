/* 
 * File:   TransitionEffect.hpp
 * Author: chlorek
 *
 * Created on June 11, 2018, 11:58 AM
 */

#ifndef TRANSITIONEFFECT_HPP
#define TRANSITIONEFFECT_HPP

#include "LinearEffect.hpp"
#include "ColorProvider.hpp"

namespace colorsair {
    template<class PROVIDER_T>
    class TransitionEffect : public LinearEffect {
        public:
            TransitionEffect(std::chrono::milliseconds duration, PROVIDER_T provider)
                : LinearEffect(duration), provider(provider), from(this->provider.next()), to(this->provider.next()) {
            }
                
            TransitionEffect(const TransitionEffect& orig)
                : LinearEffect(orig), provider(orig.provider) {
            };
            
            virtual ~TransitionEffect() {
            }
            
            virtual float tick() {
                float progress = LinearEffect::tick();
                std::fill(&(colors[0]), &(colors[4]), Effect::lerp(from, to, progress));
                
                if(progress >= 1) {
                    from = to;
                    to = provider.next();
                }
            }
        private:
            PROVIDER_T provider;
            RGB from, to;
    };
}

#include "TransitionEffect.hpp"

#endif /* TRANSITIONEFFECT_HPP */

