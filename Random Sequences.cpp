#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <ctime>
#include <string>

using namespace std;


#define ESPACIO 12
#define NUMS_POR_SEC 10

int userSequence();  // Devuelve el número de secuencias a ser creadas (o leidas).
void makeFilenames(fstream &, fstream &, bool &);  // Crea los archivos.
void makeSequences(fstream &, int, long double [][5][NUMS_POR_SEC]);  // Crea las secuencias.
void getSequences(fstream &, fstream &, int, long double [][5][NUMS_POR_SEC]);  // Normaliza las secuencias.

// Nuevas funciones implementadas:
double calcDeviation(long double [][5][NUMS_POR_SEC], int, double);  // Calcula la deviación estándar.
string lowerCase(string);  // Devuelve el string provisto en lowercase.
void readSequences(fstream &, int, long double [][5][NUMS_POR_SEC]);  // Lee las secuencias de un archivo existente.
bool askReadFile();  // Pregunta si se desea leer un archivo existente o crear uno nuevo para las secuencias.

int main() {
    srand((unsigned)time(0));  // Comienza una nueva semilla para los números randoms.

    int numberOfSeqs;  // Número de secuencias a crear (o leer).
    bool readFile;  // 'true' si se va a leer un archivo existente.
    fstream SeqsFile;  // fstream object para las secuencias random.
    fstream NormlicedFile;  // fstream object para las secuencias normalizadas.

    /* Se le pregunta al usuario cúantas secuencias se van a leer (o a crear), y
    se guarda en ésta variable. */
    numberOfSeqs = userSequence();

    long double RandNums[numberOfSeqs][5][NUMS_POR_SEC];
    /* Se crea un arreglo de 3 dimensiones de la siguiente manera. Ejemplo:
        arreglo[] = {
            {{rand(1), rand(2), ...}, {clicks}, {núm_mayor}, {media}, {deviación}},  // Secuencia 1
            {{rand(7), rand(4), ...}, {clicks}, {núm_mayor}, {media}, {deviación}},  // Secuencia 2
            ...
        }

    Más ejemplos:
        a) arreglo[0][0][n] denota el número n en la columna n, fila 0.
        b) arreglo[2][0][n] denota el número n en la columna n, fila 2.
        c) arreglo[2][1][0] denota los clicks de la fila/secuencia 2.
        d) arreglo[2][2][0] denota el número mayor de la fila/secuencia 2.
        e) arreglo[2][4][0] denota la deviación en la fila/secuencia 2 (dicha deviación va a ser definida
                                                                        a la hora de normalizar la secuencia).
    */

    makeFilenames(SeqsFile, NormlicedFile, readFile);  // Crea los archivos.

    if (readFile)  // Si readFile es cierto: si se va a leer un archivo
        // Se leen los archivos.
        readSequences(SeqsFile, numberOfSeqs, RandNums);
    else
        /* De lo contrario, crear un nuevo archivo y crear nuevas secuencias
        / dentro del mismo. */
        makeSequences(SeqsFile, numberOfSeqs, RandNums);

    // Normalizar las secuencias.
    getSequences(SeqsFile, NormlicedFile, numberOfSeqs, RandNums);

    // Cerrar los archivos.
    SeqsFile.close();
    NormlicedFile.close();
    return 0;
}


int userSequence() {
    int num_seq;  // Número de secuencias.
    cout << "Ingrese el numero de secuencias a crear (o leer):" << endl;
    cin >> num_seq;  // Se guarda el input del usuario en la variable respectiva
    return num_seq;  // y se devuelve.
}

void makeFilenames(fstream &Secuencias, fstream &Normalizadas, bool &readFile) {
    string answerReadFile;  // Respuesta a si se desea leer un archivo.
    string seqFilename;  // Nombre del archivo con las secuencias sin normalizar.
    string normlicedFilename;  // Nombre del archivo con las secuencias normalizadas.

    if (askReadFile()) {  // Si el usuario desea leer un archivo existente
        readFile = true;  // guardar ese hecho en esta variable
        // y preguntarle qué archivo desea leer.
        cout << endl << "Ingrese el nombre del archivo que desea leer" << endl;
    }
    else {
        readFile = false;  // De lo contrario, guardar su respuesta
        // y preguntarle en qué archivo desea guardas las secuencias a crear.
        cout << endl << "Ingrese el nombre del archivo"
        << " en donde desea guardar las secuencias:" << endl;
    }
    cin >> seqFilename;  // Se guarda el nombre del archivo para las secuencias sin normalizar.
    if (readFile) {  // Si se va a leer un archivo

        // Abrir el archivo sin borrar su contenido previo.
        Secuencias.open(seqFilename + ".txt");
        
        // Validar que el nombre provisto del archivo exista.
        while (!Secuencias.is_open()) {  // Si no existe, dejarle saber al usuario que no existe
            cout << endl << "El archivo que ha ingresado no existe. Asegurese de que el archivo"
            << endl << "exista o que haya escrito su nombre correctamente." << endl;

            // y preguntarle el nombre otra vez.
            cin >> seqFilename;
            Secuencias.open(seqFilename + ".txt");
        }
    }
    else  // Si no se va a leer un archivo
        /* Crear un nuevo archivo con el nombre provisto si el mismo no existe,
        o borrar el contenido del archivo con el mismo nombre si el mismo ya existe. */
        Secuencias.open(seqFilename + ".txt", fstream::out | fstream::in | fstream::trunc);

    // Preguntar por el nombre del archivo para las secuencias normalizadas.
    cout << endl << "Ingrese el nombre del archivo"
    << " en donde desea guardar las secuencias normalizadas:" << endl;
    cin >> normlicedFilename;  // Guardar la respuesta en la variable.
    Normalizadas.open(normlicedFilename + ".txt", fstream::out);  // Abrir el archivo con el nombre dado.
}

