#include <stdio.h>
#include <string.h>

char *int_position_strings[] = { "", "", "", "thousand", "thousand", "thousand", "million", "million", "million", "billion", "billion", "billion" };

char *int_tens_strings[] = { "", "", "twenty-", "thirty-", "forty-", "fifty-", "sixty-", "seventy-", "eighty-", "ninety-" };

char *int_teens_strings[] = { "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen" };

char *int_strings[] = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };

char *int_to_string(int i, char *buf) {
    int position = 0;
    int digits[32];
    int max_digits;
    char temp[512] = {0};

    while(i) {
        digits[position++] = i % 10;
        i /= 10;
    }

    max_digits = position;

    for(position = 0; position < max_digits; position++) {
        strcpy(temp, buf);

        switch(position % 3) {
            case 0:
                if(max_digits > 1 && digits[position + 1] == 1) {
                    strcpy(buf, int_teens_strings[digits[position]]);
                } else {
                    strcpy(buf, int_strings[digits[position]]);
                }

                if(position >= 2) {
                    strcat(buf, " ");
                    strcat(buf, int_position_strings[position]);
                    strcat(buf, " ");
                }

                strcat(buf, temp);
                break;
            case 1:
                if(digits[position] != 1) {
                    sprintf(buf, "%s%s", int_tens_strings[digits[position]], temp);
                }
                break;
            default:
                if(digits[position] > 0) {
                    sprintf(buf, "%s hundred %s", int_strings[digits[position]], temp);
                }
                break;
        }
    }
    
    return buf;
}

int main(void) {
    char buf[512] = {0};

    puts(int_to_string(23056109, buf));

    return 0;
}