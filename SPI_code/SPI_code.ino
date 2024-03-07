//Master Arduino Code:

//SPI MASTER (ARDUINO)

//SPI COMMUNICATION BETWEEN TWO ARDUINO 

#include<SPI.h>                             //Library for SPI 
         
int x = 0;

int ss0 = 4;
int ss1 = 2;

void setup (void){
  pinMode(ss0,OUTPUT);
  pinMode(ss1,OUTPUT);


  Serial.begin(115200);                   //Starts Serial Communication at Baud Rate 115200 
  SPI.begin();                            //Begins the SPI commnuication
  SPI.setDataMode(SPI_MODE3);
  SPI.setClockDivider(SPI_CLOCK_DIV8);    //Sets clock for SPI communication at 8 (16/8=2Mhz)
  digitalWrite(ss0,HIGH); 
  digitalWrite(ss1,HIGH);                  // Setting SlaveSelect as HIGH (So master doesnt connnect with slave)

}


void loop(void){

  byte Mastersend,Mastereceive;          

  digitalWrite(ss1, LOW);                  //Starts communication with Slave connected to master
  Mastersend = 10;                            
  Mastereceive=SPI.transfer(Mastersend); //Send the mastersend value to slave also receives value from slave
  //Serial.print("From Tishan - ");
  //Serial.print(Mastereceive);
  digitalWrite(ss1,HIGH);

  //Serial.print("   ");
  //Serial.print("From Chathura - ");

  //delayMicroseconds(1);

  digitalWrite(ss0, LOW);                  //Starts communication with Slave connected to master
  Mastersend = 64;                            
  Mastereceive=SPI.transfer(Mastersend); //Send the mastersend value to slave also receives value from slave
  Serial.println(Mastereceive);
  digitalWrite(ss0,HIGH);



  x++;
  if(x==100){
    x = 0;
  }


  delay(50);

}

