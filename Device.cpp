/* 
 * File:   Device.cpp
 * Author: chlorek
 * 
 * Created on June 9, 2018, 6:27 PM
 */

#include "Device.hpp"

#include <limits>

namespace colorsair {
    using namespace std;
    
    const uint16_t Device::VENDOR_ID = 0x1b1c;
    const uint16_t Device::LIGHTNING_NODE_ID = 0x0c0b;
    
    bool Device::libusbInitialized = false;
    int Device::libusbInitCode = std::numeric_limits<int>::min();
    libusb_device** Device::devices;
    libusb_context* Device::ctx;
    
    Device::Device(libusb_device_handle* handle) : handle(handle), referenceCount(new int(1)) {
    }

    Device::Device(const Device& orig) : handle(orig.handle), referenceCount(orig.referenceCount) {
        (*referenceCount)++;
    }

    Device::~Device() {
        if(--referenceCount == 0) {
            if(handle != nullptr)
                libusb_close(handle);
        }
    }
    
    Device Device::openDevice(uint16_t vendorId, uint16_t productId) {
        if(initialize() != 0)
            throw Uninitialized("libusb not initialized (error code: "+ to_string(libusbInitCode) +")", libusbInitCode);
        
        ssize_t devCount = libusb_get_device_list(ctx, &devices);
        libusb_device_handle* devHandle = libusb_open_device_with_vid_pid(ctx, vendorId, productId);
        if(devHandle == nullptr)
            throw Uninitialized("device not found");
        
        return Device(devHandle);
    }
    
    void Device::cleanup() {
        libusb_free_device_list(devices, 1);
        libusb_exit(NULL);
    }
    
    bool Device::detachKernelDriver() {
        if(libusb_kernel_driver_active(handle, 0) == 1 && libusb_detach_kernel_driver(handle, 0) != 0)
            return false;
        return true;
    }
    
    int Device::openInterface(int id) {
        return libusb_claim_interface(handle, id);
    }
    
    void Device::reset() {
        libusb_reset_device(handle);
    }
    
    WriteResult Device::writeInterrupt(unsigned char endpoint, std::vector<unsigned char> data) {
        int written;
        int res = libusb_interrupt_transfer(handle, (endpoint | LIBUSB_ENDPOINT_OUT), &data[0], data.size(), &written, 100);
        return {res, written};
    }
    
    int Device::initialize() {
        if(!libusbInitialized) {
            libusbInitCode = libusb_init(NULL);
            if(libusbInitCode == 0)
                libusbInitialized = true;
        }
        return libusbInitCode;
    }
}