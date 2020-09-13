﻿#include "Sequence.h"
#include <iomanip>
#include <string>
#include <fstream>
#include <sys/time.h>
#include <cmath>
#include <vector>


#define ESPACIO 12  // Amount of padding space between numbers
#define TABLA_W 30  // Amount of padding space for furthermost values.

// Selection Sort method for Sequence class
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

// Bubble Sort method for Sequence class
void Sequence::bubbleSort() {
    bool swapped;
    do {
        swapped = false;
        for (int i = 0; i < NUMS_POR_SEC - 1; i++) {
            if (nrmlz_numbers[i] > nrmlz_numbers[i + 1]) {
                swapped = true;
                std::swap(nrmlz_numbers[i], nrmlz_numbers[i + 1]);
            }
        }
    } while (swapped);
}

// Get amount of sequences
int userSequence() {
    int num_seq;  // Number of sequences.
    cout << "Provive the number of sequences to be read or created:" << endl;
    cin >> num_seq;  // Save user input in variable
    return num_seq;  // and return it.
}

// Create files
void makeFilenames(fstream &fileSeqs, fstream &fileNorms, bool &readFile, int &numSeqs) {
    string seqFilename;  // Filename wherein to save randomly generated sequences.
    string normlicedFilename;  // Filename in which to save normalized sequences.

    if (askReadFile()) {  // If user wants to read sequences from existing file.
        readFile = true;  // Set flag as true and ask for filename.
        cout << endl << "Type in the name of file you wish for the program to read:" << endl;
    }
    else {
        readFile = false;  // Else set flag as false.
        cout << endl << "Type in filename"
        << " in which to save the random sequences:" << endl;
    }
    cin >> seqFilename;  // Save sequence filename.

    if (readFile) {  // If sequences are to be read
        // Open file without erasing its content.
        fileSeqs.open(seqFilename + ".txt", fstream::out | fstream::in);

        // Validate existence of file.
        while (!fileSeqs.is_open()) {  // If file doesn't exist, notify user
            cout << endl << "The file provided does not exist. Make sure that the file"
            << endl << "exist or that its name be typed correctly." << endl;

            // Ask user again for filename.
            cin >> seqFilename;
            fileSeqs.open(seqFilename + ".txt", fstream::out | fstream::in);
        }
    }
    else {  // If not reading a file
        // Create new file with provided name or erase content of equally named file.
        fileSeqs.open(seqFilename + ".txt", fstream::out | fstream::in | fstream::trunc);
    }

    // Ask where to save the normalized sequences.
    cout << endl << "Provide the name of the file"
    << " in which the normalized sequences will be saved:" << endl;
    cin >> normlicedFilename;  // Save input in variable
    fileNorms.open(normlicedFilename + ".txt", fstream::out);  // Create file with said name.
}

// Ask user if random sequences file is to be read
bool askReadFile() {
    string answer;  // User's answer.

    do {
        // Ask user and save answer in variable.
        cout << endl << "Do you wish to read sequences from an existing file?" << endl;
        cin >> answer;

        // Turn answer to lowercase for easier validation.
        answer = lowerCase(answer);

        // If answer is yes or any variation, return true
        if (answer == "yes" || answer == "y"
            || answer == "si" || answer == "1")
                return true;
        // If the answer is no, return false
        else if (answer == "no" || answer == "n" || answer == "0")
                return false;
        else  // If answer isn't any of the possible answers, let user know.
            cout << endl << "Please, only answer with a \"yes\" or \"no\".";
    } while (1);  // Repeat forever until user provides valid answer.
}

