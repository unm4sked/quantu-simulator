#include "quantum.h"
#include <math.h>
#include <iostream>
#include <vector>

struct QuantumComputer {
    int registerSize;
    int baseVectorsCount;
    bool isNormalize;
    bool isMeasured;
    std::vector<double> baseVector;

    QuantumComputer(int regSize, double probability[], int arrSize) {
        this->registerSize = regSize;
        this->baseVectorsCount = 0;
        this->isNormalize = false;
        this->isMeasured = false;

        validateArraySize(arrSize, regSize);

        for (int i = 0; i < arrSize; i++) {
            baseVector.push_back(probability[i]);
        };

        validateProbability();
        countNonZeroBaseVector();

    };

    void countNonZeroBaseVector() {
        for (auto x: this->baseVector) {
            if ((double) x != 0.0) {
                this->baseVectorsCount++;
            }
        }
    }

    void resetState() {
        std::vector<double>::iterator it;
        for (it = this->baseVector.begin(); it < this->baseVector.end(); it++) {
            *it = 0.0;
        }
        this->baseVector.at(0) = 1;
    }

    static int integerToBinary(int num) {
        if (num == 0) {
            return 0;
        }
        if (num == 1) {
            return 1;
        }
        return (num % 2) + 10 * integerToBinary(num / 2);
    }

    void viewProbability() {
        std::cout << "\nVector with probabilities {";
        for (auto x: this->baseVector) {
            printf("[%.4f]", x);
        }
        std::cout << "}\n";
    }

    void viewQubitInMathExpression() {
        if (!this->isNormalize) {
            std::cout
                    << "Base Vector is not in normalize state. To view qubit you should normalize it before.  Use .normalize() function for that"
                    << std::endl;
        } else {
            printf("\nQubit in expression: ");
            int i = 0;
            for (auto x: this->baseVector) {
                if (x != 0) {
                    int binary = integerToBinary(i);
//                    std::string binaryStringValue = std::to_string(binary);  TODO: Refactor printing of qubit in qxpression  for register(2) -> |00> not |0>
                    if (x == 1.00) {
                        if (binary == 0) {
                            std::string tmp = "";
                            for (int i = 0; i < this->registerSize; i++) {
                                tmp += "0";
                            }
                            std::cout << "|" << tmp << ">";
                        } else {
                            printf("|%d> ", binary);
                        }
                    } else {
                        if (binary == 0) {
                            std::string tmp = "";
                            for (int i = 0; i < this->registerSize; i++) {
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

    void validateProbability() {
        double result = 0.0;

        for (auto x: this->baseVector) {
            result += pow(sqrt(fabs(x)), 2);
        }

        if (result != 1.0) {
            printf("[ERROR] Probability should be equal 1, u can normalize vector use .normalize() function for that");
            this->isNormalize = false;
        } else {
            this->isNormalize = true;
        }

    }

    // TODO:  DO IT
    void normalizeRegister() {
        std::cout << "[Here will be function to normalize vector!]" << std::endl;
    }

    // TODO:  DO IT
    void measure() {
        if(this->isMeasured){
            std::cout<<"U cannot measure collapsed qubit"<<std::endl;
            return;
        }
        std::cout << "[Here will be function to measure register!]" << std::endl;

        this->isMeasured = true;
    }
};


void quantum::simulate() {
    int registerSize = 2;
    double probability[] = {0.0, 0.0, 1.0, 0.0};
    auto arrSize = std::size(probability);
    struct QuantumComputer qc = QuantumComputer(registerSize, probability, arrSize);


    qc.resetState();
    qc.viewProbability();
    qc.viewQubitInMathExpression();
}