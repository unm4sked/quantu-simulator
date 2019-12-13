#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

int calculateBaseVectorCount(double probability[],int regSize){

    int count = 0;

    for(int i = 0 ; i < (int)pow(regSize,2); i++) {
        if((double)probability[i] != 0.0) {
            count++;
        }
    }

    return count;
}

void validateArraySize(double probability[],int regSize) {


    if (regSize<1) {
        printf("[ERROR] Register size cannot be less than 1");
        exit(1);
    }

    int n = sizeof(probability);
    if(n != pow(regSize,2)){
        printf("[ERROR] Invalid Register arr with []Probability");
        exit(1);
    }

}

void validateProbability(double probability[],int regSize){
    double result = 0.0;

    for(int i = 0 ; i < (int)pow(regSize,2); i++) {
        result += pow(fabs(probability[i]),2);
    }

    if(result != 1.0) {
        printf("[ERROR] Probability schould be equal 1");
        exit(1);
    }
}

struct QuantumComputer initialQuantumRegisters(int regSize, double probability[]) {

    validateArraySize(probability,regSize);
    validateProbability(probability,regSize);

    struct QuantumComputer quantumComputer = {
            .baseVectorsCount = calculateBaseVectorCount(probability,regSize),
            .registerSize = regSize,
            .probability = probability
    };

    return quantumComputer;
}

void viewProbability(struct QuantumComputer *qc) {
    printf("\nVector with probabilities {");
    for(int i = 0 ; i < (int)pow(qc->registerSize,2); i++) {
        printf("[%.4f]", qc->probability[i]);
    }
    printf("}\n");
}

void viewQubitInMathExpression(struct QuantumComputer *qc) {
    printf("\nQubit in expression: ");

    for(int i = 0 ; i < (int)pow(qc->registerSize,2); i++) {
        if(qc->probability[i] != 0) {
            printf("%.4f|%d> ",qc->probability[i],integerToBinary(i));

        }
    }
}

int main() {

    int registerSize = 2;
    double probability[] = {0,0,1,0};
    struct QuantumComputer qc = initialQuantumRegisters(registerSize,&probability);
    viewQubitInMathExpression(&qc);
    viewProbability(&qc);
    return 0;
}
