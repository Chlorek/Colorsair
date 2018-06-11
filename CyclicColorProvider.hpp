/* 
 * File:   CyclicColorProvider.hpp
 * Author: chlorek
 *
 * Created on June 11, 2018, 10:55 AM
 */

#ifndef CYCLICCOLORPROVIDER_HPP
#define CYCLICCOLORPROVIDER_HPP

#include <vector>
#include "ColorProvider.hpp"

namespace colorsair {
    class CyclicColorProvider : public ColorProvider {
        public:
            CyclicColorProvider(std::vector<RGB> colors);
            CyclicColorProvider(const CyclicColorProvider& orig);
            virtual ~CyclicColorProvider();
            
            RGB next();
        private:
            std::vector<RGB> colors;
            unsigned int nextColor = 0;
    };
}

#endif /* CYCLICCOLORPROVIDER_HPP */

