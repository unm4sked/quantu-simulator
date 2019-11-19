#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int *parseInput(char *input);

struct QuantumComputer {
    int noQubits;
    int *registers;
    double *probabilities;
    double result;
};

int convertQubitVectorIndex(long long n) {
    int dN = 0;
    int i = 0;
    int r;

    while (n != 0) {
        r = n % 10;
        n = n / 10;
        dN = dN + r * pow(2, i);
        i = i + 1;
    }
    return dN;
}

int convertStringToInt(char *str) {
    int number;
    sscanf(str, "%d", &number);

    return number;
}

double vectorLength(int *vector, int size) {
    double vectorLength = 0.0;

    for (int i = 0; i < size; i++) {
        vectorLength += (double) pow(vector[i], 2);
    }

    vectorLength = sqrt(vectorLength);

    return vectorLength;
}

void initQuantumComputer(struct QuantumComputer *qc, char* input) {
    int qubits = strlen(input);
    qc->noQubits = qubits;
    qc->registers = parseInput(input);
    qc->probabilities = (double *) malloc((double) pow(2, qubits) * sizeof(double));
    for (int i = 0; i < (int) pow(2, qubits); i++) {
        qc->probabilities[i] = 0.0;
    }
};

void viewProbabilities(struct QuantumComputer *q) {
    printf("\n[Probabilities] [");
    for (int i = 0; i < (int) pow(2, q->noQubits); i++) {
        printf("(%f)", q->probabilities[i]);
    }
    printf("]\n");
}

void viewRegister(struct QuantumComputer *q) {
    printf("\n[Register]\n");
    for (int i = 0; i < (int) pow(2, q->noQubits); i++) {
        printf("[ %d ]\n", q->registers[i]);
    }
    printf("\n");
};


void destroyQuantumComputer(struct QuantumComputer *q) {
    free(q->registers);
    free(q->probabilities);
}


int *parseInput(char *input) {
    for (int i = 1; i < strlen(input) - 1; i++) {
        if (input[i] != '0' && input[i] != '1') {
            printf("Error wrong input alphabet = { 0 , 1}");
            exit(1);
        }
    }
    int numOfQubits = strlen(input);
    int *register_ = (int *) malloc(sizeof(int) * (int) pow(2, numOfQubits));
    for (int i = 0; i < (int) pow(2, numOfQubits); i++) {
        register_[i] = 0;
    }

//    printf("INPUT %s\n", input);
    long number = (long) convertStringToInt(input);
    int index = convertQubitVectorIndex(number);
    register_[index] = 1;
//    printf("INDEX %d\n", index);
    return register_;

};

void measure(struct QuantumComputer *qc) {
    for (int i = 0; i < (int) pow(2, qc->noQubits); i++) {
        double prob = (double) pow(abs(qc->registers[i]), 2);
        qc->probabilities[i] = prob;

        // TODO: MEASURE IT
    }
};

int main() {
    char* input = "111";
    int *reg = parseInput(input);
    struct QuantumComputer quantumComputer;
    initQuantumComputer(&quantumComputer, input);
//    measure(&quantumComputer);
    viewRegister(&quantumComputer);
//    viewProbabilities(&quantumComputer);
//
    destroyQuantumComputer(&quantumComputer);
    return 0;
}