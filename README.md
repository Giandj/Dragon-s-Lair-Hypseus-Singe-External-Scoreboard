Tanks to DirtBagXon, for External Hypseus Singe Scoreboard for Dragon's Lair game,
see original project: https://github.com/DirtBagXon/hypseus_scoreboard

Watch my video for demonstration of this project: https://youtu.be/NafDWzedd7g?si=RvfrlTbz5X83yFe-

<img width="1302" height="628" alt="immagine" src="https://github.com/user-attachments/assets/b04cdf04-1149-49a0-a282-417559da4259" />



I rewrote ALL the Original Code and Adjusted to use only n.2 MAX7219 modules, for 2 Players, instead of n.5 MAX7219 modules (a great saves of money)
and FINALLY WORKS (!) for ESP32 Wroom Dev kit v1 - (30 PIN).

<img width="1616" height="871" alt="immagine" src="https://github.com/user-attachments/assets/be034d43-734e-4adb-a938-a0326a73fc44" />



System Requirements:
- You must have Hypseus installed and working on your pc: https://github.com/DirtBagXon/hypseus-singe
- You must have an original copy of Dragon's Lair game working.
- You must have Arduino Ide installed and working on your pc
- You must have an ESP32 Wroom Dev Kit v1 - 30 pin (i think it can works also on ESP32 38 PIN, take care of schematic.txt connections)
- You must have 2 modules "MAX7219 8-Digit LED Display", and 10 "dupont cables" to connect ESP32 to Max7219 in daisy chain (see schematic.txt)
- The project uses serial communication with an Esp32 30 PIN driving n.2 "MAX7219 8-Digit LED Display" to power 7-segment LED.

The provided sketch (scoreboard.ino) demonstrate the serial communication (using serialib) between hypseus and the Arduino IDE. 
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
