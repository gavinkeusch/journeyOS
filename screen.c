#include "screen.h"

void screen_init()
{
    video = 0xB8000;
    next_text_pos = 0;
    curr_line = 0;
}

void print(char* str) 
{
    int curr_char_location_in_vid_mem, curr_color_location_in_vid_mem;

    while (*str != '\0') {
        curr_char_location_in_vid_mem = next_text_pos * 2;
        curr_color_location_in_vid_mem = curr_char_location_in_vid_mem + 1;

        video[curr_char_location_in_vid_mem] = *str;
        video[curr_color_location_in_vid_mem] = 15;

        next_text_pos++;
        str++;
    }
}

void println()
{
    next_text_pos = ++curr_line * 80;
}

void printi(int number) 
{
    char* digit_to_str[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};

    if (number >= 0 && number <= 9) {
        print(digit_to_str[number]);
        return;
    } else {
        int remaining = number % 10;
        number = number / 10;

        printi(number);
        printi(remaining);
    }
}