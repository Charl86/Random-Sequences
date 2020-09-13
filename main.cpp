/*
    This program takes a file of randomly generated sequences and processess them, or
    creates a new file of randomly generated sequences in order to process it. During
    the processing phase this program will normalize the sequences, find the mean value,
    find the standard deviation and sorts them using the Selection Sort and Bubble Sort
    algorithms.
*/

#include "Sequence.h"
#include <ctime>
#include <vector>


int main() {
    srand((unsigned)time(0));  // Start a new random seed using the current time.

    int numberOfSeqs;  // Number of sequences to be read or to be created.
    bool readFile;  // Hold value of true if sequences are to be read.
    fstream SeqsFile;  // fstream object to read random sequences file.
    fstream NormlicedFile;  // fstream object wherein to output processed sequences.

    /* Ask user how many sequences are wanted to be processed and whether or not
    to create said sequences on the spot or read them from an existing file. */
    numberOfSeqs = userSequence();

    // Create a vector of sequences.
    vector <Sequence> Sequences(0);

    makeFilenames(SeqsFile, NormlicedFile, readFile, numberOfSeqs);  // Create files.

    if (readFile)  // If sequences are to be read, call readSequences function
        readSequences(SeqsFile, numberOfSeqs, Sequences);
    else  // Otherwise, create the sequences.
        makeSequences(SeqsFile, numberOfSeqs, Sequences);

    // Normalize sequences.
    getSequences(SeqsFile, NormlicedFile, numberOfSeqs, Sequences);

    // Close files.
    SeqsFile.close();
    NormlicedFile.close();
    return 0;
}
