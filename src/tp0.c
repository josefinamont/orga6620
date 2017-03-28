#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define QUICKSORT 'q'
#define BUBBLESORT 'b'
#define LIMITE 200

void quickSort(char** unorderedList, int words);
void bubbleSort(char ** unorderedList, int words);
int compareWords(char * firstWord, char * secondWord);
void qs(char ** unorderedList,int leftLimit,int rightLimit);

void fillOutputFile(char ** result, FILE* output, int words);

/*GCompareDataFunc func(char* word1, char* word2) {
	return strcmp(word1, word2);
}*/

// verifica que el archivo no esté vacío
bool empty(FILE* file) {
    long savedOffset = ftell(file);
    fseek(file, 0, SEEK_END);

    if (ftell(file) == 0) {
        return true;
    }

    fseek(file, savedOffset, SEEK_SET);
    return false;
}

// primero valida que exista
// despues que no esté vacío
bool validFile(FILE* file, char modo, char* argopt) {
	if (file == NULL) {
		printf("El archivo %s no existe, por favor ingrese un archivo existente \n", argopt);
		return false;
	}

	if (empty(file) && modo != 'w') {
		printf("El archivo %s está vacío, por favor ingrese un archivo no vacío \n", argopt);
		return false;
	}

	printf("Se recibió el archivo %s \n", argopt);
	return true;
}

char ** parseFile(FILE* file, int words) {
	 rewind(file);
	 char linea [LIMITE];
	 const char delimitadores[30] = " ,;.\n\"\'-()[]_:?¿¡!&/#·*";
	 memset(&linea, 0, LIMITE);
	 char ** list = calloc(words, sizeof(char *));
	 int index = 0;
	 while (fgets(linea, LIMITE, file) != NULL) {
		 linea[strlen(linea)-2] = '.';
		 linea[strlen(linea)-1] = '.';
		 char* token = strtok(linea, delimitadores);
		 while (token != NULL) {
			 char* palabra;
			 //if (strcmp(token,"s") && (strcmp(token,"re"))) {
			 palabra = strdup(token);;
			 //palabra[0]= tolower(palabra[0]);
			 list[index] = palabra;
			 index++;
			 //}
			 token = strtok(NULL, delimitadores);
		}
		memset(&linea, 0, LIMITE);
	 }
	 /*for(int i = 0; i < words; i++){
	 	 printf("%s\n", list[i]);
		 printf("%d\n", i);
	  }*/
     fclose(file);
	 //(*maxLog) = index;
	 //printf("maximoLogico: %d", index);
     return list;
}

int calcularTamanio(FILE* file) {
	char linea [LIMITE];
	const char delimitadores[30] = " ,;.\n\"\'-()[]_:?¿¡!&/#·*";
	int contador = 0;

	while (fgets(linea, LIMITE, file) != NULL) {
		 linea[strlen(linea)-2] = '.';
		 linea[strlen(linea)-1] = '.';
		 char* token = strtok(linea, delimitadores);
		 while (token != NULL) {
			 contador ++;
			 token = strtok(NULL, delimitadores);
		 }
	}
	contador--;
	printf("tamanio %d\n",contador);
	return contador;
}

void sortWordsOf(FILE* inputFile, FILE* outputFile, char sortMethod) {

	//int maxLogico;
	int tamanio = calcularTamanio(inputFile);
	char** listWords = parseFile(inputFile, tamanio);//, &maxLogico);
	if (sortMethod == QUICKSORT) {
		printf("Tengo que ordenar con el método quicksort \n");
		clock_t inicio,fin;
		inicio = clock();
		quickSort(listWords, tamanio);
		fin = clock();
		// obtenemos y escribimos el tiempo en segundos
		printf("Tiempo empleado: %f\n",(fin - inicio)/(double) CLOCKS_PER_SEC);

	} else if (sortMethod == BUBBLESORT) {
		printf("Tengo que ordenar con el método bubblesort \n");
    	clock_t inicio,fin;
		inicio = clock();
		bubbleSort(listWords, tamanio);
		fin = clock();
		// obtenemos y escribimos el tiempo en segundos
		printf("Tiempo empleado: %f\n",(fin - inicio)/(double) CLOCKS_PER_SEC);
	}
	fillOutputFile(listWords, outputFile, tamanio);
	for(int i = 0; i < tamanio; i++){
		free(listWords[i]);
	}
	free(listWords);
}

void fillOutputFile(char ** result, FILE* output, int words){
	for(int i = 0; i < words; i++){
		//TODO completar casos de error
		fputs(result[i], output);
		fputs("\n", output);
	};
	fclose(output);
}


//gcc $(pkg-config --cflags --libs glib-2.0) -o ejemplo prueba.c -lglib-2.0

