/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
 * scan matrix
 */
#include <stdint.h>
#include <stdbool.h>
#include "config.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"
#include <stdio.h>
#include "wait.h"
#include <wiringPiI2C.h>



#ifndef DEBOUNCE
#   define DEBOUNCE	5
#endif

static uint8_t debouncing = DEBOUNCE;

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

static matrix_row_t read_cols(void);
static uint8_t read_rows(void);
static void init_cols(void);
static void unselect_rows(void);
static void select_row(uint8_t row);

static int i2c_dev_1;
static int i2c_dev_2;

void matrix_setup(){
    //printf("matrix_setup\n");
    i2c_dev_1 = wiringPiI2CSetup(0x20);
    i2c_dev_2 = wiringPiI2CSetup(0x21);

    if(i2c_dev_1 == -1 || i2c_dev_2 == -1){
        dprintf("i2c init failed\n");
        dprintf("i2c_dev_1 = %d \n",i2c_dev_1);
        dprintf("i2c_dev_2 = %d \n",i2c_dev_2);
        return;
    }
    //设定 row 输出低
    //设定 col input 上拉
    
    // row1-8 set output
    if(wiringPiI2CWriteReg8(i2c_dev_1,0x06,0x00) == -1){
        dprintf("set pin faild row1-8\n");
        return ;
    }
    // row1-8 set output low
    if(wiringPiI2CWriteReg8(i2c_dev_1,0x02,0x00) == -1){
        dprintf("set pin faild row1-8 output low\n");
        return ;
    }

    //col1-8 set input
    if(wiringPiI2CWriteReg8(i2c_dev_1,0x07,0xff) == -1){
        dprintf("set pin faild col1-8 \n");
        return ;
    }
    //col9-16 set input
    if(wiringPiI2CWriteReg8(i2c_dev_2,0x06,0xff) == -1){
        dprintf("set pin faild col9-16 \n");
        return ;
    }
    //col17-24 set input
    if(wiringPiI2CWriteReg8(i2c_dev_2,0x07,0xff) == -1){
        dprintf("set pin faild col17-24 \n");
        return ;
    }

}


void matrix_init(void)
{
    // initialize row and col
    unselect_rows();
    init_cols();

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) {
        matrix[i] = 0;
        matrix_debouncing[i] = 0;
    }
}

uint8_t matrix_scan(void)
{
    /*dprintf("matrix row %d \n",MATRIX_ROWS);*/
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        select_row(i);
        _delay_us(30);  // without this wait read unstable value.
        matrix_row_t cols = read_cols();
        /*
         *
         * uint8_t row_now = read_rows();
         * dprintf("row: %d %x, cols:",i,row_now);
         *  //dprintf("col: %x\n",cols);
         * print_bin_reverse24(cols);
         * printf("\n");
         * _delay_ms(1000);  
         * 
         */
        if (matrix_debouncing[i] != cols) {
            matrix_debouncing[i] = cols;
            if (debouncing) { debug("bounce!: "); debug_hex(debouncing); debug("\n");
            }
            debouncing = DEBOUNCE;
        }
        unselect_rows();
    }

    //printf("debouncing %d\n",debouncing);

    if (debouncing) {
        if (--debouncing) {
            //_delay_ms(1);
        } else {
            for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
                matrix[i] = matrix_debouncing[i];
            }
        }
    }

    return 1;
}

inline
matrix_row_t matrix_get_row(uint8_t row)
{
    return matrix[row];
}

/* Column pin configuration
 * col: 0   1   2   3   4   5   6   7   8   9   10  11  12  13
 * pin: F0  F1  E6  C7  C6  B6  D4  B1  B0  B5  B4  D7  D6  B3  (Rev.A)
 * pin:                                 B7                      (Rev.B)
 */
static void  init_cols(void)
{
    // Input with pull-up(DDR:0, PORT:1)
}

static uint32_t read_cols(void)
{
    uint8_t col_1 = wiringPiI2CReadReg8(i2c_dev_1,0x01);
    uint8_t col_2 = wiringPiI2CReadReg8(i2c_dev_2,0x00);
    uint8_t col_3 = wiringPiI2CReadReg8(i2c_dev_2,0x01);
    /*
     *dprintf("col_1: %x\n",col_1);
     *dprintf("col_2: %x\n",col_2);
     *dprintf("col_3: %x\n",col_3);
     *uint32_t ans =  (~((col_3<<16) | (col_2 << 8) | col_1)) & 0x00ffffff;
     *dprintf("ans: %x\n",ans);
     */
    return  (~((col_3<<16) | (col_2 << 8) | col_1)) & 0x00ffffff;
}
static uint8_t read_rows(void){
    uint8_t row  =   wiringPiI2CReadReg8(i2c_dev_1,0x02);
    return row;
}

static void unselect_rows(void)
{
    // i2c pca9555 row1-8 to unselect
    wiringPiI2CWriteReg8(i2c_dev_1,0x02,0xff);
}

static void select_row(uint8_t row)
{
    // Output low(DDR:1, PORT:0) to select
    row = 7-row;
    uint8_t row_data = ~(1<<(row));
    wiringPiI2CWriteReg8(i2c_dev_1,0x02,row_data);
}
