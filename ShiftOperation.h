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

    QuadrupleOperation *reverse() override {
        switch (shift) {
            case Shift::NONE:
                break;
            case Shift::RIGHT:
                return new ShiftOperation(Shift::LEFT);
                break;
            case Shift::LEFT:
                return new ShiftOperation(Shift::RIGHT);
                break;
            default:
                return nullptr;
        }
        return new ShiftOperation(Shift::NONE);
    }
};


#endif //REVERSIBLETURINGMACHINE_SHIFTOPERATION_H
