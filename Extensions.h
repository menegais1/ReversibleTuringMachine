//
// Created by menegais on 10/01/2021.
//

#ifndef REVERSIBLETURINGMACHINE_EXTENSIONS_H
#define REVERSIBLETURINGMACHINE_EXTENSIONS_H

std::vector<std::string> split(const std::string &s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

enum Shift {
    RIGHT = 'R',
    LEFT = 'L',
    NONE = 'N',
};

const std::string BLANK = "B";
const std::string MOVEMENT_INDICATOR = "/";

template<typename Base, typename T>
inline bool instanceof(const T *ptr) {
    return dynamic_cast<const Base*>(ptr) != nullptr;
}

#endif //REVERSIBLETURINGMACHINE_EXTENSIONS_H
