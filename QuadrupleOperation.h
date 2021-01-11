//
// Created by menegais on 10/01/2021.
//

#ifndef REVERSIBLETURINGMACHINE_QUADRUPLEOPERATION_H
#define REVERSIBLETURINGMACHINE_QUADRUPLEOPERATION_H

#include "Tape.h"

class ShiftOperation;

class ReadWriteOperation;

class QuadrupleOperation {
public:
    std::string read = BLANK;
    std::string write = BLANK;
    Shift shift = Shift::NONE;

    virtual bool execute(Tape &tape) = 0;

    virtual bool canExecute(Tape tape) = 0;

    virtual QuadrupleOperation* reverse() = 0;
    std::string getOperation() {
        if (instanceof<ShiftOperation>(this)) return std::string(1, this->shift);
        else return this->write;
    }
};


#endif //REVERSIBLETURINGMACHINE_QUADRUPLEOPERATION_H
