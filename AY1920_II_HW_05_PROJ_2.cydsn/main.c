/**
*
* In this project we set up a I2C master device with
* to understand the I2C protocol and communicate with a
* a I2C Slave device (LIS3DH Accelerometer).
*
* we have to use the accelerometer in Normal mode  
* in order to acquire the data relating to the acceleration in 
* the three directions. Then we visualize values with
* Bridge Control Panel
*
* For the comunication we use a baud rate of 9600 because
* we have to sample with a frequency of 100Hz, so we have 
* 100 sample per second; we have to send to the 
* UART an array with size of 8. So 8*8*100=6400 that is lower
* than 9600
*/

// Include required header files
#include "I2C_Interface.h"
#include "project.h"
#include "stdio.h"
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
        /**
        *   \brief Hex value to set the frequency of the accelerator in normal mode (the normal mode 
        *   is set by leaving low the bit Lpen in the CTRL_REG1 and low the bit HR in the CTRL_REG4)
        */
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
    
    
    ctrl_reg4 = LIS3DH_CTRL_REG4_BDU_ACTIVE; // must be changed to the appropriate value
    
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
    uint8_t header = 0xA0;//header for UART comunication
    uint8_t footer = 0xC0;//footer for UART comunication
    uint8_t OutArray[8]; //array to be sent through UART
    uint8_t XYZData[10];//Array used to read data
    uint8_t register_count=5;//it is 5--> we need to read six value, from *(data) to  *(data+5)

    OutArray[0] = header;
    OutArray[7] = footer;
    
    for(;;)
    {
        //verify new Data is available using StatusReg information
        error = I2C_Peripheral_ReadRegister(LIS3DH_DEVICE_ADDRESS,
                                        LIS3DH_STATUS_REG,
                                        &status_register);
        
        // only if there are new Data  available, we comunicate with the UART. In addition in this way we obtain 
        //a sample rate in the bridge control panel of 100 samples per sec
        if(status_register & (1<<LIS3DH_STATUS_REG_ACTIVE_ZYXDA))
        {
            //Use of multi-read function to read 6 consequent registers starting from OUT_X_L
            error = I2C_Peripheral_ReadRegisterMulti(LIS3DH_DEVICE_ADDRESS,
                                            LIS3DH_OUT_X_L,
                                            register_count,
                                            &XYZData[0]);
           
            if(error == NO_ERROR)
            {

                OutX = (int16)((XYZData[0] | (XYZData[1]<<8)))>>6;//merge data into a single int16 variable
                OutY = (int16)((XYZData[2] | (XYZData[3]<<8)))>>6;//merge data into a single int16 variable
                OutZ = (int16)((XYZData[4] | (XYZData[5]<<8)))>>6;//merge data into a single int16 variable
                
                //From the Datasheet we can read that in the normal mode we have a correspondece of 4 mg/digit
                OutX=(OutX*CONVERSION_CONSTANT_mg)/DATA_RANGE;//Conversion into mg
                OutY=(OutY*CONVERSION_CONSTANT_mg)/DATA_RANGE;//Conversion into mg
                OutZ=(OutZ*CONVERSION_CONSTANT_mg)/DATA_RANGE;//Conversion into mg
               
                OutArray[1] = (uint8_t)(OutX & 0xFF);//copy of the LSB of x into the position 1 of the array
                OutArray[2] = (uint8_t)(OutX >> 8);//copy of the MSB of x into the position 2 of the array
                OutArray[3] = (uint8_t)(OutY & 0xFF);//copy of the LSB of y into the position 3 of the array
                OutArray[4] = (uint8_t)(OutY >> 8);//copy of the MSB of y into the position 4 of the array
                OutArray[5] = (uint8_t)(OutZ & 0xFF);//copy of the LSB of z into the position 5 of the array
                OutArray[6] = (uint8_t)(OutZ >> 8);//copy of the MSB of z into the position 6 of the array
                UART_Debug_PutArray(OutArray, 8);//UART comunication
            }
        }
    }
}

/* 
*   \Author: Quaranta Mattia
*/
