# MiCSVZ89TE
Arduino libraire for tVOC sensor MiCSVZ89TE

Introducing -----------------------------------------------------

This librairy very simple allow to get the informations of the MiCSVZ89TE tVOC sensor.
A only fonction getStatus_MiCSVZ89TE() allow to set some globals variables in theire status.
After the call of this fonction, you can use the globals variables tVOC, CO2_EQU, RESISTOR, Status and CRC in your main code !!!

Installation ----------------------------------------------------

Dowload the .zip ans add it with the Arduino IDE.

 - Open Arduino IDE
 - Go on Sketch -> Include librairy -> Add.ZIP librairy

Usage ----------------------------------------------------------

First:

Include the librairy with

#include <MiCSVZ89TE.h>

Setup:

If you use the librairy Wire.h you don't need to use the fonction config_MiCSVZ89TE(byte I2C_address);
Else in your Setup add the fonction: config_MiCSVZ89TE(byte I2C_address); /!\ Your card will take the I2C_address as I2C master address.

Loop:

Use the fonction getStatus_MiCSVZ89TE() to reset the values of the differents varaibles tVOC, CO2_equ, RESISTOR, STatus and CRC.
If this fonction retunr 1 : the transmission succeeded, if retunr 0 : There is an error with the CRC -> the transmission has failed