// Create random sequences
void makeSequences(fstream &fileSeqs, int num_sec, vector <Sequence> &arrSecuencias) {
    arrSecuencias.resize(num_sec);  // Resize vector of sequences with provided amount.

    struct timespec start, end;  // Variables to measure performance speed.
    double clicks;  // Variable to save performance speed.

    // For each sequence index up to amount of sequences
    for (int i = 0; i < num_sec; i++) {
        // Insert and save dataID.
        fileSeqs << setw(9) << "dataID#" << (i + 1);
        arrSecuencias[i].dataID = "dataID#" + to_string(i + 1);

        // Initialize variable in order to find greatest number in sequence.
        int mayor = -1;
        clock_gettime(CLOCK_MONOTONIC, &start);  // Start stopwatch.
        ios_base::sync_with_stdio(false);
        for (int j = 0; j < NUMS_POR_SEC; j++) {  // For each number index in sequence
            int random_number = rand();  // Generate random number.

            // If created number is greater than previously greatest number
            if (random_number > mayor)
                mayor = random_number;  // Make that one the greatest.

            // Insert some padding space.
            fileSeqs << setw(ESPACIO) << random_number;
            // Save created number in 2D sequences array, with coordinates (i, j).
            arrSecuencias[i].rand_numbers[j] = random_number;
        }
        clock_gettime(CLOCK_MONOTONIC, &end);  // Stop stopwatch. (the redundancy)

        // Compute performance speed.
        clicks = (((end.tv_sec - start.tv_sec) * 1e9) + (end.tv_nsec - start.tv_nsec)) * 1e-9;

        // Output clicks to file.
        fileSeqs << setw(ESPACIO) << fixed << clicks << defaultfloat;
        // Output greatest number.
        fileSeqs << setw(ESPACIO) << mayor;

        // Save performance speed in sequence object.
        arrSecuencias[i].clicks = clicks;

        // Save greatest number in sequence object.
        arrSecuencias[i].mayor = mayor;

        // If not iterating through the last line, insert a new line.
        if (i + 1 != num_sec) {fileSeqs << endl;}
    }
}

// Read sequences from file
void readSequences(fstream &fileSeqs, int &num_sec, vector <Sequence> &arrSecuencias) {
    string id_text;  // Data id.
    int random_number;  // Current random number of sequence.
    double clicks;  // Performance speed.
    int mayor;  /// Greatest number per sequence.

    int line_counter = 0;
    // While not end of file and counter less than amount of sequences
    while (fileSeqs >> id_text && line_counter < num_sec) {
        // Create new sequence and append to vector.
        Sequence new_sequence;
        arrSecuencias.push_back(new_sequence);

        // Save data id in sequence object.
        arrSecuencias[line_counter].dataID = id_text;

        // For each random number index in sequence
        for (int j = 0; j < NUMS_POR_SEC; j++) {
            // Read current random number
            fileSeqs >> random_number;

            // Store random number in sequence object random numbers array.
            arrSecuencias[line_counter].rand_numbers[j] = static_cast<double>(random_number);
        }
        // Read performance speed and greatest number.
        fileSeqs >> clicks;
        fileSeqs >> mayor;

        // Store clicks and greatest number in respective sequence object members.
        arrSecuencias[line_counter].clicks = clicks;
        arrSecuencias[line_counter].mayor = static_cast<double>(mayor);

        line_counter += 1;
    }

    // If line counter is less than amount of sequences
    if (line_counter < num_sec) {
        // Let user know than only ${line_counter} amount of sequences were read.
        cout << endl <<"Only " << line_counter << " of the " << num_sec
        << " stated sequences were read" << endl;
        num_sec = line_counter;
    }
}

