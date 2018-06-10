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
#include <algorithm>

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
            : dev(dev), fansCount(fansCount) {
        effects.reserve(fansCount);
        for(int i = 0; i < fansCount; ++i)
            effects.push_back(nullptr);
    }

    FanController::~FanController() {
    }
    
    void FanController::setEffect(unsigned int fanId, Effect* effect) {
        std::lock_guard<std::mutex> lock(stateMutex);
        effects[fanId] = effect;
    }
    
    void FanController::setEffect(unsigned int fanId, Effect& effect) {
        std::lock_guard<std::mutex> lock(stateMutex);
        effects[fanId] = &effect;
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
            for(int i = 0; i < effects.size(); ++i) {
                std::lock_guard<std::mutex> lock(stateMutex);
                if(effects[i] != nullptr) {
                    effects[i]->tick();
                    /*state[i*4] = effects[i]->colors[0];
                    state[i*4+1] = effects[i]->colors[1];
                    state[i*4+2] = effects[i]->colors[2];
                    state[i*4+3] = effects[i]->colors[3];*/
                    //std::memcpy(state+(i*4), effects[i]->colors, 4);
                    //std::fill(state+(i*4), state+(i*4)+4, i == 0 ?RGB{255, 255, 0} : RGB{255, 0, 0} );
                }                    
            }
            
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
                            colorCmd.push_back(effects[i/4]->colors[i%4].r);
                            break;
                        case 1:
                            colorCmd.push_back(effects[i/4]->colors[i%4].g);
                            break;
                        case 2:
                            colorCmd.push_back(effects[i/4]->colors[i%4].b);
                            break;
                        default:;
                    }
                }
                while(colorCmd.size() < 64)
                    colorCmd.push_back(0x00);
                //std::cout << colorCmd << "\n" << std::endl;
                WriteResult wr = dev.writeInterrupt(1, colorCmd);
                if(wr.result != 0 || wr.written != 64)
                    std::cout << "Write Error #" << wr.result << " | written " << wr.written << endl;
            }
            
            std::this_thread::sleep_for(2ms);
        }
    }
}