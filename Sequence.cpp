#include "Sequence.h";
#include <iostream>
using namespace std;


void Sequence::selectSort() {
    double smallest;
    int smallestIdx;

    for (int start = 0; start < NUMS_POR_SEC - 1; start++) {
        smallest = nrmlz_numbers[start];
        smallestIdx = start;
        for (int i = start + 1; i < NUMS_POR_SEC; i++) {
            if (smallest > nrmlz_numbers[i]) {
                smallest = nrmlz_numbers[i];
                smallestIdx = i;
            }
        }
        nrmlz_numbers[smallestIdx] = nrmlz_numbers[start];
        nrmlz_numbers[start] = smallest;
    }
}

void Sequence::bubbleSort() {
    bool swapped;
    do {
        swapped = false;
        for (int i = 0; i < NUMS_POR_SEC - 1; i++) {
            if (nrmlz_numbers[i] > nrmlz_numbers[i + 1]) {
                swapped = true;
                swap(nrmlz_numbers[i], nrmlz_numbers[i + 1]);
            }
        }
    } while (swapped);
}