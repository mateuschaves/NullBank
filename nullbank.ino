#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Mensagem de boas vindas !
char hellow[] = "Sem dinheiro irmao";

void setup() {
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.autoscroll();
  for(int i = 0; i < 18; i++){
    lcd.print(hellow[i]);
    delay(100);
  }
}
 