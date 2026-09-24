============================================================
YUVAINTERN - WEEK 2
FIRMWARE DEVELOPMENT AND IMPLEMENTATION
============================================================

PROJECT TITLE
Timer Interrupt-Based LED Controller with UART Communication

PLATFORM
Arduino Uno (ATmega328P)

============================================================
1. PROJECT OBJECTIVE
============================================================

The objective of this project is to develop and test firmware
for an embedded system using hardware timer interrupts and
UART communication.

The system provides both manual and automatic LED control.

In manual mode, the LED is controlled through UART commands.

In automatic mode, Timer1 generates periodic interrupts and
the LED toggles approximately once every second.


============================================================
2. HARDWARE USED
============================================================

1. Arduino Uno
2. Built-in LED connected to digital pin 13
3. USB connection for programming and UART communication


============================================================
3. SOFTWARE USED
============================================================

1. Arduino IDE
2. Arduino Uno board package
3. Serial Monitor
4. Embedded C/C++ Arduino firmware


============================================================
4. SYSTEM FEATURES
============================================================

The firmware provides the following features:

- Manual LED ON control
- Manual LED OFF control
- LED status monitoring
- Automatic LED blinking
- Timer1 hardware interrupt
- UART serial communication
- Invalid command detection


============================================================
5. UART COMMANDS
============================================================

Command: ON

Function:
Turns the LED ON and switches the system to MANUAL mode.


Command: OFF

Function:
Turns the LED OFF and switches the system to MANUAL mode.


Command: STATUS

Function:
Displays the current LED state and operating mode.


Command: AUTO

Function:
Enables automatic LED control using the Timer1 interrupt.


============================================================
6. FIRMWARE ARCHITECTURE
============================================================

The firmware is divided into the following functional sections:

1. System initialization
2. Timer1 initialization
3. Timer interrupt service routine
4. UART command processing
5. Main program loop


System flow:

START
  |
  v
Initialize LED
  |
  v
Initialize UART
  |
  v
Initialize Timer1
  |
  v
Main Loop
  |
  +------> Check Timer Event
  |              |
  |              v
  |        Toggle LED in AUTO mode
  |
  +------> Check UART
                 |
                 v
          Process Command
                 |
                 v
             Repeat


============================================================
7. TIMER INTERRUPT IMPLEMENTATION
============================================================

Timer1 of the Arduino Uno is configured in CTC
(Clear Timer on Compare Match) mode.

The Arduino Uno operates at a clock frequency of 16 MHz.

Timer1 uses a prescaler of 1024 and a compare value of 15624.

This produces an interrupt approximately once every second.

The Timer1 interrupt service routine (ISR) does not directly
perform lengthy operations. Instead, it sets a timer event flag.

The main loop checks this flag and toggles the LED.

This approach keeps the interrupt service routine short and
allows the main program to handle the actual LED operation.


============================================================
8. UART COMMUNICATION
============================================================

UART communication is initialized at a baud rate of 9600.

The Serial Monitor is used to send commands to the Arduino.

The firmware reads the received command and passes it to the
command processing function.

The command processor identifies valid commands and performs
the corresponding operation.

If an unknown command is received, the firmware displays an
invalid command message.


============================================================
9. TESTING PROCEDURE
============================================================

The firmware was tested using an Arduino Uno and the Arduino
IDE Serial Monitor.

The following functions were tested:

1. System startup
2. LED ON command
3. LED OFF command
4. STATUS command
5. AUTO mode
6. STATUS in AUTO mode
7. Invalid command
8. Returning from AUTO mode to MANUAL mode


============================================================
10. TEST RESULTS
============================================================

Test 1:
Test: System startup
Expected Result: System Ready message is displayed
Result: PASS


Test 2:
Test: ON command
Expected Result: LED turns ON and system enters MANUAL mode
Result: PASS


Test 3:
Test: STATUS command
Expected Result: LED state and operating mode are displayed
Result: PASS


Test 4:
Test: OFF command
Expected Result: LED turns OFF and system remains in MANUAL mode
Result: PASS


Test 5:
Test: AUTO command
Expected Result: Automatic LED blinking starts using Timer1
Result: PASS


Test 6:
Test: STATUS command in AUTO mode
Expected Result: LED state and AUTO mode are displayed
Result: PASS


Test 7:
Test: Invalid command
Expected Result: Invalid command message is displayed
Result: PASS


Test 8:
Test: ON command after AUTO mode
Expected Result: AUTO mode is disabled and LED remains ON
Result: PASS


============================================================
11. DEBUGGING AND OBSERVATIONS
============================================================

During development, the firmware was compiled and tested
using the Arduino IDE.

The initial implementation required correction of the timer
configuration and board/port setup.

After selecting the Arduino Uno board and the correct COM port,
the firmware was successfully uploaded to the Arduino.

The Serial Monitor was then used to verify UART communication
and command responses.

All planned functional tests were successfully completed.


============================================================
12. RESULT
============================================================

The Timer Interrupt-Based LED Controller was successfully
implemented and tested on an Arduino Uno.

The system successfully demonstrated:

- Hardware timer interrupt operation
- UART communication
- Manual LED control
- Automatic LED control
- Status reporting
- Command validation

All defined functional tests passed successfully.


============================================================
13. CONCLUSION
============================================================

The project successfully demonstrates the implementation of
basic embedded firmware using timer interrupts and UART
communication.

The use of a Timer1 interrupt allows the system to perform
periodic LED control without continuously depending on delay
functions.

The project also demonstrates structured firmware development,
interrupt handling, serial communication, command processing,
debugging, and functional testing.


============================================================
14. FILES INCLUDED
============================================================

YuvaIntern_Week2_Firmware.ino
README.txt

Testing screenshots:
- Startup
- Manual Control
- Automatic Mode
- Invalid Command


============================================================
END OF README
============================================================