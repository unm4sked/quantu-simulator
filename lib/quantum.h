#ifndef UNTITLED_QUANTUM_H
#define UNTITLED_QUANTUM_H

#include <vector>
#include <string>

namespace quantum {
    struct QuantumComputer {
        int registerSize;
        int baseVectorsCount;
        bool isNormalize;
        bool isMeasured;
        std::vector<double> baseVector;

        QuantumComputer(int regSize, double array[], int arrSize);

        void countNonZeroBaseVector();

        void extendRegister(int size);

        void setValueInRegister(int arrayIndex, double value);

        void displayInfo();

        void resetState();

        void viewValuesInBaseVector();

        void viewProbabilityForBaseVector();

        void viewQubitsInDiracNotation();

        static void validateArraySize(int arrSize, int regSize);

        void validateProbability();

        void normalizeRegister();

        void measure();
    };
}

#endif