#include "ModelCSVRAL.h"

ModelCSVRAL::ModelCSVRAL(int ralCode, rgb rgbCode, std::string englishName) {
    // with new ?
        this->ralCode = ralCode;
        this->rgbCode = rgbCode;
        this->englishName = new std::string(englishName);
    }

ModelCSVRAL::~ModelCSVRAL() {
    delete this->englishName;
}

int ModelCSVRAL::getRal() const {
    return this->ralCode;
}

rgb ModelCSVRAL::getRgb() const {
    return this->rgbCode;
}

std::string ModelCSVRAL::getEnglishName() const {
    return *(this->englishName);
}

std::ostream& operator<<(std::ostream& os, const ModelCSVRAL& mcr) {
    os << mcr.ralCode << " {" << mcr.rgbCode.r << "," << mcr.rgbCode.g << "," << mcr.rgbCode.b << "} " << *(mcr.englishName);
    return os;
}
