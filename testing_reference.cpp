#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <ctime>
#include <string>

using namespace std;

#define ESPACIO 14

void getFilenames(fstream &, fstream &);

void makeSequences(fstream &, int);
void getSequences(fstream &, fstream &, int);
int userSequence();


int main() {
    srand((unsigned)time(0));

    int numberOfSeqs;
    fstream SeqsFile;
    fstream NormlicedFile;

    numberOfSeqs = userSequence();

    getFilenames(SeqsFile, NormlicedFile);
    makeSequences(SeqsFile, numberOfSeqs);
    getSequences(SeqsFile, NormlicedFile, numberOfSeqs);

    SeqsFile.close();
    NormlicedFile.close();
    return 0;
}


int userSequence() {
    int num_seq;
    cout << "Ingrese el numero de secuencias:" << endl;
    cin >> num_seq;
    return num_seq;
}


void getFilenames(fstream &Secuencias, fstream &Normalizadas) {
    string seqFilename;
    string normlicedFilename;

    cout << endl << "Ingrese el nombre del archivo"
    << " en donde desea guardar las secuencias:" << endl;
    cin >> seqFilename;

    cout << endl << "Ingrese el nombre del archivo"
    << " en donde desea guardar las secuencias normalizadas:" << endl;
    cin >> normlicedFilename;
    
    Secuencias.open(seqFilename + ".txt", fstream::out | fstream::in | fstream::trunc);
    Normalizadas.open(normlicedFilename + ".txt", fstream::out);
}


void makeSequences(fstream &Secuencias, int num_sec) {
    Secuencias << "Data ID    ";
    for (int numsPerSeq = 1; numsPerSeq <= 10; numsPerSeq++) {
        Secuencias << setw(ESPACIO - 1) << "No. " << numsPerSeq;
    } 

    Secuencias << setw(ESPACIO) << "Clicks" << setw(ESPACIO) << "Numero Mayor" << endl;
    Secuencias << string(180, '=') << endl;

    for (int i = 1; i <= num_sec; i++) {
        Secuencias << "Secuencia #" << i;
        int mayor = -1;
        for (int j = 1; j <= 10; j++) { // 10 es el número de núms. rands. por secs.
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
    // Secuencias.close();
}


void getSequences(fstream &Secuencias, fstream &Normalizadas, int num_secs) {
    Secuencias.seekg(0, ios::beg);

    string first_lines;
    getline(Secuencias, first_lines);
    Normalizadas << first_lines << endl;

    getline(Secuencias, first_lines);
    Normalizadas << first_lines << endl;

    // Normalizar números por secuencia.
    for (int n = 1; n <= num_secs; n++) {
        Normalizadas << "Secuencia #" << n;  // Se inserta el número de la secuencia.
        
        string resto_secs;
        double mayor;
        Secuencias.seekg(173, ios::cur);  // Va a donde se encuentra el número mayor.
        Secuencias >> mayor;
        
        Secuencias.seekg(-162, ios::cur); // Va al primero número de la enésima secuencia.

        double currNum;
        for (int x = 1; x <= 10; x++) {
            Secuencias >> currNum;  // Se lee el número x de la secuencia n.
    
            Logging:
            cout << "Num " << x << "    " << currNum << "    " << currNum << '/' << mayor;
            cout << endl;
    
            // Se guarda la división del número x y el número mayor de la secuencia
            Normalizadas << setw(ESPACIO) << currNum/mayor;  // en el archivo del objeto 'Normalizadas'.
        }
        getline(Secuencias, resto_secs);
        Normalizadas << resto_secs;
        if (n != num_secs)  // Si se está interando por la última
            Normalizadas << endl; // secuencia, entonces no insertar una línea en blanco (al final).
    }
}
