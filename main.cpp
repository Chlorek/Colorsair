/* 
 * File:   main.cpp
 * Author: chlorek
 *
 * Created on June 8, 2018, 4:55 PM
 */

#include <iostream>

#include "Device.hpp"
#include "FanController.hpp"

using namespace std;
using namespace colorsair;

int main(int argc, char** argv) {
    try {
        Device dev = Device::openDevice(Device::VENDOR_ID, Device::LIGHTNING_NODE_ID);
        
        if(!dev.detachKernelDriver())
            cout << "Could not detach kernel driver, trying to continue anyway..." << endl;

        int result;
        if((result = dev.openInterface(0)) == 0) {
            cout << "Communication channel established" << endl;
            
            FanController ctrl(dev, 2);
            ctrl.setColor(0, {RGB{255, 255, 0}, RGB{255, 255, 0}, RGB{255, 255, 0}, RGB{255, 255, 0}});
            //ctrl.setColor(1, {RGB{255, 255, 0}, RGB{255, 255, 0}, RGB{255, 255, 0}, RGB{255, 255, 0}});
            ctrl.setColor(1, {RGB{255, 0, 0}, RGB{255, 0, 255}, RGB{255, 0, 0}, RGB{255, 0, 255}});
            
            cout << "Loop started" << endl;
            ctrl.loop();
        } else
            cout << "Could not open device interface (error code " << result << ")";
    } catch(Uninitialized ex) {
        cout << ex.what() << endl;
    } catch(exception ex) {
        cout << ex.what() << "\nSorry it happened! Program will exit..." << endl;
    }
    
    Device::cleanup();
    
    return 0;
}

