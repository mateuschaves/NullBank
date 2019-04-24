/* 
 *  Frank Aguiar Module 
 * 
 *  2019+ Copyright (c) NullBank.
 *  All rights reserved.
*/

// Bibliotecas
#include <Keypad.h>
#include <string.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <RFID.h>

#define SDA_DIO 9
#define RESET_DIO 8

RFID RC522(SDA_DIO, RESET_DIO);

// Inicializa o display no endereco 0x27
LiquidCrystal_I2C lsd(0x27,2,1,0,4,5,6,7,3, POSITIVE);

 
const byte amountLines = 4; 
const byte amountColumns = 4; 
 
// Matriz de caracteres
char matrix[amountLines][amountColumns] = {
  {'1','2','3',' '},
  {'4','5','6',' '},
  {'7','8','9',' '},
  {'C','0','E',','}
};
 
byte JubileuLines[amountLines] = {30, 32, 34, 36}; 
byte JunileuColunas[amountColumns] = {38,40, 42,44};
 
Keypad keyboard = Keypad( makeKeymap(matrix), JubileuLines, JunileuColunas, amountLines, amountColumns); 

enum {
  Welcome,
  Credit,
  Debit,
  Price,
  Quota,
  InsertCard,
  Password,
  Sucess,
  Fail
};

int State = Welcome;
String password;
int pressedKey = 0;
String price;
int lastState;
String months;

int isPasswordValid();
void clearManPassword();
void antibioticos();
void WelcomeDeLadin();
void Fiado();
void Talkeis();
void inflation();
void impostoEhRoubo();
void heyNubankVaiTomaNoCu();
void caraCracha();
void pontual();

void setup(){
  Serial.begin(9600);
  lsd.begin(16,2);
  lsd.setCursor(0,0);
  SPI.begin(); 
  RC522.init();
}
  
void loop(){
  
  switch(State){
    case Welcome:  
        WelcomeDeLadin();
        break;
     case Credit:
        Fiado();
        break;
     case Debit:
        Neon();
        break;
     case Price:
        Talkeis();
        break;
     case Quota:
        impostoEhRoubo();
        break;
     case InsertCard:
        heyNubankVaiTomaNoCu();
        break;
     case Password:
        caraCracha();
        break; 
  }
}

int isPasswordValid(){
  if(password.length() != 6 ){
    pressedKey = 0;
    return 0;
  }else{
    return 1;
  }
}

void antibioticos(){
  if(password.length() == 1){
    password = "";
  }else{
    password.remove(password.length() - 1, 1);  
  }
  Serial.println(password);
  lsd.clear();
}

void pontual(){
  if(months.length() == 1){
    months = "";
  }else{
    months.remove(months.length() - 1, 1);  
  }
  Serial.println(months);
  lsd.clear();
  lsd.print(months);
}

void inflation(){
  if(price.length() == 1){
    price = "";
  }else{
    price.remove(price.length() - 1, 1);  
  }
  Serial.println(price);
  lsd.clear();
  lsd.print(price);
}


void clearManPassword(){
  password = "";
}

/*
  Welcome state
*/
void WelcomeDeLadin(){
  char key = keyboard.getKey();
  lsd.clear();
  lsd.setCursor(3,0);
  lsd.print("NullBank");
  lsd.setCursor(0,1);
  lsd.print("1-Debit/2-Credit");
  switch(key){
    case '1':
      lastState = Debit;
      State = Debit;
      break;
    case '2':
      lastState = Credit;
      State = Credit;
      break;
  }
}
  
/*
  Credit state
*/
void Fiado(){
  lsd.clear();
  lsd.setCursor(1, 0);
  lsd.print("Choosed Credit");
  lsd.setCursor(1, 1);
  lsd.print("Type the price");
  delay(2000);
  State = Price;
}

/*
  Debit state
*/
void Neon(){
  lsd.clear();
  lsd.setCursor(1, 0);
  lsd.print("Choosed Debit");
  lsd.setCursor(1, 1);
  lsd.print("Type the price");
  delay(2000);
  State = Price;
}

/*
  Price state
*/
void Talkeis(){
  
  char key = keyboard.getKey();
  //Serial.println(key);

  if( key == 'C' )
    inflation();
  
  if( key && (key != 'E' && key != 'C') ){
    price.concat(key);
    Serial.println(price);
    lsd.clear();
    lsd.print(price); 
  }

  if( key == 'E' ){
    if(lastState == Credit){
        lsd.clear();
        lsd.print("How many months?");
        delay(1000);
        State = Quota;
    }else{
        lsd.clear();
        lsd.print("Insert card");
        delay(1000);
        State = InsertCard;
    }
  }
}

void impostoEhRoubo(){

  char key = keyboard.getKey();

  if( key && (key != 'E' && key != 'C' && key != ',') ){
    lsd.clear();
    if( months.length() < 2 )
      months.concat(key);
    lsd.print(months); 
  }

  if( key == 'C' )
    pontual();

  if( key == 'E' ){
    lsd.clear();
    lsd.print("Insert card");
    delay(1000);
    State = InsertCard;
  }
  
}

void heyNubankVaiTomaNoCu(){
  if (RC522.isCard()){
    RC522.readCardSerial();
    lsd.clear();
    lsd.print("Type a password");
    delay(1000);
    State = Password;
    for(int i=0;i<5;i++){ 
      //Serial.println(RC522.serNum[i]);
    }
  }
}

void caraCracha(){
  
  char key = keyboard.getKey();
  
  if(key == 'E'){
    if(!isPasswordValid()){
      lsd.clear();
      lsd.setCursor(0, 0);
      lsd.print("Invalid password");
      lsd.setCursor(3, 1);
      lsd.print("Try again");
      clearManPassword();
      lsd.print(password);
    }else{
      lsd.clear();
      lsd.setCursor(3, 0);
      lsd.print("Success");
      delay(1000);
      clearManPassword();
      months = "";
      price = "";
      pressedKey = 0;
      State = Welcome;
    }
  }

  if(key == 'C'){
      antibioticos();
      for(int i = 0; i < password.length(); i++)
        lsd.print("*");
  }
  
  if(pressedKey > 6){
    pressedKey = 0;
  }
  
  if( key && (key != 'E' && key != 'D' && key != 'C') ){
    password.concat(key);
    pressedKey++;
    lsd.clear();
    Serial.println(password);
    for(int i = 0; i < password.length(); i++)
      lsd.print("*");
  }
}
