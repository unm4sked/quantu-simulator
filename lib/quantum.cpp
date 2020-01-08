#include "quantum.h"
#include <math.h>
#include <iostream>

struct QuantumComputer {
    int registerSize;
    double *probability;
    int baseVectorsCount;
};

int integerToBinary(int num) {
    if (num == 0) {
        return 0;
    }
    if (num == 1) {
        return 1;
    }
    return (num % 2) + 10 * integerToBinary(num / 2);
}

int calculateBaseVectorCount(double probability[], int regSize) {
    int count = 0;

    for (int i = 0; i < (int) pow(regSize, 2); i++) {
        if ((double) probability[i] != 0.0) {
            count++;
        }
    }

    return count;
}

void validateArraySize(int arrSize, int regSize) {
    if (regSize < 1) {
        printf("[ERROR] Register size cannot be less than 1");
        exit(1);
    }

    if (arrSize != pow(regSize, 2)) {
        printf("[ERROR] Invalid Register arr with []Probability");
        exit(1);
    }
}

void validateProbability(double probability[], int regSize) {
    double result = 0.0;

    for (int i = 0; i < (int) pow(regSize, 2); i++) {
        result += pow(sqrt(fabs(probability[i])), 2);
    }

    if (result != 1.0) {
        printf("[ERROR] Probability should be equal 1");
        exit(1);
    }
}

struct QuantumComputer initialQuantumRegisters(int regSize, double probability[],int arrSize) {
    validateArraySize(arrSize, regSize);
    validateProbability(probability, regSize);

    struct QuantumComputer quantumComputer = {
            .registerSize = regSize,
            .probability = probability,
            .baseVectorsCount = calculateBaseVectorCount(probability, regSize)
    };

    return quantumComputer;
}

void viewProbability(struct QuantumComputer *qc) {
    std::cout << "\nVector with probabilities {";
    for (int i = 0; i < (int) pow(qc->registerSize, 2); i++) {
        printf("[%.4f]", qc->probability[i]);
    }
    std::cout << "}\n";
}

void viewQubitInMathExpression(struct QuantumComputer *qc) {
    printf("\nQubit in expression: ");

    for (int i = 0; i < (int) pow(qc->registerSize, 2); i++) {
        if (qc->probability[i] != 0) {
            if(qc->probability[i] == 1.00) {
                printf("|%d> ", integerToBinary(i));
            } else {
                printf("%.4f |%d> ", qc->probability[i], integerToBinary(i));
            }
        }
    }
}

void quantum::simulate() {
    int registerSize = 2;
    double probability[] = {0.0, 0.0, 1.0, 0.0 };
    auto arrSize = std::size(probability);
    struct QuantumComputer qc = initialQuantumRegisters(registerSize, probability,arrSize);
    viewQubitInMathExpression(&qc);
    viewProbability(&qc);
}