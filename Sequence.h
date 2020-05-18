#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


const int NUMS_POR_SEC = 10;  // La cantidad de números por secuencia.

struct Sequence {  // El struct llamado 'Secuencia'
    std::string dataID;  // Miembro dataID, donde se va a guardar el número de la secuencia.
    double mayor;  // El número mayor de la secuencia.
    double media;  // La media de la secuencia.
    double stdDev;  // La desviación estándar de la secuencia.
    double clicks;  // Los clicks que se tomaron en producir la secuencia de números randoms.
    double rand_numbers[NUMS_POR_SEC];  // Los números randoms producidos.
    double nrmlz_numbers[NUMS_POR_SEC];  // Los números randoms normalizados.

    // Métodos:

    // Método para ordenar los números normalizados de menor a mayor usando el selection sort.
    void selectSort();
    // Método para ordenar los números normalizados de menor a mayor usando el bubble sort.
    void bubbleSort();
};

/* Le pregunta al usuario cuántas secuencias se van a leer y devuelve ese número.
 Utiliza una variable 'num_seq', que guarda el número de secuencias a producir ingresado, y el mismo
es devuelto. */
int userSequence();

/* Le pregunta al usuario en dónde se van a guardar los archivos de las secuencias y si se va a leer
un archivo para los números randoms o a crear uno nuevo. Toma como argumentos dos objetos fstream,
'fileSeqs' y 'fileNomrs', que serán asociados a los archivos con las secuencias random y normalizadas
respectivamente, un bool por referencia 'readFile' (que guarda si se va a leer un archivo de secuencias
randoms o a crear uno), y el número de secuencias ingresado por el usuario. Utililza las variables
'seqFilename' y 'normlicedFilename' para guardar los nombres de los archivos de las secuencias random
y normalizadas respectivamente. */
void makeFilenames(fstream &, fstream &, bool &, int &);

/* Crea las secuencias de números randoms en caso de no ser leídas. Toma como argumentos el vector
'arrSecuencias' en donde se van a guardar las secuencias de tipo 'Sequence', el objeto fstream 'fileSeqs'
asociado al archivo de las secuencias de núms. random, y el número de secuencias 'num_sec'. Utiliza las
variables 'start', 'end', para comenzar a calcular los clicks, que son guardados dentro de la variable
'clicks'. Utiliza la variable 'mayor' para guardar el número mayor por cada secuencia. */
void makeSequences(fstream &, int, vector <Sequence> &);

/* Lee las secuencias del archivo de secuencias de núms. random. Toma como argumentos dos objectos
fstream 'fileSeqs' y 'fileNorms', asociados a los archivos de secuencias randoms y secuencias normalizadas,
el núm. de secuencias 'num_secs' y el vector de secuencias 'arrSecuencias'. Utiliza variables como
'menor', que se engarga de guardar el número menor entre todas las secuencias, la variable 'menor_pos',
que guarda la posición (n, x) en donde se encuentra el número menor, donde n es el índice de la secuencia
y x es la posición dentro de la misma secuencia. También contiene variables como 'mayor', que se utiliza para
normalizar cada secuencia, en vez de tener que referirse al mismo como e.g. arrSecuencias[i].mayor por cada
número dentro de cada secuencia. Contiene la variable 'deviation', que guarda la desviación por cada secuencia,
la variable 'nrmlzCurrNum', que guarda el número normalizado actual, la variable 'media', que guarda la media
de cada secuencia. */
void getSequences(fstream &, fstream &, int, vector <Sequence> &);

// Nuevas funciones implementadas:

/* Calcula la desviación estándar de un arreglo de números normalizados. Toma como argumentos
el arreglo de núms. normalizados 'randomSeq' y la media de los mismos 'seq_mean'. Devuelve la
desviación estándar. Utiliza como variables 'std_deviation', que va acumulando el valor de
desviación por cada número en la secuencia y finalmente es devuelto por la función. */
double calcDeviation(double [], double);

