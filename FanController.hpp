/* 
 * File:   FanController.hpp
 * Author: chlorek
 *
 * Created on June 10, 2018, 3:37 PM
 */

#ifndef FANCONTROLLER_HPP
#define FANCONTROLLER_HPP

#include <vector>
#include <mutex>

#include "Device.hpp"
#include "Types.hpp"
#include "Effect.hpp"

namespace colorsair {
    class FanController {
        public:
            FanController(Device& dev, unsigned int fansCount);
            FanController(const FanController& orig);
            virtual ~FanController();
            
            void setEffect(unsigned int fanId, Effect* effect);
            void setEffect(unsigned int fanId, Effect& effect);
            void loop();
        private:
            Device& dev;
            unsigned int fansCount;
            //RGB* state;
            std::vector<Effect*> effects;
            std::mutex stateMutex;
    };
}

#endif /* FANCONTROLLER_HPP */

