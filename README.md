Tanks to DirtBagXon, for External Hypseus Singe Scoreboard for Dragon's Lair game,
see original project: https://github.com/DirtBagXon/hypseus_scoreboard

I rewrote ALL Code and Adjusted to use only N.2 MAX7219 modules, for 2 Players, (a great saves of money)
and FINALLY WORKS (!) for ESP32 Wroom Dvkit v1 - (30 PIN), adding parameter, on lair.bat files, with right number of COM (1 or 2...or 6 ,etc),
at 115200 on COM "x" PC Port.

System Requirements:
- You must have Hypseus installed and working on your pc: https://github.com/DirtBagXon/hypseus-singe
- You must have an original copy of Dragon's Lair game working.
- You must have Arduino Ide installed and working on your pc
- You must have an ESP32 Wroom Kit 30 pin
- You must have 2 modules "MAX7219 8-Digit LED Display", and 10 "dupont cables" to connect ESP32 to Max7219 in daisy chain (see schematic.txt)
- The project uses serial communication with an Esp32 30 PIN driving n.2 "MAX7219 8-Digit LED Display" to power 7-segment LED.
The provided sketches demonstrate the serial communication (using serialib) between hypseus and the Arduino IDE. 
These should be portable to other programmable microcontrollers able to handle serial communication.

- Required By Arduino IDE libraries: "LEDControl" and "SerialLib"

STEPS TO PROGRAM AND TEST:
1) Connect your ESP32 to 2 Modules Max7219 (8 digit) following my schematic.txt
2) Open a new empty sketch on Arduino Ide
3) Copy and paste Scoreboard.ino code in Arduino Ide
4) Program ESP32 30 pin "DOIT ESP32 DEV KIT v1", and remember wath COM port is used by IDE
5) Close Ardunino IDE after ESP32 is programmed !
6) Modify your HYPSEUS file "lair.bat" command or lair.commands, used by HYPSEUS to launch game, adding this options  (at the end of the file):

    -usbscoreboard COM x 115200
   
Important: number "x" must be replaced with your COM <port number> used by Arduino IDE (the same COM port used in the step 4).
for example if Arduino IDE uses COM 6 to program ESP32, you must rename x with 6:

    -usbscoreboard COM 6 115200

if Arduino IDE uses COM 3 to program ESP32, you must replace "x" simbols with port number 3:

-usbscoreboard COM 3 115200

8) Save lair.bat and execute lair.bat and scoreboard works!
