/* 
 *  Frank Aguiar# Project 
 *  
 *  "Nunca deixe alguém dizer que você não pode 
 *  terminar o trabalho um dia antes da entrega" - CHAVES, Mateus (2019).
 *  
 *  "Projeto comunitário a base de socialismo.
 *   Agradecimentos: Jonathan, Eduardo, Carvalho, 
 *   Fusion, Unicompra e a você xuxa" - COSTA, Felipe (2019).
 *   
 *   "A Nullbank gostaria de informar que privatizamos o 
 *   conceito morderno de capitalismo, um forte abraço" - BANK, Null (2000).
 *   
 *   
 *   Made with ♥ in URSAL.
 *   
 *   Developed by:
 *    - Hacker Boy - https://github.com/mateuschaves
 *    - Feijão Tropeiro - https://github.com/Felipe-matheus
 * 
 *  2019+ Copyright (c) NullBank.
 *  All rights reserved.
*/

// Bibliotecas
#include <Keypad.h>
#include <string.h>
#include <LiquidCrystal_I2C.h>
#include <RFID.h>
#include <SPI.h>
#include <Ethernet.h>

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


char server[] = "192.168.49.105";    // name address for Google (using DNS)


String gamb;

// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(192, 168, 0, 177);
IPAddress myDns(192, 168, 0, 1);

String porra = "id=5d00801dd35bb10a9c757787&password=";
String dataBuy = "user=5d00801dd35bb10a9c757787&password=";

int cu = 0;

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;

// Variables to measure the speed
unsigned long beginMicros, endMicros;
unsigned long byteCount = 0;
bool printWebData = true;  // set to false for better speed measurement


 
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
  Fail,
  verifyUser,
  readPassword,
  Inundacao,
  readTransactionResponse,
  Buy
};


struct CLIENT {
  String id;
  String password;
};

CLIENT nedved = { "492251719726", "5d00801dd35bb10a9c757787" };

String auth = "id=5d00801dd35bb10a9c757787&password=";

int State = Welcome;
String password;
int pressedKey = 0;
String price;
String type;
int lastState;
String months;
String id;

int isPasswordValid();
int isPasswordCorrect();
void clearManPassword();
void antibioticos();
void WelcomeDeLadin();
void Fiado();
void Talkeis();
void inflation();
void impostoEhRoubo();
void DaoLaudo();
void caraCracha();
void Tudopassa();
void duda();
void authUser();
void analfabetoFuncional();
void semInternetIrmao();
void puta();
void rapariga();