bool askReadFile() {
    string answer;  // La respuesta a si desea leer un archivo existente.

    do {  // Inicio de un do-while loop pseudo infinito.
        cout << endl << "Desea leer las secuencias de un archivo existente?" << endl;
        cin >> answer;
        
        /* Se convierte la respuesta a lowercase. E.g. Si el usuario ingresa "Si"
        en vez de "si", se toma eso en cuenta. */
        answer = lowerCase(answer);  

        // Si la respuesta es remotamente afirmativa
        if (answer == "yes" || answer == "y"
            || answer == "si" || answer == "1")
                return true;  // Devolver cierto.
        // Si la respuesta es un 'No' o algo similar
        else if (answer == "no" || answer == "n" || answer == "0")
                return false;  // Devolver falso.
        // Si la respuesta ni es un "si" ni es un "no" (u otras alternativas)
        else
            // Decirle al usuario que responda de una manera u otra.
            cout << endl << "Por favor, responda con un 'si' o un 'no'.";
    } while (1);  /* Esto se va a repetir infinitamente, a menos que el usuario
                     responda correctamente. */
}

void makeSequences(fstream &Secuencias, int num_sec, long double RandArray[][5][NUMS_POR_SEC]) {
    // Función para crear las secuencias de números random.

    // Por cada secuencia hasta el número de secuencias provisto
    for (int i = 0; i < num_sec; i++) {
        // Inserta un dataID para cada secuencia
        Secuencias << setw(9) << "dataID#" << (i + 1);

        // Crea una variable para el número mayor inicializado a -1.
        int mayor = RandArray[i][0][0];
        for (int j = 0; j < NUMS_POR_SEC; j++) {  // Por cada número random nuevo 10 veces
            int random_number = rand();  // Se crea un número random

            // Se verifica si este número random es mayor que el número mayor
            if (random_number > mayor)
                // Si lo es, se guarda en la variable 'mayor'.
                mayor = random_number;
            
            // Se inserta una cantidad de espacios, seguidos por el número random creado.
            Secuencias << setw(ESPACIO) << random_number;
            // Se guarda el número random en el arreglo, en la fila i columna j.
            RandArray[i][0][j] = random_number;
        }
        Secuencias << setw(ESPACIO) << 0;  // Clicks.
        Secuencias << setw(ESPACIO) << mayor;  // Se inserta el número mayor.

        RandArray[i][1][0] = 0;  // Clicks.

        // Se guarda el número mayor en la fila i, en el arreglo a la derecha de los clicks.
        RandArray[i][2][0] = mayor;  

        // Si no se itera por la última secuencia, insertar una nueva línea.
        if (i != num_sec) {Secuencias << endl;}
    }
}

void readSequences(fstream &Secuencias, int num_sec, long double RandArray[][5][NUMS_POR_SEC]) {
    // Función para leer las secuencias de un archivo existente.

    string id_text;  // Variable para el dataID.
    int random_number;
    double clicks;
    int mayor;

    // Por cada secuencia
    for (int i = 0; i < num_sec; i++) {
        // Se lee el dataID. Si no está el dataID, se debe comentar esta línea de código.
        Secuencias >> id_text;

        // Por cada número random
        for (int j = 0; j < NUMS_POR_SEC; j++) {
            // Se lee ese número random y se guarda en la variable
            Secuencias >> random_number;

            // y luego se guarda en el arreglo, en la fila i columna j.
            RandArray[i][0][j] = random_number;
        }
        // Se leen los clicks y el número mayor
        Secuencias >> clicks;
        Secuencias >> mayor;

        /* y se guardan en el arreglo, después de los números randoms de la
        secuencia i. */
        RandArray[i][1][0] = clicks;
        RandArray[i][2][0] = mayor;
    }
}

