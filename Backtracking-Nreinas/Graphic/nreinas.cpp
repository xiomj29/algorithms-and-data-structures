#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <graphics.h>


void colocarReinas(int reinas[],int nreinas, int fila);
int comprobar(int reinas[], int nreinas, int fila);
void pintarTablero(int reinas[], int nreinas, int isSolved);
void pintarReina(int x, int y);
int checkFileExists(char *filename); //Revisa si un archivo existe
int addSolutions(char *filename, int reinas[], int nreinas); //añade soluciones al archivo
void addFile(int reinas[], int nreinas);

int cont = 0, ymax;
char sol[50], *solucion;

int main(int argc, char *argv[]) {
	
	solucion = sol;
	//Variable de control
	int i;
	//"nreinas" será el numero de reinas
	int nreinas;
	//"*reinas" será un vector que represente la columna mediante el 
	//indice y la fila mediante el valor que tenga un indice
	int *reinas;
	
	
	printf("Bienvenido al problema de las N Reinas, Ingrese el  numero de reinas:\n");
	scanf("%d",&nreinas);

	reinas = (int *)malloc(nreinas*sizeof(int));
	
	for(i = 0;i<nreinas;i++){
		
		reinas[i] = -1;
		
	}
	
	initwindow(300+100*nreinas,1000)
	colocarReinas(reinas,nreinas,0);
	
	free(reinas);
	getch();
	closegraph();
	
	return 0;
}


void colocarReinas(int reinas[],int nreinas, int fila){
	
	int i, isSolved = 0;
	
	/*
	Este es el caso base, donde se indica si se ha encontrado
	una solución, lo que implica que ya no hay mas reinas por colocar
	y se han colocado todas las n reinas en el tablero
	*/
	if(fila == nreinas){
		isSolved = 1;
	}

	pintarTablero(reinas, nreinas, isSolved); //pinta el tablero con las reinas colocadas
	
	if(fila == nreinas){ //Si se ha colocado todas las reinas
		
		//Se imprime la solución encontrada
		printf("Solucion %d: ", ++cont);
		for(i = 0; i < nreinas; i++){
			printf("[ %d]", reinas[i]);
		}
		printf("\n", fila, nreinas);
		
		addFile(reinas, nreinas); //Agrega la solucion al archivo
		
	}
	else{

		for(reinas[fila] = 0; reinas[fila] < nreinas; reinas[fila]++){
			
			//Comprueba si se puede colocar la reina en la fila
			if(comprobar(reinas, nreinas, fila) == 1){
				
				//Si se puede colocar, se llama recursivamente a la funcion
				colocarReinas(reinas, nreinas, fila + 1);

				pintarTablero(reinas, nreinas, isSolved); //Pinta el tablero nuevamente
				
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
	nreinas - Es el numero de reinas*/

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

void pintarTablero(int reinas[], int nreinas, int isSolved){
	
	cleardevice();
	int x = 100; y =100;
	int i = 0, j = 0, odd = 0;
	char num[2];

	settextstyle(1, 0, 3);

	for(i = 0; i < nreinas; i++){
		x = x + 100;
		sprintf(num, "%d", i);
		outtextxy(x + 50, y - 50, num);
	}
	x = 100;

	for(i = 0; i < nreinas; i++){
		y = y + 100;
		sprintf(num, "%d", i);
		outtextxy(x + 50, y - 50, num);
	}
	y = 100;

	for(i = 0; i< nreinas; i++){
		for(j = 0; j < nreinas; j++){

			x = x + 100;
			rectangle(x, y, x + 100, y + 100);

			if((i % 2 == 0) && (j % 2 == 0)){
				setfillstyle(3,7);
				floodfill(x + 1, y + 1, 15);
				odd++;
			}
			else if((i % 2 != 0) && (j % 2 != 0)){
				setfillstyle(3,7);
				floodfill(x + 1, y + 1, 15);
				odd++;
			}

			if(reinas[i] == j){
				pintarReina(x , y);
			}
		}	

		x = 100;
		y = y + 100;
	}

	ymax = y;

	if(isSolved == 1){
		sprintf(solucion, "Solucion No. %d encontrada", ++cont);
		outtextxy(100, ymax + 50, solucion);
	}

	getch();

}

void pintarReina(int x, int y){

	int crown[20]= {x+15, y+20, x+25, y+70, x+75, y+70, x+85, y+20, x+65, y+50,
					x+65, y+20, x+50, y+50, x+35, y+20, x+35, y+50,
					x+15, y+20};

	int franja[10] = {
		x+25, y+70,
		x+75, y+70,
		x+75, y+75,
		x+25, y+75,
		x+25, y+70,
	};

	//Puntos para pintar la base
	//                [x]     [y]
	int base[10] = {
		x+25, y+75,
		x+25, y+85,
		x+75, y+85,
		x+75, y+75,
		x+25, y+75,
	};

	setfillstyle(1,7);
	//Pinta la corona
	fillpoly(10,crown);

	//Pinta la base de la corona
	fillpoly(5,base);

	//Pinta la base de la corona
	setfillstyle(1,14);
	fillpoly(5,franja);	
	
	setfillstyle(1,2);
	fillellipse(x+15-3,y+20-5,5,5); //Punto 1
	fillellipse(x+85+3,y+20-5,5,5); //Punto 2

	setfillstyle(1,4);
	fillellipse(x+65,y+20-5,5,5);   //Punto 3
	fillellipse(x+35,y+20-5,5,5);   //Punto 4

	//Pinta gemas en las reinas
	setfillstyle(1,4);

	fillellipse(x+30,y+60,5,5);
	fillellipse(x+70,y+60,5,5);
	//Gema de en medio
	setfillstyle(1,1);

	fillellipse(x+50,y+60,5,7);
} 



void addFile(int nreinas){ //agrega las soluciones al archivo
	

	
	//variables de control
	int option, i = 0;
	char soluciones[200];
	
	sprintf(soluciones,"Solucion %d reinas.txt",nreinas); //pone el nombre al archivo de acuerdo a n reinas
	
	if(checkFileExists(soluciones) == 1){ //verifica si el archivo existe
		
		if(addSolutions(soluciones, reinas, nreinas) == 0){ //agrega la solucion al archivo
			
			printf("\nNo se pudo registrar la solucion...\n");
			
		}
	}
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

int addSolutions(char *filename, int reinas[], int nreinas){
	
	//Abre el archivo en modo "append" para agregar al final
	FILE *file = fopen(filename,"a+");

	//char para almacenar lo ingresado
	char linea[230], solucion[nreinas * 20];
	//Variables de control
	int i = 0;

	fprintf(file, "Solucion No. %d: \n", ++cont);

	for (i = 0; i<nreinas; i++){
    
    fprintf(file,"[%d] ",reinas[i]);
    
	}

	fprintf(file,"\n");

	//Cierra el archivo
	fclose(file);
	return 1;

}