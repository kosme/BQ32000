/*
 * bq32000.h
 *
 * Created: 01/09/2014 02:47:20 p.m.
 *  Author: kosme
 */ 

#include <stdlib.h>
#include <stdio.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
//#include <avr/interrupt.h>
#include "types.h"
#include "defs.h"
#include "i2c.h"

//Registros

/*#define slaveWrite 0b11010000
#define slaveRead 0b11010001*/
#define timeReg 0x00
#define dateReg 0x04

//Estructuras

/*struct time
{
	uint8_t hora;
	uint8_t fecha;
};*/

#ifndef BQ32000_H_
#define BQ32000_H_

class Bq32000
{
	private:
	
	public:
	Bq32000(void);
	~Bq32000(void);
	bool setTime(BYTE seg, BYTE min, BYTE hora);
	bool setDate(BYTE dia, BYTE mes, BYTE ano);
	BYTE *getTime();
	bool detect();
};



#endif /* BQ32000_H_ */