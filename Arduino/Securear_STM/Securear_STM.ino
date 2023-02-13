#include <Password.h> 
int baris[4] = {PB12, PB13, PB14, PB15};
int kolom[3] = {PA8, PA9, PA10};
Password password = Password( "123456" );
int steper =PA11 ;

void keypad(){
  digitalWrite(kolom[0],HIGH);
  digitalWrite(kolom[1],LOW);
  digitalWrite(kolom[2],LOW);
  digitalWrite(kolom[3],LOW);
 
  if(digitalRead(baris[0]) == HIGH && digitalRead(baris[1]) == LOW && digitalRead(baris[2]) == LOW && digitalRead(baris[3]) == LOW){
        Serial.println("1");
  }else if(digitalRead(baris[0]) == LOW && digitalRead(baris[1]) == HIGH && digitalRead(baris[2]) == LOW && digitalRead(baris[3]) == LOW){
        Serial.println("4");  
  }else if(digitalRead(baris[0]) == LOW && digitalRead(baris[1]) == LOW && digitalRead(baris[2]) == HIGH && digitalRead(baris[3]) == LOW){
        Serial.println("7");
  }else if(digitalRead(baris[0]) == LOW && digitalRead(baris[1]) == LOW && digitalRead(baris[2]) == LOW && digitalRead(baris[3]) == HIGH){
        Serial.println("*");
  }else{;}
  delay(100);
 
  digitalWrite(kolom[0],LOW);
  digitalWrite(kolom[1],HIGH);
  digitalWrite(kolom[2],LOW);
  digitalWrite(kolom[3],LOW);
 
  if(digitalRead(baris[0]) == HIGH && digitalRead(baris[1]) == LOW && digitalRead(baris[2]) == LOW && digitalRead(baris[3]) == LOW){
        Serial.println("2");
  }else if(digitalRead(baris[0]) == LOW && digitalRead(baris[1]) == HIGH && digitalRead(baris[2]) == LOW && digitalRead(baris[3]) == LOW){
        Serial.println("5");  
  }else if(digitalRead(baris[0]) == LOW && digitalRead(baris[1]) == LOW && digitalRead(baris[2]) == HIGH && digitalRead(baris[3]) == LOW){
        Serial.println("8");
  }else if(digitalRead(baris[0]) == LOW && digitalRead(baris[1]) == LOW && digitalRead(baris[2]) == LOW && digitalRead(baris[3]) == HIGH){
        Serial.println("0");
  }else{;}
  delay(100);
 
  digitalWrite(kolom[0],LOW);
  digitalWrite(kolom[1],LOW);
  digitalWrite(kolom[2],HIGH);
  digitalWrite(kolom[3],LOW);
 
  if(digitalRead(baris[0]) == HIGH && digitalRead(baris[1]) == LOW && digitalRead(baris[2]) == LOW && digitalRead(baris[3]) == LOW){
        Serial.println("3");
  }else if(digitalRead(baris[0]) == LOW && digitalRead(baris[1]) == HIGH && digitalRead(baris[2]) == LOW && digitalRead(baris[3]) == LOW){
        Serial.println("6");  
  }else if(digitalRead(baris[0]) == LOW && digitalRead(baris[1]) == LOW && digitalRead(baris[2]) == HIGH && digitalRead(baris[3]) == LOW){
        Serial.println("9");
  }else if(digitalRead(baris[0]) == LOW && digitalRead(baris[1]) == LOW && digitalRead(baris[2]) == LOW && digitalRead(baris[3]) == HIGH){
        Serial.println("#");
  }else{;}
  delay(100);
  }

void keypadEvent(eKey){
  switch (keypad.getState()){
    case PRESSED:
  Serial.print("Pressed: ");
  Serial.println(eKey);
  switch (eKey){
    case '*': checkPassword(); break;
    case '#': password.reset(); break;
    default: password.append(eKey);
     }
  }
}
  
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
//membuat kolom
pinMode(steper,OUTPUT);
pinMode(PA8, OUTPUT);
pinMode(PA9, OUTPUT);
pinMode(PA10, OUTPUT);
//membuat baris
pinMode(PB12, OUTPUT);
pinMode(PB13, OUTPUT);
pinMode(PB14, OUTPUT);
pinMode(PB15, OUTPUT);
}
void loop() {
  // put your main code here, to run repeatedly:

}
