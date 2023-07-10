#define size 26
#define maxs 200 //cant maxima de caracteres para linea y significado
#define maxp 100 //cant maxima de caracteres para las palabras

//Definicion de estructura
typedef struct nodo {
    char valor;
    int finp;
    char significado[maxs];
    struct nodo *hijos[size];
} nodo;

//Declaracion de funciones
nodo *crear_nodo(char valor);
void add_palabras(nodo *raiz, char *palabra, char *significado);
nodo *buscar_palabra(nodo *raiz, char *palabra);
void print_prefijo(nodo *actual, char *prefijo);
void load_dic(nodo *raiz, char *nombre_arch);
void mostrar_ayuda();
