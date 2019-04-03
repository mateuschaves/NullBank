#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Inicializa o display no endereco 0x27
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);

char* greeting = "Hi, i'm NullBank";
char* insertCard = "Insert your credit card";
 
void setup()
{
  lcd.begin(16,2);
}
 
void loop(){
  
  lcd.setBacklight(HIGH);
  
  lcd.setCursor(0,0);
  lcd.print(greeting);
  
  lcd.setCursor(0,1);
  lcd.autoscroll();
  for(int i = 0; i < strlen(insertCard); i++){
    lcd.print(insertCard[i]);
    delay(300);
  }
}
  