// Process and normalize sequences
void getSequences(fstream &fileSeqs, fstream &fileNorms, int num_secs, vector <Sequence> &arrSecuencias) {
    // Insert header in out file.
    fileNorms << setw(10) << "dataID";
    for (int i = 0; i < NUMS_POR_SEC; i++)
        fileNorms << setw(11) <<"Value_" << (i + 1);

    // Headers for mean value and standard deviation:
    fileNorms << setw(11) << "Mean" << setw(12) << "StdDev";

    // Output divisory time:
    fileNorms << endl << string(155, '-') << endl;

    // Intitialzie lowest number to greatest number.
    double menor = arrSecuencias[0].mayor;
    int menor_pos[2] = {0};
    // For each sequence index
    for (int n = 0; n < num_secs; n++) {
        // Insert sequence data id.
        fileNorms << setw(9 - (to_string(n + 1).length() - 1)) << arrSecuencias[n].dataID;

        // Store greatest number.
        double mayor = arrSecuencias[n].mayor;

        // Initialize mean value, deviation and
        double media = 0.0;
        double deviation = 0.0;
        double nrmlzCurrNum;
        // For each number index per sequence
        for (int x = 0; x < NUMS_POR_SEC; x++) {
            // Compute normalized value.
            nrmlzCurrNum = arrSecuencias[n].rand_numbers[x]/(mayor);

            media += nrmlzCurrNum;  // Add to mean.

            /* If computed number is greater than greatest number, make it the greatest and record
            its position. */
            if (menor > nrmlzCurrNum) {
                menor = nrmlzCurrNum;
                menor_pos[0] = n;
                menor_pos[1] = x;
            }

            // Save normalized value.
            arrSecuencias[n].nrmlz_numbers[x] = nrmlzCurrNum;
            // Output normalized value to file.
            fileNorms << setw(ESPACIO) << nrmlzCurrNum;
        }
        /* Compute mean value. */
        media = media/NUMS_POR_SEC;

        // .
        deviation = calcDeviation(arrSecuencias[n].nrmlz_numbers, media);

        // Store values in respective sequence object.
        arrSecuencias[n].media = media;
        arrSecuencias[n].stdDev = deviation;

        // Output values.
        fileNorms << setw(ESPACIO) << arrSecuencias[n].media;
        fileNorms << setw(ESPACIO) << arrSecuencias[n].stdDev;
        // If not iterating through last line, insert a new line.
        if (n + 1 != num_secs) { fileNorms << endl; }
        else {
            // If iterating through last line, output lowest number of all sequences.
            fileNorms << string(2, '\n') << "Minimum value of all sequences is: " << menor << ", found"
            << " on column " << (menor_pos[1] + 1) << " of sequence number " << (menor_pos[0] + 1);
        }
    }

    // Display 'ALGORITHM' header in terminal.
    cout << endl << "ALGORITHM" << setw(TABLA_W + 20) << "Time taken to order sequences array using the mean value"
    << setw(TABLA_W + 15) << "Average time taken to order each sequence";

    // Order array of sequences using the respective algorithms.
    selectionSort(arrSecuencias, num_secs, fileNorms);
    bubbleSort(arrSecuencias, num_secs, fileNorms);
}

// Compute standard deviation
double calcDeviation(double randomSeq[], double seq_mean) {
    double std_deviation = 0.0;  // Se inicializa la desviación.

    // For each normalized number index of sequence
    for (int i = 0; i < NUMS_POR_SEC; i++) {
        // Compute raw deviation.
        std_deviation += pow(randomSeq[i] - seq_mean, 2);
    }
    // Compute standard deviation and return it.
    std_deviation = sqrt(std_deviation/NUMS_POR_SEC);
    return std_deviation;
}

// Selection sort algorithm to sort array of sequences
void selectionSort(vector <Sequence> arrSecuencias, int numsOfSeqs, fstream &fileNorms) {
    struct timespec start, end;  // Variables to operate 'stopwatch'
    double clicks;  // Performance speed.

    clock_gettime(CLOCK_MONOTONIC, &start);  // Start stopwatch.
    ios_base::sync_with_stdio(false);

    // Order sequences array using the mean value as key.
    Sequence smallestMeanSeq;
    int sm_meanIdx;
    for (int start = 0; start < numsOfSeqs - 1; start++) {
        smallestMeanSeq = arrSecuencias[start];
        sm_meanIdx = start;
        for (int i = start + 1; i < numsOfSeqs; i++) {
            if (smallestMeanSeq.media > arrSecuencias[i].media) {
                smallestMeanSeq = arrSecuencias[i];
                sm_meanIdx = i;
            }
        }
        arrSecuencias[sm_meanIdx] = arrSecuencias[start];
        arrSecuencias[start] = smallestMeanSeq;
    }
    clock_gettime(CLOCK_MONOTONIC, &end);  // Stop stopwatch.
    // Compute performance speed.
    clicks = (((end.tv_sec - start.tv_sec) * 1e9) + (end.tv_nsec - start.tv_nsec)) * 1e-9;

    // Display 'SELECTION' header, along with the performance speed.
    cout << endl << "SELECTION" << setw(TABLA_W + 3) << fixed << clicks;

    // Call function to output sequences sorted by Selection Sort.
    outSortedArray(arrSecuencias, numsOfSeqs, fileNorms, false);
}

