#include<stdio.h> //libreria estandar
#include<graphics.h> //librer�a para usar los gr�ficos
#include<math.h> //libreria para sumar y restar las coordenadas (animacion de gr�ficos)

//prototipos de funciones
void push(int mover_destino, int no_disco);//agrega un disco a la torre
int pop(int mover_origen); //elimina un disco de la torre
void dibujo_principal(); //es la plantilla inicial del hanoi (torres y discos)
void animador(); //realiza la animaci�n de movimiento de los discos 
void hanoi(int n, int origen, int auxiliar, int destino); //hace el proceso del hanoi recursivo
void titulo();

//variables globales
int torres[3][10]; //arreglo bidimensional, donde las "filas" son los 10 posibles discos y las "columnas" son las tres torres: origen, auxiliar, destino
int disco_superior[3];//parte de arriba (discos) de las tres torres
int mover_origen,mover_destino;//"Mover origen" mueve el disco de la torre de origen, "mover destino" mueve el disco de la torre destino
int mover_disco;//se obtiene el numero de discos que se han movido (1-10)
int longitud, parte_abajo, parte_arriba; //obtienen las medidas de la pantalla

int main(){
	
	int i,gd=DETECT,gm,n;
	printf("Ingrese el numero de discos que desea: \n"); //se ingresa la cantidad de discos que se quiere para el hanoi
	scanf("%d",&n); //lee el n�mero de discos
	
	system("cls"); //limpia la consola
 	printf("\tMovimientos\n\n 1 = torre origen\n 2 = torre auxiliar\n 3 = torre destino\n\n"); //imprime en consola el texto que complementar� los movimientos 
 	
	initwindow(500,400); //comienzan a utilizarse los gr�ficos
	
	for(i=0;i<3;i++){ 
	
 		disco_superior[i]=-1; //se inicializan las torres vac�as
 		
 	}
 	
	for(i=n;i>0;i--){ 
	
 		push(1,i); //se colocan los discos en la torre origen
 		
 	}
 	
	longitud=getmaxx()/4; //obtiene las coordenadas m�ximas de la pantalla en "x", horizontal
	parte_abajo=getmaxy()-50; //obtiene las coordenadas en "x, y" de la parte de abajo de la pantalla
	parte_arriba=getmaxy()/3+100; //obtiene las coordenadas en "x,y" de la parte de arriba de la pantalla, lo divide entre 3 para hacer las torres
	hanoi(n,1,2,3); //se manda a llamar a hanoi para resolverse (en esta misma se imprimen los movimientos)
	delay(4000); //crea un retardo en la ejecuci�n y cierre del programa
	getch();
}

void push(int mover_destino, int no_disco){

	//coloca los discos en la torre
	torres[mover_destino-1][++disco_superior[mover_destino-1]]=no_disco;
	
}

int pop(int mover_origen){ 
	
	//toma el disco superior de la torre para moverlo hacia otra, lo "elimina"
	return(torres[mover_origen-1][disco_superior[mover_origen-1]--]);
	
}

void dibujo_principal(){
	
	int j,i,disco; //i, j son variables para iteraci�n de los ciclos
	cleardevice(); //usa el color de fondo actual, como es establecido por la funci�n setbkcolor, para rellenar la pantalla
	
	for(j=1;j<=3;j++){
		
 		//par�metros para pintar las torres
 		setfillstyle(BKSLASH_FILL ,WHITE); //tipo de relleno de la figura y color
 		bar(j*longitud,parte_arriba,j*longitud+5,parte_abajo); //se calcula el tama�o de las torres de acuerdo a la longitud de la pantalla
    	
 		//par�metros para dibujar los discos en la torre
 		for(i=0;i<=disco_superior[j-1];i++){
 			
  			disco=torres[j-1][i];
  			
  			/*par�metros para pintar los discos, color de relleno y se
			usa el valor del color que va incrementando para cambiar de acuerdo al n�mero de discos*/
  			setfillstyle(SOLID_FILL,1+disco);
  			bar(j*longitud-15-disco*5,parte_abajo-(i+1)*10,j*longitud+5+15+disco*5,parte_abajo-i*10);
  			
  		}
  		titulo(); //imprime el t�tulo en la pantalla gr�fica
 	}
}

