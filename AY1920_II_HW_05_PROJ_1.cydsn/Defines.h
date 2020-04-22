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
    *   \brief Address of the Control register 1
    */
    #define LIS3DH_CTRL_REG1 0x20

    /**
    *   \brief Hex value to set normal mode to the accelerator
    */
    #define LIS3DH_NORMAL_MODE_CTRL_REG1 0x47

    /**
    *   \brief  Address of the Temperature Sensor Configuration register
    */
    #define LIS3DH_TEMP_CFG_REG 0x1F

    #define LIS3DH_TEMP_CFG_REG_ACTIVE 0xC0

    /**
    *   \brief Address of the Control register 4
    */
    #define LIS3DH_CTRL_REG4 0x23

    #define LIS3DH_CTRL_REG4_BDU_ACTIVE 0x80

    /**
    *   \brief Address of the ADC output LSB register
    */
    #define LIS3DH_OUT_ADC_3L 0x0C

    /**
    *   \brief Address of the ADC output MSB register
    */
    #define LIS3DH_OUT_ADC_3H 0x0D
    
#endif

/* [] END OF FILE */
