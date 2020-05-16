#ifndef SEQUENCE_H
#define SEQUENCE_H
#include <iostream>
#include <fstream>

using namespace std;


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

int userSequence();  // Devuelve el número de secuencias a ser creadas (o leidas).
void makeFilenames(fstream &, fstream &, bool &, int &);  // Crea los archivos.
void makeSequences(fstream &, int, Sequence []);  // Crea las secuencias.
void getSequences(fstream &, fstream &, int, Sequence []);  // Normaliza las secuencias.

// Nuevas funciones implementadas:
double calcDeviation(double [], double);  // Calcula la desviación estándar.
string lowerCase(string);  // Devuelve el string provisto en lowercase.
void readSequences(fstream &, int, Sequence []);  // Lee las secuencias de un archivo existente.
bool askReadFile();  // Pregunta si se desea leer un archivo existente o crear uno nuevo para las secuencias.
int countLines(fstream &);

// Nuevas nuevas funciones implementadas:
void outSortedArray(Sequence [], int, fstream &, bool =true);
void selectionSort(Sequence [], int, fstream &);
void bubbleSort(Sequence [], int, fstream &);

#endif
