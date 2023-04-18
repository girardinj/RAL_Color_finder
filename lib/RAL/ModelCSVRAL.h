#pragma once

#include <string>
#include <iostream>

struct rgb {
    int r;
    int g;
    int b;
};

class ModelCSVRAL {
    public:
        ModelCSVRAL(int ralCode, rgb rgbCode, std::string englishName);
        ~ModelCSVRAL();

        int getRal() const;
        rgb getRgb() const;
        std::string getEnglishName() const;

        friend std::ostream& operator<<(std::ostream& os, const ModelCSVRAL& mcr);

    private:
        int ralCode;
        rgb rgbCode;
        std::string* englishName;
};
