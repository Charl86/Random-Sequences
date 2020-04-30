/*
    Carlos A. Hernández

    Este programa se encarga de crear (o leer) un archivo de secuencias random. Cada
    secuencia tendrá generalmente 10 números y la cantidad de secuencias es indicada
    por el usuario. Luego de las secuencias random, se crea un nuevo archivo en donde
    las secuencias van a ser normalizadas desplegadas, seguidas por la media y la desviación
    estándar de la secuencia.
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <ctime>
#include <string>
#include <sys/time.h>

using namespace std;


#define ESPACIO 12
#define NUMS_POR_SEC 10

int userSequence();  // Devuelve el número de secuencias a ser creadas (o leidas).
void makeFilenames(fstream &, fstream &, bool &, int &);  // Crea los archivos.
void makeSequences(fstream &, int, double [][5][NUMS_POR_SEC]);  // Crea las secuencias.
void getSequences(fstream &, fstream &, int, double [][5][NUMS_POR_SEC]);  // Normaliza las secuencias.

// Nuevas funciones implementadas:
double calcDeviation(double [][5][NUMS_POR_SEC], int, double);  // Calcula la desviación estándar.
string lowerCase(string);  // Devuelve el string provisto en lowercase.
void readSequences(fstream &, int, double [][5][NUMS_POR_SEC]);  // Lee las secuencias de un archivo existente.
bool askReadFile();  // Pregunta si se desea leer un archivo existente o crear uno nuevo para las secuencias.
int countLines(fstream &);

int main() {
    srand((unsigned)time(0));  // Comienza una nueva semilla para los números randoms.

    int numberOfSeqs;  // Número de secuencias a crear (o leer).
    bool readFile;  // 'true' si se va a leer un archivo existente.
    fstream SeqsFile;  // fstream object para las secuencias random.
    fstream NormlicedFile;  // fstream object para las secuencias normalizadas.

    /* Se le pregunta al usuario cúantas secuencias se van a leer (o a crear), y
    se guarda en ésta variable. */
    numberOfSeqs = userSequence();

    double RandNums[numberOfSeqs][5][NUMS_POR_SEC];
    /* Se crea un arreglo de 3 dimensiones de la siguiente manera. Ejemplo:
        arreglo[] = {
            {{rand(1), rand(2), ...}, {clicks}, {núm_mayor}, {media}, {desviación}},  // Secuencia 1
            {{rand(7), rand(4), ...}, {clicks}, {núm_mayor}, {media}, {desviación}},  // Secuencia 2
            {{rand(4), rand(10), ...}, {clicks}, {núm_mayor}, {media}, {desviación}},  // Secuencia 3
            ...
        }

    Más ejemplos:
        a) arreglo[0][0][n] denota el número n en la columna n, fila 0.
        b) arreglo[2][0][n] denota el número n en la columna n, fila 2.
        c) arreglo[2][1][0] denota los clicks de la fila/secuencia 2.
        d) arreglo[2][2][0] denota el número mayor de la fila/secuencia 2.
        e) arreglo[2][4][0] denota la desviación en la fila/secuencia 2 (dicha desviación va a ser definida
                                                                        a la hora de normalizar la secuencia).
    */

    makeFilenames(SeqsFile, NormlicedFile, readFile, numberOfSeqs);  // Crea los archivos.

    if (readFile)  // Si readFile es cierto; es decir, si se va a leer un archivo
        // se leen los archivos.
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

void makeFilenames(fstream &Secuencias, fstream &Normalizadas, bool &readFile, int &numSeqs) {
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

        // abrir el archivo sin borrar su contenido previo
        // Secuencias.open(seqFilename + ".txt");
        Secuencias.open(seqFilename + ".txt", fstream::out | fstream::in);
        
        // validar que el nombre provisto del archivo exista.
        while (!Secuencias.is_open()) {  // Si no existe, dejarle saber al usuario que no existe
            cout << endl << "El archivo que ha ingresado no existe. Asegurese de que el archivo"
            << endl << "exista o que haya escrito su nombre correctamente." << endl;

            // y preguntarle el nombre otra vez.
            cin >> seqFilename;
            Secuencias.open(seqFilename + ".txt", fstream::out | fstream::in);
        }

        // Cuenta las líneas que hay en el archivo para leer.
        int Secuencias_lineCount = countLines(Secuencias);
        // Si el número de secuencias a leer es no menor que el número de líneas que hay en el archivo
        while (!(numSeqs <= Secuencias_lineCount)) {
            /* desplega un mensaje que le indica al usuario que ingrese un número de secuencias a leer
            mayor que el número de líneas disponibles en el archivo */
            cout << endl << "El numero de filas a leer no puede ser mayor que el numerio de filas"
            << " en el archivo provisto." << endl << "Ingrese un numero de filas menor o igual a "
            << Secuencias_lineCount << ":" << endl;
            cin >> numSeqs;  // y se guarda el nuevo número.
        }
    }
    else  // Si no se va a leer un archivo
        /* crear un nuevo archivo con el nombre provisto si el mismo no existe,
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
                return true;  // devolver ciertd.
        // Si la respuesta es un 'No' o algo similar
        else if (answer == "no" || answer == "n" || answer == "0")
                return false;  // devolver falso.
        // Si la respuesta ni es un "si" ni es un "no" (u otras alternativas)
        else
            // decirle al usuario que responda de una manera u otra.
            cout << endl << "Por favor, responda con un 'si' o un 'no'.";
    } while (1);  /* Este proceso se va a repetir infinitamente, a menos que el usuario
                     responda correctamente. */
}

