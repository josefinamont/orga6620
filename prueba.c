#include <stdio.h>
#include <stdlib.h>
#include <glib-2.0/glib.h>
#include <string.h>
//#include <glib-2.0/glib/galloca.h>
//#include <glib.h>
#define LIMITE 200

int main(int argc, char** argv) {

	 GList* list = NULL;
	 GList* elementoList = NULL;
	 char linea [LIMITE];
	 FILE* fichero;
	 fichero = fopen("alice.txt", "r");
	 //printf("The list is now %d items long\n", g_list_length(list));
	 /*list = g_list_prepend(list, "first");
	 list = g_list_prepend(list, "second");
	 list = g_list_prepend(list, "hola");
	 list = g_list_prepend(list, "gorsu");
	 list = g_list_prepend(list, "jochi");
	 // printf("The list is now %d items long\n", g_list_length(list));
	 //printf("The first item is '%s'\n", g_list_first(list)->data);
	 if (g_list_find(list,"jochi") == NULL) {
					 list = g_list_prepend(list, "jochi");
	 }*/
	 int contadorArchivo = 0;
	 const char delimitadores[4] = " ,.\n";
	 memset(&linea, 0, LIMITE);
	 while (fgets(linea, LIMITE, fichero) != NULL) {
		 linea[strlen(linea)-2] = '.';
		 linea[strlen(linea)-1] = '.';
		 char* token = strtok(linea, delimitadores);
		 while (token != NULL) {
			 char* palabra;
			 palabra = strdup(token);
			 //strcpy(palabra,token);
			 //palabra = token;
			 if (g_list_find(list,palabra) == NULL) {
				 list = g_list_prepend(list, palabra);
			 }
			 //printf ("%s\n", palabra);
			 token = strtok(NULL, delimitadores);
		}
		//contadorArchivo ++;
		memset(&linea, 0, LIMITE);
	 }

	 int contador = 0;
	 int largo = g_list_length(list);
	 list = g_list_reverse(list);
	 while (contador < largo) {
		 elementoList = g_list_nth ( list, contador);
		 printf("el elemento: %s\n", elementoList->data);
		 contador++;
	 }
	 g_list_free(list);
	 return 0;
}
