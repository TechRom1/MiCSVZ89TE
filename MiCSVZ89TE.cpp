/*-----------------------------------------------------------------------------------------------------------------------------
  tVOC sensor : MiCSVZ89TE - V1.0
  Created by Romain, society LOCA SERVICE (FRANCE)
  First release: 15/06/2022
  Last release: 15/06/2022

  SENSOR DATASHEET:   https://www.sgxsensortech.com/content/uploads/2016/07/MiCS-VZ-89TE-V1.0.pdf
                    https://www.sgxsensortech.com/content/uploads/2017/03/I2C-Datasheet-MiCS-VZ-89TE-rev-H-ed170214-Read-Only.pdf
                    https://www.sgxsensortech.com/content/uploads/2016/07/VZ869-E-Version-rev-B-I2C-communication-quick-manual.pdf
  -----------------------------------------------------------------------------------------------------------------------------*/

#include <Arduino.h>
#include <Wire.h>
#include "MiCSVZ89TE.h"

//_____Variables and constants________________________________________________
const byte sensor_address = 0b1110000;    // tVOC sensor I2C address
byte tab_data[7] = {0};                   // table to receive raw data
const byte size_ = 7;
long RESISTOR, tVOC, CO2_equ, Status, CRC;
//____________________________________________________________________________


void config_MiCSVZ89TE(byte address) {
  Wire.begin(address);
}//______________________________________________________________________________________________________________________________________________________________________________________________

boolean getStatus_MiCSVZ89TE() {

  Wire.setClock(100000);

  boolean transmissionStatus;                   //Return: 1 = transmission completed,   0 = transmission failled

  Wire.beginTransmission(sensor_address);       //Begin the connection with the tVoc sensor
  Wire.write(byte(0x0C));                       //Give data request
  Wire.write(byte(0x00));
  Wire.write(byte(0x00));
  Wire.write(byte(0x00));
  Wire.write(byte(0x00));
  Wire.write(byte(0xFF - (0xE0 + 0x0C)));       //Send CRC
  Wire.endTransmission();                       //End of the transmission

  delay(100);                                   //Waiting request time

  Wire.requestFrom(sensor_address, 7);          //Give data request of 7  bytes on sensor address

  if ( Wire.available() >= size_) {             //table tab_data get the values of data sent by the sensor
    for (byte i = 0; i < size_; i++) {
      tab_data[i] = Wire.read();
    }
  }

  if (tab_data[6] == verif_CRC(tab_data, size_)) {                                    //CRC vérification

    tVOC = (tab_data[0] - 13) * (1000 / 229);                                         //tVOC calcul, view doc
    CO2_equ = (tab_data[1] - 13) * (1600 / 229) + 400;                                //CO2_equ calcul, view doc
    RESISTOR = 10 * (tab_data[4] + (256 * tab_data[3]) + (65536 * tab_data[2]));      //RESISTOR calcul, view doc
    Status = tab_data[5];                                                             //Error_Status
    CRC = tab_data[6];                                                                //CRC

    transmissionStatus = 1;                                                           //Transmission completed

  } else {
    transmissionStatus = 0;                                                           //Transmission failed
  }

  return transmissionStatus;

}//______________________________________________________________________________________________________________________________________________________________________________________________


byte verif_CRC(byte *tab, byte size_CRC) {

  byte crc = 0x00;
  byte i = 0x00;
  uint16_t sum = 0x0000;

  /* Summation with carry */
  for (i = 0; i < size_CRC - 1; i++) {
    sum += tab[i];
  }//end loop
  crc = (byte)sum;
  crc += (sum / 0x0100); 					// Add with carry
  crc = 0xFF - crc; 							// Complement
  return (crc);                   //Return CRC

}//______________________________________________________________________________________________________________________________________________________________________________________________
