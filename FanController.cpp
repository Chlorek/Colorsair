/* 
 * File:   FanController.cpp
 * Author: chlorek
 * 
 * Created on June 10, 2018, 3:37 PM
 */

#include <cstring>
#include <vector>
#include <thread>
#include <chrono>

#include <iostream>
#include <iomanip>

#include "FanController.hpp"

namespace colorsair {
    std::ostream &operator<<(std::ostream& os, const std::vector<uint8_t>& list) {
        cout << "{ ";
        for(uint8_t val : list)
            os << "0x" << std::hex << std::setfill('0') << std::setw(2) << (int)val << ", ";
        os << "}";
        return os;
    }
    
    FanController::FanController(Device& dev, unsigned int fansCount)
            : dev(dev), fansCount(fansCount), state(new RGB[fansCount*4]) {
    }

    FanController::FanController(const FanController& orig)
            : dev(orig.dev), fansCount(orig.fansCount) {
        std::memcpy(state, orig.state, fansCount*4);
    }

    FanController::~FanController() {
        delete[] state;
    }
    
    void FanController::setColor(unsigned int fanId, std::array<RGB, 4> colors) {
        for(int i = 0; i < 4; ++i)
            state[fanId * 4 + i] = colors[i];
    }
    
    void FanController::loop() {
        dev.reset();
        
        std::vector<uint8_t> magicData[] {
            {0x33, 0xFF},
            {0x38, 0x01, 0x02},
            {0x34, 0x01},
            {0x33, 0xFF},
            {0x38, 0x00, 0x02}
        };
        std::vector<uint8_t> colorData {0x32, 0x00, 0x00, (uint8_t)(fansCount*4)};
        
        for(;;) {
            // write constant boilerplate
            for(auto line : magicData) {
                while(line.size() < 64) //pad the data with zeroes
                    line.push_back(0x00);

                WriteResult wr = dev.writeInterrupt(1, line);
                if(wr.result != 0 || wr.written != 64)
                    std::cout << "Write Error #" << wr.result << " | written " << wr.written << endl;
            }

            // write colors
            for(int channel = 0; channel < 3; ++channel) {
                std::vector<uint8_t> colorCmd(colorData.begin(), colorData.end());
                colorCmd.reserve(64);
                colorCmd.push_back(channel);
                for(int i = 0; i < fansCount*4; ++i) {
                    switch(channel) {
                        case 0:
                            colorCmd.push_back(state[i].r);
                            break;
                        case 1:
                            colorCmd.push_back(state[i].g);
                            break;
                        case 2:
                            colorCmd.push_back(state[i].b);
                            break;
                        default:;
                    }
                }
                while(colorCmd.size() < 64)
                    colorCmd.push_back(0x00);
                //std::cout << colorCmd << "\n" << std::endl;
                WriteResult wr = dev.writeInterrupt(1, colorCmd);
            }
            
            std::this_thread::sleep_for(2ms);
        }
    }
}