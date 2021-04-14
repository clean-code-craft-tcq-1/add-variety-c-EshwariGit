#include "typewise-alert.h"
#include <stdio.h>

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  }
  if(value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

BreachLimit classifyTemperatureBreach[3] = {{0,35}, {0,45}, {0,40}};

InfoType(*Alert[])(BreachType) = {sendToController, sendToEmail,sendToConsole};
InfoType checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {
  InfoType Value = FAIL;
  BreachType breachType = inferBreach(classifyTemperatureBreach[batteryChar.coolingType].lowerLimit,  classifyTemperatureBreach[batteryChar.coolingType].upperLimit, temperatureInC);
  Value = Alert[alertTarget](breachType);
  return Value;

}

InfoType sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
  return PASS;
}

InfoType sendToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";
 
  switch(breachType) {
    case TOO_LOW:
      printf("Hi, the temperature is too low\n");
      printf("To: %s\n", recepient);
      break;
    case TOO_HIGH:
    
      printf("Hi, the temperature is too high\n");
      printf("To: %s\n", recepient);
      break;

  }
  return PASS;
}
// Print to console
InfoType sendToConsole(BreachType breachType){
  printf( "The Console reads : %x\n", breachType);
  return PASS;
}
