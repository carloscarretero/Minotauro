/*
 * 	-------------------------------------------------------------------------
 * 	|  Maze solving robot algorithm                         								|
 *	|  Authors:  Carlos Carretero Aguilar, Rafael Moreno Anarte             |
 * 	|  Date:    11 - 16 - 2015                                             	|
 * 	|  Version: 1.00                                                       	|
 * 	|  Description: 
 * 	-------------------------------------------------------------------------
 */

#include "components.h"
#include <Servo.h>
#include "String.h"

//Variables globales:


int vector_valores[4]; // Para la toma de decisiones.
int pos_actual=0; // Esta es la posición hacia la que está mirando el minotauro en este momento
                        // por defecto empieza mirando hacia arriba.
int pos_siguiente;

int ejeX = 4, ejeY = 4; // Definimos la posición inicial.

int PRIORIDAD_0 = 3;  // Prioridad MAX
int PRIORIDAD_1 = 2;
int PRIORIDAD_2 = 0;
int PRIORIDAD_3 = 1;  // Priorida MIN

Engines engines(5,6,10,9,255,180);
Led led(11,12,13);
Sharp sharp(A3,7);
mySerial myserial;
Battery battery(A6);
myBluetooth mybluetooth;

int maze[5][5][4] = {};

void setup()
{
	Serial1.begin(9600);
  myserial.setup();
  engines.setup();
  sharp.setup();
  led.setup();
}

void observar()
{
  //Esto lo hará siempre y siempre bien.
  maze[ejeX][ejeY][pos_actual] = sharp.lookFront();
  if(maze[ejeX][ejeY][pos_actual]) // Si es != 0
        mybluetooth.sendWall(pos_actual);
  //Las otras opciones dependen de la pos_actual
  if(pos_actual == 0) //Estamos mirando hacia arriba
  {
    maze[ejeX][ejeY][2] = sharp.lookLeft();
    if(maze[ejeX][ejeY][2]) // Si es != de 0
      mybluetooth.sendWall(2);
    //ard.posInicial(); //Volvemos a la posición inicial
    maze[ejeX][ejeY][3] = sharp.lookRight();
    if(maze[ejeX][ejeY][3]) // Si es != de 0
      mybluetooth.sendWall(3);
  }
  else 
    if(pos_actual == 1) //Mirando hacia abajo
    {
      maze[ejeX][ejeY][3] = sharp.lookLeft();
      if(maze[ejeX][ejeY][3]) // Si es != 0
        mybluetooth.sendWall(3);
      //ard.posInicial(); //Volvemos a la posición inicial
      maze[ejeX][ejeY][2] = sharp.lookRight();
      if(maze[ejeX][ejeY][2]) // Si es != 0
        mybluetooth.sendWall(2);
    }
    else
      if(pos_actual == 2)
      {
        maze[ejeX][ejeY][1] = sharp.lookLeft();
        if(maze[ejeX][ejeY][1]) // Si es != 0
          mybluetooth.sendWall(1);
        //ard.posInicial(); //Volvemos a la posición inicial
        maze[ejeX][ejeY][0] = sharp.lookRight();
        if(maze[ejeX][ejeY][0]) // Si es != 0
          mybluetooth.sendWall(0);
      }
      else
        if(pos_actual == 3)
        {
          maze[ejeX][ejeY][0] = sharp.lookLeft();
          if(maze[ejeX][ejeY][0]) // Si es != 0
            mybluetooth.sendWall(0);
          //ard.posInicial(); //Volvemos a la posición inicial
          maze[ejeX][ejeY][1] = sharp.lookRight();
          if(maze[ejeX][ejeY][1]) // Si es != 0
            mybluetooth.sendWall(1);
        }
}

int decide_camino()
{  
  if(vector_valores[PRIORIDAD_0] == 0)
    return PRIORIDAD_0;
  else
    if(vector_valores[PRIORIDAD_1] == 0)
      return PRIORIDAD_1;
    else
      if(vector_valores[PRIORIDAD_2] == 0)
        return PRIORIDAD_2;
      else
        if(vector_valores[PRIORIDAD_3] == 0)
          return PRIORIDAD_3;
        else
          {
            int i;
            for(i=0;vector_valores[i]!=5;++i){}
            return i; // Si no hay 5, puede haber bucle infinito. Puede solucionarse con un || i >= 4
          }
}

