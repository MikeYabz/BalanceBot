#include "MPU6050.h"

unsigned char buffer [10];
uint8_t addressWrite = 0xD0; // 1101 0000
uint8_t addressRead = 0xD1; // 1101 0001
int error;
uint8_t addresses[6] = {0x3B,0x3D,0x3F,0x43,0x45,0x47}; //x,y,z,pitch,yaw,roll

void Init(void)
{	
		//exit sleep mode
	buffer[0] = 0x6B;
	buffer[1] = 0x08; //reset = 0, sleep = 0, cycle = 0, internal 8Mhz oscillator, disable temp sensor
	error = HAL_I2C_Master_Transmit(&hi2c1, addressWrite, buffer, 2, 100);
	
		//set accelerometer sensitivity
	buffer[0] = 0x1C;
	buffer[1] = 0x10; 
	error = HAL_I2C_Master_Transmit(&hi2c1, addressWrite, buffer, 2, 100);
	
		//set gyroscope sensitivity
	buffer[0] = 0x1B;
	buffer[1] = 0x10; //reset = 0, sleep = 0, cycle = 0, internal 8Mhz oscillator, disable temp sensor
	error = HAL_I2C_Master_Transmit(&hi2c1, addressWrite, buffer, 2, 100);	
}

void check(float data[6])
{
	for (int i=0;i<6;i++)
	{
		int16_t temp[6];
		buffer[0] = addresses[i];
		error = HAL_I2C_Master_Transmit(&hi2c1, addressRead, buffer, 1, 1000); 
		error = HAL_I2C_Master_Receive(&hi2c1, addressRead, buffer, 1, 1000);
		temp[i] = buffer[0]<<8;		
		buffer[0] = addresses[i]+1;
		error = HAL_I2C_Master_Transmit(&hi2c1, addressRead, buffer, 1, 1000); 
		error = HAL_I2C_Master_Receive(&hi2c1, addressRead, buffer, 1, 1000);
		temp[i] |= buffer[0];
		temp[i] -= 1;
		temp[i] = ~temp[i];
		data[0] = (float)temp[0];
		data[1] = (float)temp[1];
		data[2] = (float)temp[2];
		data[3] = (float)temp[3];
		data[4] = (float)temp[4];
		data[5] = (float)temp[5];
	}
}

/*void sleepOff() //turns off sleep and cycle
{
	buffer[0]=0x6B;
	HAL_I2C_Master_Transmit(&hi2c1, addressRead, buffer, 1, 100); 
	HAL_I2C_Master_Receive(&hi2c1, addressRead, buffer, 1, 100);
	buffer[1] = buffer[0] & 0x9F;
	buffer[0] = 0x6B;
	HAL_I2C_Master_Transmit(&hi2c1, addressWrite, buffer, 2, 100);	
}*/


/*

		int16_t xReading;
		int16_t yReading;
		int16_t zReading;
		
		
		buffer[0] = 0x3B;
		error = HAL_I2C_Master_Transmit(&hi2c1, addressRead, buffer, 1, 1000); 
		error = HAL_I2C_Master_Receive(&hi2c1, addressRead, buffer, 1, 1000);
		xReading = buffer[0]<<8;		
		buffer[0] = 0x3C;
		error = HAL_I2C_Master_Transmit(&hi2c1, addressRead, buffer, 1, 1000); 
		error = HAL_I2C_Master_Receive(&hi2c1, addressRead, buffer, 1, 1000);
		xReading |= buffer[0];
		xReading -= 1;
		xReading = ~xReading;
		
		buffer[0] = 0x3D;
		error = HAL_I2C_Master_Transmit(&hi2c1, addressRead, buffer, 1, 1000); 
		error = HAL_I2C_Master_Receive(&hi2c1, addressRead, buffer, 1, 1000);
		yReading = buffer[0]<<8;		
		buffer[0] = 0x3E;
		error = HAL_I2C_Master_Transmit(&hi2c1, addressRead, buffer, 1, 1000); 
		error = HAL_I2C_Master_Receive(&hi2c1, addressRead, buffer, 1, 1000);
		yReading |= buffer[0];
		yReading -= 1;
		yReading = ~yReading;
		
		buffer[0] = 0x3F;
		error = HAL_I2C_Master_Transmit(&hi2c1, addressRead, buffer, 1, 1000); 
		error = HAL_I2C_Master_Receive(&hi2c1, addressRead, buffer, 1, 1000);
		zReading = buffer[0]<<8;		
		buffer[0] = 0x40;
		error = HAL_I2C_Master_Transmit(&hi2c1, addressRead, buffer, 1, 1000); 
		error = HAL_I2C_Master_Receive(&hi2c1, addressRead, buffer, 1, 1000);
		zReading |= buffer[0];		
		zReading -= 1;
		zReading = ~zReading;
		
		
		int16_t pitchReading;
		int16_t rollReading;
		int16_t yawReading;
		
		
		buffer[0] = 0x43;
		error = HAL_I2C_Master_Transmit(&hi2c1, addressRead, buffer, 1, 1000); 
		error = HAL_I2C_Master_Receive(&hi2c1, addressRead, buffer, 1, 1000);
		pitchReading = buffer[0]<<8;		
		buffer[0] = 0x44;
		error = HAL_I2C_Master_Transmit(&hi2c1, addressRead, buffer, 1, 1000); 
		error = HAL_I2C_Master_Receive(&hi2c1, addressRead, buffer, 1, 1000);
		pitchReading |= buffer[0];
		pitchReading -= 1;
		pitchReading = ~pitchReading;
		
		buffer[0] = 0x45;
		error = HAL_I2C_Master_Transmit(&hi2c1, addressRead, buffer, 1, 1000); 
		error = HAL_I2C_Master_Receive(&hi2c1, addressRead, buffer, 1, 1000);
		rollReading = buffer[0]<<8;		
		buffer[0] = 0x46;
		error = HAL_I2C_Master_Transmit(&hi2c1, addressRead, buffer, 1, 1000); 
		error = HAL_I2C_Master_Receive(&hi2c1, addressRead, buffer, 1, 1000);
		rollReading |= buffer[0];
		rollReading -= 1;
		rollReading = ~rollReading;
		
		buffer[0] = 0x47;
		error = HAL_I2C_Master_Transmit(&hi2c1, addressRead, buffer, 1, 1000); 
		error = HAL_I2C_Master_Receive(&hi2c1, addressRead, buffer, 1, 1000);
		yawReading = buffer[0]<<8;		
		buffer[0] = 0x48;
		error = HAL_I2C_Master_Transmit(&hi2c1, addressRead, buffer, 1, 1000); 
		error = HAL_I2C_Master_Receive(&hi2c1, addressRead, buffer, 1, 1000);
		yawReading |= buffer[0];		
		yawReading -= 1;
		yawReading = ~yawReading;
		
	*/	
		
