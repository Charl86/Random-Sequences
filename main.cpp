#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <ctime>
#include <string>

using namespace std;

#define ESPACIO 14

int userSequence();
string makeSequences(int);
void getSequences(string, int);


int main() {
    srand((unsigned)time(0));

    int numberOfSeqs;

    numberOfSeqs = userSequence();

    getSequences(makeSequences(numberOfSeqs), numberOfSeqs);

    return 0;
}


int userSequence() {
    int num_seq;
    cout << "Ingrese el numero de secuencias:" << endl;
    cin >> num_seq;
    return num_seq;
}


string makeSequences(int num_sec) {
    string seqFilename;
    cout << endl << "Ingrese el nombre del archivo"
    << " en donde desea guardar las secuencias:" << endl;
    cin >> seqFilename;

    ofstream Secuencias;
    Secuencias.open(seqFilename + ".txt");  // Ajusta el tipo del archivo.

    Secuencias << "Data ID    ";
    for (int numsPerSeq = 1; numsPerSeq <= 10; numsPerSeq++) {
        Secuencias << setw(ESPACIO - 1) << "No. " << numsPerSeq;
    }
    Secuencias << setw(ESPACIO) << "Clicks" << setw(ESPACIO) << "Numero Mayor" << endl;
    Secuencias << string(180, '=') << endl;

    for (int i = 1; i <= num_sec; i++) {
        Secuencias << "Secuencia #" << i;
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
        if (i != num_sec) {Secuencias << endl;}
    }
    Secuencias.close();
    return seqFilename;
}


void getSequences(string secFileName, int num_sec) {
    fstream Secuencias;
    Secuencias.open(secFileName + ".txt");  // Ajusta el tipo del archivo.

    string nrmlzFileName;
    cout << endl << "Ingrese el nombre del archivo"
    << " en donde desea guardar las secuencias normalizadas:" << endl;
    cin >> nrmlzFileName;

    ofstream Normalized;
    Normalized.open(nrmlzFileName + ".txt");

    double currNum;

    Normalized << "Data ID    ";
    for (int numsPerSeq = 1; numsPerSeq <= 10; numsPerSeq++) {
        Normalized << setw(ESPACIO - 1) << "No. " << numsPerSeq;
    }
    Normalized << setw(ESPACIO) << "Clicks" << setw(ESPACIO) << "Numero Mayor" << endl;
    Normalized << string(180, '=') << endl;
    // Debugging:
    // string some_other_string;
    string some_string;
    Secuencias.seekg(531, ios::beg);  // Go to greatest num.
    // Secuencias.seekg(254L, ios::beg);
    // Secuencias.seekg(387L, ios::beg);
    // Secuencias >> some_other_string;
    // cout << endl << some_other_string;
    // Secuencias.seekg(133L * 4L + (16L), ios::beg);  // Go to first num. in sequence.
    Secuencias >> some_string;
    cout << endl <<some_string;

    // Normalizar números por secuencia.
    for (int i = 1; i <= num_sec; i++) {
        Normalized << "Secuencia #" << i;

        double mayor;
        Secuencias.seekg(181 * (i + 1), ios::beg);  // Go to beginning of nth sequence.
        Secuencias.seekg(175, ios::cur);
        Secuencias >> mayor;

        Secuencias.seekg(181 * (i + 1), ios::beg);
        Secuencias.seekg(20, ios::cur);  // Go to first number in sequence.
        // switch(i) {
        //     case 1: Secuencias.seekg(133 * (i - 1) + (9 + ESPACIO/2.0), ios::beg); break;
        //     case 2: Secuencias.seekg(133 * (i - 1) + 14, ios::beg); break;
        // }

        for (int j = 1; j <= 10; j++) {
            Secuencias >> currNum;
            
            // cout << endl << currNum/mayor << endl;

            Normalized << setw(ESPACIO) << currNum/mayor;
        }
        Normalized << setw(ESPACIO) << "{Clicks}";
        Normalized << setw(ESPACIO) << mayor;
        if (i != num_sec) {Normalized << endl;}
    }
    Secuencias.close();
    Normalized.close();
}
