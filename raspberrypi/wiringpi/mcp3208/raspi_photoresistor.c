/*
 * Use Raspberry Pi to get light strength data with photoresistor
 * https://osoyoo.com/2016/12/16/raspberrypi-photoresistor/
 * 
 * PostgreSQL C
 * https://zetcode.com/db/postgresqlc/
 * 
 * Compilation
 * gcc -std=c99 -I/usr/include/postgresql -lwiringPi -lpq -o app raspi_photoresistor.c
 * 
 * Execution
 * sudo ./app
 *
 * If no value:
 * rmmod spi_bcm2708 or spi_bcm2835
 * modprobe spi_bcm2708 or spi_bcm2835
 * 
 * 
 * Wiring
 * 
 * MCP3208           Rasbery Pi          WiringPi Pin
 * Pin Symbol        Pin Symbol
 *  9  DGND     GND  39  GND
 * 10  CS/SHDN       24  GPIO  8 (CE0)   10
 * 11  DIN           19  GPIO 10 (MOSI)  12
 * 12  DOUT          21  GPIO  9 (MISO)  13
 * 13  CLK           23  GPIO 11 (SCLK)  14
 * 14  AGND     GND  39  GND
 * 15  VREF     3.3V  1  3.3V
 * 16  VDD      3.3V  1  3.3V
 *
 */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#include <libpq-fe.h>

#include <wiringPi.h>
#include <wiringPiSPI.h>

#define CS_MCP3208  8       // BCM_GPIO8

#define SPI_CHANNEL 0
//#define SPI_SPEED   100000  // !! Start low here and if all works try to increase if needed on a breadboard I could go upto about 750000
#define SPI_SPEED   10000

static PGconn* pgc = 0;
static PGresult *pgr = 0;

static int cleanupandexit(int rc);
static int read_mcp3208_adc(unsigned char adcChannel);

static char query[1024];

int main (void) {
  int adc1Channel = 0;
  int adc1Value   = 0;
  double adc1Sum, adc2Average, adc1Ratio, adc1Voltage;
  int count, i;

  pgc = PQconnectdb("host=localhost user=orri password=Bios93 dbname=poc");

  if (PQstatus(pgc) == CONNECTION_BAD) {
    fprintf(stderr, "Connection to database failed: %s\n", PQerrorMessage(pgc));
    return cleanupandexit(1);
  }

  if (wiringPiSetup() == -1) {
    fprintf (stderr, "Unable to start wiringPi: %s\n", strerror(errno));
    return cleanupandexit(1);
  }

  if(wiringPiSPISetup(SPI_CHANNEL, SPI_SPEED) == -1) {
    fprintf (stderr, "wiringPiSPISetup Failed: %s\n", strerror(errno));
    return cleanupandexit(1);
  }

  pinMode(CS_MCP3208, OUTPUT);

  while(1) {
    count = 0;
    adc1Sum = 0.0;
    adc2Average = 0.0;
    for (i = 0; i < 10; i++) {
      adc1Value = read_mcp3208_adc(adc1Channel);
      if (adc1Value > 0) {
        adc1Sum += (double)adc1Value;
        count++;
      }
      usleep(10000);
    }
    if (count > 0) {
      adc2Average = adc1Sum / ((double)count);
    }

    adc1Value = (int)adc2Average;
    adc1Ratio = adc2Average / 4096.0;
    adc1Voltage = 3.3 * adc1Ratio;

    printf("adc0 Average: %04u\n", adc1Value);

    if (adc1Value > 0) {
      sprintf(query, "INSERT INTO mcp3208(tsz, i, v) VALUES(now(), %d, %f)", adc1Value, adc1Ratio);
      pgr = PQexec(pgc, query);
      if (PQresultStatus(pgr) != PGRES_COMMAND_OK) {
        fprintf(stderr, "Insert failed: %s\n", PQerrorMessage(pgc));
        cleanupandexit(1);  
      }
      PQclear(pgr);
    }
  }

  return cleanupandexit(0);
}

int cleanupandexit(int rc) {
  if (pgr) {
    PQclear(pgr);
    pgr = 0;
  }
  if (pgc) {
    PQfinish(pgc);
    pgc = 0;
  }
  return rc;
}

int read_mcp3208_adc(unsigned char adcChannel) {
  unsigned char buff[3];
  int adcValue = 0;

  buff[0] = 0x06 | ((adcChannel & 0x07) >> 7);
  buff[1] = ((adcChannel & 0x07) << 6);
  buff[2] = 0x00;

  digitalWrite(CS_MCP3208, 0);  // Low : CS Active

  wiringPiSPIDataRW(SPI_CHANNEL, buff, 3);

  buff[1] = 0x0F & buff[1];
  adcValue = ( buff[1] << 8) | buff[2];

  digitalWrite(CS_MCP3208, 1);  // High : CS Inactive

  return adcValue;
}
