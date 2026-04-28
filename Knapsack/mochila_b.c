/*Código: Implementación del problema de mochila con bpusqueda exhaustiva
Versión 1.0 Abril 2023
Autor: Montes Jaimes Danna Xiomara

Compilación windows: gcc mochila_b.c -o mochila_b.exe -std=c11*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Knapsack(int c, int i, int n, int *w, int *v, int *s);
int max(int a, int b);

int main(int argc, char *argv[])
{
    /*Variables para el programa:
      - c es el peso o capacidad de la mochila
      - n es la cantidad de elementos que se tienen
      - i es el índice del elemento en el array
      - *w es el puntero al arreglo de pesos de cada elemento
      _ *v es el puntero al arreglo de valores de los elementos
    */
    int c, i, n, *w, *v,*s;
    
    // Recibir por argumento el tamaño de n y la capacidad de la mochila
    if (argc != 3)
    {
        exit(1);
    }
    c = atoi(argv[1]);
    n = atoi(argv[2]);
    //reservar memoria
    w = malloc(n * sizeof(int));
    v = malloc(n * sizeof(int));
    s = (int *)calloc(n, sizeof(int));


    // Lectura del peso de los n objetos
    for (i = 0; i < n; i++)
        scanf("%d", &w[i]);

    // Lectura del valor de los n objetos
    for (i = 0; i < n; i++)
        scanf("%d", &v[i]);

    // se manda a llamar a la funcion knapsack y muestra la máxima ganancia 
    printf("Ganancia maxima: %d\n", Knapsack(c, 0, n, w, v, s));

    //objetos que se van a incluir
    printf("Objetos seleccionados:\n");
    for(i=0; i<n; i++)
        if(s[i])
            printf("\nObjeto: %d, Peso: %d, Valor %d", i+1, w[i], v[i]);

    //liberacion de memoria
    free(w);
    free(v);
    free(s);

    return 0;
}

/*retorna la mayor ganancia obtenida*/
int max(int a, int b)
{
    return a > b ? a : b;
}

/*función para resolver el problema de mochila con el listado de objetos para la mayor ganancia*/
int Knapsack(int c, int i, int n, int *w, int *v, int *s) {

    /*se verifica si la capacidad de la mochila es cero o si ya no hay más elementos disponibles 
    para agregar, de ser así, devuelve cero*/
    if (c==0 || i == n)
        return 0;
    /*si el peso del elemento es mayor que la capacidad que tiene la mochila, se llama a la funcion
    knapsack con el elemento que sigue para probar con ese*/    
    if (w[i] > c)
        return Knapsack(c, i + 1, n, w, v, s);

    //declaracion de punteros, asignacion de memoria e inicialización en ceros
    int *a = (int *)calloc(n, sizeof(int));
    int *b = (int *)calloc(n, sizeof(int));

    // Se incluye el elemento actual asignándole 1 a a[i]
    a[i] = 1;

    /* ocurre si incluimos el elemento actual (arreglo a), se reserva memoria para b, que llevara
    los elementos que se incluyen en la mochila, luego se copia el contenido del arreglo s en el arreglo*/
    int v1 = v[i] + Knapsack(c - w[i], i + 1, n, w, v, a);
    /* ocurre si no se incluye el elemento actual (arreglo b), se reserva memoria para b, que llevara
    los elementos que se incluyen en la mochila, luego se copia el contenido del arreglo s en el arreglo*/
    int v2 = Knapsack(c, i + 1, n, w, v, b);

    //se declara variable que contiene el valor máximo de los dos
    int valor_max = max(v1, v2);

     /*se itera sobre el arreglo para combinar la seleccion de los elementos actuales con la solucion 
    actual, dependiendo de cual da la ganancia máxima*/
    if (v1 == valor_max) {
        //si se incluye el elemento actual
        for (int i = 0; i < n; i++)
            s[i] |= a[i];
    }
    else {
        //si no se incluye el elemento actual
        for (int i = 0; i < n; i++)
            s[i] |= b[i];
    }

    // Liberar la memoria dinámica
    free(a);
    free(b);

    return valor_max;
}