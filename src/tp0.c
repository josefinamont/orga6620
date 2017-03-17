#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <stdbool.h>

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

	printf("Recibi archivo %s \n", argopt);
}

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
				}
				break;
			case 'q':
				if (methodDefined) {
					printf("No puede ingresar los dos métodos a la vez, elija uno. \n");
					return 0;
				} else {
					sortMethod = option;
					methodDefined = true;
				}
				break;
			default:
			    printf ("Opción inválida. Para ver más información ingrese -h. \n");

		}
	}

	printf("Hola \n");

	// TODO
	// revisar que validaciones faltan, estan las basicas

	return 0;
}
