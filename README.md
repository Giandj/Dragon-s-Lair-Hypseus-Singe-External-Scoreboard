# Dragon-s-Lair-Hypseus-Singe-External-Scoreboard
I rewrote ALL Code and Adjusted to use only N.2 MAX7219 modules, for 2 Players, (a great saves of money)

FINALLY WORKS (!) on my ESP32 30 PIN, adding parameter, on .bat files, with right number of COM (1 or 2...or 6 ,etc),
at 115200 on COM PC Port:

-usbscoreboard COM 6 115200  (number 6 can be changed with your COM number, for example 2,3,4,5,depends wich com port use your pc)

MY CONNECTIONS ARE SIMPLYFIED ON ESP32 30 PIN DEV KIT (SCHEMATIC):

CONNECTIONS FROM ESP32 TO MAX7219 (first module MAX7219 #0 Input)
ESP32 VIN → Module 0 VCC (input)
ESP32 GND → Module 0 GND (input)
ESP32 D23 → Module 0 DIN (input)
ESP32 D5 → Module 0 CS (input)
ESP32 D18 → Modulo 0 CLK (input)

CASCADE (Daisy Chain) CONNECTIONS FROM MAX7219 MODULE #0 (output) TO MODULE #1 (second MAX7219 Input):
Module 0 VCC (Output) → Module 1 VCC (input)
Module 0 GND (Output) → Module 1 GND (input)
Module 0 DOUT (Output) → Module 1 DIN (input)
Module 0 CS (Output) → Module 1 CS (input)
Module 0 CLK (Output) → Module 1 CLK (input)
