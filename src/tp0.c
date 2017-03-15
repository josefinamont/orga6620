#include <stdio.h>
#include <string.h>
#include <getopt.h>

int main(int argc, char *argv[]) {

	int option = 0;
	const char* short_opt = "qbi:o:hV";
	struct option long_opt[] = {
	      {"version", no_argument, NULL, 'V'},
	      {"help", no_argument, NULL, 'h'},
		  {"input", no_argument, NULL, 'i'},
		  {"output", no_argument, NULL, 'o'},
		  {"qsort", no_argument, NULL, 'q'},
		  {"bsort", no_argument, NULL, 'b'},
	      {NULL,            0,                 NULL, 0  }
	};

	while ((option = getopt_long(argc, argv, short_opt, long_opt, NULL)) != -1) {
		switch(option) {
			case 'b': /*if (!strcmp(argv[1], "-h") || !strcmp(argv[1], "-H")) {
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
						printf("	-b, --bsort		Use bubblesort. \n");*/
					printf("Hello \n");
					break;
		}
	}

	return 0;
}
