/*-----------------------------------------------------------------------------------------------------------------------------
tVOC sensor : MiCSVZ89TE - V1.0
Created by Romain, society LOCA SERVICE (FRANCE)
First release: 15/06/2022
Last release: 15/06/2022

SENSOR DATASHEET: 	https://www.sgxsensortech.com/content/uploads/2016/07/MiCS-VZ-89TE-V1.0.pdf
					          https://www.sgxsensortech.com/content/uploads/2017/03/I2C-Datasheet-MiCS-VZ-89TE-rev-H-ed170214-Read-Only.pdf
				          	https://www.sgxsensortech.com/content/uploads/2016/07/VZ869-E-Version-rev-B-I2C-communication-quick-manual.pdf
-----------------------------------------------------------------------------------------------------------------------------*/

#ifndef MICSVZ89TE_H
#define MICSVZ89TE_H

//_____Variables and constants__________

extern const byte size_;				        // Number of byte send by the sensor

extern long RESISTOR, tVOC, CO2_equ, Status, CRC;		//All long variables that you can use on your main code, use getStatus() to set them

//_____Fonctions________________________

void config_MiCSVZ89TE(byte address);		    //Return: void ; Pram: I2C address of your card (master)
boolean getStatus_MiCSVZ89TE();			        //Return: boolean 0 = transmission failed, 1 = transmission completed ; Param: null
											                      //getStatus() fonction set the RESISTANCE, tVOC, CO2_equ, Error_Status and CRC statut
byte verif_CRC(byte *tab, byte size_CRC);	  //Retunr: byte CRC calculated

#endif
