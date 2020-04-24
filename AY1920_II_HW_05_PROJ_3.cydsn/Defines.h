/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#ifndef Defines_H
    #define Defines_H
   
    /**
    *   \brief 7-bit I2C address of the slave device.
    */
    #define LIS3DH_DEVICE_ADDRESS 0x18

    /**
    *   \brief Address of the WHO AM I register
    */
    #define LIS3DH_WHO_AM_I_REG_ADDR 0x0F

    /**
    *   \brief Address of the Status register
    */
    #define LIS3DH_STATUS_REG 0x27
        
    /**
    *   \brief Address of the Status register to control the presence of new data
    */

    #define LIS3DH_STATUS_REG_ACTIVE_ZYXDA 0x03 

    /**
    *   \brief Address of the Control register 1
    */
    #define LIS3DH_CTRL_REG1 0x20

    /**
    *   \brief Hex value to set the frequency of the accelerator in high resolution mode (the high-resolution mode 
    *   is set by leaving low the bit Lpen in the CTRL_REG1 and high the bit HR in the CTRL_REG4)
    */
    #define LIS3DH_NORMAL_MODE_CTRL_REG1 0x57

    /**
    *   \brief  Address of the Temperature Sensor Configuration register
    */
    #define LIS3DH_TEMP_CFG_REG 0x1F

    #define LIS3DH_TEMP_CFG_REG_ACTIVE 0xC0

    /**
    *   \brief Address of the Control register 4
    */
    #define LIS3DH_CTRL_REG4 0x23
    //the HR bit is high for the high resolution mode, and also the FS0 must be high for a FSR of +-4
    #define LIS3DH_CTRL_REG4_BDU_ACTIVE 0x98 

    /**
    *   \brief Address of the ADC output LSB register
    */
    #define LIS3DH_OUT_ADC_3L 0x0C

    /**
    *   \brief Address of the ADC output MSB register
    */
    #define LIS3DH_OUT_ADC_3H 0x0D

    /**
    *   \brief Address of the accelerometer registers
    */
    #define LIS3DH_OUT_X_L 0x28
    #define LIS3DH_OUT_X_H 0x29
    #define LIS3DH_OUT_Y_L 0x2A
    #define LIS3DH_OUT_Y_H 0x2B
    #define LIS3DH_OUT_Z_L 0x2C
    #define LIS3DH_OUT_Z_H 0x2D

    /*
    *   \brief Constant of gravitational acceleration
    */
    #define CONSTANT_G 9.807

    /*
    *   \brief Conversion 1g=512
    */
    #define DATA_RANGE 512    
        
#endif

/* [] END OF FILE */
