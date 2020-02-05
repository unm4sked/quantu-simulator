#ifndef UNTITLED_QUANTUM_H
#define UNTITLED_QUANTUM_H

#include <vector>

namespace quantum {
    struct QuantumComputer {
        int registerSize;
        int baseVectorsCount;
        bool isNormalize;
        bool isMeasured;
        std::vector<double> baseVector;

        QuantumComputer(int regSize, double probability[], int arrSize);

        void countNonZeroBaseVector();

        void resetState();

        void viewProbability();

        void viewQubitsInMathExpression();

        static void validateArraySize(int arrSize, int regSize);

        void validateProbability();

        void normalizeRegister();

        void measure();
    };
}

#endif