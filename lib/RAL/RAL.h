#pragma once

#include <unordered_map>
#include "ModelCSVRAL.h"
#include <math.h>

/**
 *  https://gist.github.com/lunohodov/1995178
 *  https://stackoverflow.com/questions/1120140/how-can-i-read-and-parse-csv-files-in-c
 * */
class RAL {
    public:
        static std::string getName(int r, int g, int b) {
            std::string rgbName = std::to_string(r) + "-" + std::to_string(g) + "-" + std::to_string(b);
            
            auto it = getInstance().rgbModelMap.find(rgbName);
            if (it != getInstance().rgbModelMap.end())
                return it->second->getEnglishName();
            // if color does not exists, approximate it?
            else {
                // https://en.wikipedia.org/wiki/Color_difference
                double smallestDistance = -1;
                ModelCSVRAL* nearestColor = nullptr;

                for (auto it = getInstance().rgbModelMap.begin(); it != getInstance().rgbModelMap.end(); ++it) {
                    ModelCSVRAL* mcv = it->second;

                    int mr = mcv->getRgb().r;
                    int mg = mcv->getRgb().g;
                    int mb = mcv->getRgb().b;
                    
                    double distance = sqrt(pow(r-mr, 2) + pow(g-mg, 2) + pow(b-mb, 2));
                    if (smallestDistance == -1 || distance < smallestDistance)
                    {
                        smallestDistance = distance;
                        nearestColor = mcv;
                    }
                }

                if (smallestDistance == -1)
                    return "error, no color registered in csv";
                else
                    return nearestColor->getEnglishName() + ", approximated by distance " + std::to_string(smallestDistance);
            }
        }

        static std::string getName(rgb colors) {
            return getName(colors.r, colors.g, colors.b);
        }

        static std::string getName(int ral) {
            std::string ralName = "RAL " + std::to_string(ral);
            
            auto it = getInstance().ralModelMap.find(ralName);
            if (it != getInstance().ralModelMap.end())
                return it->second->getEnglishName();
            else {
                return "color not registered";
            }
        }

        static const std::string getHeader() { return getInstance().header; }

    RAL(RAL const&) = delete;
    void operator=(RAL const&) = delete;

    private:
        static RAL& getInstance() {
            static RAL instance;
            return instance;
        }
        
        std::unordered_map<std::string, ModelCSVRAL*> ralModelMap;
        std::unordered_map<std::string, ModelCSVRAL*> rgbModelMap;

        RAL();
        ~RAL();

        std::string header;
};
