/* 
 * File:   Device.hpp
 * Author: chlorek
 *
 * Created on June 9, 2018, 6:27 PM
 */

#ifndef DEVICE_HPP
#define DEVICE_HPP

#include <libusb-1.0/libusb.h>
#include <stdexcept>
#include <string>
#include <vector>

#include "Types.hpp"

namespace colorsair {
    using namespace std;
    
    class Uninitialized : public runtime_error {
        public:
            Uninitialized(const char* msg, int errorCode = 0) : runtime_error(msg), errorCode(errorCode) {};
            Uninitialized(const string& msg, int errorCode = 0) : runtime_error(msg), errorCode(errorCode) {};

            const int errorCode;
    };
    
    class Device {
        public:
            Device(libusb_device_handle* handle);
            Device(const Device& orig);
            virtual ~Device();
            
            static Device openDevice(uint16_t vendorId, uint16_t productId);
            static void cleanup();
            
            bool detachKernelDriver();
            int openInterface(int id);
            void reset();
            WriteResult writeInterrupt(unsigned char endpoint, std::vector<unsigned char> data);
            
            static const uint16_t VENDOR_ID;
            static const uint16_t LIGHTNING_NODE_ID;
        private:
            static bool libusbInitialized;
            static int libusbInitCode;
            static libusb_device** devices;
            static libusb_context* ctx;
            libusb_device_handle* handle;
            int* referenceCount;
            
            static int initialize();
    };
}

#endif /* DEVICE_HPP */

