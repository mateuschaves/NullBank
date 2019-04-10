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

// Inicializa o display no endereco 0x27
LiquidCrystal_I2C lsd(0x27,2,1,0,4,5,6,7,3, POSITIVE);

 
const byte amountLines = 4; 
const byte amountColumns = 4; 
 
// Matriz de caracteres
char matrix[amountLines][amountColumns] = {
  {'1','2','3',' '},
  {'4','5','6',' '},
  {'7','8','9',' '},
  {'C','0','E','D'}
};
 
 
byte JubileuLines[amountLines] = {3, 4, 5, 6}; 
byte JunileuColunas[amountColumns] = {8, 9, 10,11};
 
Keypad keyboard = Keypad( makeKeymap(matrix), JubileuLines, JunileuColunas, amountLines, amountColumns); 
 
String password;
int pressedKey = 0;

int isPasswordValid(char * password);
void clearManPassword();
void antibioticos();

void setup(){
  Serial.begin(9600);
  lsd.begin(16,2);
  lsd.setCursor(0,0);

}
  
void loop(){
  
  char key = keyboard.getKey();
  
  
  if(key == 'E'){
    if(!isPasswordValid(password)){
      lsd.clear();
      lsd.print("Can't do this ");
      lsd.setCursor(0, 1);
      lsd.print("right ? Moises");
      clearManPassword();
      lsd.print(password);
    }
  }

  if(key == 'C'){
      antibioticos();
      lsd.print(password);
  }
  
  if(pressedKey > 6){
    pressedKey = 0;
  }
  
  if( key && (key != 'E' && key != 'D' && key != 'C') ){
    password.concat(key);
    pressedKey++;
    lsd.clear();
    lsd.print(password);
    
  }
  
  
}

int isPasswordValid(String password){
  if(password.length() < 6 ){
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

void clearManPassword(){
  password = "";
}
