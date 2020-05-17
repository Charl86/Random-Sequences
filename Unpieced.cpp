#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sys/time.h>
#include <cmath>
#include <vector>

using namespace std;


const int NUMS_POR_SEC = 10;
#define ESPACIO 12
#define TABLA_W 30

struct Sequence {  // El struct llamado 'Secuencia'
    std::string dataID;  // Miembro dataID, donde se va a guardar el número de la secuencia.
    double mayor;  // El número mayor de la secuencia.
    double media;  // La media de la secuencia.
    double stdDev;  // La desviación estándar de la secuencia.
    double clicks;  // Los clicks que se tomaron en producir la secuencia de números randoms.
    double rand_numbers[NUMS_POR_SEC];  // Los números randoms producidos.
    double nrmlz_numbers[NUMS_POR_SEC];  // Los números randoms normalizados.

    // Métodos:
    void selectSort();  // Método para ordenar los números normalizados usando el selection sort.
    void bubbleSort();  // Método para ordenar los números normalizados usando el bubble sort.
};

void Sequence::selectSort() {
    // Método para ordenar el miembro 'nrmlz_numbers' de la secuencia usando el bubble sort algorithm.

    // Como este método se aplica en la copia de la secuencia, no importa si se modifica de esta manera.
    // Se aplica el selection sort algorithm en el arreglo de números normalizados de la secuencia.
    double smallest;
    int smallestIdx;
    for (int start = 0; start < NUMS_POR_SEC - 1; start++) {
        smallest = nrmlz_numbers[start];
        smallestIdx = start;
        for (int i = start + 1; i < NUMS_POR_SEC; i++) {
            if (smallest > nrmlz_numbers[i]) {
                smallest = nrmlz_numbers[i];
                smallestIdx = i;
            }
        }
        nrmlz_numbers[smallestIdx] = nrmlz_numbers[start];
        nrmlz_numbers[start] = smallest;
    }
}

void Sequence::bubbleSort() {
    // Método para ordenar el miembro 'nrmlz_numbers' de la secuencia usando el selection sort algorithm.
    bool swapped;
    do {
        swapped = false;
        for (int i = 0; i < NUMS_POR_SEC - 1; i++) {
            if (nrmlz_numbers[i] > nrmlz_numbers[i + 1]) {
                swapped = true;
                std::swap(nrmlz_numbers[i], nrmlz_numbers[i + 1]);
            }
        }
    } while (swapped);
}

// Le pregunta al usuario cuántas secuencias se van a leer y devuelve ese número.
int userSequence();

/* Le pregunta al usuario en dónde se van a guardar los archivos de las secuencias y si se va a leer
un archivo para los números randoms o a crear uno nuevo. Toma como argumentos dos objetos fstream,
un bool por referencia (que guarda si se va a leer un archivo de secuencias randoms o a crear uno),
y el número de secuencias ingresado por el usuario. */
void makeFilenames(fstream &, fstream &, bool &, int &);

/* Crea las secuencias de números randoms en caso de no ser leídas. Toma como argumentos el vector
en donde se van a guardar las secuencias de tipo 'Sequence', el objeto fstream asociado al archivo
de las secuencias de núms. random, y el número de secuencias. */
void makeSequences(fstream &, int, vector <Sequence> &);

/* Lee las secuencias del archivo de secuencias de núms. random. Toma como argumentos dos objectos
fstream, asociados a los archivos de secuencias randoms y secuencias normalizadas, el núm. de
secuencias y el vector de secuencias. */
void getSequences(fstream &, fstream &, int, vector <Sequence> &);

// Nuevas funciones implementadas:

/* Calcula la desviación estándar de un arreglo de números normalizados. Toma como argumentos
el arreglo de núms. y su media. Devuelve la desviación estándar. */
double calcDeviation(double [], double);

/* Recibe como argumento un string cualquiera y devuelve el mismo string en lowercase. */
string lowerCase(string);

/* Lee las secuencias de un archivo de secuencias randoms existente en caso de que el mismo no se vaya
a crear. Toma como argumentos el objeto fstream asociado al archivo ya existente, el núm. de secuencias
y el vector de secuencias (que va a ser llenado a medida que se lea el archivo). */
void readSequences(fstream &, int &, vector <Sequence> &);

