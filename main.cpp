#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <ctime>
#include <string>

using namespace std;


#define ESPACIO 14
#define NUMS_POR_SEC 10

void makeFilenames(fstream &, fstream &);
void makeSequences(fstream &, int, long int [][NUMS_POR_SEC + 2]);
void getSequences(fstream &, fstream &, int, long int [][NUMS_POR_SEC + 2]);
int userSequence();


int main() {
    srand((unsigned)time(0));

    int numberOfSeqs;
    fstream SeqsFile;
    fstream NormlicedFile;

    numberOfSeqs = userSequence();

    long int RandNums[numberOfSeqs][NUMS_POR_SEC + 2];

    makeFilenames(SeqsFile, NormlicedFile);
    makeSequences(SeqsFile, numberOfSeqs, RandNums);
    getSequences(SeqsFile, NormlicedFile, numberOfSeqs, RandNums);

    return 0;
}


int userSequence() {
    int num_seq;
    cout << "Ingrese el numero de secuencias:" << endl;
    cin >> num_seq;
    return num_seq;
}


void makeFilenames(fstream &Secuencias, fstream &Normalizadas) {
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


void makeSequences(fstream &Secuencias, int num_sec, long int RandArray[][NUMS_POR_SEC + 2]) {
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

            RandArray[i - 1][j - 1] = random_number;
        }
        Secuencias << setw(ESPACIO) << 0;
        Secuencias << setw(ESPACIO) << mayor;
        RandArray[i - 1][10] = 0;
        RandArray[i - 1][11] = mayor;
        if (i != num_sec) {Secuencias << endl;}
    }
}


void getSequences(fstream &Secuencias, fstream &Normalizadas, int num_secs, long int RandArray[][NUMS_POR_SEC + 2]) {
    Secuencias.seekg(0, ios::beg);

    string first_lines;
    getline(Secuencias, first_lines);
    Normalizadas << first_lines << endl;

    getline(Secuencias, first_lines);
    Normalizadas << first_lines << endl;

    // Normalizar números por secuencia.
    for (int n = 1; n <= num_secs; n++) {
        Normalizadas << "Secuencia #" << n;  // Se inserta el número de la secuencia.
        
        double mayor = RandArray[n - 1][11];
        double currNum;
        for (int x = 1; x <= 10; x++) {
            // Secuencias >> currNum;  // Se lee el número x de la secuencia n.
            currNum = RandArray[n - 1][x - 1];
    
            // Logging:
            // cout << "Num " << x << "    " << currNum << "    " << currNum << '/' << mayor;
            // cout << endl;
    
            // Se guarda la división del número x y el número mayor de la secuencia
            Normalizadas << setw(ESPACIO) << currNum/mayor;  // en el archivo del objeto 'Normalizadas'.
        }
        Normalizadas << setw(ESPACIO) << RandArray[n - 1][10];
        Normalizadas << setw(ESPACIO) << RandArray[n - 1][11];
        if (n != num_secs)  // Si se está interando por la última secuencia,
            Normalizadas << endl;  // entonces no insertar una línea en blanco (al final).
    }
    Secuencias.close();
    Normalizadas.close();
}
