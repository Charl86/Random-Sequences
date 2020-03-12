/*
 *
 *  main.cpp
 *
 *  José C. Sánchez Curet
 *  Carlos Hernández
 *  Pablo Puig
 *
 *
 *  Purpose: This program generate random columns and rows of numbers (based on user's input)
 *            - Calculate the amount of time the random numbers on each row take to be generated
 *            - Pick the maximum number per row to then normalized all the random numbers
 *            - Create a file per random numbers generated and normalized numbers.
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <ctime>
#include <string>

using namespace std;

#define ESPACIO 14

/*
 *
 *  PROTOTYPES
 *
 */

int userSequence();  // Receive user's input to generate rows
string makeSequences(int);  // Produce random sequence and save on file based on user's input
void getSequences(string, int);  // use makeSequences results to normalize sequence and save into another file


/*
 *
 *  main Function
 *
 */

int main() {
    srand((unsigned)time(0));  // Se comienza una nueva semilla.

    int numberOfSeqs;

    numberOfSeqs = userSequence();  // Se asigna el número de secuencias.

    // Esta función toma como argumentos el archivo para las secuencias
    // y el número de secuencias.
    getSequences(makeSequences(numberOfSeqs), numberOfSeqs);

    return 0;
}

/*
 *
 *  userSequence Function
 *
 */

int userSequence() {
    int num_seq;
    cout << "Ingrese el numero de secuencias:" << endl;
    cin >> num_seq;                             // user's input of number of sequences
    return num_seq;
}

/*
 *
 *  makeSequences Function
 *
 */

string makeSequences(int num_sec) {
    string seqFilename;
    cout << endl << "Ingrese el nombre del archivo"
    << " en donde desea guardar las secuencias:" << endl;
    cin >> seqFilename;                                // user's input of filename

    ofstream Secuencias;
    Secuencias.open(seqFilename + ".txt");         // Ajusta el tipo del archivo.

    Secuencias << "Data ID    ";
    for (int numsPerSeq = 1; numsPerSeq <= 10; numsPerSeq++) {
        Secuencias << setw(ESPACIO - 1) << "No. " << numsPerSeq;
    }                                                // Producing time it takes to produce sequences
    Secuencias << setw(ESPACIO) << "Clicks" << setw(ESPACIO) << "Numero Mayor" << endl;
    Secuencias << string(180, '=') << endl;

    for (int i = 1; i <= num_sec; i++) {
        Secuencias << "Secuencia #" << i;
        int mayor = -1;
        for (int j = 1; j <= 10; j++) {                 // 10 es el número de núms. rands. por secs.
            int random_number = rand();

            if (random_number > mayor) {
                mayor = random_number;
            }
            Secuencias << setw(ESPACIO) << random_number;
        }
        Secuencias << setw(ESPACIO) << "{Clicks}";
        Secuencias << setw(ESPACIO) << mayor;
        if (i != num_sec) {Secuencias << endl;}
    }
    Secuencias.close();
    return seqFilename;
}

/*
 *
 *  getSequences Function
 *
 */

void getSequences(string secFileName, int num_sec) {
    fstream Secuencias;
    Secuencias.open(secFileName + ".txt");            // Ajusta el tipo del archivo.

    string nrmlzFileName;  // Nombre del archivo para las secuencias normalizadas.
    cout << endl << "Ingrese el nombre del archivo"
    << " en donde desea guardar las secuencias normalizadas:" << endl;
    cin >> nrmlzFileName;

    ofstream Normalized;  // Se crea un objeto para el archivo de las secs. normalizadas
    Normalized.open(nrmlzFileName + ".txt");  // y se crea el archivo según el nombre provisto.

    // Se la categoría de identificación de las secuencias.
    Normalized << "Data ID    ";

    // Por cada número de las secuencias, se crea una categoría para los mismos.
    // E.g. No. 1, No. 2, No. 3, ...
    for (int numsPerSeq = 1; numsPerSeq <= 10; numsPerSeq++) {
        Normalized << setw(ESPACIO - 1) << "No. " << numsPerSeq;
    }
    // Se insertan las categorías para los clicks y los números mayores
    Normalized << setw(ESPACIO) << "Clicks" << setw(ESPACIO) << "Numero Mayor" << endl;
    
    // Se inserta una línea para separar las categorías de la data.
    Normalized << string(180, '=') << endl;
    
    // Normalizar números por secuencia.
    for (int n = 1; n <= num_sec; n++) {
        Normalized << "Secuencia #" << n;  // Se inserta el número de la secuencia.
        
        double mayor;
        // Va al principio de la enésima secuencia.
        Secuencias.seekg(181 * (n + 1), ios::beg);
        Secuencias.seekg(175, ios::cur);  // Va a donde se encuentra el número mayor.
        Secuencias >> mayor;
        
        // Va al principio de la enésima secuencia.
        Secuencias.seekg(181 * (n + 1), ios::beg);
        Secuencias.seekg(20, ios::cur);  // Va al primero número de la enésima secuencia.

        double currNum;
        for (int x = 1; x <= 10; x++) {
            Secuencias >> currNum;  // Se lee el número x de la secuencia n.
            // Se guarda la división del número x y el número mayor de la secuencia
            Normalized << setw(ESPACIO) << currNum/mayor;  // en el archivo del objeto 'Normalized'.
        }
        Normalized << setw(ESPACIO) << "{Clicks}";  // Se insertan los clicks.
        Normalized << setw(ESPACIO) << mayor;  // Se coloca el número mayor otra vez?
        if (n != num_sec) {Normalized << endl;}  // Si se está interando por la última
                                                // secuencia, entonces no insertar una línea
                                               // en blanco (al final).
    }
    Secuencias.close();
    Normalized.close();
}