/* Función que pregunta si el usuario desea leer un archivo de secuencias ya existence o crear uno nuevo.
Valida hasta cierto punto la respuesta del usuario y finalmente devuelve su respuesta como bool; es decir,
cierto si se va a leer de un archivo, o falso si no se va a leer. */
bool askReadFile();  // Pregunta si se desea leer un archivo existente o crear uno nuevo para las secuencias.

/* Cuenta las líneas de un archivo ya existente. Esta función está en desuso pues ya no se está
leyendo el archivo inicialmente para contar sus líneas, y después volverlo a leer. Toma como argumento
el objeto fstream asociado al archivo y devuelve las líneas contadas. */
int countLines(fstream &);

// Últimas funciones implementadas:

/* Función que ordena el vector de secuencias utilizando el selection sort algorithm. Toma como argumentos
el vector de secuencias, el núm. de secuencias y el objeto fstream asociado al archivo de secuencias
normalizadas. También desplega los clicks que se toma en ordenar el vector. */
void selectionSort(vector <Sequence>, int, fstream &);

/* Función que ordena el vector de secuencias utilizando el bubble sort algorithm. Toma como argumentos
el vector de secuencias, el núm. de secuencias y el objeto fstream asociado al archivo de secuencias
normalizadas. También desplega los clicks que se toma en ordenar el vector. */
void bubbleSort(vector <Sequence>, int, fstream &);

/* Función que se encarga de desplegar (en el archivo) las secuencias del vector ya ordenado. 
A su vez va ordenando las secuencias una por una, es decir; ordena los números en cada secuencia,
y luego los va desplegando uno a uno en el archivo de secuencias normalizadas. También calcula el
promedio que se tomó en ordenar cada secuencia y lo desplega (en la consola/terminal). Toma como
argumentos el vector de secuencias, el núm. de secuencias, el objeto fstream asociado al archivo de
secuencias normalizadas, y un bool. Este bool determina si para las secuencias se va a realizar el
bubble sort o el selection sort. De esta manera, no habría necesidad de crear dos funciones aparte,
para ordenar los números en las secuencias con el bubble y selection sort, sino que el parámetro
bool determina cuál algoritmo de ordenamiento realizar, y lo demás aplica para ambos algoritmos. */
void outSortedArray(vector <Sequence>, int, fstream &, bool =true);

