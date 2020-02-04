#include <iostream>
#include "lib/quantum.h"

using namespace quantum;

int main() {
    int registerSize = 2;
    double probability[] = {4.0, 0.0, 3.0, 0.0};
    auto arrSize = std::size(probability);
    struct QuantumComputer qc = QuantumComputer(registerSize, probability, arrSize);

    qc.normalizeRegister();
    qc.viewProbability();
    qc.resetState();
    qc.viewProbability();
    qc.viewQubitInMathExpression();

    return 0;
}