// Bubble Sort algorithm to sort array of sequences
void bubbleSort(vector <Sequence> arrSecuencias, int numsOfSeqs, fstream &fileNorms) {
    struct timespec start, end;  // Variables to operate 'stopwatch'
    double clicks;  // Performance speed.

    clock_gettime(CLOCK_MONOTONIC, &start);  // Start stopwatch.
    ios_base::sync_with_stdio(false);

    // Sort sequences array using the mean value as key.
    bool swapped;
    do {
        swapped = false;
        for (int i = 0; i < numsOfSeqs - 1; i++) {
            if (arrSecuencias[i].media > arrSecuencias[i + 1].media) {
                swap(arrSecuencias[i], arrSecuencias[i + 1]);
                swapped = true;
            }
        }
    } while (swapped);

    clock_gettime(CLOCK_MONOTONIC, &end);  // Stop stopwatch.

    // Compute clicks.
    clicks = (((end.tv_sec - start.tv_sec) * 1e9) + (end.tv_nsec - start.tv_nsec)) * 1e-9;

    // Display 'BUBBLE' header along with performance speed.
    cout << endl << "BUBBLE" << setw(TABLA_W + 6) << clicks;

    // Output sorted array.
    outSortedArray(arrSecuencias, numsOfSeqs, fileNorms, true);
}

// Output to file sorted array of sequences, and sorting each sequence before output
void outSortedArray(vector <Sequence> arrSecuencias, int numsOfSeqs, fstream &fileNorms, bool bubbleSort) {
    fileNorms << endl << endl;  // Padding lines.

    // If output is bubble sorted array
    if (bubbleSort) {
        // Output Bubble Sort sentence.
        fileNorms << setw(15) << "Sorting with BUBBLE we got:" << endl;
    }
    else  // Output Selection Sort sentence.
        fileNorms << setw(15) << "Sorting with SELECTION we got:" << endl;

    // Output headers for dataID and mean value.
    fileNorms << setw(11) << "dataID" << setw(131) << "Mean" << endl;
    fileNorms << string(144, '-') << endl;  // Divisory line for visual purposes.

    struct timespec start, end;  // Variables to compute performance speed.
    double clicks;  // Performance speed.
    double sumOfClicks = 0.0;  // Sum of all performance speed values.
    for (int i = 0; i < numsOfSeqs; i++) {  // For each sequence index
        clock_gettime(CLOCK_MONOTONIC, &start);  // Start stopwatch.
        ios_base::sync_with_stdio(false);
        if (!bubbleSort) {  // If not bubble sorted
            arrSecuencias[i].selectSort();  // Selection sort the sequence.
        }
        else {  // Else, bubble sort the sequence.
            arrSecuencias[i].bubbleSort();
        }
        clock_gettime(CLOCK_MONOTONIC, &end);  // Stop stopwatch.

        // Compute performance speed
        clicks = (((end.tv_sec - start.tv_sec) * 1e9) + (end.tv_nsec - start.tv_nsec)) * 1e-9;

        sumOfClicks += clicks;  // Add performance speed to sum of all of clicks values.

        fileNorms << setw(13) << arrSecuencias[i].dataID;  // Output dataID of sequence.

        for (int j = 0; j < NUMS_POR_SEC; j++) {  // Output to file numbers in sequence.
            if (j + 1 == NUMS_POR_SEC)
                fileNorms << setw(ESPACIO - 5) << arrSecuencias[i].nrmlz_numbers[j];
            else
                fileNorms << setw(ESPACIO) << arrSecuencias[i].nrmlz_numbers[j];
        }

        // Output mean value of sequence.
        fileNorms << setw(ESPACIO + 3) << arrSecuencias[i].media;

        // If not iterating through the last line, insert a new line.
        if (i + 1 != numsOfSeqs)
            fileNorms << endl;
    }
    if (!bubbleSort) {  // Insert padding space if there's still one more sorting algorithm to output.
        fileNorms << string(2, '\n') << string(144, '-');
        fileNorms << endl << string(144, '-');
    }
    // Display average performance speed value.
    cout << setw(TABLA_W + 18) << sumOfClicks/numsOfSeqs;
}

// Return lowercase parameter
string lowerCase(string word) {
    for (int i = 0; i < word.length(); i++) {
        word[i] = tolower(word[i]);  // Lowercase each character of parameter.
    }
    return word;  // Return lowercase word
}
