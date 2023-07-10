#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "p2.h"

void main() {
    nodo *raiz = crear_nodo('\0');
    char opcion[2];
    while(1){
        printf("> ");
        scanf("%s",opcion);
        //carga la informacion de un archivo
        if (opcion[0]=='l'){ 
            printf("Introduzca el nombre del archivo\n");
            char nombre_arch[50]; //Nombre del archivo
            scanf("%s", nombre_arch);
            strcat(nombre_arch, ".dic");
            load_dic(raiz, nombre_arch);
        } else 
            //buscar la definicion de una palabra
            if (opcion[0]=='s'){
                printf("Introduzca la palabra a buscar\n");
                char word[17];
                scanf("%s", word);
                system("clear");
                nodo *palabra_encontrada = buscar_palabra(raiz, word);
                if (palabra_encontrada != NULL) {
                    printf("%s: %s\n", word, palabra_encontrada->significado);
                } else {
                    printf("La palabra \"%s\" no se encuentra en el diccionario.\n", word);
                }
        } else 
            //muestra las palabras con el prefijo
            if (opcion[0]=='p'){
                printf("Introduzca el prefijo\n");
                char prefijo[9];//Prefijo
                int valido=1;
                scanf("%s", prefijo);
                nodo *actual = raiz;
                system("clear");
                for (int i = 0; i < strlen(prefijo); i++) {//for para determinar si hay palabras con el prefijo
                    int indice = prefijo[i] - 'a';
                    if (actual->hijos[indice] == NULL) {
                        printf("No hay palabras en el diccionario que comiencen con el prefijo \"%s\".\n", prefijo);
                        valido=0;
                        break;
                    }
                    actual = actual->hijos[indice];
                }
                if (valido == 1)
                    print_prefijo(actual, prefijo);
        } else 
            //ofrece ayuda
            if (opcion[0]=='h'){
                system("Clear");
                mostrar_ayuda();
        } else 
            //sale del programa
            if (opcion[0]=='q'){
                printf("Gracias por utilizar el programa\n");
                break;
        } else printf("Comando no reconocido\n");
    }
}
