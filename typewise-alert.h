#pragma once

typedef enum {
  PASSIVE_COOLING,
  HI_ACTIVE_COOLING,
  MED_ACTIVE_COOLING
} CoolingType;

typedef enum {
  NORMAL,
  TOO_LOW,
  TOO_HIGH
} BreachType;

typedef struct {
	double lowerLimit;
	double upperLimit;
}BreachLimit;


typedef enum {
  TO_CONTROLLER,
  TO_EMAIL,
  TO_CONSOLE
} AlertTarget;

typedef struct {
  CoolingType coolingType;
  char brand[48];
} BatteryCharacter;

typedef enum{
	FAIL,
	PASS
} InfoType;
InfoType checkAndAlert(
  AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);
BreachType inferBreach(double value, double lowerLimit, double upperLimit);
InfoType sendToController(BreachType breachType);
InfoType sendToEmail(BreachType breachType);
InfoType sendToConsole(BreachType breachType);
