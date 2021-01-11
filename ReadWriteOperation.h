//
// Created by menegais on 10/01/2021.
//

#ifndef REVERSIBLETURINGMACHINE_READWRITEOPERATION_H
#define REVERSIBLETURINGMACHINE_READWRITEOPERATION_H

#include "QuadrupleOperation.h"
#include "Tape.h"

class ReadWriteOperation : public QuadrupleOperation {
public:
    ReadWriteOperation(std::string read,std::string  write) {
        this->read = read;
        this->write = write;
    }

    bool execute(Tape &tape) override {
        if (tape.tape[tape.head] == this->read){
            tape.tape[tape.head] = this->write;
            return true;
        }
        return false;
    }
};


#endif //REVERSIBLETURINGMACHINE_READWRITEOPERATION_H
