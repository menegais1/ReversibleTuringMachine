#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include "Extensions.h"
#include "QuadrupleOperation.h"
#include "ShiftOperation.h"
#include "ReadWriteOperation.h"
#include "Tape.h"

//Segue a descrição do nosso trabalho 1. Primeiramente, vocês devem ler e estudar o artigo sobre MT reversível.
//
//Implementação de um Simulador de Máquina de Turing Reversível.
// A seguir temos um exemplo de arquivo de entrada ilustrativo.
// A primeira linha apresenta números, que indicam: número de estados, número de símbolos no alfabeto de entrada, número de símbolos no alfabeto da fita e número de transições, respectivamente.
// A seguir, temos os estados, na próxima linha alfabeto de entrada e
// logo alfabeto da fita. N
// as linhas sequentes temos a funcão de transição (como explicada no artigo). Depois da funcão de transição, segue uma entrada.
// Lembrando que o estado de aceitação é o último, no caso do exemplo, o 6.
//
//LEMBRETE: o seu programa deve ler de um arquivo como ele lê da entrada padrão. Por exemplo, a chamada deve funcionar para:
//
//./simulador < entrada.txt

class OrdinalTransition {
public:
    OrdinalTransition(std::string stringTransition, int id) : id(id) {

        stringTransition.erase(remove(stringTransition.begin(), stringTransition.end(), '('), stringTransition.end());
        stringTransition.erase(remove(stringTransition.begin(), stringTransition.end(), ')'), stringTransition.end());
        std::replace(stringTransition.begin(), stringTransition.end(), '=', ',');
        auto list = split(stringTransition, ',');

        curState = list[0];
        read = list[1];
        nextState = list[2];
        write = list[3];
        shift = (Shift) list[4][0];
    }

    std::string curState;
    std::string nextState;
    std::string read;
    std::string write;
    Shift shift;
    int id;

    void toString() {
        std::cout << "ID " << id << ":" << "{" << std::endl;
        std::cout << "Current State " << curState << std::endl;
        std::cout << "Read " << read << std::endl;
        std::cout << "Next State " << nextState << std::endl;
        std::cout << "Write " << write << std::endl;
        std::cout << "Shift " << (char) shift << std::endl;
        std::cout << "}" << std::endl;
    }

private:
    std::string originalString;
};

class OrdinalTuringMachine {
public:

    std::vector<OrdinalTransition> transitions;
    std::vector<std::string> statesList;
    std::vector<std::string> tapeAlphabetList;

    std::string input;

    OrdinalTuringMachine() {
        parseTuringMachine();
        for (int i = 0; i < transitionsList.size(); ++i) {
            transitions.push_back(OrdinalTransition(transitionsList[i], i));
        }
    }

    void parseTuringMachine() {
        std::string ordinalTuringMachineDefinitionLine;
        std::string statesLine;
        std::string inputAlphabetLine;
        std::string tapeAlphabetLine;
        std::string entryLine;
        std::getline(std::cin, ordinalTuringMachineDefinitionLine);
        std::getline(std::cin, statesLine);
        std::getline(std::cin, inputAlphabetLine);
        std::getline(std::cin, tapeAlphabetLine);

        auto list = split(ordinalTuringMachineDefinitionLine, ' ');
        int stateAmount = atoi(list[0].c_str());
        int inputAlphabetAmount = atoi(list[1].c_str());
        int tapeAlphabetAmount = atoi(list[2].c_str());
        int transitionsAmount = atoi(list[3].c_str());

        std::cout << "State amount: " << stateAmount << std::endl;
        std::cout << "Input Alphabet amount: " << inputAlphabetAmount << std::endl;
        std::cout << "Tape Alphabet amount: " << tapeAlphabetAmount << std::endl;
        std::cout << "Transitions amount: " << transitionsAmount << std::endl;

        std::string curLine;
        for (int i = 0; i < transitionsAmount; ++i) {
            std::getline(std::cin, curLine);
            transitionsList.push_back(curLine);
        }

        std::getline(std::cin, input);

        statesList = split(statesLine, ' ');
        inputAlphabetList = split(inputAlphabetLine, ' ');
        tapeAlphabetList = split(tapeAlphabetLine, ' ');

        std::cout << "States: " << std::endl;
        for (int i = 0; i < statesList.size(); ++i) {
            std::cout << statesList[i] << std::endl;
        }

        std::cout << "Input Alphabet: " << std::endl;
        for (int i = 0; i < inputAlphabetList.size(); ++i) {
            std::cout << inputAlphabetList[i] << std::endl;
        }

        std::cout << "Tape Alphabet: " << std::endl;
        for (int i = 0; i < tapeAlphabetList.size(); ++i) {
            std::cout << tapeAlphabetList[i] << std::endl;
        }

        std::cout << "Transitions: " << std::endl;
        for (int i = 0; i < transitionsList.size(); ++i) {
            std::cout << transitionsList[i] << std::endl;
        }
    }

private:
    std::vector<std::string> inputAlphabetList;
    std::vector<std::string> transitionsList;
};

class MultiTapeTransition {
public:

    MultiTapeTransition() {}

