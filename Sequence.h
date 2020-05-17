#ifndef SEQUENCE_H
#define SEQUENCE_H
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


const int NUMS_POR_SEC = 10;

struct Sequence {  // El struct llamado 'Secuencia'
    std::string dataID;  // Miembro dataID, donde se va a guardar el número de la secuencia.
    double mayor;  // El número mayor de la secuencia.
    double media;  // La media de la secuencia.
    double stdDev;  // La deviación estándar de la secuencia.
    double clicks;  // Los clicks que se tomaron en producir la secuencia de números randoms.
    double rand_numbers[NUMS_POR_SEC];  // Los números randoms producidos.
    double nrmlz_numbers[NUMS_POR_SEC];  // Los números randoms normalizados.

    // Métodos:
    void selectSort();  // Método para ordenar los números normalizados usando el selection sort.
    void bubbleSort();  // Método para ordenar los números normalizados usando el bubble sort.
};

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

/* Calcula la deviación estándar de un arreglo de números normalizados. Toma como argumentos
el arreglo de núms. y su media. Devuelve la deviación estándar. */
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


#endif
