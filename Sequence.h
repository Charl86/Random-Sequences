#ifndef SEQUENCE_H
#define SEQUENCE_H
#include <iostream>

const int NUMS_POR_SEC = 10;

struct Sequence {
    std::string dataID;
    double mayor;
    double media;
    double stdDev;
    double clicks;
    double rand_numbers[NUMS_POR_SEC];
    double nrmlz_numbers[NUMS_POR_SEC];

    // Métodos:
    void selectSort();
    void bubbleSort();
};

#endif
