#include <avr/pgmspace.h>
#include "font.h"

#define CLOCKDELAY 100
#define MAXCHIPS 3 //change this variable to set how many MAX7219's you'll use


int dataIn = 2;
int load = 3;
int clock = 4;

int e = 0;
int count = 0;

String text = "";   //text to display
int length = 0;    //length of the text

//framebuffer initialization
char framebuffer[MAXCHIPS+1][8] = { { 0 } };


// define max7219 registers
byte max7219_reg_noop        = 0x00;
byte max7219_reg_digit0      = 0x01;
byte max7219_reg_digit1      = 0x02;
byte max7219_reg_digit2      = 0x03;
byte max7219_reg_digit3      = 0x04;
byte max7219_reg_digit4      = 0x05;
byte max7219_reg_digit5      = 0x06;
byte max7219_reg_digit6      = 0x07;
byte max7219_reg_digit7      = 0x08;
byte max7219_reg_decodeMode  = 0x09;
byte max7219_reg_intensity   = 0x0a;
byte max7219_reg_scanLimit   = 0x0b;
byte max7219_reg_shutdown    = 0x0c;
byte max7219_reg_displayTest = 0x0f;

void putByte(byte data) {
    byte i = 8;
    byte mask;
    while(i > 0) {
        mask = 0x01 << (i - 1);      // get bitmask
        digitalWrite( clock, LOW);   // tick
        if (data & mask){            // choose bit
            digitalWrite(dataIn, HIGH);// send 1
        }
        else{
            digitalWrite(dataIn, LOW); // send 0
        }
        // delayMicroseconds(CLOCKDELAY);
        //the max7219 wants a clock delay of 50ns. digitalWrite isn't anywhere near that fast, so don't worry about it
        digitalWrite(clock, HIGH);   // tock
        // delayMicroseconds(CLOCKDELAY);
        i--;                         // move to lesser bit
    }
}

void maxSingle(byte reg, byte col) {
    digitalWrite(load, LOW);       // begin
    putByte(reg);                  // specify register
    putByte(col);//((data & 0x01) * 256) + data >> 1); // put data
    digitalWrite(load, LOW);       // and load
    digitalWrite(load, HIGH);
}

void maxAll(byte reg, byte col) {    // initialize  all  MAX7219's in the system
    int c = 0;
    digitalWrite(load, LOW);  // begin
    for ( c = 1; c <= MAXCHIPS; c++) {
        putByte(reg);  // specify register
        putByte(col);//((data & 0x01) * 256) + data >> 1); // put data
    }
    digitalWrite(load, LOW);
    digitalWrite(load, HIGH);
}

void maxOne(byte maxNr, byte reg, byte col) {
    //maxOne is for adressing different MAX7219's,
    //while having a couple of them cascaded
    //this is really inefficient, especially with a framebuffer

    int c = 0;
    digitalWrite(load, LOW);  // begin

    for ( c = MAXCHIPS; c > maxNr; c--) {
        putByte(0);    // means no operation
        putByte(0);    // means no operation
    }

    putByte(reg);  // specify register
    putByte(col);//((data & 0x01) * 256) + data >> 1); // put data

    for ( c = maxNr-1; c >= 1; c--) {
        putByte(0);    // means no operation
        putByte(0);    // means no operation
    }

    digitalWrite(load, LOW); // and load
    digitalWrite(load, HIGH);
}

void updateDisplay(){
    for(byte j = 0; j < 7; j++){
        // digitalWrite(load, LOW);  // begin
        // delayMicroseconds(1);
        for(int i = MAXCHIPS; i > 0; i--){
            // putByte(j+1);
            // putByte(framebuffer[i-1][j]);
            maxOne(i, j+1, framebuffer[i-1][j]);
        }
        // digitalWrite(load, LOW); // and load
        // digitalWrite(load, HIGH);
    }

}

void writechar(char in, int seg){
    for(int i=0; i<7; i++){
        framebuffer[seg][i] = pgm_read_byte_near( &(font[in][i]) );
        //maxOne(seg,i+1,font[in][i]);
    }
}

void shiftLeft(){
    for(int j = 0; j < 7; j++){
        framebuffer[0][j] /= 2; // move the whole first segment one left, discard extra value

        //loop through remaining segments
        for(int i = 1; i <= MAXCHIPS; i++){

            //if the LSB of the segment is set, set the 'MSB' (0x10) of the segment to the left 
            if((framebuffer[i][j]) & 0x1){ //is odd
                framebuffer[i-1][j] += 0x10;
            }
            framebuffer[i][j] /= 2;
        }
    }
}

void invertFrame(int seg){
    for(int i=0;i<7;i++){
        framebuffer[seg][i] = (~framebuffer[seg][i] & 0x3f); //
    }
}

void clearFrame(){
    for(int i=0; i<=MAXCHIPS; i++){
        memset(framebuffer[i], 0, 7);
    }
}

void setup () {
    pinMode(dataIn, OUTPUT);
    pinMode(clock,  OUTPUT);
    pinMode(load,   OUTPUT);

    //beginSerial(9600);
    //digitalWrite(13, HIGH);

    //initiation of the max 7219
    maxAll(max7219_reg_scanLimit, 0x07);
    maxAll(max7219_reg_decodeMode, 0x00);  // using an led matrix (not 7 segment)
    maxAll(max7219_reg_shutdown, 0x01);    // not in shutdown mode
    maxAll(max7219_reg_displayTest, 0x00); // no display test
    for (e=1; e<=8; e++) {    // empty registers, turn all LEDs off
        maxAll(e,0);
    }
    maxAll(max7219_reg_intensity, 0x0f & 0x0f);    // the first 0x0f is the value you can set
    // range: 0x00 to 0x0f

    text = " Arbor Networks  ";//"The quick brown fox jumped over the lazy dog. ";
    length = text.length();
}

void loop () {
    for(int i=0; i<length; i++){
        writechar(text[i],MAXCHIPS);
        // invertFrame(MAXCHIPS);
        // updateDisplay();
        // shiftLeft();
        //delay(100);
        for(int k=0; k<6; k++){
            updateDisplay();
            shiftLeft();
            delay(200);
        }
    }
}