/* Recibe como argumento un string 'word' cualquiera y devuelve el mismo string en lowercase.
Utiliza la variable 'lowered', que resulta ser un arreglo de caracteres, en donde se va a copiar
los caracteres de la variable 'word', pero en lowercase. Este arreglo es entonces devuelto como
string. */
string lowerCase(string);

/* Lee las secuencias de un archivo de secuencias randoms existente en caso de que el mismo no se vaya
a crear. Toma como argumentos el objeto fstream 'fileSeqs' asociado al archivo ya existente, el núm. de
secuencias, el vector de secuencias 'arrSecuencias' (que va a ser repleto de secuencias a medida que se
lea el archivo) y el número de secuencias 'num_sec'. Crea variables como 'id_text', que se encarga de leer
el dataID de la secuencia, la variable 'random_number', que guarda el número random leído al momento, la
variable 'clicks' que guarda el número de clicks de la secuencia, la variable 'mayor' que guarda el núm.
mayor de la secuencia y la variable 'line_counter', que guarda el contedo de las líneas leídas mientras
se lee el archivo. */
void readSequences(fstream &, int &, vector <Sequence> &);

/* Función que pregunta si el usuario desea leer un archivo de secuencias ya existence o crear uno nuevo.
Valida hasta cierto punto la respuesta del usuario y finalmente devuelve su respuesta con un literal booleano;
es decir, cierto si se va a leer de un archivo, o falso si no se va a leer. Utiliza la variable 'answer' para
guardar la respuesta del usuario y validarla. */
bool askReadFile();

// Últimas funciones implementadas:

/* Función que ordena el vector de secuencias utilizando el selection sort algorithm. Toma como argumentos
el vector de secuencias 'arrSecuencias', el núm. de secuencias 'numOfSeqs' y el objeto fstream asociado al
archivo de secuencias 'fileNorms' normalizadas. También desplega los clicks que se toma en ordenar el vector.
Utiliza las variables 'start', 'end' que se encargan de medir los clicks, y la variable 'clicks' que guarda
los clicks calculados. Utiliza la variable 'smallestMeanSeq', para guardar la secuencia con la media regresivamente
más pequeña, y la variable 'sm_meanIdx' para guardar el índice de dicha secuencia, y lograr el swap del selection
algorithm. */
void selectionSort(vector <Sequence>, int, fstream &);

/* Función que ordena el vector de secuencias utilizando el bubble sort algorithm. Toma como argumentos
el vector de secuencias 'arrSecuencias', el núm. de secuencias 'numsOfSeqs' y el objeto fstream "fileNorms"
asociado al archivo de secuencias normalizadas. También desplega los clicks que se toma en ordenar el vector.
Utiliza las variables 'start', 'end' y 'clicks' para medir y guardar los clicks, la variable 'swapped' para
guardar si se ha hecho un cambio u ordenamiento en la secuencia. */
void bubbleSort(vector <Sequence>, int, fstream &);

/* Función que se encarga de desplegar (en el archivo) las secuencias del vector ya ordenado. 
A su vez va ordenando las secuencias una por una, es decir; ordena los números en cada secuencia,
y luego los va desplegando uno a uno en el archivo de secuencias normalizadas. También calcula el
promedio que se tomó en ordenar cada secuencia y lo desplega (en la consola/terminal). Toma como
argumentos el vector de secuencias 'arrSecuencias', el núm. de secuencias 'numsOfSeqs', el objeto
fstream 'fileNorms' asociado al archivo de secuencias normalizadas, y un bool 'bubbleSort', que denota
si se van a ordenar las secuencias con el bubble sort o con el selection sort. De esta manera,
no habría necesidad de crear dos funciones aparte, para ordenar los números en las secuencias
con el bubble y selection sort, sino que el parámetro bool determina cuál algoritmo de ordenamiento
realizar, y lo demás aplica para ambos algoritmos. Utiliza las variables 'start', 'end' y 'clicks', para
medir y guardar los clicks tomados en ordenar cada secuencia, y la variable 'sumOfClicks', para acumular
todos los clicks y calcular su promedio. */
void outSortedArray(vector <Sequence>, int, fstream &, bool =true);


#endif
