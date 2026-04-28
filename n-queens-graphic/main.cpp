#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <graphics.h>

void colocarReinas(int reinas[],int nreinas, int fila);
int comprobar(int reinas[], int nreinas, int fila);
int checkFileExists(char *filename); //Revisa si un archivo existe
int addSolutions(char *filename); //añade soluciones al archivo
void addFile(int nreinas);

typedef struct{ //struct para las soluciones
	
	char solucion[200];
	
}Solution;

int cont = 0, queen=0; //variable de control que indica el número de solucion

int main(int argc, char *argv[]) {
	
	
	//Variable de control
	int i;
	//"nreinas" será el numero de reinas
	int nreinas;
	//"*reinas" será un vector que represente la columna mediante el 
	//indice y la fila mediante el valor que tenga un indice
	int *reinas;
	
	
	printf("Bienvenido al problema de las N Reinas, Ingrese el  numero de reinas:\n");
	scanf("%d",&nreinas);
	queen = nreinas;
	reinas = (int *)malloc(nreinas*sizeof(int));
	
	for(i = 0;i<nreinas;i++){
		
		reinas[i] = -1;
		
	}
	
	colocarReinas(reinas,nreinas,0);
	
	free(reinas);
	
	return 0;
}


void colocarReinas(int reinas[],int nreinas, int fila){
	
	int i;
	
	/*
	Este es el caso base, donde se indica si se ha encontrado
	una solución, lo que implica que ya no hay mas reinas por colocar
	y se han colocado todas las n reinas en el tablero
	*/
	if(fila == nreinas){
		printf("Solucion No.%d:\n",++cont);
		for(i = 0; i < nreinas;i++){
			printf("[ %d ]\t",reinas[i]);
			
			addFile(nreinas); //crea el archivo con las soluciones
			
			/*interpretacion de solucion 
			4 reinas 
			
			indice del arreglo: columna
			valor en el índice del arreglo: fila
			
			             0  1  2  3
			solucion 1: [1][3][0][2]   
			  
				0   1   2   3
			0  [-] [-] [x] [-]
			1  [x] [-] [-] [-]
			2  [-] [-] [-] [x]
			3  [-] [x] [-] [-]
			
			             0  1  2  3			           
			solucion 2: [2][0][3][1]
			
				0   1   2   3
			0  [-] [x] [-] [-]
			1  [-] [-] [-] [x]
			2  [x] [-] [-] [-]
			3  [-] [-] [x] [-]
			
			*/
			
		}
		
		printf("\n",fila,nreinas);
	}
	//Aun no se han colocado todas las reinas
	else{
		
		for(reinas[fila]=0;reinas[fila]<nreinas;reinas[fila]++){
			
			if( comprobar(reinas, nreinas, fila) == 1){ //verifica si se puede colocar una reina en x casilla 
				
				colocarReinas(reinas, nreinas, fila+1);
				
			}
			
		}
		
	}
	
}


/*
Comprueba si la reina "n" se puede colocar en una casilla
---------------------------------------------------------
Parámetros:
	fila - Es la fila donde se quiere colocar una reina
	reinas[] - Es el arreglo con las posiciones de las reinas
	nreinas - Es el numero de reinas
*/
int comprobar(int reinas[], int nreinas, int fila){
	
	int i;
	
	//Repite hasta que "i" coincida con "fila"
	for(i=0;i<fila;i++){
		
		//Comprueba si se puede colocar la reina en una casilla
		//Evaluando la fila y las diagonales
		if( ( reinas[i]==reinas[fila] ) || ( abs(fila-i) == abs(reinas[fila]-reinas[i]) ) ){
			
			return 0;
			
		}
		
	}
	
	return 1;
	
}


void addFile(int nreinas){ //agrega las soluciones al archivo
	

	
	//variables de control
	int option, i = 0;
	char soluciones[200];
	
	sprintf(soluciones,"Solucion%d.txt",nreinas); //pone el nombre al archivo de acuerdo a n reinas
	
				checkFileExists(soluciones); //revisa si existe el archivo
				//Si la funcion devuelve 1, significa que se agrego un conjunto de soluciones
				//Si devuelve 0, significa que hubo un error
				if(addSolutions(soluciones) == 0){
									
					printf("No se pudo registrar la solucion...");
									
				}
	/*system("pause");
	system("cls");*/
		
	
}

//Comprueba si existe un archivo
int checkFileExists(char *filename){
	
	//Abre el archivo en modo lectura para no sobreescribirlo/crearlo
	FILE *file = fopen(filename,"r");
	
	//Si el archivo no se pudo abrir, el puntero es NULL
	//Si se logró abrir, se cierra y se retorna 1
	if(file != NULL){
		
		//cierra el archivo	
		fclose(file);
		return 1;
	}
	else{
		
		//Cierra el archivo para evitar errores
		fclose(file);
		
		//Como el archivo no existe, lo crea con "w"
		file = fopen(filename,"w");
		fclose(file);
			
		return 1;
	}
}

int addSolutions(char *filename){
	
	//Abre el archivo en modo "append" para agregar al final
	FILE *file = fopen(filename,"a+");
	//Variable para almacenar e imprimir los resultados
	Solution new_solution;
	//char para almacenar lo ingresado
	char linea[230];
	//Variables de control
	int i = 0, j;
	
	if(file == NULL){
		
		//se cierra pero no existe un archivo 
		fclose(file); 
		return 0;
		
	}
	else{
		
		//Limpia el buffer
		fflush(stdin);
		//Envia con nombre la solucion del problema
		scanf("%[^\n]",new_solution.solucion);
		//Limpia nuevamente el buffer para evitar errores en los datos introducidos
		fflush(stdin);
		
		//Cierra el archivo
		fclose(file);
		return 1;
	}
	
}
