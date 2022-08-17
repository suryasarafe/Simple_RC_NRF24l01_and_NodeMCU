// =======================
// Simple Reciever for RC
// by: Surya Sarafe
// =======================
#include <RH_NRF24.h>
#include <Servo.h>

int steerPin      = 0; // D3
int escPin        = 5; // D1

Servo mySteer;
Servo myEsc;

int code    = 212;  // 0 
int steer   = 90;   // 1    (0,180)
int esc     = 90;   // 2    (0,180)

RH_NRF24 nrf24(2,4);

unsigned long lastUpdate  = 0;    // for failsafe
int interval              = 500;  // for failsafe

void setup() 
{
  Serial.begin(9600);
  while (!Serial);      
  if (!nrf24.init())
    Serial.println("initialization failed");
  if (!nrf24.setChannel(1))
    Serial.println("Channel set failed");
  if (!nrf24.setRF(RH_NRF24::DataRate2Mbps, RH_NRF24::TransmitPower0dBm))
    Serial.println("RF set failed");    

  Serial.setDebugOutput(true);

  Serial.println("");
  delay(500);

  // 544 and 2400 is my personal reference, maybe different for other servo
  mySteer.attach(steerPin, 544, 2400, 1500);
  mySteer.write(steer);

  delay(500);

  // 1000 and 2000 is my personal reference, maybe different for other servo
  myEsc.attach(escPin, 1000, 2000, 1500);
  myEsc.write(esc);

  delay(500);
}
 
void loop() {
  failsafe();
  if (nrf24.available()) {
    reciper2();
  }
}

void failsafe() {
  unsigned long currentMillis = millis();
  if (currentMillis - lastUpdate > interval) {
    mySteer.write(90);
    myEsc.write(90);
  }
}

void reciper2() {
  lastUpdate = millis();
  uint8_t buf[RH_NRF24_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);
  if(nrf24.recv(buf, &len)) {
    
    // Check the code is same with the transmitter we send
    if (code == buf[0]) {
      steer = buf[1];
      esc = buf[2];
      mySteer.write(steer);
      myEsc.write(esc);
    }
  } else {
    Serial.println("recv failed");
  }
}