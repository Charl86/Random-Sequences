#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <ctime>

using namespace std;

#define ESPACIO 10

string getSequence();
void makeSequences(string, int);
void nrmlzSequences(string, int);


int main() {
    srand((unsigned)time(0));

    int num_seq;
    string fileName;

    cout << "Ingrese el numero de secuencias:" << endl;
    cin >> num_seq;

    fileName = getSequence();

    makeSequences(fileName, num_seq);
    nrmlzSequences(fileName, num_seq);

    return 0;
}


string getSequence() {
    string seqFilename;

    cout << endl << "Ingrese el nombre del archivo"
    << " en donde desea guardar las secuencias:" << endl;
    cin >> seqFilename;

    return seqFilename;
}


void makeSequences(string fileN, int num_sec) {
    ofstream Secuencias;
    Secuencias.open(fileN + ".txt");  // Ajusta el tipo del archivo.


    for (int i = 1; i <= num_sec; i++) {
        Secuencias << "Secuencia " << i;
        int mayor = -1;
        for (int j = 1; j <= 10; j++) {  // 10 es el número de núms. rands. por secs.
            int random_number = rand();

            if (random_number > mayor) {
                mayor = random_number;
            }
            Secuencias << setw(ESPACIO) << random_number;
        }
        Secuencias << setw(ESPACIO) << "{Clicks}";
        Secuencias << setw(ESPACIO) << mayor;
        Secuencias << endl;
    }
    Secuencias.close();
}


void nrmlzSequences(string fileN, int num_sec) {
    fstream Secuencias;
    Secuencias.open(fileN + ".txt");  // Ajusta el tipo del archivo.

    ofstream Normalized;
    Normalized.open("Secuencias_Normalizadas.txt");

    string nameOfSeq;
    double randNum;

    // Debugging:
    string some_string;
    Secuencias.seekg(72L + 19L + 20L + 10L, ios::beg);
    Secuencias >> some_string;
    cout << endl << some_string;

    // Normalizar números por secuencia.
    // while (!(Secuencias.eof())) {
    //     for (int i = 1; i <= num_sec; i++) {
    //         Secuencias >> nameOfSeq;
    //         Normalized << "Secuencia #" << i;
    //         for (int j = 1; j <= 10; j++) {
    //             Secuencias >> randNum;
    //             // Normalized << setw(ESPACIO) << randNum/mayor;
    //         }
    //     }

    // }
    Secuencias.close();
    Normalized.close();
}
