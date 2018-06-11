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
    
    FanController::FanController(Device& dev, unsigned int fansCount, uint8_t framerate)
            : dev(dev), fansCount(fansCount), framerate(framerate),
              timestep(1000/framerate), frameCountTime(std::chrono::system_clock::now()) {
        effects.reserve(fansCount);
        for(int i = 0; i < fansCount; ++i)
            effects.push_back(nullptr);
    }

    FanController::~FanController() {
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
            frameStart = std::chrono::system_clock::now();
            for(int i = 0; i < effects.size(); ++i) {
                std::lock_guard<std::mutex> lock(stateMutex);
                if(effects[i])
                    effects[i]->tick();                
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
                    std::lock_guard<std::mutex> lock(stateMutex);
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
                    std::cout << "Write Error #" << wr.result << " | written " << wr.written << std::endl;
            }
            
            // Frames control
            unsigned int frameTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - frameStart).count();
            if(frameTime < timestep) {
                //std::cout << "Sleeping for " << timestep-frameTime << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(timestep-frameTime));
            }
            
            ++frames;
            if(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - frameCountTime).count() > 1000) {
                frameCountTime = std::chrono::system_clock::now();
                //std::cout << "Framerate " << (int)frames << std::endl;
                frames = 0;
            }
        }
    }
}