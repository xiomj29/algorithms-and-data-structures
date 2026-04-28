/*Código: Nreinas
Versión 1.0 Abril 2023
Autor: Montes Jaimes Danna Xiomara

Compilación windows: gcc nreinas.c -o nreinas.exe -std=c11

Ejecución windows n reinas: nreinas.exe [n]*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//prototipos de funciones

void NReinas(int n);
bool nReinasBacktracking(int **tablero,int columna,int n);
bool validarPosicion(int **tablero,int  fila,int columna, int n);
void imprimir(int **tablero, int n);

//variables globales para el programa
int i, j;

int main(int argc, char *argv[]){

    //declaracion de variables para el programa
    int n;

    //Recibir por argumento el tamaño de n 
	if (argc!=2) 
	{
		printf("\nIndique el tamanio de n\n",argv[0]);
		exit(1);
	} 
	
	//Usa el argumento 1 del main y lo guarda en la variable n
	n = atoi(argv[1]); 

    //se manda a llamar a la funcion Nreinas
    NReinas(n);

    return 0;
}

/*Recibe como parámetro un número entero que indica el número de reinas que se deben colocar
en el tablero nxn. Inicializa un nuevo tablero con ceros y luego llama a la funcion auxiliar 
nReinasBacktracking(tablero, columna, n) con el tablero vacío y la columna inicial 0*/
void NReinas(int n){

    //declaración del tablero nxn y reservas memoria
    int **tablero=malloc(n*sizeof(int*));

    //se reserva memoria para columnas
    for(i=0; i<n;i++)
        tablero[i]=malloc(n*sizeof(int));

    
    //se inicializa en 0 el tablero
    for(i=0; i<n; i++)
        for(j=0; j<n; j++)
            tablero[i][j]=0;

    //se verifica si existe una solución, de ser así imprime el tablero
    if (nReinasBacktracking(tablero, 0, n))
        imprimir(tablero,n);
    else
        printf("No se encontró solución");

    //liberar memoria del tablero, para las filas y columnas
    for(i=0; i<n; i++)
        free(tablero[i]); 
    free(tablero);      
}


/*Es la función recursiva que implementa el algoritmo de backtracking para resolver las Nreinas.
Recibe como parámetros el tablero y columna actual y el número total de reinas (n). La funcion 
verifica si se han colocado todas las reinas en el tablero (es decir, si columna>=n), si es así 
retorna true, de lo contrario, intenta colocar una reina en cada fila posible de la columna actual
y llama recursivamente a la función con la siguiente columna. Cuando se encuentra una solución 
retorna true, de no ser así se restaura el tablero y retorna false.*/
bool nReinasBacktracking(int **tablero,int columna, int n){

    imprimir(tablero,n);

    //si se han colocado todas las reinas se retorna true
    if(columna >= n)
        return true;

    for(int fila=0; fila<n; fila++){
        /*si la reina se pudo colocar (funcion validarPosicion retorna true) entonces llama recursivamente
        e intenta colocar en la siguiente columna y si se puede retorna true*/
        if(validarPosicion(tablero, fila, columna,n)){

            /*si se pudo colocar la reina, se coloca un 1 en el tablero*/
            tablero[fila][columna]=1;

            if(nReinasBacktracking(tablero, columna+1, n))
                return true;
            
            /*backtracking, si no se puede colocar la reina se retira del tablero (colocando un 0)*/
            tablero[fila][columna]=0;
        }
        
    }
    /*si no se pudieron colocar las reinas, es decir, si no hay solución, se retorna false*/
    return false;
}


/*Verifica si es reguro colocar una reina en la posición(fila, columna) del tablero actual. 
Para hacerlo verifica que no haya otras reinas en la misma fila o en diagonales de la posición a*/
bool validarPosicion(int **tablero,int fila,int columna, int n){

    /*valida que no haya otra reina en la fila actual*/
    for(i=0; i<=columna-1;i++)
        if(tablero[fila][i]==1)
            return false;

    /*valida que no haya otra reina en la diagonal superior izquierda*/
    for(i=fila, j=columna;i>=0 && j>=0;i--,j--)
        if(tablero[i][j]==1)
            return false;

    /*valida que no haya otra reina en la diagonal inferior izquierda*/
    for(i=fila, j=columna; i< n && j>=0; i++, j--)   
        if(tablero[i][j]==1)
            return false;

    /*si se puede colocar la reina, devuelve true*/
    return true;
}

//imprimir tablero
void imprimir(int **tablero, int n){

    for(i=0; i<n; i++){
            for(j=0;j<n;j++){
                
                if(tablero[i][j])
                    printf(" R ");
                else
                    printf(" - ");
            }
            printf("\n");
        }
    printf("\n");
}