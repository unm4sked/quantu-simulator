#include "quantum.h"
#include <cmath>
#include <iostream>
#include <vector>
#include <string>


quantum::QuantumComputer::QuantumComputer(int regSize, double array[], int arrSize) {
    this->registerSize = regSize;
    this->baseVectorsCount = 0;
    this->isNormalize = false;
    this->isMeasured = false;

    validateArraySize(arrSize, regSize);

    for (int i = 0; i < arrSize; i++) {
        baseVector.push_back(array[i]);
    };

    validateProbability();
    countNonZeroBaseVector();
}

void quantum::QuantumComputer::countNonZeroBaseVector() {
    for (auto x: this->baseVector) {
        if ((double) x != 0.0) {
            this->baseVectorsCount++;
        }
    }
}

void quantum::QuantumComputer::resetState() {
    std::vector<double>::iterator it;
    for (it = this->baseVector.begin(); it < this->baseVector.end(); it++) {
        *it = 0.0;
    }
    this->baseVector.at(0) = 1;
}

int integerToBinary(int num) {
    if (num == 0) {
        return 0;
    }
    if (num == 1) {
        return 1;
    }
    return (num % 2) + 10 * integerToBinary(num / 2);
}

void quantum::QuantumComputer::viewValuesInBaseVector() {
    std::cout << "\nVector with values {";
    for (auto x: this->baseVector) {
        printf("[%.4f]", x);
    }
    std::cout << "}\n";
}

void quantum::QuantumComputer::viewQubitsInDiracNotation() {
    if (!this->isNormalize) {
        std::cout
                << "Base Vector is not in normalize state. To view qubit you should normalize it before.  Use .normalizeRegister() function for that"
                << std::endl;
    } else {
        printf("\nQubit in expression: ");
        int i = 0;
        for (auto x: this->baseVector) {
            if (x != 0) {
                int binary = integerToBinary(i);
//                    std::string binaryStringValue = std::to_string(binary);  TODO: Refactor printing of qubit in expression  for register(2) -> |00> not |0>
                if (x == 1.00) {
                    if (binary == 0) {
                        std::string tmp = "";
                        for (int j = 0; j < this->registerSize; j++) {
                            tmp += "0";
                        }
                        std::cout << "|" << tmp << ">";
                    } else {
                        printf("|%d> ", binary);
                    }
                } else {
                    if (binary == 0) {
                        std::string tmp = "";
                        for (int j = 0; j < this->registerSize; j++) {
                            tmp += "0";
                        }
                        std::cout << "|" << tmp << ">";
                    } else {
                        printf("%.4f |%d> ", x, binary);
                    }
                }
            }

            i++;
        }
    }
}

void quantum::QuantumComputer::validateArraySize(int arrSize, int regSize) {
    if (regSize < 1) {
        printf("[ERROR] Register size cannot be less than 1\n");
        exit(1);
    }

    if (arrSize != pow(2, regSize)) {
        printf("[ERROR]\n");
        printf("Failed to initialize the register of qubits, check the size of the base vector and the number of elements in the array\n");
        exit(1);
    }
}

void quantum::QuantumComputer::viewProbabilityForBaseVector(){
    std::cout << "\nVector with probability {";
    for (auto x: this->baseVector) {
        printf("[%.4f]", pow(fabs(x), 2));
    }
    std::cout << "}\n";
}

void quantum::QuantumComputer::validateProbability() {
    double result = 0.0;

    for (auto x: this->baseVector) {
        result += pow(sqrt(fabs(x)), 2);
    }

    if (result != 1.0) {
        printf("[ERROR] Probability should be equal 1, u can normalize vector use .normalizeRegister() function for that\n");
        this->isNormalize = false;
    } else {
        this->isNormalize = true;
    }

}

void quantum::QuantumComputer::normalizeRegister() {
    double vectorLength = 0.0;

    for (auto x: this->baseVector) {
        vectorLength += pow(x, 2);
    }

    vectorLength = sqrt(vectorLength);
    std::vector<double>::iterator it;

    for (it = this->baseVector.begin(); it < this->baseVector.end(); it++) {
        *it = *it / vectorLength;
    }

    this->isNormalize = true;

    std::cout << "Now vector is normalized" << std::endl;

}

// TODO:  Implement logic for chose result
void quantum::QuantumComputer::QuantumComputer::measure() {
    if (this->isMeasured) {
        std::cout << "U cannot measure collapsed qubit" << std::endl;
        return;
    }
    std::cout << "[Here will be function to measure register!]" << std::endl;

    this->isMeasured = true;
}

void quantum::QuantumComputer::extendRegister(int resizeAmount) {
    if (this->registerSize >= resizeAmount) {
        std::cout << "You can only resize your register, not decrease" << std::endl;
        return;
    }

    int sizeOfBaseVector = (int) this->baseVector.size();

    int elementsToAdd = resizeAmount - this->registerSize;
    if (elementsToAdd < 0) {
        std::cout << "Number of Qubits to add must be positive" << std::endl;
        return;
    }

    for (int i = pow(2, this->registerSize); i < pow(2, resizeAmount); i++) {
        this->baseVector.push_back(0);
    }

    this->registerSize = resizeAmount;

    std::cout << "Register resized correctly" << std::endl;
    std::cout << "Number of qubits in register: " << resizeAmount << std::endl;

}

void quantum::QuantumComputer::setValueInRegister(int arrayIndex, double value) {
    if (arrayIndex < 0) {
        std::cout << "Index of value must be positive" << std::endl;
    }

    int sizeOfBaseVector = (int) this->baseVector.size();

    if (arrayIndex >= sizeOfBaseVector) {
        std::cout << "Index of value must be the number between " << 0 << sizeOfBaseVector - 1 << std::endl;
    }

    double oldValue = this->baseVector[arrayIndex];
    double &element = this->baseVector[arrayIndex];

    element = value;
    std::cout << "Value from index \"" << arrayIndex << "\" changed from \"" << oldValue << "\" to \"" << element
              << "\"" << std::endl;

    this->validateProbability();
}

inline const char *boolToString(bool b) {
    return b ? "true" : "false";
}

void quantum::QuantumComputer::displayInfo() {



    std::cout << "*****" << std::endl;
    std::cout << "Information about state" << std::endl;
    std::cout << "Current register size(qubits): " << this->registerSize << std::endl;
    std::cout << "Register is normalized: " << boolToString(this->isNormalize) << std::endl;
    std::cout << "Register is measured: " << boolToString(this->isMeasured) << std::endl;
    std::cout << "Size of baseVector: " << this->baseVector.size() << std::endl;
    std::cout << "Values in baseVector array: " << std::endl;
    int i = 0;
    for (auto x: this->baseVector) {
        printf("  index [%d] value [%.4f] \n",i, x);
        i++;
    }
    std::cout << "*****" << std::endl;
}

