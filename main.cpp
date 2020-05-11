#include <iostream>
#include <cmath>
#include "lib/quantum.h"

using namespace quantum;

int main() {

    int numberOfQubits = 1;
    double base[] = {0.0, 1.0};
    auto arrSize = std::size(base);
    struct QuantumComputer qc =
            QuantumComputer(numberOfQubits, base, arrSize);
    qc.resetState();
    qc.setValueInRegister(0, 1 / (sqrt(2)));
    qc.setValueInRegister(1, 1 / (sqrt(2)));
    qc.viewProbabilityForBaseVector();

    return 0;
}
