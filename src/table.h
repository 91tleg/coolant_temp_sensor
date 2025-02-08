#ifndef TABLE_H
#define TABLE_H

#include <Arduino.h>
#include <stdint.h>
#include "def.h"

int16_t coolant_temp_lookup_value = 0;

const byte coolant_look_up_table[256] PROGMEM = 
{
    // The first 14 values need 255 added
    146,132,117,105, 90, 76, 63, 48, 36, 29, 22, 15,  9,  2,
                                                            250,243,
    237,234,230,226,223,219,216,212,208,205,203,199,198,194,192,189,
    187,185,183,181,180,178,176,174,172,171,169,167,165,163,162,160,
    158,156,154,153,153,151,149,147,147,145,144,144,142,140,140,138,
    138,136,135,135,133,131,131,129,129,127,127,126,126,124,124,122,
    122,120,120,118,118,117,117,115,115,113,113,111,111,109,109,108,
    108,106,106,104,104,102,102,100,100, 99, 99, 97, 97, 97, 95, 95,
     95, 93, 93, 91, 91, 90, 90, 88, 88, 86, 86, 84, 84, 84, 82, 82,
     82, 81, 81, 79, 79, 79, 77, 77, 77, 75, 75, 73, 73, 73, 72, 72,
     72, 70, 70, 68, 68, 68, 66, 66, 66, 64, 64, 63, 63, 61, 61, 59,
     59, 57, 57, 55, 55, 55, 54, 54, 54, 52, 52, 50, 50, 50, 48, 48,
     48, 46, 46, 45, 45, 43, 43, 41, 41, 39, 39, 37, 37, 37, 36, 36,
     36, 34, 34, 32, 32, 30, 30, 28, 28, 27, 27, 25, 25, 23, 23, 21,
     21, 19, 18, 18, 16, 14, 14, 12, 12, 10,  9,  9,  7,  5,  5,  3,
      3,  1,  0,
                  2,  4,  6,  8,  9,  9, 11, 13, 15, 17, 18, 20, 22,
     24, 27, 31, 33, 36, 40, 42, 45, 47, 47, 47, 47, 47, 47, 47, 47   
    // The last 29 values need to be inverted (to negative)
};

int8_t adc_to_byte(float voltage)
{
    return (int8_t)((voltage / V_REF) * ADC_MAX);
}

void lookup_coolant_temp(byte b) 
{
    coolant_temp_lookup_value = pgm_read_byte(&coolant_look_up_table[b]);
    if (coolant_temp_lookup_value < 14) 
    {   
        coolant_temp_lookup_value += 255;
    }
    else if (coolant_temp_lookup_value > (255 - 29)) 
    {
        coolant_temp_lookup_value = -coolant_temp_lookup_value;
    }
}

#endif