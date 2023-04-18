#include "RAL.h"
#include <iostream>
#include "ModelCSVRAL.h"
#include <fstream>
#include <sstream>

const std::string WHITESPACE = " \n\r\t\f\v";
 
std::string ltrim(const std::string &s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}
 
std::string rtrim(const std::string &s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}
 
std::string trim(const std::string &s) {
    return rtrim(ltrim(s));
}

RAL::RAL() {
    std::ifstream ralColorData("data/RALColors.csv");

    std::string line;
    
    // get first line
    if (!std::getline(ralColorData, line)) {
        std::cerr << "ERROR: csv file is empty or non-existent" << std::endl;
        return;
    }
    header = line;

    // get the rest to populate our hashMaps
    while(std::getline(ralColorData, line)) {
        //sRal, sRgb, sHex, sGerman, sEnglish, sFrench, sSpanish, sItalian, sNederlands;
        std::string values[9] = {};
        std::string value = "";
        int valuesIndex = 0;
        for(int i = 0; i < line.size(); ++i) {
            char c = line[i];
            if (c == ',') {
                values[valuesIndex++] = trim(value);
                value = "";
            } else {
                value += c;
            }
        }
        // we have to add the last one
        values[valuesIndex++] = trim(value);
        
        // remove the initial "RAL "
        int ralCode = std::stoi(values[0].substr(4));
        int rgb[3] = {};
        int rgbIndex = 0;
        std::string rgbCode = "";
        std::string rgbString = values[1];
        for(int i = 0; i < rgbString.size(); ++i) {
            char c = rgbString[i];
            if (c == '-') {
                rgb[rgbIndex++] = std::stoi(rgbCode);
                rgbCode = "";
            } else {
                rgbCode += c;
            }
        }
        // we have to add the last one
        rgb[rgbIndex++] = std::stoi(rgbCode);


        ModelCSVRAL* mcr = new ModelCSVRAL(ralCode, {rgb[0], rgb[1], rgb[2]}, values[4]);

        ralModelMap.insert(std::make_pair(values[0], mcr));
        rgbModelMap.insert(std::make_pair(values[1], mcr));
    }
}

RAL::~RAL() {
    for (auto it = ralModelMap.begin(); it != ralModelMap.end(); ++it) {
        delete it->second;
    }
}
