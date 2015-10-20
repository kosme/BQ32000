/*
 * bq32000.cpp
 *
 * Created: 01/09/2014 02:47:37 p.m.
 *  Author: kosme
 */ 

#include "bq32000.h"

namespace
{
	#define slaveWrite 0b11010000
	#define slaveRead 0b11010001
}

 Bq32000::Bq32000(void)
{
	
}

 Bq32000::~Bq32000(void)
{
	
}


BYTE *Bq32000::getTime()
{
	static BYTE tiempo[6];
	i2cSendStart();
	i2cWaitForComplete();
	i2cSendByte(slaveWrite);
	i2cWaitForComplete();
	i2cSendByte(0x00);
	i2cWaitForComplete();
	//i2cSendStop();
	
	i2cSendStart();
	//i2cWaitForComplete();
	i2cSendByte(slaveRead);
	i2cWaitForComplete();
	for(BYTE i=0;i<3;i++)
	{
		i2cReceiveByte(TRUE);
		i2cWaitForComplete();
		tiempo[2-i]=i2cGetReceivedByte();
		i2cWaitForComplete();
	}
	//aquí se está recibiendo y descartando el día de la semana (1-7)
	i2cReceiveByte(TRUE);
	i2cWaitForComplete();
	//Leer día y mes
	for(BYTE i=0;i<2;i++)
	{
		i2cReceiveByte(TRUE);
		i2cWaitForComplete();
		tiempo[i+3]=i2cGetReceivedByte();
		i2cWaitForComplete();
	}
	//Leer año
	i2cReceiveByte(FALSE);
	i2cWaitForComplete();
	tiempo[5]=i2cGetReceivedByte();
	i2cSendStop();
	return tiempo;
}

bool Bq32000::setTime(BYTE seg, BYTE min, BYTE hora)
{
	i2cSendStart();
	i2cWaitForComplete();
	i2cSendByte(slaveWrite);
	i2cWaitForComplete();
	i2cSendByte(timeReg);
	i2cWaitForComplete();
	if (((seg&0x70)>0x50)||((seg&0x0F)>0x09))
		return false;
	else
		i2cSendByte(seg);
	i2cWaitForComplete();
	if (((min&0x70)>0x50)||((min&0x0F)>0x09))
		return FALSE;
	else
		i2cSendByte(min);
	i2cWaitForComplete();
	if(((hora&0x0F)>0x09)||((hora&0x3F)>0x23))
		return FALSE;
	else
		i2cSendByte(hora);
	i2cWaitForComplete();
	i2cSendStop();
	return TRUE;
}

bool Bq32000::setDate(BYTE dia, BYTE mes, BYTE ano)
{
	i2cSendStart();
	i2cWaitForComplete();
	i2cSendByte(slaveWrite);
	i2cWaitForComplete();
	i2cSendByte(dateReg);
	i2cWaitForComplete();
	if(((dia&0x3F)>0x31)||(((dia&0x3F)==0x00))||((dia&0x0F)>0x09))
		return false;
	else
		i2cSendByte(dia&0x3F);
	i2cWaitForComplete();
	if(((mes&0x1F)>0x12)||((mes&0x1F)==0x00)||((mes&0x0F)>0x09))
		return false;
	else
		i2cSendByte(mes&0x1F);
	i2cWaitForComplete();
	if(((ano&0xF0)>0x90)||((ano&0x0F)>0x09))
		return false;
	else
		i2cSendByte(ano);
	i2cWaitForComplete();
	i2cSendStop();
	return true;
}

bool Bq32000::detect()
{
	i2cSendStart();
	i2cWaitForComplete();
	i2cSendByte(slaveWrite);
	i2cWaitForComplete();
	i2cSendByte(0x08);
	i2cWaitForComplete();
	
	i2cSendStart();
	//i2cWaitForComplete();
	i2cSendByte(slaveRead);
	i2cWaitForComplete();
	i2cReceiveByte(FALSE);
	i2cWaitForComplete();
	BYTE c = i2cGetReceivedByte();
	i2cSendStop();
	if(c==0x90)
		return true;
	else
		return false;
}