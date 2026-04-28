/*Código: Implementación del problema de mochila con busqueda exhaustiva
Versión 1.0 Enero 2024
Autor: Montes Jaimes Danna Xiomara

Compilación windows: gcc mochila_a.c -o mochila_a.exe -std=c11*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Knapsack(int c, int i, int n, int *w, int *v);
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
    int c, i, n, *w, *v;
    
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

    // Lectura del peso de los n objetos
    for (i = 0; i < n; i++)
        scanf("%d", &w[i]);

    // Lectura del valor de los n objetos
    for (i = 0; i < n; i++)
        scanf("%d", &v[i]);

    // se manda a llamar a la funcion knapsack y muestra la máxima ganancia 
    printf("Ganancia maxima: %d\n", Knapsack(c, 0, n, w, v));

    //liberacion de memoria
    free(w);
    free(v);

    return 0;
}

/*retorna la mayor ganancia obtenida*/
int max(int a, int b)
{
    return a > b ? a : b;
}

/*función para resolver el problema de mochila con la mayor ganancia*/
int Knapsack(int c, int i, int n, int *w, int *v)
{
    /*se verifica si la capacidad de la mochila es cero o si ya no hay más elementos disponibles 
    para agregar, de ser así, devuelve cero*/
    if (c == 0 || i == n)
        return 0;
    /*si el peso del elemento es mayor que la capacidad que tiene la mochila, se llama a la funcion
    knapsack con el elemento que sigue para probar con ese*/    
    if (w[i] > c)
        return Knapsack(c, i + 1, n, w, v);
    /*si el peso del elemento actual es menor o igual a la capacidad de la mochila, se calcula el valor
    maximo que se puede obtener con el elemento actual y sin ese elemento.*/    
    int v1 = v[i] + Knapsack(c - w[i], i + 1, n, w, v);
    int v2 = Knapsack(c, i + 1, n, w, v);

    /*compara los dos valores y devuelve el mayor de ellos*/
    return max(v1, v2);
}
