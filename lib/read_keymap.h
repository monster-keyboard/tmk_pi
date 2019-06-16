/* Author:Rainboy */


#include <stdint.h>

#ifndef READ_KEYMAP_H
#define READ_KEYMAP_H

char *getfileall(char *fname);
int setKeyMap(char *str,uint8_t keymap[][MATRIX_ROWS][MATRIX_COLS]);
int read_keymap_init(char path[][255],uint8_t keymap[][MATRIX_ROWS][MATRIX_COLS]);
#endif
