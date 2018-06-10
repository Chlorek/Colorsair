/* 
 * File:   FanController.hpp
 * Author: chlorek
 *
 * Created on June 10, 2018, 3:37 PM
 */

#ifndef FANCONTROLLER_HPP
#define FANCONTROLLER_HPP

#include <array>

#include "Device.hpp"
#include "Types.hpp"

namespace colorsair {
    class FanController {
        public:
            FanController(Device& dev, unsigned int fansCount);
            FanController(const FanController& orig);
            virtual ~FanController();
            
            void setColor(unsigned int fanId, std::array<RGB, 4> colors);
            void loop();
        private:
            Device& dev;
            unsigned int fansCount;
            RGB* state;
    };
}

#endif /* FANCONTROLLER_HPP */

