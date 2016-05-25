#include <avr/pgmspace.h>
#include "font.h"

#define CLOCKDELAY 100
#define MAXCHIPS 4


int dataIn = 2;
int load = 3;
int clock = 4;

int maxInUse = MAXCHIPS;    //change this variable to set how many MAX7219's you'll use

int e = 0;
int count = 0;

String text = "";   //text to display
int length = 0;    //length of the text

//framebuffer initialization
char framebuffer[7][MAXCHIPS+1] = {
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0}
};


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
        //delayMicroseconds(CLOCKDELAY);
        digitalWrite(clock, HIGH);   // tock
        //delayMicroseconds(CLOCKDELAY);
        --i;                         // move to lesser bit
    }
}

void maxSingle( byte reg, byte col) {
    //maxSingle is the "easy"  function to use for a     //single max7219

    digitalWrite(load, LOW);       // begin
    putByte(reg);                  // specify register
    putByte(col);//((data & 0x01) * 256) + data >> 1); // put data
    digitalWrite(load, LOW);       // and load da shit
    digitalWrite(load,HIGH);
}

void maxAll (byte reg, byte col) {    // initialize  all  MAX7219's in the system
    int c = 0;
    digitalWrite(load, LOW);  // begin
    for ( c =1; c<= maxInUse; c++) {
        putByte(reg);  // specify register
        putByte(col);//((data & 0x01) * 256) + data >> 1); // put data
    }
    digitalWrite(load, LOW);
    digitalWrite(load,HIGH);
}

void maxOne(byte maxNr, byte reg, byte col) {
    //maxOne is for adressing different MAX7219's,
    //whilele having a couple of them cascaded

    int c = 0;
    digitalWrite(load, LOW);  // begin

    for ( c = maxInUse; c > maxNr; c--) {
        putByte(0);    // means no operation
        putByte(0);    // means no operation
    }

    putByte(reg);  // specify register
    putByte(col);//((data & 0x01) * 256) + data >> 1); // put data

    for ( c = maxNr-1; c >= 1; c--) {
        putByte(0);    // means no operation
        putByte(0);    // means no operation
    }

    digitalWrite(load, LOW); // and load da shit
    digitalWrite(load, HIGH);
}


void writechar(char in, int seg){
    for(int i=0;i<7;i++){
        framebuffer[i][seg] = (pgm_read_byte_near(&(font[in][i])));
        //maxOne(seg,i+1,font[in][i]);
    }
}

void updateDisplay(){
 for(int i=0;i<maxInUse;i++){
        for(int j=0;j<7;j++){
             maxOne(i+1,j+1,framebuffer[j][i]);
        }
    }
}

void shiftLeft(){
 for(int j=0;j<7;j++){
     framebuffer[j][0]/=2; // move the whole first segment one left, discard extra value
     for(int i=1;i<maxInUse+1;i++){
            if((framebuffer[j][i]) & 0x1){ //is odd
                framebuffer[j][i-1]+= 16;
            }
            framebuffer[j][i]/=2;
        }
    }
}

void invertFrame(int seg){
    for(int i=0;i<7;i++){
             framebuffer[i][seg] = (~framebuffer[i][seg] & 0x3f);
     }
}

void clearFrame(){
     for(int i=0;i<7;i++){
         for(int j=0;j<MAXCHIPS+1;j++){
             framebuffer[i][j] = 0;
         }
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
    maxAll(max7219_reg_decodeMode, 0x00);  // using an led matrix (not digits)
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
    for(int i=0;i<length;i++){
        writechar(text[i],MAXCHIPS);
        //invertFrame(MAXCHIPS);
        //updateDisplay();
        //delay(100);
        shiftLeft();
        for(int k=0;k<5;k++){
            updateDisplay();
            shiftLeft();
            delay(200);
        }
    }
}