void pivotar()
{
  int pivote =0;
    
  if(pos_actual == 0)
    switch (pos_siguiente)
    {
      case 1: //queremos hacer un giro de 180
        pivote = 2;
        break;
      case 2:
        pivote = 0;
        break;
      case 3:
        pivote = 1;
        break;
    }
  else
    if(pos_actual == 1)
      switch (pos_siguiente)
      {
        case 0: //queremos hacer un giro de 180
          pivote = 2;
          break;
        case 2:
          pivote = 1;
          break;
        case 3:
          pivote = 0;
          break;
      }
    else
      if(pos_actual == 2)
      switch (pos_siguiente)
      {
        case 0: 
          pivote = 1;
          break;
        case 1:
          pivote = 0;
          break;
        case 3:
          pivote = 2;//queremos hacer un giro de 180
          break;
      }
      else
        if(pos_actual == 3)
        switch (pos_siguiente)
        {
          case 0: 
            pivote = 0;
            break;
          case 1:
            pivote = 1;
            break;
          case 2:
            pivote = 2;//queremos hacer un giro de 180
            break;
        }
  engines.pivot(pivote);
}

//método avanzar (ejecutar movimiento)

void avanzar ()
{
   engines.goForw();  
   switch(pos_actual)
  {
      case 0:
          ejeY++;
          break;
      case 1:
          ejeY--;
          break;
      case 2:
          ejeX--;
          break;
      default:// Si vale 3
          ejeX++;
          break;
  }

}

 
void loop()
{
	
  //establecerPrioridades(int(control[0])); //Este casting no es tal cual

  //****************** TESTS ********************************  

  int batteryLevel = battery.testLevel();
  if(batteryLevel == 0)
    led.green();
  else if(batteryLevel == 1)
    led.yellow();
    else if(batteryLevel == 2)
      led.red();
      else 
        led.no_color();
  
  
  //****************** CONTROL DEL ENTORNO ********************************   
  observar();

 //****************** ASIGNACIÓN DE VALORES A LA MATRIZ ********************************  

  switch(pos_actual)
  {
          case 0:   
              maze[ejeX][ejeY][1]=5;   //En la opuesta a donde estamos mirando ponemos el 5
              vector_valores[0]=maze[ejeX][ejeY][0];
              vector_valores[2]=maze[ejeX][ejeY][2];
              vector_valores[3]=maze[ejeX][ejeY][3];
              break;
          case 1:
              vector_valores[0]=5;
              vector_valores[2]=maze[ejeX][ejeY][2];
              vector_valores[3]=maze[ejeX][ejeY][3];
              vector_valores[1]=maze[ejeX][ejeY][1];
              break;
          case 2:
              vector_valores[3]=5;
              vector_valores[2]=maze[ejeX][ejeY][2];
              vector_valores[1]=maze[ejeX][ejeY][1];
              vector_valores[0]=maze[ejeX][ejeY][0];
              break;
          default: //Realmente sería case 3
              vector_valores[2]=5;
              vector_valores[3]=maze[ejeX][ejeY][3];
              vector_valores[1]=maze[ejeX][ejeY][1];
              vector_valores[0]=maze[ejeX][ejeY][0];
              break;
  }

  //****************** DECISIÓN DEL CAMINO ********************************  
  pos_siguiente=decide_camino();

  //******************** PIVOTE *******************************************
  if(pos_actual != pos_siguiente)
    pivotar();

  avanzar();
  // engines.goForw(); //hacia delante.
  mybluetooth.sendMaze(ejeX,ejeY);
  delay(2000);
}

/*void winCondition()
{
  while(true){}
}*/

/* Podemos hacer esto en el main, ya que implica un cambio de contexto para 2 asignaciones.
void casillaInicial(String casilla,ejeX,ejeY)
{

  ejeX = casilla[0];
  ejeY = casilla[1];
}
*/