int main() {
    srand((unsigned)time(0));  // Comienza una nueva semilla para los números randoms.

    int numberOfSeqs;  // Número de secuencias a crear (o leer).
    bool readFile;  // 'true' si se va a leer un archivo existente.
    fstream SeqsFile;  // fstream object para las secuencias random.
    fstream NormlicedFile;  // fstream object para las secuencias normalizadas.

    /* Se le pregunta al usuario cúantas secuencias se van a leer (o a crear), y
    se guarda en ésta variable. */
    numberOfSeqs = userSequence();

    // Se crea un vector que guarda elementos de tipo 'Sequence', sin ningún elemento.
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

int userSequence() {
    int num_seq;  // Número de secuencias.
    cout << "Ingrese el numero de secuencias a crear (o leer):" << endl;
    cin >> num_seq;  // Se guarda el input del usuario en la variable respectiva
    return num_seq;  // y se devuelve.
}

void makeFilenames(fstream &fileSeqs, fstream &fileNorms, bool &readFile, int &numSeqs) {
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
        // fileSeqs.open(seqFilename + ".txt");
        fileSeqs.open(seqFilename + ".txt", fstream::out | fstream::in);
        
        // validar que el nombre provisto del archivo exista.
        while (!fileSeqs.is_open()) {  // Si no existe, dejarle saber al usuario que no existe
            cout << endl << "El archivo que ha ingresado no existe. Asegurese de que el archivo"
            << endl << "exista o que haya escrito su nombre correctamente." << endl;

            // y preguntarle el nombre otra vez.
            cin >> seqFilename;
            fileSeqs.open(seqFilename + ".txt", fstream::out | fstream::in);
        }
    }
    else {  // Si no se va a leer un archivo
        /* crear un nuevo archivo con el nombre provisto si el mismo no existe,
        o borrar el contenido del archivo con el mismo nombre si el mismo ya existe. */
        fileSeqs.open(seqFilename + ".txt", fstream::out | fstream::in | fstream::trunc);
    }

    // Preguntar por el nombre del archivo para las secuencias normalizadas.
    cout << endl << "Ingrese el nombre del archivo"
    << " en donde desea guardar las secuencias normalizadas:" << endl;
    cin >> normlicedFilename;  // Guardar la respuesta en la variable.
    fileNorms.open(normlicedFilename + ".txt", fstream::out);  // Abrir el archivo con el nombre dado.
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
                return true;  // devolver cierto.
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

// void makeSequences(fstream &fileSeqs, int num_sec, Sequence arrSecuencias[]) {
void makeSequences(fstream &fileSeqs, int num_sec, vector <Sequence> &arrSecuencias) {
    // Función para crear las secuencias de números random.
    
    arrSecuencias.resize(num_sec);

    struct timespec start, end;  // Variables para comenzar y terminar el 'cronómetro'.
    double clicks;  // Variable para guardar los clicks.

    // Por cada secuencia hasta el número de secuencias provisto
    for (int i = 0; i < num_sec; i++) {
        // Inserta un dataID para cada secuencia
        fileSeqs << setw(9) << "dataID#" << (i + 1);
        arrSecuencias[i].dataID = "dataID#" + to_string(i + 1);

        // Crea una variable para el número mayor inicializado a -1.
        int mayor = -1;

        clock_gettime(CLOCK_MONOTONIC, &start);  // Comienza el cronómetro.
        ios_base::sync_with_stdio(false);
        for (int j = 0; j < NUMS_POR_SEC; j++) {  // Por cada número random nuevo 10 veces
            int random_number = rand();  // Se crea un número random

            // Se verifica si este número random es mayor que el número mayor
            if (random_number > mayor)
                // Si lo es, se guarda en la variable 'mayor'.
                mayor = random_number;
            
            // Se inserta una cantidad de espacios, seguidos por el número random creado.
            fileSeqs << setw(ESPACIO) << random_number;
            // Se guarda el número random en el arreglo, en la fila i columna j.
            arrSecuencias[i].rand_numbers[j] = random_number;
        }
        clock_gettime(CLOCK_MONOTONIC, &end);  // Se detiene el cronómetro.
        
        // Se calculan los clicks (esta es la única manera en la que salen sin ser 0):
        clicks = (((end.tv_sec - start.tv_sec) * 1e9) + (end.tv_nsec - start.tv_nsec)) * 1e-9;

        // Se desplegan los clicks.
        fileSeqs << setw(ESPACIO) << fixed << clicks << defaultfloat;
        // Se desplega el número mayor.
        fileSeqs << setw(ESPACIO) << mayor;

        // Se guardan los clicks en la fila i, en el arreglo a la derecha de los números random.
        arrSecuencias[i].clicks = clicks;

        // Se guarda el número mayor en la fila i, en el arreglo a la derecha de los clicks.
        arrSecuencias[i].mayor = mayor;  

        // Si no se itera por la última secuencia, insertar una nueva línea.
        if (i + 1 != num_sec) {fileSeqs << endl;}
    }
}

void readSequences(fstream &fileSeqs, int &num_sec, vector <Sequence> &arrSecuencias) {
    // Función para leer las secuencias de un archivo existente.

    // Variables para el dataID, el número random, los clicks y el número mayor.
    string id_text;
    int random_number;
    double clicks;
    int mayor;

    int line_counter = 0;  // Variable para contar las líneas leídas.
    /* Mientras se pueda seguir leyendo y el número de líneas leídas sea menor
    que el número de líneas a leer */
    while (fileSeqs >> id_text && line_counter < num_sec) {
        // El dataID se guarda en su variable respectiva.
        
        // Se crea una nueva secuencia y se añade al vector de secuencias.
        Sequence new_sequence;
        arrSecuencias.push_back(new_sequence);

        // Se guarda el dataID en el miembro de dataID.
        arrSecuencias[line_counter].dataID = id_text;

        // Por cada número random
        for (int j = 0; j < NUMS_POR_SEC; j++) {
            // Se lee ese número random y se guarda en la variable
            fileSeqs >> random_number;

            // y luego se guarda en el arreglo, en la fila i columna j.
            arrSecuencias[line_counter].rand_numbers[j] = static_cast<double>(random_number);
        }
        // Se leen los clicks y el número mayor
        fileSeqs >> clicks;
        fileSeqs >> mayor;

        /* y se guardan en el arreglo, después de los números randoms de la
        secuencia i en el vector de secuencias. */
        arrSecuencias[line_counter].clicks = clicks;
        arrSecuencias[line_counter].mayor = static_cast<double>(mayor);
        
        line_counter += 1;  // Se suma uno al contador de líneas.
    }

    // Si el contador de líneas es menor que el número de líneas ingresado a leer
    if (line_counter < num_sec) {
        /* Desplegar que el número de líneas que se leyeron es menor que el número ingresado de líneas
        a leer, y que solo se leyeron las líneas que habían. */
        cout << endl <<"Solamente habian " << line_counter << " de las " << num_sec
        << " secuencias ingresadas para leer." << endl << "Asi que se leyeron "
        << line_counter << " secuencias." << endl;
        num_sec = line_counter;  // Igualar el número ingresado de líneas al número de líneas leídas.
    }
}

void getSequences(fstream &fileSeqs, fstream &fileNorms, int num_secs, vector <Sequence> &arrSecuencias) {
    // Función para normalizar las secuencias.

    // Inserción del header:
    fileNorms << setw(10) << "dataID";  // header para el dataID
    for (int i = 0; i < NUMS_POR_SEC; i++)
        fileNorms << setw(11) <<"Value_" << (i + 1);  // header para los valores

    // header para la media y la desviación:
    fileNorms << setw(11) << "Mean" << setw(12) << "StdDev";
    
    // Línea divisora:
    fileNorms << endl << string(155, '-') << endl;

    // Se inicializa el número menor arbitrariamente al número mayor de la primera secuencia.
    double menor = arrSecuencias[0].mayor;
    int menor_pos[2] = {0};
    // Para cada secuencia
    for (int n = 0; n < num_secs; n++) {
        // se inserta una cantidad de espacios específica, seguidos por el dataID
        fileNorms << setw(9 - (to_string(n + 1).length() - 1)) << arrSecuencias[n].dataID;
        
        // se obtiene al número mayor de la secuencia respectiva
        double mayor = arrSecuencias[n].mayor;
        double media = 0.0;
        double deviation = 0.0;
        double nrmlzCurrNum;

        // Por cada número en la secuencia n
        for (int x = 0; x < NUMS_POR_SEC; x++) {
            /* se define el número normalizado como el número random en la fila n, columna x
            dividido por el número mayor de la misma secuencia. */
            nrmlzCurrNum = arrSecuencias[n].rand_numbers[x]/(mayor);

            media += nrmlzCurrNum;  // se añade este número normalizado a la media

            // Si el número menor es mayor que el número normalizado actual, guardar éste último.
            if (menor > nrmlzCurrNum) {
                menor = nrmlzCurrNum;
                menor_pos[0] = n;
                menor_pos[1] = x;
            }

            // se guarda el número normalizado en el arreglo
            arrSecuencias[n].nrmlz_numbers[x] = nrmlzCurrNum;
            // y se inserta en el archivo de las secuencias normalizadas.
            fileNorms << setw(ESPACIO) << nrmlzCurrNum;  
        }
        /* Se calcula la media como la suma de los números normalizados
        divididos por la cantidad de los mismos. */
        media = media/NUMS_POR_SEC;

        // Se calcula la desviación dadas una secuencia n y su media.
        deviation = calcDeviation(arrSecuencias[n].nrmlz_numbers, media);

        /* Se guardan la media y la desviación en sus propios arreglos, después
        de los números normalizados de la secuencia n, sus clicks y el número mayor. */
        arrSecuencias[n].media = media;
        arrSecuencias[n].stdDev = deviation;

        // Se desplegan la media y la desviación en el archivo.
        fileNorms << setw(ESPACIO) << arrSecuencias[n].media;
        fileNorms << setw(ESPACIO) << arrSecuencias[n].stdDev;
        // Si no se itera por la última secuencia, insertar una nueva línea.
        if (n + 1 != num_secs) { fileNorms << endl; }
        // Si esta era la última línea
        else {
            // Desplegar el número menor de todas las secuencias.
            fileNorms << string(2, '\n') << "Minimum value of all sequences is: " << menor << ", found"
            << " on column " << (menor_pos[1] + 1) << " of sequence number " << (menor_pos[0] + 1);
        }
    }

    /* Se desplega el header de 'ALGORITMO' en la tabla (no del archivo), junto con el header
    del tiempo tomado en ordenar el vector de secuencias y a su vez cada secuencia */
    cout << endl << "ALGORITMO" << setw(TABLA_W + 30) << "Tiempo en ordenar el vector de secuencias usando la media"
    << setw(TABLA_W + 15) << "Tiempo promedio en ordenar cada secuencia";

    // Aplicar el selection sort y el bubble sort en el vector de secuencias.
    selectionSort(arrSecuencias, num_secs, fileNorms);
    bubbleSort(arrSecuencias, num_secs, fileNorms);
}
                                                                                                          
double calcDeviation(double randomSeq[], double seq_mean) {
    // Función para calcular la desviación de la secuencia 'sec_idx' con la media 'seq_mean'.

    double std_deviation = 0.0;  // Se inicializa la desviación.

    // Por cada número normalizado en la secuencia seq_idx
    for (int i = 0; i < NUMS_POR_SEC; i++) {
        /* se cuadra la diferencia entre el número i y la media de la secuencia, y se
        añade a la desviación. */
        std_deviation += pow(randomSeq[i] - seq_mean, 2);
    }
    /* Finalmente, se divide la desviación por la cantidad de números por secuencia 
    y se le saca la raíz cuadrada */
    std_deviation = sqrt(std_deviation/NUMS_POR_SEC);
    return std_deviation;  // y se devuelve el resultado.
}

void selectionSort(vector <Sequence> arrSecuencias, int numsOfSeqs, fstream &fileNorms) {
    // Función para ordenar el vector de secuencias usando el selection sort algorithm.

    struct timespec start, end;  // Variables para calcular el tiempo (o clicks).
    double clicks;  // Variable para guardar los clicks.

    clock_gettime(CLOCK_MONOTONIC, &start);  // Comienza el cronómetro.
    ios_base::sync_with_stdio(false);

    // Se aplica el selection sort algorithm en base a la media de cada secuencia.
    Sequence smallestMeanSeq;
    int sm_meanIdx;
    for (int start = 0; start < numsOfSeqs - 1; start++) {
        smallestMeanSeq = arrSecuencias[start];
        sm_meanIdx = start;
        for (int i = start + 1; i < numsOfSeqs; i++) {
            if (smallestMeanSeq.media > arrSecuencias[i].media) {
                smallestMeanSeq = arrSecuencias[i];
                sm_meanIdx = i;
            }
        }
        arrSecuencias[sm_meanIdx] = arrSecuencias[start];
        arrSecuencias[start] = smallestMeanSeq;
    }
    clock_gettime(CLOCK_MONOTONIC, &end);  // Se detiene el cronómetro.
    // Se calculan los clicks.
    clicks = (((end.tv_sec - start.tv_sec) * 1e9) + (end.tv_nsec - start.tv_nsec)) * 1e-9;

    // Se desplega la columna de 'SELECTION' junto a sus clicks.
    cout << endl << "SELECTION" << setw(TABLA_W + 3) << fixed << clicks;

    // Se llama la función outsortedArray con la copia de la secuencia.
    outSortedArray(arrSecuencias, numsOfSeqs, fileNorms, false);
}

void bubbleSort(vector <Sequence> arrSecuencias, int numsOfSeqs, fstream &fileNorms) {
    // Función para ordenar el vector de secuencias usando el bubble sort algorithm.

    struct timespec start, end;  // Variables para calcular el tiempo (o clicks).
    double clicks;  // Variable para guardar los clicks.

    clock_gettime(CLOCK_MONOTONIC, &start);  // Comienza el cronómetro.
    ios_base::sync_with_stdio(false);

    /* Se aplica el bubble sort algorithm en el vector de secuencias
    en base a la media de cada secuencia. */
    bool swapped;
    do {
        swapped = false;
        for (int i = 0; i < numsOfSeqs - 1; i++) {
            if (arrSecuencias[i].media > arrSecuencias[i + 1].media) {
                swap(arrSecuencias[i], arrSecuencias[i + 1]);
                swapped = true;
            }
        }
    } while (swapped);

    clock_gettime(CLOCK_MONOTONIC, &end);  // Se detiene el cronómetro.
    
    // Se calculan los clicks
    clicks = (((end.tv_sec - start.tv_sec) * 1e9) + (end.tv_nsec - start.tv_nsec)) * 1e-9;

    // Se desplega la columna de 'BUBBLE' junto con sus clicks.
    cout << endl << "BUBBLE" << setw(TABLA_W + 6) << clicks;

    // Se llama la función outsortedArray con la copia del vector de secuencias.
    outSortedArray(arrSecuencias, numsOfSeqs, fileNorms, true);
}

void outSortedArray(vector <Sequence> arrSecuencias, int numsOfSeqs, fstream &fileNorms, bool bubbleSort) {
    /* Función para desplegar los clicks para cada ordenamiento realizado y para poner las secuencias
    ordenadas dentro del archivo de secuencias normalizadas. */

    // Double línea en blanco para separar la información desplegada.
    fileNorms << endl << endl;

    // Si el argumento 'bubbleSort' se pasó como cierto
    if (bubbleSort) {
        // Indicar los resultados del bubble sort.
        fileNorms << setw(15) << "Sorting with BUBBLE we got:" << endl;
    }
    else  // Si no, indicar los resultados del selection sort.
        fileNorms << setw(15) << "Sorting with SELECTION we got:" << endl;

    // Desplegar el header para el dataID y la media.
    fileNorms << setw(11) << "dataID" << setw(131) << "Mean" << endl;
    fileNorms << string(144, '-') << endl;  // Línea divisora entre los headers y el contenido.

    struct timespec start, end;  // Variables para calcular el tiempo (o clicks).
    double clicks;  // Variable para guardar los clicks.
    double sumOfClicks = 0.0;  // Variable para acumular el promedio de los clicks
    for (int i = 0; i < numsOfSeqs; i++) {  // Por cada secuencia
        clock_gettime(CLOCK_MONOTONIC, &start);  // Comienza el cronómetro.
        ios_base::sync_with_stdio(false);
        if (!bubbleSort) {  // Si no se pasó el bubbleSort como cierto
            arrSecuencias[i].selectSort();  // Aplicar el selection sort en la secuencia misma.
        }
        else {  // Si se pasó como cierto, realizar el bubble sort en la secuencia misma.
            arrSecuencias[i].bubbleSort();
        }
        clock_gettime(CLOCK_MONOTONIC, &end);  // Se detiene el cronómetro.

        // Se calculan los clicks
        clicks = (((end.tv_sec - start.tv_sec) * 1e9) + (end.tv_nsec - start.tv_nsec)) * 1e-9;
        
        sumOfClicks += clicks;  // Se añaden los clicks a ésta variable.

        fileNorms << setw(13) << arrSecuencias[i].dataID;  // Desplegar el dataID de la secuencia.
        
        for (int j = 0; j < NUMS_POR_SEC; j++) {  // Por cada número en la secuencia, se desplega.
            if (j + 1 == NUMS_POR_SEC)
                fileNorms << setw(ESPACIO - 5) << arrSecuencias[i].nrmlz_numbers[j];
            else
                fileNorms << setw(ESPACIO) << arrSecuencias[i].nrmlz_numbers[j];
        }

        // Desplegar la media de la secuencia.
        fileNorms << setw(ESPACIO + 3) << arrSecuencias[i].media;

        // Si no se está interando por la última secuencia, insertar una línea en blanco.
        if (i + 1 != numsOfSeqs)
            fileNorms << endl;
    }
    if (!bubbleSort) {  // Si no se hizo el bubble sort en cada secuencia
        // Insertar líneas divisoras y espacios.
        fileNorms << string(2, '\n') << string(144, '-');
        fileNorms << endl << string(144, '-');
    }
    // Desplegar el promedio de los clicks en ordenar cada secuencia.
    cout << setw(TABLA_W + 25) << sumOfClicks/numsOfSeqs;
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

    return count;  // Se devuelve lo contado.
}
