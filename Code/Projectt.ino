#include <TMRpcm.h>
#include <SD.h>                     
#define SD_ChipSelectPin 4           
//#include <TMRpcm.h>           
#include <SPI.h>

TMRpcm tmrpcm;                      
int Status;
unsigned long time = 0;
const int ao=A0;
const int at=A1;
const int athr=A2;
const int afo=A3;
const int afi=A4;
int sen1=0;
int sen2=0;
int sen3=0;
int sen4=0;
int sen5=0;
int fo;
int tf;
int ths;
int fs;
int fis;
int ft;
int te;
int the;
int fe;
int fie;
bool state=0;
void setup() {
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
  pinMode(A4,INPUT);
  pinMode(2,INPUT);
  Serial.begin(9600);
  tmrpcm.speakerPin = 9;            
  tmrpcm.volume(7);
  pinMode(13,OUTPUT);
  if (!SD.begin(SD_ChipSelectPin)) {   
    Serial.println("SD fail");
    digitalWrite(13,HIGH);  
    return;   
    }
  else{   
    Serial.println("SD ok");   
    }
  tmrpcm.play("initia.wav");   
  delay(3000);
  //Calibration Start in 3 Second
    Serial.println("Going for open hand calibration");
    tmrpcm.play("oph.wav");
    delay(5000);
    fo=analogRead(A0);
    tf=analogRead(A1);
    ths=analogRead(A2);
    fs=analogRead(A3);
    fis=analogRead(A4);
  Serial.println("Going for Close hand calibration");
    tmrpcm.play("clh.wav");
    delay(5000);             
    ft=analogRead(A0);
    te=analogRead(A1);
    the=analogRead(A2);
    fe=analogRead(A3);
    fie=analogRead(A4);
  Serial.println("Calibration Complete");
  delay(3000);
  tmrpcm.play("cc.wav"); 
  delay(3000);
}

void loop() {
// delay(100);
  sen1=analogRead(A0);
  delay(100);
  sen2=analogRead(A1);
  delay(100);
  sen3=analogRead(A2);
  delay(100);
  sen4=analogRead(A3);
  delay(100);
  sen5=analogRead(A4);
  Serial.println("");
  Serial.println("Finger Data");
  Serial.print("ONE:");
  Serial.println(sen1);
  Serial.print("TWO:");
  Serial.println(sen2);
  Serial.print("Three:");
  Serial.println(sen3);
  Serial.print("FOUR:");
  Serial.println(sen4);
  Serial.print("Five:");
  Serial.println(sen5);

  if(sen5>920&& sen3<735){
    Status = 'h';
  }
  else if(sen5>896 && sen1>664 && sen3>735){
    Status = 't';
    Serial.print("]t");
  }
  else if(sen1>705){
    Status = 'b';
  }
  else if(sen2>742){
    Status = 's';                                               
  }
  else if(sen4>672){
    Status = 'S'; 
  }
  else{
    Status = 'S';
    }

   switch(Status){
    case 'h': tmrpcm.play("hello.wav");Status='S';break;
    case 's': tmrpcm.play("Sorry.wav");Status='S';break;
    case 'b': tmrpcm.play("help.wav"); Status='S';break;
    case 't': tmrpcm.play("Thankyou.wav");Status='S';break;
    case 'w': tmrpcm.play("Welcome.wav");Status='S';break;
    case 'S': tmrpcm.stopPlayback();break;
    default:break;
   }
  delay(500);
}
