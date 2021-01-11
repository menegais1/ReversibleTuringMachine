//
// Created by menegais on 10/01/2021.
//

#ifndef REVERSIBLETURINGMACHINE_SHIFTOPERATION_H
#define REVERSIBLETURINGMACHINE_SHIFTOPERATION_H

#include "QuadrupleOperation.h"
#include "Extensions.h"


class ShiftOperation : public QuadrupleOperation {
public:

    ShiftOperation(Shift shift) {
        this->shift = shift;
        this->read = MOVEMENT_INDICATOR;
    }

    bool execute(Tape &tape) override {
        switch (shift) {
            case Shift::NONE:
                break;
            case Shift::RIGHT:
                tape.head++;
                break;
            case Shift::LEFT:
                tape.head--;
                break;
            default:
                return false;
        }

        return true;
    }

    bool canExecute(Tape tape) override {
        return true;
    }
};


#endif //REVERSIBLETURINGMACHINE_SHIFTOPERATION_H
