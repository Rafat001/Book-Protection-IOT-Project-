#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_1_PIN        10         // Configurable, take a unused pin, only HIGH/LOW required, must be diffrent to SS 2
#define SS_2_PIN        8          // Configurable, take a unused pin, only HIGH/LOW required, must be diffrent to SS 1

#define NR_OF_READERS   2
#define Buzzer 3

byte ssPins[] = {SS_1_PIN, SS_2_PIN};
String myid="";
String goodTag="19810023948";

MFRC522 mfrc522[NR_OF_READERS];   // Create MFRC522 instance.

/**
 * Initialize.
 */
void setup() {

  Serial.begin(9600); // Initialize serial communications with the PC
  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)

  SPI.begin();        // Init SPI bus

  for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
    mfrc522[reader].PCD_Init(ssPins[reader], RST_PIN); // Init each MFRC522 card
    Serial.print(F("Reader "));
    Serial.print(reader);
    Serial.print(F(": "));
    mfrc522[reader].PCD_DumpVersionToSerial();
  }
}

/**
 * Main loop.
 */
void loop() {

  for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
    // Look for new cards

    if (mfrc522[reader].PICC_IsNewCardPresent() && mfrc522[reader].PICC_ReadCardSerial()) {

      dump_byte_array(mfrc522[reader].uid.uidByte, mfrc522[reader].uid.size);
      //byte tag=Serial.read();
      //Serial.println(tag);
      //byte mytag=mfrc522[reader].PICC_ReadCardSerial();
     // Serial.println(mytag);
      //Serial.println(mfrc522[reader].PICC_ReadCardSerial());
      if(goodTag!=myid){

      // Buzzer Starting

      for (int y = 0; y < 2; y++){

        tone(Buzzer, 1000); // Send 1KHz sound signal...
        delay(1000);        // ...for 1 sec
        noTone(Buzzer);     // Stop sound...
        delay(1000); 
          /*Serial.println(F("Buzzer On Please"));
          digitalWrite (Buzzer, HIGH) ;// Buzzer On
          delay (300) ;// Delay 1ms 
          digitalWrite (Buzzer, LOW) ;// Buzzer Off
          Serial
          delay (300) ;// delay 1ms  */
          }}
          //delay(500); 
        tone(Buzzer, 1000); // Send 1KHz sound signal...
        delay(1000);        // ...for 1 sec
        noTone(Buzzer);     // Stop sound...
        delay(1000);
      // Buzzer Ending
      Serial.print(F("Reader "));
      Serial.print(reader);
      // Show some details of the PICC (that is: the tag/card)
      Serial.print(F(": Card UID:"));
      Serial.print(myid);
      Serial.println();
      Serial.print(F("PICC type: "));
      MFRC522::PICC_Type piccType = mfrc522[reader].PICC_GetType(mfrc522[reader].uid.sak);
      Serial.println(mfrc522[reader].PICC_GetTypeName(piccType));

      // Halt PICC
      mfrc522[reader].PICC_HaltA();
      // Stop encryption on PCD
      mfrc522[reader].PCD_StopCrypto1();
      myid="";
    } //if (mfrc522[reader].PICC_IsNewC
  } //for(uint8_t reader
}

/**
 * Helper routine to dump a byte array as hex values to Serial.
 */
void dump_byte_array(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    //Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    //Serial.print(buffer[i], HEX);
    myid+=buffer[i];
  }
}
