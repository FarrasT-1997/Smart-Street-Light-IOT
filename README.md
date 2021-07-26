# Smart-Street-Light-IOT
Project with my friend about a miniature street light that can control from smartphone.

Thanks for BLYNK, a simple application IOT that can handle many IOT's activity such as sending data from Arduino and show it in your phone
or give an instruction to switch on your LED just in one touch anywhere.

We separated the system into 2 modes, there are automatic and manual.
The manual mode works very simple, just give instruction to switch on or off every LED.
The automatic mode will switch on or off all LED depends on LDR sensor "Cuaca" (it means Weather).

The Cuaca Sensor will detect surrounding area whether it sunny, cloudy, night or else.
When the sensor detect cloudy or night, it will trigger the system to switch on LED, vice versa.

Each LED has its own LDR sensor to make sure LED is indeed ON when the system give signal to ON. 
When system give signal ON but the LDR is not detect light from LED, BLYNK will give sign "there's a light that's off".