void animador(){
	
	//mostrar el movimiento que hace el disco de una torre a otra
	int x,y,dif,sign; //x, y son variables de las coordenadas para mover los discos
	mover_disco=pop(mover_origen);
	x=mover_origen*longitud; //se multiplican las coordenadas de origen por la longitud de la pantalla para obtener las nuevas coordenadas a donde se mover� el disco
	y=parte_abajo-(disco_superior[mover_origen-1]+1)*10;
	
	//se toma el disco superior de la torre
	for(;y>parte_arriba-20;y-=15){
		
 		dibujo_principal(); //se utiliza el dibujo base (torres y discos a mover)
 		
 		/*par�metros para pintar los discos, color de relleno y se
		  usa el valor del color que va incrementando para cambiar de acuerdo al n�mero de discos*/
 		setfillstyle(SOLID_FILL,1+mover_disco);
 		bar(x-15-mover_disco*5,y-10,x+5+15+mover_disco*5,y);
 		delay(100);//crea un retardo en la ejecuci�n y cierre del programa
 		
 	}
	y=parte_arriba-20;
	dif=mover_destino*longitud-x;
	sign=dif/abs(dif);
	
	//se mueve el disco hacia la torre de destino
	for(;abs(x-mover_destino*longitud)>25;x+=sign*15){
		
 		dibujo_principal();//se utiliza el dibujo base (torres y discos a mover)
 		
 		/*par�metros para pintar los discos, color de relleno y se
		usa el valor del color que va incrementando para cambiar de acuerdo al n�mero de discos*/
 		setfillstyle(SOLID_FILL,1+mover_disco); 
 		bar(x-15-mover_disco*5,y-10,x+5+15+mover_disco*5,y);
 		delay(100);//crea un retardo en la ejecuci�n y cierre del programa
 		
 	}
	x=mover_destino*longitud;
	
	//se coloca el disco en la torre de objetivo
	for(;y<parte_abajo-(disco_superior[mover_destino-1]+1)*10;y+=15){
		
 		dibujo_principal();
 		setfillstyle(SOLID_FILL,1+mover_disco);
 		bar(x-15-mover_disco*5,y-10,x+5+15+mover_disco*5,y);
 		delay(100);//crea un retardo en la ejecuci�n y cierre del programa
 		
 	}
	push(mover_destino,mover_disco);
	dibujo_principal();
}


void hanoi(int n, int origen, int auxiliar, int destino){ //funcion que ejecuta el hanoi

	/*Se busca mover los discos de la torre de origen (1) a la torre destino (3), se usa la torre auxiliar (2) para poder 
	pasar todos los discos cumpliendo las reglas del hanoi (no se permite un disco grande encima de uno peque�o)*/ 
 	
	if(n>=1){ //si n es mayor o igual a uno se efectuan las funciones recursivas para poder resolverlo, se pasa un disco cada que n=1
	
 		hanoi(n-1,origen, destino, auxiliar);
 		printf("Mover de %i a %i\n", origen, destino); //imprime en consola los movimientos que se realizan
 		dibujo_principal();
 		delay(1000);//crea un retardo en la ejecuci�n y cierre del programa
 		mover_origen=origen;
 		mover_destino=destino;
 		
 		//realiza la animaci�n del movimiento 
 		animador();
 		hanoi(n-1,auxiliar, origen, destino);
 		
 	}
}

void titulo(){ //par�metros para imprimir el t�tulo en la pantalla gr�fica

	settextstyle(8, 0, 5);//fuente, direccion, tama�o
	outtextxy(130, 100, "H a n o i");//x, y, char
	
}