void setup(){
  //byte maque[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
  Serial.begin(9600);
  lsd.begin(16,2);
  lsd.setCursor(0,0);
  SPI.begin(); 
  RC522.init();
  byte maque[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
  // You can use Ethernet.init(pin) to configure the CS pin
  //Ethernet.init(10);  // Most Arduino shields
  //Ethernet.init(5);   // MKR ETH shield
  //Ethernet.init(0);   // Teensy 2.0
  //Ethernet.init(20);  // Teensy++ 2.0
  //Ethernet.init(15);  // ESP8266 with Adafruit Featherwing Ethernet
  //Ethernet.init(33);  // ESP32 with Adafruit Featherwing Ethernet

  // Open serial communications and wait for port to open:
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // start the Ethernet connection:
  Serial.println("Initialize Ethernet with DHCP:");
  if (Ethernet.begin(maque) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // Check for Ethernet hardware present
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
      while (true) {
        delay(1); // do nothing, no point running without Ethernet hardware
      }
    }
    if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(maque, ip, myDns);
  } else {
    Serial.print("  DHCP assigned IP ");
    Serial.println(Ethernet.localIP());
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.print("connecting to ");
  Serial.print(server);
  Serial.println("...");

  // if you get a connection, report back via serial:
  if (client.connect(server, 3000)) {
    Serial.print("connected to ");
    Serial.println(client.remoteIP());
    // Make a HTTP request:
    client.println("POST /user/login");
    client.println("Host: 192.168.49.105");
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.println("Connection:close");
    client.print("Content-Length:");
    client.println(porra.length());
    client.println();
    client.print(porra);

    //client.stop();
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
    State = Inundacao;
  }
  beginMicros = micros();

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
        DaoLaudo();
        break;
     case Password:
        //duda();
        caraCracha();
        break; 
     case verifyUser:
        authUser();
        break;
     case readPassword:
        analfabetoFuncional();
        break;
     case Inundacao:
        semInternetIrmao();
        break;
     case Buy:
        puta();
        break;
     case readTransactionResponse:
        rapariga();
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

/*
  Corrige a senha
*/
void antibioticos(){
  if(password.length() == 1){
    password = "";
  }else{
    password.remove(password.length() - 1, 1);  
  }
  lsd.clear();
}

/*
  Corrige o mês
*/
void Tudopassa(){
  if(months.length() == 1){
    months = "";
  }else{
    months.remove(months.length() - 1, 1);  
  }
  lsd.clear();
  lsd.print(months);
}

/*
  Corrige o preço
*/
void inflation(){
  if(price.length() == 1){
    price = "";
  }else{
    price.remove(price.length() - 1, 1);  
  }
  lsd.clear();
  lsd.print(price);
}


void clearManPassword(){
  password = "";
  porra = "id=5d00801dd35bb10a9c757787&password=";
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
      type = "debit";
      break;
    case '2':
      lastState = Credit;
      State = Credit;
      type = "credit";
      break;
  }
  delay(400);
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

/*
  Quota state
*/
void impostoEhRoubo(){

  char key = keyboard.getKey();

  if( key && (key != 'E' && key != 'C' && key != ',') ){
    lsd.clear();
    if( months.length() < 2 )
      months.concat(key);
    lsd.print(months); 
  }

  if( key == 'C' )
    Tudopassa();

  if( key == 'E' ){
    lsd.clear();
    lsd.print("Insert card");
    delay(1000);
    State = InsertCard;
  }
}

/*
  InsertCard state
*/
void DaoLaudo(){
  if (RC522.isCard()){
    RC522.readCardSerial();
    lsd.clear();  
    lsd.print("Type a password");
    delay(1000);
    State = Password;
    id = "";
    for(int i=0;i<5;i++){ 
      id.concat(RC522.serNum[i]);
    }
  }
}

void caraCracha(){
  
  char key = keyboard.getKey();
  
  if(key == 'E'){
    porra.concat(password);
    State = verifyUser;
    
    /*if(!isPasswordCorrect()){
      lsd.clear();
      lsd.setCursor(0, 0);
      lsd.print("Invalid password");
      lsd.setCursor(3, 1);
      lsd.print("Try again");
      clearManPassword();
      lsd.print(password);
    } else{
      lsd.clear();
      lsd.setCursor(3, 0);
      lsd.print("Success");
      delay(1000);
      clearManPassword();
      months = "";
      price = "";
      pressedKey = 0;
      State = Welcome;
    }*/
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
    for(int i = 0; i < password.length(); i++)
      lsd.print("*");
  }
}

int isPasswordCorrect(){
      delay(3000); 
      Serial.print(gamb.substring(205,208));
      if( gamb.substring(205,208).equals("104") ){
          return 0;
      }else{
          return 1; 
      } 
}

void authUser(){
  
  Serial.print("connecting to ");
  Serial.print(server);
  Serial.println("...");

  // if you get a connection, report back via serial:
  if (client.connect(server, 3000)) {
    Serial.print("connected to ");
    Serial.println(client.remoteIP());
    // Make a HTTP request:
    client.println("POST /user/login");
    client.println("Host:  192.168.137.194");
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.println("Connection:close");
    client.print("Content-Length:");
    client.println(porra.length());
    client.println();
    client.print(porra);
    delay(3000);
    State = readPassword;
  }else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
    delay(3000);
    State = Welcome;
  }
}


void analfabetoFuncional(){
  if (client.available()) {
    char c = client.read();
    gamb.concat(c);
    if(gamb.substring(205,208).length() == 3){
        Serial.print("RESULTADO DA API\n");
        Serial.print(gamb.substring(205,208));
        if(gamb.substring(205,208) == "104"){
          lsd.clear();
          lsd.setCursor(0, 0);
          lsd.print("Invalid password");
          lsd.setCursor(3, 1);
          lsd.print("Try again");
          clearManPassword();
          lsd.print(password);
          delay(1000);
          State = Password;
          gamb = "";
        }else if (gamb.substring(205,208) == "105"){
          lsd.clear();
          lsd.setCursor(3, 0);
          lsd.print("Success");
          delay(1000);
          
          pressedKey = 0;
          gamb = "";
          State = Buy;
        }
    }
  }else {
    /*lsd.clear();
    lsd.setCursor(3, 0);
    lsd.print("Connection failed");
    delay(1000);
    clearManPassword();
    months = "";
    price = "";
    pressedKey = 0;
    State = Welcome;
    gamb = "";*/
  }
}

void semInternetIrmao(){
  lsd.clear();
  lsd.setCursor(3, 0);
  lsd.print("Connection");
  lsd.setCursor(4, 1);
  lsd.print("failed");
  delay(1000);
  clearManPassword();
  months = "";
  price = "";
  pressedKey = 0;
  gamb = "";
}

void puta(){
  dataBuy.concat(password + "&type=" + type + "&quota=" + months + "&price=" + price);
  clearManPassword();
  months = "";
  price = "";
  Serial.print(dataBuy);
  Serial.print("connecting to ");
  Serial.print(server);
  Serial.println("...");

  // if you get a connection, report back via serial:
  if (client.connect(server, 3000)) {
    Serial.print("connected to ");
    Serial.println(client.remoteIP());
    // Make a HTTP request:
    client.println("POST /payment");
    client.println("Host:  192.168.137.194");
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.println("Connection:close");
    client.print("Content-Length:");
    client.println(dataBuy.length());
    client.println();
    client.print(dataBuy);
    delay(3000);
    State = readTransactionResponse;
  }else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
    State = Welcome;
  }
}

void rapariga(){
  if (client.available()) {
    char c = client.read();
    gamb.concat(c);
    if(gamb.substring(215,218).length() == 3){
        Serial.print("SALDO\n");
        Serial.print(gamb.substring(215,218));
    }
  }
}