int main(int argc, char *argv[]) {

	int option = 0;
	const char* short_opt = "qbi:o:hV";
	struct option long_opt[] = {
	      {"version", no_argument, NULL, 'V'},
	      {"help", no_argument, NULL, 'h'},
		  {"input", required_argument, NULL, 'i'},
		  {"output", required_argument, NULL, 'o'},
		  {"qsort", no_argument, NULL, 'q'},
		  {"bsort", no_argument, NULL, 'b'},
	      {NULL, 0, NULL, 0}
	};
	FILE* inputFile;
	FILE* outputFile;
	char sortMethod;
	bool methodDefined = false;

	if (argc == 1) {
		printf("Debe ingresar algún argumento, para mas información ingrese -h \n");
		return 0;
	}

	while ((option = getopt_long(argc, argv, short_opt, long_opt, NULL)) != -1) {
		switch(option) {
			case 'V':
				printf("TP0 de la materia Organización de Computadoras \n");
				printf("Alumnos: \n");
				printf("	Flórez Del Carpio Christian\n	Montenegro Josefina \n	Riego Leonardo \n");
				break;
			case 'h':
				printf("Usage: \n");
				printf("	%s -h \n", argv[0]);
				printf("	%s -V \n", argv[0]);
				printf("	%s [options] file \n", argv[0]);
				printf("Options: \n");
				printf("	-V, --version		Print version and quit. \n");
				printf("	-h, --help		Print this information. \n");
				printf("	-o, --output		Path to output file. \n");
				printf("	-i, --input		Path to input file. \n");
				printf("	-q, --qsort		Use quicksort. \n");
				printf("	-b, --bsort		Use bubblesort. \n");
				break;
			case 'i':
				inputFile = fopen(optarg, "r");
				if (!validFile(inputFile, 'r', optarg)) {
					return 0;
				}
				break;
			case 'o':
				outputFile = fopen(optarg, "w");
				if (!validFile(outputFile, 'w', optarg)) {
					return 0;
				}
				break;
			case 'b':
				if (methodDefined) {
					printf("No puede ingresar los dos métodos a la vez, elija uno. \n");
					return 0;
				} else {
					sortMethod = option;
					methodDefined = true;
					printf("Se definió bubblesort como método de ordenamiento \n");
				}
				break;
			case 'q':
				if (methodDefined) {
					printf("No puede ingresar los dos métodos a la vez, elija uno. \n");
					return 0;
				} else {
					sortMethod = option;
					methodDefined = true;
					printf("Se definió quicksort como método de ordenamiento \n");
				}
				break;
			default:
			    printf ("Opción inválida. Para ver más información ingrese -h. \n");
		}
	}

	if (argc == 5 && sortMethod != QUICKSORT && sortMethod != BUBBLESORT) {
		printf("Por defecto el método de ordenamiento es bubblesort \n");
		sortMethod = BUBBLESORT;
	}

	sortWordsOf(inputFile, outputFile, sortMethod);
	return 0;
}


void bubbleSort(char **unorderedList, int words) {
    char * actual = NULL;
    char * next = NULL;
    char * temporal = NULL;
    for(int i = 0; i < words -1 ; i++){
        for(int j = 0; j < words - i - 1; j++){
            if(compareWords(unorderedList[j], unorderedList[j+1]) == 1) {
                temporal = unorderedList[j];
                unorderedList[j] = unorderedList[j+1];
                unorderedList[j+1] = temporal;
            }
        }
    }
}

void quickSort(char ** unorderedList, int words){
   qs(unorderedList, 0, words - 1);
}

void qs(char ** unorderedList, int leftLimit,int rightLimit){
   int left,right;
   char * pivot;
   char * temporal = NULL;
   left = leftLimit;
   right = rightLimit;
   pivot = unorderedList[(left+right)/2];

   do{
     	while(compareWords(unorderedList[left], pivot) == -1 && left < rightLimit){
		  	left++;
	   }
     while(compareWords(pivot, unorderedList[right]) == -1 && right > leftLimit){
		   	right--;
	   }
       if(left <= right){
           temporal = unorderedList[left];
           unorderedList[left] = unorderedList[right];
           unorderedList[right] = temporal;
           left++;
           right--;
       }
   } while(left<=right);
   if(leftLimit<right){qs(unorderedList,leftLimit,right);}
   if(rightLimit>left){qs(unorderedList,left,rightLimit);}
}

//Devuelve 1 si firstWord > secondWord, -1 si firstWord < secondWord, 0 si son iguales
int compareWords(char * firstWord, char * secondWord){
    for(int i = 0; firstWord[i]; i++){
        if(firstWord[i] == secondWord[i]){
            if(secondWord[i+1] && !firstWord[i+1]){
                return -1;
            }
            if(!firstWord[i+1] && !secondWord[i+1]){
                return 0;
            }
            if(!secondWord[i]){
                return 1;
            }
        }
        if(firstWord[i] > secondWord[i]) {
            return 1;
        } else if (firstWord[i] < secondWord[i]){
            return -1;
        }

    }
}
