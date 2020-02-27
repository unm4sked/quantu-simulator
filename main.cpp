#include <iostream>
#include "lib/quantum.h"

using namespace quantum;

int main() {

    int numberOfQubits = 3;
    double probability[] = {4.0, 0.0, 3.0, 0.0, 4.0, 0.0, 3.0, 0.0};

    auto arrSize = std::size(probability);
    struct QuantumComputer qc = QuantumComputer(numberOfQubits, probability, arrSize);

    qc.normalizeRegister();
    qc.viewProbability();
    qc.resetState();
    qc.viewProbability();
    qc.viewQubitsInMathExpression();

    return 0;
}