void makeSequences(fstream &Secuencias, int num_sec, double RandArray[][5][NUMS_POR_SEC]) {
    // Función para crear las secuencias de números random.
    
    struct timespec start, end;  // Variables para comenzar y terminar el 'cronómetro'.
    double clicks;  // Variable para guardar los clicks.

    // Por cada secuencia hasta el número de secuencias provisto
    for (int i = 0; i < num_sec; i++) {
        // Inserta un dataID para cada secuencia
        Secuencias << setw(9) << "dataID#" << (i + 1);

        // Crea una variable para el número mayor inicializado a -1.
        int mayor = RandArray[i][0][0];

        clock_gettime(CLOCK_MONOTONIC, &start);  // Comienza el cronómetro.
        ios_base::sync_with_stdio(false);
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
        clock_gettime(CLOCK_MONOTONIC, &end);  // Se detiene el cronómetro.
        
        // Se calculan los clicks (esta es la única manera en la que salen sin ser 0):
        clicks = (((end.tv_sec - start.tv_sec) * 1e9) + (end.tv_nsec - start.tv_nsec)) * 1e-9;

        // Se desplegan los clicks.
        Secuencias << setw(ESPACIO) << fixed << clicks << defaultfloat;
        // Se desplega el número mayor.
        Secuencias << setw(ESPACIO) << mayor;

        // Se guardan los clicks en la fila i, en el arreglo a la derecha de los números random.
        RandArray[i][1][0] = clicks;

        // Se guarda el número mayor en la fila i, en el arreglo a la derecha de los clicks.
        RandArray[i][2][0] = mayor;  

        // Si no se itera por la última secuencia, insertar una nueva línea.
        if (i != num_sec) {Secuencias << endl;}
    }
}

void readSequences(fstream &Secuencias, int num_sec, double RandArray[][5][NUMS_POR_SEC]) {
    Secuencias.clear();  // Se borra el flag de eof() para poder leer el file nuevamente.
    // Se va al principio del archivo antes de comenzar a leer las secuencias.
    Secuencias.seekg(0, ios::beg);
    // Función para leer las secuencias de un archivo existente.

    string id_text;  // Variable para el dataID.
    int random_number;
    double clicks;
    int mayor;

    // Por cada secuencia
    for (int i = 0; i < num_sec; i++) {
        // Se lee el dataID. Si no hay dataIDs, se debe comentar esta línea de código.
        Secuencias >> id_text;

        // Por cada número random
        for (int j = 0; j < NUMS_POR_SEC; j++) {
            // Se lee ese número random y se guarda en la variable
            Secuencias >> random_number;

            // y luego se guarda en el arreglo, en la fila i columna j.
            RandArray[i][0][j] = static_cast<double>(random_number);
        }
        // Se leen los clicks y el número mayor
        Secuencias >> clicks;
        Secuencias >> mayor;

        /* y se guardan en el arreglo, después de los números randoms de la
        secuencia i. */
        RandArray[i][1][0] = clicks;
        RandArray[i][2][0] = static_cast<double>(mayor);
    }
}

void getSequences(fstream &Secuencias, fstream &Normalizadas, int num_secs, double RandArray[][5][NUMS_POR_SEC]) {
    // Función para normalizar las secuencias.

    // Se va al principio del archivo antes de comenzar a leer las secuencias.
    Secuencias.seekg(0, ios::beg);

    // Inserción del header:
    Normalizadas << setw(10) << "dataID";  // header para el dataID
    for (int i = 0; i < NUMS_POR_SEC; i++)
        Normalizadas << setw(11) <<"Value_" << (i + 1);  // header para los valores

    // header para la media y la desviación:
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
        /* Se calcula la media como la suma de los números normalizados
        divididos por la cantidad de los mismos. */
        media = media/NUMS_POR_SEC;

        // Se calcula la desviación dadas una secuencia n y su media.
        deviation = calcDeviation(RandArray, n, media);

        /* Se guardan la media y la desviación en sus propios arreglos, después
        de los números normalizados de la secuencia n, sus clicks y el número mayor. */
        RandArray[n][3][0] = media;
        RandArray[n][4][0] = deviation;

        // Se desplegan la media y la desviación en el archivo.
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

double calcDeviation(double RandArray[][5][NUMS_POR_SEC], int seq_idx, double seq_mean) {
    // Función para calcular la desviación de la secuencia 'sec_idx' con la media 'seq_mean'.

    double std_deviation = 0.0;  // Se inicializa la desviación.

    // Por cada número normalizado en la secuencia seq_idx
    for (int i = 0; i < NUMS_POR_SEC; i++) {
        /* se cuadra la diferencia entre el número i y la media de la secuencia, y se
        añade a la desviación. */
        std_deviation += pow(RandArray[seq_idx][0][i] - seq_mean, 2);
    }
    /* Finalmente, se divide la desviación por la cantidad de números por secuencia 
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

int countLines(fstream  &readFile) {
    // Función para contar las líneas en el archivo readFile.

    string nth_line;
    double numbers;
    int count = 0;

    // Mientras haya una línea disponible para ser guardada en nth_line
    while (getline(readFile, nth_line))
        count += 1;  // sumar 1 al contador.

    return count;
}