    MultiTapeTransition(const std::string &curState, const std::string &nextState, QuadrupleOperation *inputTapeOperation, QuadrupleOperation *historyTapeOperation,
                        QuadrupleOperation *outputTapeOperation) : fromState(curState), toState(nextState), inputTapeOperation(inputTapeOperation), historyTapeOperation(historyTapeOperation),
                                                                   outputTapeOperation(outputTapeOperation) {}

    QuadrupleOperation *operator[](int index) {
        if (index == 0) return inputTapeOperation;
        if (index == 1) return historyTapeOperation;
        if (index == 2) return outputTapeOperation;
    }


    void toString() {
        std::cout << fromState << "[" << inputTapeOperation->read << " " << historyTapeOperation->read << " " << outputTapeOperation->read << "] -> [";
        std::cout << inputTapeOperation->getOperation() << " " << historyTapeOperation->getOperation() << " " << outputTapeOperation->getOperation() << "]" << toState << std::endl;

    }

    bool execute(Tape &inputTape, Tape &historyTape, Tape &outputTape) {
        inputTapeOperation->execute(inputTape);
        historyTapeOperation->execute(historyTape);
        outputTapeOperation->execute(outputTape);
        return true;
    }

    bool canExecute(Tape inputTape, Tape historyTape, Tape outputTape) {
        return inputTapeOperation->canExecute(inputTape) && historyTapeOperation->canExecute(historyTape) && outputTapeOperation->canExecute((outputTape));
    }

    std::string fromState;
    std::string toState;
    QuadrupleOperation *inputTapeOperation;
    QuadrupleOperation *historyTapeOperation;
    QuadrupleOperation *outputTapeOperation;
};


class ReversibleTuringMachineSimulator {
public:
    Tape inputTape;
    Tape historyTape;
    Tape outputTape;
    std::vector<QuadrupleOperation *> operations;
    std::vector<MultiTapeTransition> transitions;
    std::vector<std::string> finalState;
    std::string initialState;
    std::string currentState;
    std::vector<std::string> tapeAlphabet;

    ReversibleTuringMachineSimulator(const std::vector<std::string> &finalState, const std::string &initialState, std::string input,
                                     std::vector<std::string> tapeAlphabet, std::vector<OrdinalTransition> ordinalTransitions) : finalState(finalState),
                                                                                                                                 initialState(initialState),
                                                                                                                                 tapeAlphabet(tapeAlphabet) {
        convertOrdinalTransitions(ordinalTransitions);
        for (int i = 0; i < transitions.size(); ++i) {
            transitions[i].toString();
        }

        for (int head = inputTape.head, j = 0; j < input.size(); head++, j++) {
            inputTape.tape[head] = input[j];
        }

        currentState = initialState;
    }

    std::string seekBeginning(std::string curState) {
        MultiTapeTransition seekBeginning = MultiTapeTransition(curState, "S0",
                                                                new ReadWriteOperation(BLANK, BLANK),
                                                                new ShiftOperation(Shift::NONE),
                                                                new ShiftOperation(Shift::NONE));
        MultiTapeTransition seekBeginning1 = MultiTapeTransition("S0", "S1",
                                                                 new ShiftOperation(Shift::LEFT),
                                                                 new ShiftOperation(Shift::NONE),
                                                                 new ShiftOperation(Shift::NONE));

        transitions.push_back(seekBeginning);
        transitions.push_back(seekBeginning1);
        for (int i = 0; i < tapeAlphabet.size(); i++) {
            if (tapeAlphabet[i] != BLANK) {
                MultiTapeTransition seekBeginning2 = MultiTapeTransition("S1", "S0",
                                                                         new ReadWriteOperation(tapeAlphabet[i], tapeAlphabet[i]),
                                                                         new ShiftOperation(Shift::NONE),
                                                                         new ShiftOperation(Shift::NONE));
                transitions.push_back(seekBeginning2);
            }
        }

        return "S1";
    }

