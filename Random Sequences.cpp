/*
    Carlos A. Hernández

    Este programa se encarga de crear (o leer) un archivo de secuencias random. Cada
    secuencia tendrá generalmente 10 números y la cantidad de secuencias es indicada
    por el usuario. Luego de las secuencias random, se crea un nuevo archivo en donde
    las secuencias van a ser normalizadas desplegadas, seguidas por la media y la desviación
    estándar de la secuencia.
*/


#include "Sequence.h"
#include <ctime>
#include <vector>


int main() {
    srand((unsigned)time(0));  // Comienza una nueva semilla para los números randoms.

    int numberOfSeqs;  // Número de secuencias a crear (o leer).
    bool readFile;  // 'true' si se va a leer un archivo existente.
    fstream SeqsFile;  // fstream object para las secuencias random.
    fstream NormlicedFile;  // fstream object para las secuencias normalizadas.

    /* Se le pregunta al usuario cúantas secuencias se van a leer (o a crear), y
    se guarda en ésta variable. */
    numberOfSeqs = userSequence();

    // Sequence Secuencias[numberOfSeqs];  // Se crea el arreglo de structs tipo 'Sequence'.
    vector <Sequence> Secuencias(0);

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
