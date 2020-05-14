#ifndef SEQUENCE_H
#define SEQUENCE_H

struct Sequence {
    string dataID;
    static const int NUMS_POR_SEC = 10;
    double rand_numbers[NUMS_POR_SEC];
    double mayor;
    double media;
    double stdDev;
    double clicks;
    double nrmlz_numbers[NUMS_POR_SEC];

    // Métodos:
    Sequence();
    void selectSort();
    void bubbleSort();
};

#endif