    void convertOrdinalTransitions(std::vector<OrdinalTransition> ordinalTransitions) {
        for (int i = 0; i < ordinalTransitions.size(); ++i) {
            OrdinalTransition transition = ordinalTransitions[i];
            std::string tempState = transition.nextState + "\'" + std::to_string(i);

            QuadrupleOperation *readWriteOperation = new ReadWriteOperation(transition.read, transition.write);
            QuadrupleOperation *shiftOperation = new ShiftOperation(transition.shift);
            operations.push_back(readWriteOperation);
            operations.push_back(shiftOperation);

            QuadrupleOperation *shiftHistoryOperation = new ShiftOperation(Shift::RIGHT);
            QuadrupleOperation *writeHistoryOperation = new ReadWriteOperation(BLANK, std::to_string((i * 2) + 1));

            QuadrupleOperation *outputOperation1 = new ShiftOperation(Shift::NONE);
            QuadrupleOperation *outputOperation2 = new ShiftOperation(Shift::NONE);

            MultiTapeTransition transition1 = MultiTapeTransition(transition.curState, tempState, readWriteOperation, shiftHistoryOperation, outputOperation1);
            MultiTapeTransition transition2 = MultiTapeTransition(tempState, transition.nextState, shiftOperation, writeHistoryOperation, outputOperation2);

            transitions.push_back(transition1);
            transitions.push_back(transition2);
        }



        // Seek InputTapeStart
        // Copy While Seek Start from InputTape to OutputTape
        // The InputTape Head is on the beggining of the word, as the OutputTape

        auto endState = seekBeginning(finalState[0]);

        std::string firstState = "B" + std::to_string(1);
        std::string firstStateL = firstState + "\'";
        std::string secondState = "B" + std::to_string(2);
        std::string secondStateL = secondState + "\'";

        MultiTapeTransition AfB1L = MultiTapeTransition(endState, firstStateL, new ReadWriteOperation(BLANK, BLANK),
                                                        new ShiftOperation(Shift::NONE),
                                                        new ReadWriteOperation(BLANK, BLANK));

        MultiTapeTransition B1LB1 = MultiTapeTransition(firstStateL, firstState, new ShiftOperation(Shift::RIGHT),
                                                        new ShiftOperation(Shift::NONE),
                                                        new ShiftOperation(Shift::RIGHT));
        MultiTapeTransition B1B2L = MultiTapeTransition(firstState, secondStateL, new ReadWriteOperation(BLANK, BLANK),
                                                        new ShiftOperation(Shift::NONE),
                                                        new ReadWriteOperation(BLANK, BLANK));
        MultiTapeTransition B2LB2 = MultiTapeTransition(secondStateL, secondState, new ShiftOperation(Shift::LEFT),
                                                        new ShiftOperation(Shift::NONE),
                                                        new ShiftOperation(Shift::LEFT));
        MultiTapeTransition B2C1 = MultiTapeTransition(secondState, "C1", new ReadWriteOperation(BLANK, BLANK),
                                                       new ShiftOperation(Shift::NONE),
                                                       new ReadWriteOperation(BLANK, BLANK));
        transitions.push_back(AfB1L);
        transitions.push_back(B1LB1);
        transitions.push_back(B1B2L);
        transitions.push_back(B2LB2);
        transitions.push_back(B2C1);
        for (int i = 0; i < tapeAlphabet.size(); i++) {
            if (tapeAlphabet[i] != BLANK) {

                MultiTapeTransition t1 = MultiTapeTransition(firstState, firstStateL,
                                                             new ReadWriteOperation(tapeAlphabet[i], tapeAlphabet[i]),
                                                             new ShiftOperation(Shift::NONE),
                                                             new ReadWriteOperation(BLANK, tapeAlphabet[i]));
                MultiTapeTransition t2 = MultiTapeTransition(secondState, secondStateL,
                                                             new ReadWriteOperation(tapeAlphabet[i], tapeAlphabet[i]),
                                                             new ShiftOperation(Shift::NONE),
                                                             new ReadWriteOperation(tapeAlphabet[i], tapeAlphabet[i]));
                transitions.push_back(t1);
                transitions.push_back(t2);
            }
        }

    }


    std::vector<MultiTapeTransition> getTransitionsFromCurrentState() {
        std::vector<MultiTapeTransition> possibleTransitions;

        for (int i = 0; i < transitions.size(); ++i) {
            if (transitions[i].fromState == currentState) possibleTransitions.push_back(transitions[i]);
        }
        return possibleTransitions;
    }

    bool isStateFinal(std::string currentState) {
        return std::find(finalState.begin(), finalState.end(), currentState) != finalState.end();
    }

    bool isHeadEmpty(Tape tape) {
        return tape.tape[inputTape.head] == BLANK;
    }

    void execute() {
        std::cout << "Executing Turing Machine" << std::endl;
        while (true) {
            auto possibleTransitions = getTransitionsFromCurrentState();
            std::cout << "Current Head " << inputTape.tape[inputTape.head] << " " << inputTape.head << std::endl;
            bool found = false;
            for (int i = 0; i < possibleTransitions.size(); ++i) {
                if (possibleTransitions[i].canExecute(inputTape, historyTape, outputTape)) {
                    possibleTransitions[i].execute(inputTape, historyTape, outputTape);
                    currentState = possibleTransitions[i].toState;
                    possibleTransitions[i].toString();
                    found = true;
                    break;
                }
                found = false;
            }

            if (!found) {
                break;
            }
        }

        if (!isStateFinal(currentState) || !isHeadEmpty(inputTape)) {
            std::cout << "Rejected Input" << std::endl;
        } else if (isStateFinal(currentState) && isHeadEmpty(inputTape)) {
            std::cout << "Accepted Input" << std::endl;
        }
        std::cout << "Finished Execution" << std::endl;

    }

};

int main() {
    OrdinalTuringMachine OTM = OrdinalTuringMachine();
    OTM.transitions[0].toString();
    ReversibleTuringMachineSimulator simulator = ReversibleTuringMachineSimulator({OTM.statesList[OTM.statesList.size() - 1]}, OTM.statesList[0], OTM.input, OTM.tapeAlphabetList, OTM.transitions);
    simulator.execute();
    simulator.inputTape.printTape();
    simulator.historyTape.printTape();
    simulator.outputTape.printTape();
    return 0;
}
