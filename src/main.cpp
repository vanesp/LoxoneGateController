/*
  Example for outlets which are configured with a 10 pole DIP switch.
  
  https://github.com/sui77/rc-switch/
*/

#ifdef ARDUINO_AVR_UNO
  // Nodo Shield on Arduino
  #define PIN_RF_TX_VCC                4          // +5 volt / Vcc spanning naar de zender.
  #define PIN_RF_TX_DATA               5          // data naar de zender
  #define PIN_RF_RX_DATA               2          // Op deze input komt het 433Mhz-RF signaal binnen. LOW bij geen signaal.
  #define PIN_RF_RX_VCC               12          // Spanning naar de ontvanger via deze pin.
  #define PIN_ENABLE                   7          // poort voor input
                                                  // is pin 3 op breakout connector
                                                  // 5V van pin 1 breakout
                                                  // GND pin 25 breakout
#endif
  
#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

void setup() {
  Serial.begin(115200);

  Serial.println("Power on, enabling TX");
  // set receiver power on
  pinMode(PIN_RF_TX_DATA, OUTPUT);
  pinMode(PIN_RF_TX_VCC,  OUTPUT);
  pinMode(PIN_RF_RX_VCC,  OUTPUT);
  #ifdef ARDUINO_AVR_UNO 
  pinMode(PIN_ENABLE, INPUT);
  #endif
  // digitalWrite(PIN_RF_RX_VCC,HIGH);               // Spanning naar de RF ontvanger aan.
  digitalWrite(PIN_RF_TX_VCC,HIGH);                  // Spanning naar de RF zender aan.
  digitalWrite(PIN_RF_RX_DATA,INPUT_PULLUP);         // schakel pull-up weerstand in om te voorkomen dat er rommel binnenkomt als pin niet 
  Serial.println("TX set up");


  // Transmitter is connected to Arduino Pin  
  mySwitch.enableTransmit(PIN_RF_TX_DATA);

  // set protocol to 11, HT12E
  mySwitch.setProtocol(11);
  
  // Optional set pulse length
  mySwitch.setPulseLength(320);

  // Repeat enough times, required for garagedoors
  mySwitch.setRepeatTransmit(20);
}

void loop() {

  // Switch on:
  // The first parameter represents the setting of the first 5 DIP switches. 
  // In this example it's ON-OFF-ON-OFF-ON.
  // 
  // The second parameter represents the setting of the last 5 DIP switches. 
  // In this example the last 5 DIP switches are OFF-ON-OFF-OFF-OFF. 
  // This translates to code 1374
  Serial.println("Waiting");
  while (digitalRead(PIN_ENABLE)==0) {
    // just wait until something happens
    delayMicroseconds(100);
  };
  
  Serial.println("Sending on");
  while (digitalRead(PIN_ENABLE)==1) {
    delayMicroseconds(100);
    // keep sending until ready
    mySwitch.send(1374, 12);  
  };
  Serial.println("Sending off");
 
  
}
