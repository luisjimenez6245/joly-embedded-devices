#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN  9    //Pin 9 para el reset del RC522
#define SS_PIN  10   //Pin 10 para el SS (SDA) del RC522
MFRC522 mfrc522(SS_PIN, RST_PIN); //Creamos el objeto para el RC522

void setup() {
  Serial.begin(115200); //Iniciamos la comunicación  serial
  SPI.begin();        //Iniciamos el Bus SPI
  mfrc522.PCD_Init(); // Iniciamos  el MFRC522
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
}
