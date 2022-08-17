// =======================
// Simple Transmitter for RC
// by: Surya Sarafe
// =======================
#include <RH_NRF24.h>

String recievedData = "";
// OutputPin
int steerPin      = 0; // D3
int escPin        = 5; // D1

// InputPin
int analogInPin   = A0;

RH_NRF24 nrf24(2,4);

int code    = 212;  // 0  for filter device connected / minimize interuption from other device 
int steer   = 90;   // 1  (0,180)
int esc     = 90;   // 2  (0,180)

// Status
int tempSteer   = 90;
int tempEsc     = 90;
int sends       = 1;

uint8_t data[3];
unsigned long previousAlive  = 0;    // for Failsafe
int interval  = 300;                 // for Failsafe

void setup() 
{
  pinMode(analogInPin, INPUT);
  pinMode(steerPin, OUTPUT);
  pinMode(escPin, OUTPUT);

  digitalWrite(steerPin, LOW);
  digitalWrite(escPin, LOW);

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
}
 
void loop()
{
  checkSensor();
}

void checkSensor() {
  // Read Potentiometer for steer
  digitalWrite(escPin, LOW);
  digitalWrite(steerPin, HIGH);
  tempSteer = analogRead(analogInPin);
  tempSteer = map(tempSteer, 0, 1023, 0, 180);
  if (tempSteer != steer) {
    steer = tempSteer;
    sends = 1;
  }
  delay(50); // delay for switch analogRead

  // Read Potentiometer for esc
  digitalWrite(steerPin, LOW);
  digitalWrite(escPin, HIGH);
  tempEsc = analogRead(analogInPin);
  tempEsc = map(tempEsc, 0, 1023, 0, 180);
  if (tempEsc != esc) {
    esc = tempEsc;
    sends = 1;
  }
  delay(50); // delay for switch analogRead


  // Sends is for not sending the value every time, because the value is the same
  // previousAlive is for failsafe because when the Transmitter off or not connected will
  // remove / minimal possibility to crash
  unsigned long currentMillis = millis();
  if ((sends == 1) || (currentMillis - previousAlive > interval)) {
    previousAlive = currentMillis;
    data[0] = code;
    data[1] = steer;
    data[2] = esc;

    nrf24.send(data, sizeof(data));
    nrf24.waitPacketSent();
    sends = 0;
  }
}