#include <iostream>
//#include <stdio.h>
#include <fstream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>

#define i2c_addr 0x20 // lcd display memory address
#define LCD_CHR 1 // Mode - Sending data
#define LCD_CMD 0 // Mode - Sending command
#define LINE1 0x80 // memory address of first line
#define LINE2 0xC0 // memory address of second line
#define LCD_BACKLIGHT 0x08 // on
// LCD_BACKLIGHT + 0x00 # Off
#define ENABLE 0b00000100 // enable bit
int fd; // global fileDescriptor


void lcd_init(void);
void lcd_byte(int bits, int mode);
void lcd_toggle_enable(int bits);
  
void typeln(const char *S);

int file_i2c;
int length;
uint8_t buffer[3] = {0};

int timingLoopFreq = 500;
int timingLoopMicroSeconds = 1000000 / timingLoopFreq;
uint8_t base_addr = 0x20;

using namespace std;

int main(int argc, char **argv)
{
    printf("Hello World!\n");

    char *filename = (char*)"/dev/i2c-1";
    if((file_i2c = open(filename, O_RDWR))< 0){
         // ERROR handling_ you can check errno to see what went wrong;
        cout << "failed to open the i2c bus" << endl;
	return 0;
    }


while (1){
    if(ioctl(file_i2c, I2C_SLAVE, base_addr) < 0){
	cout << "Failed to aquire bus access and/or talk to slave" << endl;
    }



    uint8_t reg = 0x00;
    uint8_t byte1 = 0x00;
    uint8_t byte2 = 0x00;
    // turn display on
    byte1 = 0x00;
    byte2=0x00;
    length = 3; // expected length?

    buffer[0] = reg;
    buffer[1] = byte1;
    buffer[2] = byte2;
    if(write(file_i2c, buffer, length) != length){
	cout << "failed to write to i2c bus" << endl; 
    }

   // write data?
   reg = 0x02;
   byte1 = 0x65;
   byte2 = 0x65;

   buffer[0] = reg;
   buffer[1] = byte1;
   buffer[2] = byte2;
   if(write(file_i2c, buffer, length) != length){
       cout << "failed to write data to i2c bus" << endl;
   }
   






/*

    // ------ write bytes to display ------
    buffer [0] = 4;
    buffer [1] = 0;
    length = 2;
    if (write(file_i2c, buffer, length) != length ){
        cout << "failed to write to the i2c bus" << endl;
    } else {
        length = 1;
	if(read(file_i2c, buffer, length) != length){
	    cout << "failed to read from the i2c bus" << endl;
	} else  {
	cout << "Data read:" << buffer[0] << endl;
	}
    }
*/
}

    return 0;
}


void lcd_byte(int bits, int mode){
  // Send byte to data pins
  // bits = the data
  // mode = 1 for data, 0 for command
  int bits_high;
  int bits_low;
  // uses two half byte writes to lcd
  bits_high = mode | (bits & 0xF0) | LCD_BACKLIGHT ;
  bits_low = mode | ((bits << 4) & 0xF0) | LCD_BACKLIGHT ;

  // high bits
  wiringPiI2CReadReg8(fd, bits_high);
  lcd_toggle_enable(bits_high);

  //low bits
  wiringPiI2CReadReg8(fd, bits_low);
  lcd_toggle_enable(bits_low);
}

void lcd_init() {
  // initialise display
  
}
