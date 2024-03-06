/**
 * FILENAME :        JoyCar.h          
 *
 * DESCRIPTION :
 *       JoyCar platform control (from Joy-It) classes
 *
 *       JoyCar
 *
 * NOTES :
 *       Developped by Villou / LEnsE
 **
 * AUTHOR :    Julien VILLEMEJANE        START DATE :    19/jan/2024
 *
 *       LEnsE / Institut d'Optique Graduate School
 *          http://lense.institutoptique.fr/
 */

#ifndef     __JOYCAR_H__
#define     __JOYCAR_H__

#include "mbed.h"
#include "WS2812.h"

/** Constant definition */
#define     DEBUG_JOYCAR    true
// Frequency of the I2C communication port - PWM control and GPIO Expander
#define JOYCAR_I2C_FREQ   400000

// I2C Address of the GPIO Expander - PF574A
#define JOYCAR_GPIOE_ADD    0x38 

// I2C Address of the PWM Driver - PCA9633
#define JOYCAR_MOTOR_ADD            0x70 
#define JOYCAR_MOTOR_RESET_ADD      0x03 
// I2C Reg Address of the PWM Driver - PCA9633
#define JOYCAR_MOTOR_PWM0_REG    0x02 
#define JOYCAR_MOTOR_PWM1_REG    0x03 
#define JOYCAR_MOTOR_PWM2_REG    0x04 
#define JOYCAR_MOTOR_PWM3_REG    0x05 
#define JOYCAR_MOTOR_MODE0_REG   0x00 
#define JOYCAR_MOTOR_MODE1_REG   0x01 
#define JOYCAR_MOTOR_LEDOUT_REG  0x08

// Headlights
#define NB_LEDS_PER_HEADLIGHTS  2
#define NB_OF_HEADLIGHTS        4
#define NB_OF_LEDS              NB_LEDS_PER_HEADLIGHTS * NB_OF_HEADLIGHTS


/**
 * @class JoyCar_Motor
 * @brief PWM control of the two motors through a PCA9633 PWM driver
 * @details     The two independent DC motors of the platform are driven by
 *          a PCA9633 PWM driver.
 *  Communication is through an I2C protocol at 400kHz.
 */

class JoyCar_Motor {
    private:
        /// I2C interface 
        I2C *__i2c;
    
    public:
        /**
        * @brief Simple constructor of the JoyCar_Motor class.
        * @details Create a JoyCar_Motor object with
        *    an I2C interface
        *    I2C communication will be initialized at 400kHz
        * @param _i2c SPI interface not initialized
        */
        JoyCar_Motor(I2C *_i2c);

        /**
        * @brief Send dutycycle to a specific PWM channel
        * @param ch PWM channel reg address of the PCA9633 - integer from 0 to 3
        * @param value Dutycycle value - integer from 0 to 255
        * @return true if acknowledgement from PCA9633 is OK
        */
        bool sendSpeed(uint8_t ch_add, char val);
        
        /**
        * @brief Reset the PWM controller with specific I2C reset address
        * @return true if acknowledgement from PCA9633 is OK
        */
        bool hardResetPWM();
        /**
        * @brief Initialize the PWM controller PCA9633
        * @return true if acknowledgement from PCA9633 is OK
        */
        bool initPWMController();

        /**
        * @brief Send command to go forward at 2 different speeds 
        *       for right and left
        * @param speedR relative speed of the right motor - integer from 0 to 100 
        * @param speedL relative speed of the left motor - integer from 0 to 100 
        * @return true if acknowledgement from PCA9633 is OK
        */
        bool goForward(uint8_t speedR, uint8_t speedL);

        /**
        * @brief Send command to go reverse at 2 different speeds 
        *       for right and left
        * @param speedR relative speed of the right motor - integer from 0 to 100 
        * @param speedL relative speed of the left motor - integer from 0 to 100 
        * @return true if acknowledgement from PCA9633 is OK
        */
        bool goReverse(uint8_t speedR, uint8_t speedL);

        /**
        * @brief Send command to stop the motor softly
        * @return true if acknowledgement from PCA9633 is OK
        */
        bool stopSoft(void);

};


class JoyCar_ServoDist {
    private:
        /// PWM output for controlling servomotor
        PwmOut  __servo;
    
    public:
    /**
        * @brief Simple constructor of the JoyCar_ServoDist class.
        * @details Create a JoyCar_ServoDist object with
        *    a PWM output to control the speed rotation 
        *    of the continuous servomotor
        *    a US sensor communication
        * @param _servPWM pin of the servomotor control
        */
        JoyCar_ServoDist(PinName _servPWM);

        /**
        * @brief Initialize the servomotor
        */
        void initServo();

};

class JoyCar_HeadLights{
    private:
        /// Data input of the first LED
        DigitalOut  __led_in;
        /// LED Strips object
        WS2812      __my_strip;
        /// pixels colors of each headlights
        int _array[NB_OF_LEDS];
        /**
        * @brief Convert a RGB values to a WS2812 compatible integer 
        * @param r red color - integer from 0 to 255
        * @param g green color - integer from 0 to 255
        * @param b blue color - integer from 0 to 255
        */
        int convertPixel(uint8_t r, uint8_t g, uint8_t b);
    
    public:
        /**
        * @brief Simple constructor of the JoyCar_HeadLights class.
        * @details Create a JoyCar_HeadLights object with
        *    a digital ouput connected to the first WS2812 LED data input
        * @param _leds pin of the first WS2812 LED data input
        */
        JoyCar_HeadLights(PinName _leds);

        /**
        * @brief Set a specific RGB color to all the lights.
        * @param R red color - integer from 0 to 255
        * @param G green color - integer from 0 to 255
        * @param B blue color - integer from 0 to 255
        */
        void setAllLights(uint8_t R, uint8_t G, uint8_t B);

};

#endif