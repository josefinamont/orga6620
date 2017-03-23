#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <stdbool.h>
#include <glib-2.0/glib.h>

#define QUICKSORT 'q'
#define BUBBLESORT 'b'
#define LIMITE 200

void quickSort(GList * unorderedList);
void bubbleSort(GList * unorderedList);
int compareWords(char * firstWord, char * secondWord);
void qs(GList * unorderedList,int leftLimit,int rightLimit);

void fillOutputFile(GList * result, FILE* output);

GCompareDataFunc func(char* word1, char* word2) {
	return strcmp(word1, word2);
}

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

GList* parseFile(FILE* file) {
	 GList* list = NULL;
	 char linea [LIMITE];
	 const char delimitadores[28] = " ,;.\n\"-()[]_:\ï\»?¿¡!&/#·*";
	 memset(&linea, 0, LIMITE);
	 while (fgets(linea, LIMITE, file) != NULL) {
		 linea[strlen(linea)-2] = '.';
		 linea[strlen(linea)-1] = '.';
		 char* token = strtok(linea, delimitadores);
		 while (token != NULL) {
			 char* palabra;
			 palabra = strdup(token);;
			 if (g_list_find_custom(list,palabra, func) == NULL) {
				 list = g_list_prepend(list, palabra);
			 }
			 token = strtok(NULL, delimitadores);
		}
		memset(&linea, 0, LIMITE);
	 }
     fclose(file);
	 return list;
}

void sortWordsOf(FILE* inputFile, FILE* outputFile, char sortMethod) {
	//listWords contiene las palabras parseadas
	GList* listWords = parseFile(inputFile);
	if (sortMethod == QUICKSORT) {
		printf("Tengo que ordenar con el método quicksort \n");
    	quickSort(listWords);
	} else if (sortMethod == BUBBLESORT) {
		printf("Tengo que ordenar con el método bubblesort \n");
    	bubbleSort(listWords);
	}
	fillOutputFile(listWords, outputFile);
}

void fillOutputFile(GList * result, FILE* output){
	GList * iterator = NULL;
	for(iterator = result; iterator; iterator = iterator->next){
		//TODO completar casos de error
		fputs((char *) iterator->data, output);
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


void bubbleSort(GList *unorderedList) {
    GList * actual = NULL;
    GList * next = NULL;
    gpointer * temporal = NULL;
    int size = g_list_length (unorderedList);
    for(int i = 0; i < size -1 ; i++){
        actual = g_list_first(unorderedList);
        for(int j = 0; j < size - i - 1; j++){
            next = g_list_next(actual);
            if(compareWords((char *)actual->data, (char *)next->data) == 1) {
                temporal = actual->data;
                actual->data = next->data;
                next->data = temporal;
            }
            actual = g_list_next(actual);
        }
    }
}

void quickSort(GList * unorderedList){
   qs(unorderedList, 0, g_list_length (unorderedList) - 1);
}

void qs(GList * unorderedList,int leftLimit,int rightLimit){
   int left,right;
   gpointer * pivot;
   gpointer * temporal = NULL;
   GList * pivotValue = NULL;
   GList * actual = NULL;
   left = leftLimit;
   right = rightLimit;
   pivot = g_list_nth(unorderedList, (left+right)/2)->data;

	GList * leftValue = NULL;
	GList * rightValue = NULL;


   do{
	   leftValue = g_list_nth(unorderedList, left);
	   rightValue = g_list_nth(unorderedList, right);

       while(compareWords((char *)leftValue->data, (char *)pivot) == -1 && left < rightLimit){
		  left++;
		  leftValue = leftValue->next;
	   }
       while(compareWords((char *)pivot, (char *)rightValue->data) == -1 && right > leftLimit){
		   right--;
		   rightValue = rightValue->prev;
	   }
       if(left <= right){
           temporal = leftValue->data;
           leftValue->data = rightValue->data;
           rightValue->data = temporal;
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
