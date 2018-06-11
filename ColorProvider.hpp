/* 
 * File:   ColorProvider.hpp
 * Author: chlorek
 *
 * Created on June 11, 2018, 10:45 AM
 */

#ifndef COLORPROVIDER_HPP
#define COLORPROVIDER_HPP

#include "Types.hpp"
#include <algorithm>

namespace colorsair {
    class ColorProvider {
        public:
            ColorProvider();
            ColorProvider(const ColorProvider& orig);
            virtual ~ColorProvider();

            virtual RGB next() = 0;
        private:

    };
}
#endif /* COLORPROVIDER_HPP */

