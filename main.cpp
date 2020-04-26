#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <ctime>
#include <string>

using namespace std;


#define ESPACIO 12
#define NUMS_POR_SEC 10

void makeFilenames(fstream &, fstream &, bool &);
void makeSequences(fstream &, int, long double [][5][NUMS_POR_SEC]);
void getSequences(fstream &, fstream &, int, long double [][5][NUMS_POR_SEC]);
int userSequence();

// Nuevas funciones creadas:
double calcDeviation(long double [][5][NUMS_POR_SEC], int, double);
string lowerCase(string);
void readSequences(fstream &, int, long double [][5][NUMS_POR_SEC]);
bool askReadFile();

int main() {
    srand((unsigned)time(0));

    int numberOfSeqs;
    bool readFile;
    fstream SeqsFile;
    fstream NormlicedFile;

    numberOfSeqs = userSequence();

    long double RandNums[numberOfSeqs][5][NUMS_POR_SEC];

    makeFilenames(SeqsFile, NormlicedFile, readFile);
    if (readFile)
        readSequences(SeqsFile, numberOfSeqs, RandNums);
    else
        makeSequences(SeqsFile, numberOfSeqs, RandNums);

    getSequences(SeqsFile, NormlicedFile, numberOfSeqs, RandNums);
    return 0;
}


int userSequence() {
    int num_seq;
    cout << "Ingrese el numero de secuencias a crear (o leer):" << endl;
    cin >> num_seq;
    return num_seq;
}

void makeFilenames(fstream &Secuencias, fstream &Normalizadas, bool &readFile) {
    string answerReadFile;
    string seqFilename;
    string normlicedFilename;

    if (askReadFile()) {
        readFile = true;
        cout << endl << "Ingrese el nombre del archivo que desea leer" << endl;
    }
    else {
        readFile = false;
        cout << endl << "Ingrese el nombre del archivo"
        << " en donde desea guardar las secuencias:" << endl;
    }
    cin >> seqFilename;
    if (readFile) {
        Secuencias.open(seqFilename + ".txt");
        
        while (!Secuencias.is_open()) {
            cout << endl << "El archivo que ha ingresado no existe. Asegurese de que el archivo"
            << endl << "exista o que haya escrito su nombre correctamente." << endl;
            cin >> seqFilename;
            Secuencias.open(seqFilename + ".txt");
        }
    }
    else
        Secuencias.open(seqFilename + ".txt", fstream::out | fstream::in | fstream::trunc);

    cout << endl << "Ingrese el nombre del archivo"
    << " en donde desea guardar las secuencias normalizadas:" << endl;
    cin >> normlicedFilename;
    Normalizadas.open(normlicedFilename + ".txt", fstream::out);
}

bool askReadFile() {
    string answer;

    do {
        cout << endl << "Desea leer las secuencias de un archivo existente?" << endl;
        cin >> answer;
        answer = lowerCase(answer);
        if (answer == "yes" || answer == "y"
            || answer == "si" || answer == "1")
                return true;
        else if (answer == "no" || answer == "0")
                return false;
        else {
            cout << endl << "Por favor, responda con un 'si' o un 'no'.";
        }
    } while (1);
}

void makeSequences(fstream &Secuencias, int num_sec, long double RandArray[][5][NUMS_POR_SEC]) {
    for (int i = 1; i <= num_sec; i++) {
        Secuencias << setw(9) << "dataID#" << (i + 1);

        int mayor = -1;
        for (int j = 1; j <= NUMS_POR_SEC; j++) {  // 10 es el número de núms. rands. por secs.
            int random_number = rand();

            if (random_number > mayor)
                mayor = random_number;
            
            Secuencias << setw(ESPACIO) << random_number;
            RandArray[i - 1][0][j - 1] = random_number;
        }
        Secuencias << setw(ESPACIO) << 0;
        Secuencias << setw(ESPACIO) << mayor;

        RandArray[i - 1][1][0] = 0;
        RandArray[i - 1][2][0] = mayor;
        if (i != num_sec) {Secuencias << endl;}
    }
}

void readSequences(fstream &Secuencias, int num_sec, long double RandArray[][5][NUMS_POR_SEC]) {
    string id_text;
    int random_number;
    double clicks;
    int mayor;

    for (int i = 0; i < num_sec; i++) {
        // Secuencias.seekg(16, ios::cur);

        Secuencias >> id_text;

        for (int j = 0; j < NUMS_POR_SEC; j++) {
            Secuencias >> random_number;
            RandArray[i][0][j] = random_number;
        }
        Secuencias >> clicks;
        Secuencias >> mayor;

        RandArray[i][1][0] = clicks;
        RandArray[i][2][0] = mayor;
    }
}

void getSequences(fstream &Secuencias, fstream &Normalizadas, int num_secs, long double RandArray[][5][NUMS_POR_SEC]) {
    Secuencias.seekg(0, ios::beg);

    Normalizadas << setw(10) << "dataID";
    for (int i = 0; i < NUMS_POR_SEC; i++)
        Normalizadas << setw(11) <<"Value_" << (i + 1);

    Normalizadas << setw(11) << "Mean" << setw(12) << "StdDev";
    Normalizadas << endl << string(155, '-') << endl;

    // Normalizar números por secuencia.
    for (int n = 0; n < num_secs; n++) {
        // Se inserta el identificador de la secuencia, separada por un espacio específico, seguido de los números.
        Normalizadas << setw(9 - (to_string(n + 1).length() - 1)) << "dataID#" << (n + 1);
        
        double nrmlzCurrNum;
        double mayor = RandArray[n][2][0];
        double media = 0.0;
        double deviation = 0.0;
        for (int x = 0; x < NUMS_POR_SEC; x++) {
            nrmlzCurrNum = RandArray[n][0][x]/(mayor);
            media += nrmlzCurrNum;
    
            // Se guarda la división del número x y el número mayor de la secuencia
            RandArray[n][0][x] = nrmlzCurrNum;
            Normalizadas << setw(ESPACIO) << nrmlzCurrNum;  // en el archivo del objeto 'Normalizadas'.
        }
        // Normalizadas << setw(ESPACIO) << RandArray[n - 1][1][0];
        // Normalizadas << setw(ESPACIO) << RandArray[n - 1][2][0];

        media = media/NUMS_POR_SEC;
        deviation = calcDeviation(RandArray, n, media);

        RandArray[n][3][0] = media;
        RandArray[n][4][0] = deviation;

        Normalizadas << setw(ESPACIO) << RandArray[n][3][0];
        Normalizadas << setw(ESPACIO) << RandArray[n][4][0];
        if (n != num_secs - 1)  // Si se está interando por la última secuencia,
            Normalizadas << endl;  // entonces no insertar una línea en blanco (al final).
    }
    Secuencias.close();
    Normalizadas.close();
}

double calcDeviation(long double RandArray[][5][NUMS_POR_SEC], int seq_idx, double seq_mean) {
    double std_deviation = 0.0;

    for (int i = 0; i < NUMS_POR_SEC; i++) {
        std_deviation += pow(RandArray[seq_idx][0][i] - seq_mean, 2);
    }

    std_deviation = sqrt(std_deviation/NUMS_POR_SEC);
    return std_deviation;
}

string lowerCase(string word) {
    char lowered[word.length()];

    for (int i = 0; i < word.length(); i++) {
        lowered[i] = tolower(word[i]);
    }
    return lowered;
}
