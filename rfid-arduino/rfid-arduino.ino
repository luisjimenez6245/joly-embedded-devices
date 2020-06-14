#include <SPI.h>
#include <MFRC522.h>


#define AUTHORIZED_PIN  6    //Pin 9 para el reset del RC522
#define RELAY_PIN  7   //Pin 10 para el SS (SDA) del RC522
#define RST_PIN  9    //Pin 9 para el reset del RC522
#define SS_PIN  10   //Pin 10 para el SS (SDA) del RC522
MFRC522 mfrc522(SS_PIN, RST_PIN); //Creamos el objeto para el RC522

void setup() {
  Serial.begin(115200); 
  SPI.begin();        
  mfrc522.PCD_Init(); 
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(AUTHORIZED_PIN, INPUT);
  digitalWrite(RELAY_PIN, HIGH);

}

void loop() {
  if ( mfrc522.PICC_IsNewCardPresent()) 
        {  
            if ( mfrc522.PICC_ReadCardSerial()) 
            {
                  for (byte i = 0; i < mfrc522.uid.size; i++) {
                      if(!i)
                          Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "_");
                      else
                         Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? "_0" : "_");

                          Serial.print(mfrc522.uid.uidByte[i], HEX);   
                  } 
                  mfrc522.PICC_HaltA(); 
                  delay(500);        
            }      
  } 
  else{
    if(digitalRead(AUTHORIZED_PIN) == LOW){
      Serial.println("AUTH");
      digitalWrite(RELAY_PIN, LOW);
      delay(1000);
      digitalWrite(RELAY_PIN, HIGH);
    }
  }
}