void getSequences(fstream &Secuencias, fstream &Normalizadas, int num_secs, long double RandArray[][5][NUMS_POR_SEC]) {
    // Función para normalizar las secuencias.

    // Por ninguna razón, se va al principio del archivo.
    Secuencias.seekg(0, ios::beg);

    // Inserción del header:
    Normalizadas << setw(10) << "dataID";  // header para el dataID
    for (int i = 0; i < NUMS_POR_SEC; i++)
        Normalizadas << setw(11) <<"Value_" << (i + 1);  // header para los valores

    // header para la media y la deviación:
    Normalizadas << setw(11) << "Mean" << setw(12) << "StdDev";
    // línea divisora:
    Normalizadas << endl << string(155, '-') << endl;

    // Se inicializa el número menor arbitrariamente al número mayor de la fila 0.
    double menor = RandArray[0][2][0];
    int menor_pos[2] = {0};
    // Para cada secuencia
    for (int n = 0; n < num_secs; n++) {
        // se inserta una cantidad de espacios específica, seguidos por el dataID
        Normalizadas << setw(9 - (to_string(n + 1).length() - 1)) << "dataID#" << (n + 1);
        
        // se obtiene al número mayor de la secuencia respectiva
        double mayor = RandArray[n][2][0];
        double media = 0.0;
        double deviation = 0.0;
        double nrmlzCurrNum;

        // Por cada número en la secuencia n
        for (int x = 0; x < NUMS_POR_SEC; x++) {
            /* se define el número normalizado como el número random en la fila n, columna x
            dividido por el número mayor de la misma secuencia. */
            nrmlzCurrNum = RandArray[n][0][x]/(mayor);

            media += nrmlzCurrNum;  // se añade este número normalizado a la media

            // Si el número menor es mayor que el número normalizado actual, guardar éste último.
            if (menor > nrmlzCurrNum) {
                menor = nrmlzCurrNum;
                menor_pos[0] = n;
                menor_pos[1] = x;
            }

            // se guarda el número normalizado en el arreglo
            RandArray[n][0][x] = nrmlzCurrNum;
            // y se inserta en el archivo de las secuencias normalizadas.
            Normalizadas << setw(ESPACIO) << nrmlzCurrNum;  
        }
        // Normalizadas << setw(ESPACIO) << RandArray[n - 1][1][0];
        // Normalizadas << setw(ESPACIO) << RandArray[n - 1][2][0];

        /* Se calcula la media como la suma de los números normalizados
        divididos por la cantidad de los mismos. */
        media = media/NUMS_POR_SEC;

        // Se calcula la deviación dadas una secuencia n y su media.
        deviation = calcDeviation(RandArray, n, media);

        /* Se guardan la media y la deviación en sus propios arreglos, después
        de los números normalizados de la secuencia n, sus clicks y el número mayor. */
        RandArray[n][3][0] = media;
        RandArray[n][4][0] = deviation;

        // Se desplegan la media y la deviación en el archivo.
        Normalizadas << setw(ESPACIO) << RandArray[n][3][0];
        Normalizadas << setw(ESPACIO) << RandArray[n][4][0];
        // Si no se itera por la última secuencia, insertar una nueva línea.
        if (n + 1 != num_secs) { Normalizadas << endl; }
        // Si esta era la última línea
        else {
            // Desplegar el número menor de todas las secuencias.
            Normalizadas << string(2, '\n') << "Minimum value of all sequences is: " << menor << ", found"
            << " on column " << (menor_pos[1] + 1) << " of sequence number " << (menor_pos[0] + 1);
        }
    }
}

double calcDeviation(long double RandArray[][5][NUMS_POR_SEC], int seq_idx, double seq_mean) {
    // Función para calcular la deviación de la secuencia 'sec_idx' con la media 'seq_mean'.

    double std_deviation = 0.0;  // Se inicializa la deviación.

    // Por cada número normalizado en la secuencia seq_idx
    for (int i = 0; i < NUMS_POR_SEC; i++) {
        /* se cuadra la diferencia entre el número i y la media de la secuencia, y se
        añade a la deviación. */
        std_deviation += pow(RandArray[seq_idx][0][i] - seq_mean, 2);
    }
    /* Finalmente, se divide la deviación por la cantidad de números por secuencia 
    y se le saca la raíz cuadrada */
    std_deviation = sqrt(std_deviation/NUMS_POR_SEC);
    return std_deviation;  // y se devuelve el resultado.
}

string lowerCase(string word) {
    // Función para devolver el string dado en lowercase.

    // Se crea un arreglo de caracteres del mismo tamaño que el parámetro.
    char lowered[word.length()];

    // Por cada caracter en el arreglo de caracteres
    for (int i = 0; i < word.length(); i++) {
        // Convertir el caracter i en lowercase y guardarlo en el arreglo.
        lowered[i] = tolower(word[i]);
    }
    /* Devolver el arreglo. Como es un arreglo de caracteres, no se devuelve la
    dirección (y el tipo de la función es string). */
    return lowered;
}
