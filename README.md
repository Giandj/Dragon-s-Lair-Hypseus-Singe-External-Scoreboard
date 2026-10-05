Tanks to DirBagXon, for External Hypseus Scoreboard,
see original project: https://github.com/DirtBagXon/hypseus_scoreboard

I rewrote ALL Code and Adjusted to use only N.2 MAX7219 modules, for 2 Players, (a great saves of money)
and FINALLY WORKS (!) for ESP32 Wroom Dvkit v1 - (30 PIN), adding parameter, on lair.bat files, with right number of COM (1 or 2...or 6 ,etc),
at 115200 on COM PC Port:

Example: add this to your lair.bat, or lair.commands, this command is documented better on: https://github.com/DirtBagXon/hypseus_scoreboard
-usbscoreboard COM 6 115200

1) Program ESP32 with my code, scoreboard.ino (and control what com port is used)
2) Diconnect ESP32, and connect 2 modules MAX7219, see schematic.txt
3) Modify your lair.bat or lair.commands, adding -usbscoreboard COM 6 115200, at the end of the file
4) Reconnect your Esp32 to USB port of your pc (the same port used to program with Arduino IDE)
5) Launch Hypseus lair.bat and scoreboard works!
