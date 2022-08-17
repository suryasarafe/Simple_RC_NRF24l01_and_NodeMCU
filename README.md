# Simple_RC_NRF24l01_and_NodeMCU
Simple RC Transciever from beginner,

This is my simple usage for NRF24l01 and nodeMCU that I have, 
this project is for my educational porpose but free for use if this useful for anyone in someway.

What I learn from this is how to use wireless connection and some basic knowlege how arduino and other component works,
and because of that I want to implement this to something I like and maybe can be useful.

# Part / Component that I use
- 2x NodeMCU v3
- 2x NRF24l01 Transciever
- 2x Potentiometer (I use B50K)
- 1x ESC 20A (no brand)
- 1x Motor (no brand)
- 1x Servo SG90 (180 degre)
- Some cable (for development porpose better use jump wire)
- 2x Battery (I use WPL 14500 500mAh 7.4v 10c) / USB cable
- 2x Dioda
 
Optional component
- 1x Breadboard (830 Pin)
- 1x Breadboard mini (170 Pin)
- 2x NodeMCU Shield Breadboard / Expansion Board

# Wiring
Basic wiring NRF24l01 to NodeMCU for Transmitter and Reciever are the same as image below

![img](/NRF24L01-ESP8266-Gateway.jpg "NodeMCU Gateway")
[NodeMCU Gateway](https://how2electronics.com/esp8266-nrf24l01-gateway-arduino-node/)




## Transmitter
I update to this is for Transmitter

![img](/transmitter.png "Transmitter Diagram")

Connection Notes: 

- Steering
  - D3 to Potentiometer VCC
  - GND to Potentiometer GND
  - A0 to Potentiometer Output with Diode
  
- ESC
  - D1 to Potentiometer VCC
  - GND to Potentiometer GND
  - A0 to Potentiometer Output with Diode

## Reciever
I update to this is for Reciever
![img](/reciever.png "Reciever Diagram")
![img](/esc.png "ESC Diagram")

Connection Notes: 

- Steering
  - VIN to Servo VCC
  - GND to Servo GND
  - D3 to Servo Signal
  
- ESC
  - VIN to ESC VCC
  - GND to ESC GND
  - D1 to ESC Signal
  - ESC Male JST socket to motor
  - ESC Female JST socket to battery

# Library
- [RH_NRF24](https://github.com/PaulStoffregen/RadioHead/blob/master/RH_NRF24.h)
- Servo (default)

# Notes
  If you find error or fail to build, in my case I need to unplug some of the cable that connected to the NodeMCU,

  In this setup I already try to create how to add more feature like turning front light, rear light and other,
  but in NodeMCU there is limitation for the other GPIO pin to use, later on I want to learn how to using 3 or 2 pin only for connection between NodeMcu and NRF24l01
  with that setup I can have more GPIO pin to use.
