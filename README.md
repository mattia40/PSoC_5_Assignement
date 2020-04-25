# PSoC_5_Assignement
# This repository contains three projects created with PSoC creator related to the use of I2C and UART comunication with a breakout 
#containing an accelerometer and a thermometer. There are also, for each project, files.ini and .iic to display data using Bridge Control 
# Panel. 

# Utility:
# - LIS3DH 3-Axis Accelerometer breakout board
# - https://cdn-learn.adafruit.com/downloads/pdf/adafruit-lis3dh-triple-axis-accelerometer-breakout.pdf
# - https://www.st.com/resource/en/datasheet/lis3dh.pdf

# Project 1:
# The aim of this project is implementing multiread and multiwrite function, and use them to read the value of temperature. Through the
# multiread we can access to the value of the two consecutive register ADC3_L and ADC3_H. This is the an additional ADC, within the 3 
# possible on the breakout.
# We are using a baud rate of 9600  

# Project 2:
# In this project we set up a I2C master device with to understand the I2C protocol and communicate with a I2C Slave device (LIS3DH 
# Accelerometer).
# We have to use the accelerometer in Normal mode (so bit Lpen in the ctrl_reg1 and HR in the ctrl_reg4 must be low) in order to acquire 
# the data relating to the acceleration in  the three directions. Then we visualize values with Bridge Control Panel
# For the comunication we use a baud rate of 9600 because we have to sample with a frequency of 100Hz, so we have 100 sample per second;
# we have to send to the UART an array with size of 8. So 8x8x100=6400 that is lower than 9600
# Only if there are new Data  available, we comunicate with the UART--> to do that we have to read the status register. We are able to read
# values with a constant sample rate of 100 samples per seconds. This is possible using an if control on the status register before sending
# values through the UART 

# Project 3:
# In this project we set up a I2C master device with to understand the I2C protocol and communicate with a I2C Slave device (LIS3DH 
# Accelerometer).
# We have to use the accelerometer in High resolution mode (so bit Lpen in the ctrl_reg1 must be low and HR in the ctrl_reg4 must be 
# high) in order to acquire the data relating to the acceleration in  the three directions. Then we visualize values with Bridge Control
#Panel
#For the comunication we use a baud rate of 19200 because we have to sample with a frequency of 100Hz, so we have 100 sample per second;
# we have to send to the UART an array with size of 8. So 8x14x100=11200 that is higher than 9600
# We have to set the FS0 high in the CTRL_REG4 for a FSR of +-4
# In this case we want to read a float value without loosing info: so we can multiply by 1000 and then, with a scale of 0.001 in the
# bridge control panel, we can read 3 decimals. But there is another faster way to send directly float values like in the following 
# implementation (using float pointer).
# Only if there are new Data  available, we comunicate with the UART--> to do that we have to read the status register. We are able to
# read values with a constant sample rate of 100 samples per seconds. This is possible using an if control on the status register before
# sending values through the UART 

