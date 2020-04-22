/**
*
* In this project we set up a I2C master device with
* to understand the I2C protocol and communicate with a
* a I2C Slave device (LIS3DH Accelerometer).
*
* we have to use the accelerometer in High resolution mode  
* in order to acquire the data relating to the acceleration in 
* the three directions. Then we visualize values with
* Bridge Control Panel
*
* For the comunication we use a baud rate of 19200 because
* we have to sample with a frequency of 100Hz, so we have 
* 100 sample per second; we have to send to the 
* UART an array with size of 14. So 8*14*100=11200 that is higher
* than 9600, so we use 19200
*/

// Include required header files
#include "I2C_Interface.h"
#include "project.h"
#include "stdio.h"
#include "math.h"
#include "Defines.h"


int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    I2C_Peripheral_Start();
    UART_Debug_Start();
    
    CyDelay(5); //"The boot procedure is complete about 5 milliseconds after device power-up."
    
    // String to print out messages on the UART
    char message[50];

    // Check which devices are present on the I2C bus
    for (int i = 0 ; i < 128; i++)
    {
        if (I2C_Peripheral_IsDeviceConnected(i))
        {
            // print out the address is hex format
            sprintf(message, "Device 0x%02X is connected\r\n", i);
            UART_Debug_PutString(message); 
        }
        
    }
    
    /******************************************/
    /*            I2C Reading                 */
    /******************************************/
    
    /* Read WHO AM I REGISTER register */
    uint8_t who_am_i_reg;
    ErrorCode error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS,
                                                  LIS3DH_WHO_AM_I_REG_ADDR, 
                                                  &who_am_i_reg);
    if (error == NO_ERROR)
    {
        sprintf(message, "WHO AM I REG: 0x%02X [Expected: 0x33]\r\n", who_am_i_reg);
        UART_Debug_PutString(message); 
    }
    else
    {
        UART_Debug_PutString("Error occurred during I2C comm\r\n");   
    }
    
    /*      I2C Reading Status Register       */
    
    uint8_t status_register; 
    error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS,
                                        LIS3DH_STATUS_REG,
                                        &status_register);
    
    if (error == NO_ERROR)
    {
        sprintf(message, "STATUS REGISTER: 0x%02X\r\n", status_register);
        UART_Debug_PutString(message); 
    }
    else
    {
        UART_Debug_PutString("Error occurred during I2C comm to read status register\r\n");   
    }
     
    /******************************************/
    /*        Read Control Register 1         */
    /******************************************/
    uint8_t ctrl_reg1; 
    error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS,
                                        LIS3DH_CTRL_REG1,
                                        &ctrl_reg1);
    
    if (error == NO_ERROR)
    {
        sprintf(message, "CONTROL REGISTER 1: 0x%02X\r\n", ctrl_reg1);
        UART_Debug_PutString(message); 
    }
    else
    {
        UART_Debug_PutString("Error occurred during I2C comm to read control register 1\r\n");   
    }
    
    /******************************************/
    /*            I2C Writing                 */
    /******************************************/
    
        
    UART_Debug_PutString("\r\nWriting new values..\r\n");
    
    if (ctrl_reg1 != LIS3DH_NORMAL_MODE_CTRL_REG1)//LP a 0
    {
        ctrl_reg1 = LIS3DH_NORMAL_MODE_CTRL_REG1;
    
        error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                                             LIS3DH_CTRL_REG1,
                                             ctrl_reg1);
    
        if (error == NO_ERROR)
        {
            sprintf(message, "CONTROL REGISTER 1 successfully written as: 0x%02X\r\n", ctrl_reg1);
            UART_Debug_PutString(message); 
        }
        else
        {
            UART_Debug_PutString("Error occurred during I2C comm to set control register 1\r\n");   
        }
    }
    
    /******************************************/
    /*     Read Control Register 1 again      */
    /******************************************/

    error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS,
                                        LIS3DH_CTRL_REG1,
                                        &ctrl_reg1);
    
    if (error == NO_ERROR)
    {
        sprintf(message, "CONTROL REGISTER 1 after overwrite operation: 0x%02X\r\n", ctrl_reg1);
        UART_Debug_PutString(message); 
    }
    else
    {
        UART_Debug_PutString("Error occurred during I2C comm to read control register 1\r\n");   
    }
    
        /******************************************/
    /*     Read Control Register 4    */
    /******************************************/
    
    uint8_t ctrl_reg4;

    error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS,
                                        LIS3DH_CTRL_REG4,
                                        &ctrl_reg4);
    
    if (error == NO_ERROR)
    {
        sprintf(message, "CONTROL REGISTER 4: 0x%02X\r\n", ctrl_reg4);
        UART_Debug_PutString(message); 
    }
    else
    {
        UART_Debug_PutString("Error occurred during I2C comm to read control register4\r\n");   
    }
    
    
    ctrl_reg4 = LIS3DH_CTRL_REG4_BDU_ACTIVE; // must be changed to the appropriate value, bit HR 0
    
    error = I2C_Peripheral_WriteRegister(LIS3DH_DEVICE_ADDRESS,
                                         LIS3DH_CTRL_REG4,
                                         ctrl_reg4);
    
    error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS,
                                        LIS3DH_CTRL_REG4,
                                        &ctrl_reg4);
    
    
    if (error == NO_ERROR)
    {
        sprintf(message, "CONTROL REGISTER 4 after being updated: 0x%02X\r\n", ctrl_reg4);
        UART_Debug_PutString(message); 
    }
    else
    {
        UART_Debug_PutString("Error occurred during I2C comm to read control register4\r\n");   
    }
    
     
    
    int16_t OutX;//used to merge the two uint8_t value from the array XYZData relative to the x direction
    int16_t OutY;//used to merge the two uint8_t value from the array XYZData relative to the y direction
    int16_t OutZ;//used to merge the two uint8_t value from the array XYZData relative to the z direction
    float32 OutXfloat;//used to save data of x acceleration with decimals
    float32 OutYfloat;//used to save data of y acceleration with decimals
    float32 OutZfloat;//used to save data of z acceleration with decimals
    uint8_t header = 0xA0;//header for UART comunication
    uint8_t footer = 0xC0;//header for UART comunication 
    uint8_t XYZData[6];//Array used to read data
    uint8_t register_count=5;//it is 5--> we need to read six value, from *(data) to  *(data+5)
    uint8_t OutArrayFloat[14];//array to be sent through UART

    OutArrayFloat[0] = header;
    OutArrayFloat[13] = footer;
    
    uint8_t accx[sizeof(float)];//useful to send float as uint8_t
    uint8_t accy[sizeof(float)];//useful to send float as uint8_t
    uint8_t accz[sizeof(float)];//useful to send float as uint8_t
    
    for(;;)
    {
        //verify new Data is available using StatusReg information
        error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS,
                                        LIS3DH_STATUS_REG,
                                        &status_register);
        
        // only if there are new Data  available, we comunicate with the UART
        if(status_register & (1<<LIS3DH_STATUS_REG_ACTIVE_ZYXDA))
        {
            
            //Use of multi-read function to read 6 consequent registers starting from OUT_X_L
            error = I2C_Peripheral_ReadRegisterMulti(LIS3DH_DEVICE_ADDRESS,
                                            LIS3DH_OUT_X_L,
                                            register_count,
                                            &XYZData[0]);
           
            if(error == NO_ERROR)
            {

                OutX = (int16)((XYZData[0] | (XYZData[1]<<8)))>>4;//merge data into a single int16 variable
                
                OutXfloat=(float32)OutX;//cast float
                
                OutXfloat=(OutXfloat*9.81)/1024;//conversion in m/s^2
                
                OutXfloat=roundf(OutXfloat*1000);//save three decimals
                
                
                
                
                OutY = (int16)((XYZData[2] | (XYZData[3]<<8)))>>4;//merge data into a single int16 variable
                
                OutYfloat=(float32)OutY;//cast float
                
                OutYfloat=(OutYfloat*9.81)/1024;//conversion in m/s^2
                 
                OutYfloat=roundf(OutYfloat*1000);//save three decimals
                
                
                
                OutZ = (int16)((XYZData[4] | (XYZData[5]<<8)))>>4;//merge data into a single int16 variable
                
                OutZfloat=(float32)OutZ;//cast float
       
                OutZfloat=(OutZfloat*9.81)/1024;//conversion in m/s^2
                
                OutZfloat=roundf(OutZfloat*1000);//save three decimals
                
                 
                
                *(float*)(accx)=OutXfloat;//save the float into the uint8_t through the pointer
                *(float*)(accy)=OutYfloat;//save the float into the uint8_t through the pointer
                *(float*)(accz)=OutZfloat;//save the float into the uint8_t through the pointer
                

                OutArrayFloat[1] = accx[0]  ;//copy of the LSB of the acc in the x direction into the position 1 of the array
                OutArrayFloat[2] = accx[1] ;
                OutArrayFloat[3] = accx[2] ;
                OutArrayFloat[4] = accx[3] ;//copy of the MSB of the acc in the x direction into the position 4 of the array
                OutArrayFloat[5] = accy[0] ;//copy of the LSB of the acc in the y direction into the position 5 of the array
                OutArrayFloat[6] = accy[1] ;
                OutArrayFloat[7] = accy[2] ;
                OutArrayFloat[8] = accy[3] ;//copy of the MSB of the acc in the y direction into the position 8 of the array
                OutArrayFloat[9] = accz[0] ;//copy of the LSB of the acc in the z direction into the position 9 of the array
                OutArrayFloat[10] =accz[1] ;
                OutArrayFloat[11] =accz[2] ;
                OutArrayFloat[12] =accz[3] ;//copy of the MSB of the acc in the z direction into the position 12 of the array
                UART_Debug_PutArray(OutArrayFloat, 14);
                
                /**************************************
                *Useful function to read with CoolTerm
                ****************************************/
                /*
                int bytesWritten;     
                char myString[50];     
                bytesWritten = sprintf(myString, "%d", accx);     
                UART_Debug_PutString(myString);    
                UART_Debug_PutString("\r\n");  
                bytesWritten = sprintf(myString, "%d", accy);     
                UART_Debug_PutString(myString);    
                UART_Debug_PutString("\r\n"); 
                bytesWritten = sprintf(myString, "%d", accz);     
                UART_Debug_PutString(myString);    
                UART_Debug_PutString("\r\n");*/
            }
        }
    }
}

/* 
*   \Author: Quaranta Mattia
*/

