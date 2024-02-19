#include <Arduino.h>

// Pin-Definitions
#define RF_DETECT PIN_PA1
#define RF_RESET PIN_PA2
#define B PIN_PA3
#define CPU_STATE PIN_PA6
#define TEST_GO PIN_PA7

#define RF_THRESHOLD 500  // Threshold Voltage at which RF-Signal is strong enough to be reliably detected by the Divider-Chips
#define ADC_VREF 2500.0  // Internal Reference Voltage of the ADC in mV

float voltRead(uint8_t pin);

void setup() {
  // put your setup code here, to run once:
  pinMode(RF_DETECT, INPUT);
  pinMode(RF_RESET, OUTPUT);
  pinMode(B, INPUT_PULLUP);
  pinMode(CPU_STATE, OUTPUT);
  pinMode(TEST_GO, INPUT_PULLUP);
  digitalWrite(RF_RESET, HIGH);
  digitalWrite(CPU_STATE, LOW);
  if(ADC_VREF < 5000){
    analogReference(INTERNAL2V5);
  } else {
    analogReference(INTERNAL4V3);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if(voltRead(RF_DETECT) > RF_THRESHOLD){
    digitalWrite(CPU_STATE, HIGH);
  } else {
    digitalWrite(CPU_STATE, LOW);
  }
}

/*
  @brief Read voltage from a pin by using the analogRead-Function to get raw ADC Value and then convert it to a voltage value.
  @param pin: Pin to read voltage from
  @return Voltage in mV
*/
float voltRead(uint8_t pin) {
  return (ADC0_RES * ADC_VREF) / 1023.0;
}

// TODO: Setup Timers for timer-based check of the RF-Detect-Pin
// TODO: ISR for the Timer Interrupt based approach
// TODO: Implement the RF-Reset-Functionality