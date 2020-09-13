#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


const int NUMS_PER_SEC = 10;  // Amount of numbers per sequence.

struct Sequence {  // Sequence struct
    std::string dataID;  // dataID member, to identify sequence.
    double greatest;  // Greatest number of sequence.
    double mean;  // Mean value of sequence.
    double stdDev;  // Standard deviation for normalized sequence.
    double clicks;  // Performance speed.
    double rand_numbers[NUMS_PER_SEC];  // Randomly generated numbers.
    double nrmlz_numbers[NUMS_PER_SEC];  // Normalized numbers.

    // Methods:
    void selectSort();
    void bubbleSort();
};

/* Asks user how many sequences are to be read or created. Returns that value for other functions
to use. */
int userSequence();

/* Asks user the name of files in which to save the randomly-generated sequences and their normalizations.
Creates files with given names. Calls function 'readFile' that asks user whether to read from an existin
file or create a new file with randomly-generated sequences. */
void makeFilenames(fstream &, fstream &, bool &, int &);

/* Creates randomly-generated sequences if instructed so. Saves each sequence in a sequences vector.
Outputs sequences to fstream object file associated with the random sequences. Finds greatest number
per sequence and stores it in sequence object member. */
void makeSequences(fstream &, int, vector <Sequence> &);

/* Reads sequences from random sequences file. Finds the smallest number between all sequences and saves
its parent sequence's coordinates in the sequences array. Normalizes each sequences using the greatest number
for the respective sequence and saves the sequences in an array. Also computes the standard deviation and
mean value per sequence. */
void getSequences(fstream &, fstream &, int, vector <Sequence> &);

/* Computes standard deviation given an array of numbers and their mean value. */
double calcDeviation(double [], double);

/* Returns parameter converted to lowercase. */
string lowerCase(string);

/* Reads random sequences from an existing file and stores them in sequence objects. */
void readSequences(fstream &, int &, vector <Sequence> &);

/* Asks if sequences are to be read or created and returns answer for other functions to use. */
bool askReadFile();

/* Uses Selection Sort algorithm to sort parameter array using the provided int parameter as sort key.
Displays time taken to sort array. */
void selectionSort(vector <Sequence>, int, fstream &);

/* Uses Bubble Sort algorithm to sort parameter array using the provided int parameter as sort key.
Displays time taken to sort array. */
void bubbleSort(vector <Sequence>, int, fstream &);

/* Receives as parameter the ordered array from the previous two functions and outputs them to file
object passed in, if not before calling the selection sort method or the bubble sort method on each
sequence to sort them right before output. Display average time taken to sort each sequence internally. */
void outSortedArray(vector <Sequence>, int, fstream &, bool =true);


#endif
