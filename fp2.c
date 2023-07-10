#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "p2.h"

//Funcion que se encarga de crear los nodos
nodo *crear_nodo(char valor) {
    nodo *nuevo_nodo = (nodo*) malloc(sizeof(nodo));
    nuevo_nodo->valor = valor;
    nuevo_nodo->finp = 0;
    nuevo_nodo->significado[0] = '\0';
    for (int i = 0; i < 26; i++) {
        nuevo_nodo->hijos[i] = NULL;
    }
    return nuevo_nodo;
}

//funcion para llenar el arbol con las palabras
void add_palabras(nodo *raiz, char *palabra, char *significado) {
    nodo *actual = raiz;
    for (int i = 0; i < strlen(palabra); i++) {
        int indice = palabra[i] - 'a';
        if (actual->hijos[indice] == NULL) {
            actual->hijos[indice] = crear_nodo(palabra[i]);
        }
        actual = actual->hijos[indice];
    }
    actual->finp = 1;
    strcpy(actual->significado, significado);
}

//se usa para buscar una palabra en el arbol
nodo *buscar_palabra(nodo *raiz, char *palabra) {
    nodo *actual = raiz;
    for (int i = 0; i < strlen(palabra); i++) {
        int indice = palabra[i] - 'a';
        if (actual->hijos[indice] == NULL) {
            return NULL;
        }
        actual = actual->hijos[indice];
    }
    if (actual->finp) {
        return actual;
    } else {
        return NULL;
    }
}

//imprime todas las palabras con un prefijo
void print_prefijo(nodo *actual, char *prefijo) {
    if (actual->finp) {
        printf("%s: %s\n", prefijo, actual->significado);
    }
    for (int i = 0; i < 26; i++) {
        if (actual->hijos[i] != NULL) {
            char nuevo_prefijo[maxs];
            sprintf(nuevo_prefijo, "%s%c", prefijo, actual->hijos[i]->valor);
            print_prefijo(actual->hijos[i], nuevo_prefijo);
        }
    }
}

//carga la informacion desde un archivo .dic
void load_dic(nodo *raiz, char *nombre_arch){
    FILE *archivo = fopen(nombre_arch, "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo \"%s\"\n", nombre_arch);
        return;
    } else printf("Se ha cargado correctamente el archivo\n");
    char linea[maxs];
    char palabra[maxp];
    char significado[maxs];
    while (fgets(linea, maxs, archivo) != NULL) {
        if (linea[0] == '+') {
            if (strlen(linea) > 1) {
                strcat(significado, &linea[1]);
                nodo *palabra_encontrada = buscar_palabra(raiz, palabra);
                if (palabra_encontrada != NULL) {
                    strcpy(palabra_encontrada->significado, significado);
                }
            }
        } else {
            sscanf(linea, "%s %[^\n]", palabra, significado);//Coloca la palabra en "palabra" y el resto en "significado"
            add_palabras(raiz, palabra, significado);
            significado[0] = '\0'; // Limpiar el significado para evitar que se agregue a la siguiente palabra
            strcat(significado, &linea[strlen(palabra)]); // Toma el resto de la línea como el significado
        }
    }
    fclose(archivo);
}

//se imprimen todos los comandos que se pueden utilizar y sus funciones
void mostrar_ayuda(){
	system("clear");
	printf("'l' Funciona para cargar el archivo\n");
    printf("'s' Funciona para buscar la definicion de una palabra\n");
    printf("'p' Funciona para buscar las definiciones de palabras por un prefijo\n");
    printf("'q' Sale de la aplicacion\n");
}
