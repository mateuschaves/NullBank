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

void setup(){
  Serial.begin(9600);
}
  
void loop(){
  
  char key = keyboard.getKey();
  
  if(key == 'E'){
    if(!isPasswordValid(password))
      Serial.println("Senha invalida parca");
      clearManPassword();
      Serial.println(password);
  }
  
  if(pressedKey > 6){
    pressedKey = 0;
  }
  
  if( key && (key != 'E' && key != 'D' && key != 'C') ){
    password.concat(key);
    pressedKey++;
    Serial.println(password);
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

void clearManPassword(){
  password = "";
}
