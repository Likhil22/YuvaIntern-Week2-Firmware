/*
 * ============================================================
 * YuvaIntern - Week 2
 * Firmware Development and Implementation
 *
 * Project:
 * Timer Interrupt-Based LED Controller with UART
 *
 * Platform:
 * Arduino Uno R3 / ATmega328P
 *
 * Features:
 * 1. Manual LED control using UART
 * 2. Automatic LED blinking using Timer1 interrupt
 * 3. LED status reporting
 *
 * UART Commands:
 * ON
 * OFF
 * STATUS
 * AUTO
 * ============================================================
 */

#include <Arduino.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#define LED_PIN 13

// Variables shared with Timer1 interrupt
volatile bool timer_event = false;
volatile bool auto_mode = false;


/*
 * ============================================================
 * TIMER1 INTERRUPT SERVICE ROUTINE
 * ============================================================
 *
 * This interrupt occurs approximately once every second.
 *
 * The ISR only sets a flag.
 * The main loop performs the actual LED operation.
 */
ISR(TIMER1_COMPA_vect)
{
    if (auto_mode)
    {
        timer_event = true;
    }
}


/*
 * ============================================================
 * TIMER1 INITIALIZATION
 * ============================================================
 *
 * Arduino Uno clock frequency = 16 MHz
 *
 * Timer1:
 * Mode      = CTC
 * Prescaler = 1024
 * Compare   = 15624
 *
 * Interrupt frequency:
 *
 * 16,000,000 / (1024 × (15624 + 1))
 * ≈ 1 Hz
 *
 * Therefore, an interrupt occurs approximately once per second.
 */
void timer1_init()
{
    // Disable interrupts during timer configuration
    noInterrupts();

    // Reset Timer1 control registers
    TCCR1A = 0;
    TCCR1B = 0;

    // Reset counter
    TCNT1 = 0;

    // CTC mode
    TCCR1B |= (1 << WGM12);

    // Compare value
    OCR1A = 15624;

    // Prescaler = 1024
    TCCR1B |= (1 << CS12);
    TCCR1B |= (1 << CS10);

    // Enable Timer1 Compare Match A interrupt
    TIMSK1 |= (1 << OCIE1A);

    // Enable global interrupts
    interrupts();
}


/*
 * ============================================================
 * PROCESS UART COMMAND
 * ============================================================
 */
void process_command(String command)
{
    command.trim();

    /*
     * ON COMMAND
     */
    if (command == "ON")
    {
        // Disable automatic mode
        auto_mode = false;

        // Turn LED ON
        digitalWrite(LED_PIN, HIGH);

        Serial.println("Manual mode: LED ON");
    }


    /*
     * OFF COMMAND
     */
    else if (command == "OFF")
    {
        // Disable automatic mode
        auto_mode = false;

        // Turn LED OFF
        digitalWrite(LED_PIN, LOW);

        Serial.println("Manual mode: LED OFF");
    }


    /*
     * STATUS COMMAND
     */
    else if (command == "STATUS")
    {
        Serial.print("LED STATUS: ");

        if (digitalRead(LED_PIN) == HIGH)
        {
            Serial.println("ON");
        }
        else
        {
            Serial.println("OFF");
        }

        Serial.print("MODE: ");

        if (auto_mode)
        {
            Serial.println("AUTO");
        }
        else
        {
            Serial.println("MANUAL");
        }
    }


    /*
     * AUTO COMMAND
     */
    else if (command == "AUTO")
    {
        // Enable automatic mode
        auto_mode = true;

        Serial.println("Automatic mode enabled");
        Serial.println("LED toggles every second");
    }


    /*
     * INVALID COMMAND
     */
    else
    {
        Serial.println("Invalid command");
        Serial.println("Available commands: ON, OFF, STATUS, AUTO");
    }
}


/*
 * ============================================================
 * SETUP
 * ============================================================
 */
void setup()
{
    // Configure built-in LED as output
    pinMode(LED_PIN, OUTPUT);

    // Initially turn LED OFF
    digitalWrite(LED_PIN, LOW);

    // Start UART communication
    Serial.begin(9600);

    // Initialize Timer1
    timer1_init();

    // Startup message
    Serial.println();
    Serial.println("================================");
    Serial.println(" Timer Interrupt LED Controller ");
    Serial.println("================================");
    Serial.println("System Ready");
    Serial.println();
    Serial.println("Available Commands:");
    Serial.println("ON     - Turn LED ON");
    Serial.println("OFF    - Turn LED OFF");
    Serial.println("STATUS - Show LED status");
    Serial.println("AUTO   - Enable automatic mode");
    Serial.println();
}


/*
 * ============================================================
 * MAIN LOOP
 * ============================================================
 */
void loop()
{
    /*
     * Check whether Timer1 generated an event
     */
    if (timer_event)
    {
        // Clear the event
        timer_event = false;

        // Toggle LED
        digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    }


    /*
     * Check for UART commands
     */
    if (Serial.available() > 0)
    {
        String command = Serial.readStringUntil('\n');

        process_command(command);
    }
}