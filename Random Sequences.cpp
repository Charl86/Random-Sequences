/*
    Carlos A. Hernández

    Este programa se encarga de crear (o leer) un archivo de secuencias random. Cada
    secuencia tendrá generalmente 10 números y la cantidad de secuencias es indicada
    por el usuario. Luego de las secuencias random, se crea un nuevo archivo en donde
    las secuencias van a ser normalizadas desplegadas, seguidas por la media y la desviación
    estándar de la secuencia.
*/

#include "Sequence.h"
// #include <iostream>
// #include <iomanip>
// #include <fstream>
// #include <cmath>
#include <ctime>
// #include <string>
// #include <sys/time.h>

using namespace std;


// #define ESPACIO 12
// #define NUMS_POR_SEC 10
// #define TABLA_W 30


// int userSequence();  // Devuelve el número de secuencias a ser creadas (o leidas).
// void makeFilenames(fstream &, fstream &, bool &, int &);  // Crea los archivos.
// void makeSequences(fstream &, int, Sequence []);  // Crea las secuencias.
// void getSequences(fstream &, fstream &, int, Sequence []);  // Normaliza las secuencias.

// // Nuevas funciones implementadas:
// double calcDeviation(double [], double);  // Calcula la desviación estándar.
// string lowerCase(string);  // Devuelve el string provisto en lowercase.
// void readSequences(fstream &, int, Sequence []);  // Lee las secuencias de un archivo existente.
// bool askReadFile();  // Pregunta si se desea leer un archivo existente o crear uno nuevo para las secuencias.
// int countLines(fstream &);

// // Nuevas nuevas funciones implementadas:
// void outSortedArray(Sequence [], int, fstream &, bool =true);
// void selectionSort(Sequence [], int, fstream &);
// void bubbleSort(Sequence [], int, fstream &);


int main() {
    srand((unsigned)time(0));  // Comienza una nueva semilla para los números randoms.

    int numberOfSeqs;  // Número de secuencias a crear (o leer).
    bool readFile;  // 'true' si se va a leer un archivo existente.
    fstream SeqsFile;  // fstream object para las secuencias random.
    fstream NormlicedFile;  // fstream object para las secuencias normalizadas.

    /* Se le pregunta al usuario cúantas secuencias se van a leer (o a crear), y
    se guarda en ésta variable. */
    numberOfSeqs = userSequence();

    Sequence Secuencias[numberOfSeqs];

    makeFilenames(SeqsFile, NormlicedFile, readFile, numberOfSeqs);  // Crea los archivos.

    if (readFile)  // Si readFile es cierto; es decir, si se va a leer un archivo
        // se leen los archivos.
        readSequences(SeqsFile, numberOfSeqs, Secuencias);
    else
        /* De lo contrario, crear un nuevo archivo y crear nuevas secuencias
        / dentro del mismo. */
        makeSequences(SeqsFile, numberOfSeqs, Secuencias);

    // Normalizar las secuencias.
    getSequences(SeqsFile, NormlicedFile, numberOfSeqs, Secuencias);

    // Cerrar los archivos.
    SeqsFile.close();
    NormlicedFile.close();
    return 0;
}
