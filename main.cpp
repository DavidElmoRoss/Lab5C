/*    
Title:  Program to display temperature on PC Screen from Grove Temp Sensor    
Author: YOUR NAME HERE    
Date:   Today’s DATE here    
Description:    This program assumes that the Grove Temperature Module
                has been connected to Connector A0 of the Grove Shield V2.                    
             It will constantly update the Temperature on the PC screen 
                in both Celsius and Fahrenheit.
*/
//Function Prototypes
void clear(void);           // clears the PC screen
void position(int x, int y);        // positions screen cursor at (x,y)

// INCLUDE SECTION
#include "mbed.h"                   // include the mbed.h library
#include "Grove_LCD_RGB_Backlight.h"

// Hardware Definitions
AnalogIn input1(A0);                // set Analog input1 to A0                                     
                                    // (A1 is not connected)
Grove_LCD_RGB_Backlight display(D14,D15);

// Global Variables and Constants
const int B=4250;                   // B constant for Thermistor                                    
                                    // in Temp Sensor V1.2
const int MAX=17;
volatile double temperature,fahren;        // output temperature
volatile unsigned int voltage;      // voltage  from Grove Temperature Sensor
volatile double voltage1;

int main(void)
{
    char buffer[MAX];
    volatile double R;                  // variable used to compute temperature
    clear();                            // clear the screen
    position(11,36);                    // positions curson at (11,36)
    printf("Temperature");              // print title Temperature 
    sprintf(buffer,"Temperature");
    display.locate(2,0);
    display.setRGB(0x00,0x00,0xff);
    display.print(buffer);
    
    while(1)                            // loop forever
    {
       wait_ms(500);                    // wait 0.5 seconds
       voltage=input1.read_u16();       //  gets 16-bit raw A/D value
       R=65536.0/((double)voltage)-1.0; 
                                        // temperature conv based on data sheet
       temperature=1.0/(log(R)/B+1/298.15)-273.15; 
       position(12,34);    
       printf("%5.1f",temperature);     // output temperature value on screen
       putchar(0xf8);                   // change Putty Translation to CP437
                                        // output Celsius and Fahrenheit temps
       fahren=(9.0/5.0)*temperature+32;
       printf("C %5.1f",fahren);
       putchar(0xf8);                   // change Putty Translation to CP437
       printf("F");
       fflush(stdin);
       display.locate(0,1);
       sprintf(buffer,"%5.1f%cC  %5.1f%cF",temperature,0xdf,fahren,0xdf);
       display.print(buffer);
       
    }
}
void clear(void)
{
    printf("\e[2J");
    fflush(stdout);   
}
void position(int x, int y)
{
    printf("\e[%d;%dH",x,y);
    fflush(stdout);
}