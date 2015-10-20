/*
 * i2c.cpp
 *
 * Created: 02/09/2014 01:21:00 a.m.
 *  Author: kosme
 */ 

#include "i2c.h"

void i2cInit(void)
{
	// set i2c bit rate to 40KHz
	//i2cSetBitrate(100);
	//set SCL to 400kHz
	TWSR = 0x00;
	TWBR = 0x0C;
	// enable TWI (two-wire interface)
	sbi(TWCR, TWEN);
}

void i2cSetBitrate(unsigned short bitrateKHz)
{
	unsigned char bitrate_div;
	
	cbi(TWSR, TWPS0);
	cbi(TWSR, TWPS1);
	
	// calculate bitrate division
	bitrate_div = ((F_CPU/4000l)/bitrateKHz);
	if(bitrate_div >= 16)
	bitrate_div = (bitrate_div-16)/2;
	outb(TWBR, bitrate_div);
}

void i2cSendStart(void)
{
	WRITE_sda();
	// send start condition
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while ((TWCR & (1<<TWINT)) == 0);
}

void i2cSendStop(void)
{
	// transmit stop condition
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}

void i2cWaitForComplete(void)
{
	int i = 0;		//time out variable
	
	// wait for i2c interface to complete operation
	while ((!(TWCR & (1<<TWINT))) && (i < 90))
	i++;
}

void i2cSendByte(unsigned char data)
{

	WRITE_sda();
	// save data to the TWDR
	TWDR = data;
	// begin send
	TWCR = (1<<TWINT)|(1<<TWEN);
}

void i2cReceiveByte(unsigned char ackFlag)
{
	// begin receive over i2c
	if( ackFlag )
	{
		// ackFlag = TRUE: ACK the recevied data
		outb(TWCR, (inb(TWCR)&TWCR_CMD_MASK)|BV(TWINT)|BV(TWEA));
	}
	else
	{
		// ackFlag = FALSE: NACK the recevied data
		outb(TWCR, (inb(TWCR)&TWCR_CMD_MASK)|BV(TWINT));
	}
}

unsigned char i2cGetReceivedByte(void)
{
	// retieve received data byte from i2c TWDR
	return( inb(TWDR) );
}

unsigned char i2cGetStatus(void)
{
	// retieve current i2c status from i2c TWSR
	return( inb(TWSR) );
}