#include <Arduino.h>
#include "task2.h"
String btnState(uint8_t btnState)
{
  if (btnState == HIGH)
  {

    return "0";
  }
  else
    return "1";
}

String ledState(uint8_t ledState)
{
  if (ledState == HIGH)
  {

    return "1";
  }
  else
    return "0";
}

void task2()
{
  enum class TaskStates
  {
    INIT,
    WAIT_COMMANDS
  };
  static TaskStates taskState = TaskStates::INIT;
  constexpr uint8_t ledYellow = 8;
  constexpr uint8_t button1Pin = 13;
  uint8_t ledValue;

  switch (taskState)
  {
  case TaskStates::INIT:
  {
    Serial.begin(115200);
    
    pinMode(ledYellow, OUTPUT);
    ledValue =LOW;
    digitalWrite(ledYellow, ledValue);
    pinMode(button1Pin, INPUT_PULLUP);
    taskState = TaskStates::WAIT_COMMANDS;
    break;
  }
  case TaskStates::WAIT_COMMANDS:
  {
    if (Serial.available() > 0)
    {
      String command = Serial.readStringUntil('\n');
      if (command == "ON")
      {
        ledValue =HIGH;
        digitalWrite(ledYellow, ledValue);
        
      }
      
      else if (command == "OFF")
      {
        ledValue = LOW;
        digitalWrite(ledYellow, ledValue);
        
      }
      else if (command == "read")
      {

        Serial.print("btn1: ");
        Serial.print(btnState(digitalRead(button1Pin)).c_str());
        Serial.print("led: ");
        Serial.print(ledState(ledValue).c_str());
        Serial.print('\n');
        //btn1: 1led: 1\n"
      }

    
    }
    break;
  }
  default:
  {
    break;
  }
  }
}