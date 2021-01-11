//
// Created by menegais on 10/01/2021.
//

#ifndef REVERSIBLETURINGMACHINE_TAPE_H
#define REVERSIBLETURINGMACHINE_TAPE_H

#include <string>
#include <vector>

class Tape {
public:
    std::vector<std::string> tape;
    int head = 500;

    Tape() {
        tape = std::vector<std::string>(1000);
        for (int i = 0; i <tape.size() ; ++i) {
            tape[i] = BLANK;
        }
    }

    void printTape() {
        for (int i = 0; i < tape.size(); ++i) {
            if (tape[i] == BLANK) continue;
            std::cout << tape[i] << " ";
        }
        std::cout << std::endl;

    }
};

#endif //REVERSIBLETURINGMACHINE_TAPE_H
