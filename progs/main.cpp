/**
 * FILENAME :        main.cpp          
 *
 * DESCRIPTION :
 *       Testing Joy-It Car Control system based on Nucleo Board
 *
 * NOTES :
 *       Developped by Villou / LEnsE
 **
 * AUTHOR :    Julien VILLEMEJANE        START DATE :    15/jan/2024
 *
 *       LEnsE / Institut d'Optique Graduate School
 *          http://lense.institutoptique.fr/
 */

#include "mbed.h"
#include "JoyCar.h"


/// JoyCar inputs/outputs declaration - based on Joy-It Car platform
/// I2C interface
I2C  my_i2c(D14, D15);

/// Motor driver
JoyCar_Motor    my_motor(&my_i2c);
/// Headlights
JoyCar_HeadLights my_lights(D8);

/*
/// Distance sensor mounted on a servomotor
JoyCar_ServoDist my_dist(D6);

Ticker controlLoopTik;
*/

/* Methods */
/**
 * Interrupt routine attached to the sampling of the Contol Loop System
 *
 * @return Updates the system control loop outputs
 */
void ISR_controlLoopTik(void);

/// Internal boolean print function
void printbool(bool v, char* name);

/* Main code */
int main()
{
    char cmd[2];

    /// PWM Driver init
    printbool(my_motor.hardResetPWM(), "Hard Reset");
    wait_us(100);
    printbool(my_motor.initPWMController(), "Init Motor");

    /*
    /// Distance Servomotor
    //my_dist.initServo();
    // controlLoopTik.attach(&ISR_controlLoopTik, 100us);
    */
    /// Headlights
    printf("LEDs OK...\r\n");
    my_lights.setAllLights(100, 0, 50);

    while (true){
        printbool(my_motor.goForward(100, 100), "Go Forward");  
        my_lights.setAllLights(0, 0, 50);
        wait_us(1000000);
        printbool(my_motor.stopSoft(), "Stop");  
        my_lights.setAllLights(100, 0, 0);
        wait_us(1000000);
    }
}


/* */
void ISR_controlLoopTik(void){


}



/// Internal boolean print function
void printbool(bool v, char* name){
    if(v == true)
        printf("%s = True \r\n", name);
    else
        printf("%s = False \r\n", name);
    
}