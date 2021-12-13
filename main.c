#include <stdio.h>
#include "hashTable.h"

// Prototype declarations
int rectify_codebar(int *barcode, size_t size);
void print_codebar(int *barcode, size_t size);
char get_character(int *starting_position);
int scan_barcode(int *barcode, size_t size);

enum bar_color
{
    black,
    white
};

char *character_encoding[11] = {
    "10000", // 0
    "10010", // 1
    "00011", // 2
    "10100", // 3
    "01100", // 4
    "11000", // 5
    "00101", // 6
    "01001", // 7
    "10001", // 8
    "00001", // 9
    "00100", // -
    "00110", // Start/Stop
    "01100", // Start/Stop reverse
};

// Global variables
enum bar_color color_flag = black;
const size_t encoding_length = 5;

// Array storing two values, the wide
int *wide_and_narrow;

int main()
{
    // Test cases
    size_t test_size_1 = 59;
    int test_data_1[59] = {
        40,
        82,
        80,
        40,
        40,
        40,
        80,
        80,
        40,
        40,
        40,
        40,
        40,
        40,
        40,
        80,
        80,
        40,
        40,
        40,
        41,
        80,
        80,
        40,
        40,
        39,
        80,
        80,
        42,
        40,
        40,
        40,
        79,
        40,
        40,
        40,
        40,
        40,
        80,
        40,
        80,
        40,
        80,
        80,
        40,
        40,
        40,
        40,
        40,
        80,
        40,
        40,
        80,
        40,
        40,
        80,
        78,
        40,
        40};

    size_t test_size_2 = 35;
    int test_data_2[35] = {30, 30, 31, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 29, 30, 30, 30, 30, 30, 31, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30};

    size_t test_size_3 = 35;
    int test_data_3[35] = {
        10,
        10,
        20,
        20,
        10,
        10,
        19,
        10,
        10,
        20,
        10,
        10,
        10,
        10,
        10,
        20,
        20,
        10,
        10,
        20,
        20,
        10,
        10,
        10,
        10,
        10,
        10,
        10,
        21,
        10,
        10,
        10,
        20,
        19,
        10,
    };

    rectify_codebar(test_data_1, test_size_1);
    scan_barcode(test_data_1, test_size_1);
}

void print_codebar(int *barcode, size_t size)
/*
This function prints the codebar
*/
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", *(barcode + i));
    }
    printf("\n");
}

char get_character(int *starting_position)
/*
This function decodes one single character and returns it's value.
*/
{
    for (int i = 0; i < encoding_length; i++)
    {
    }
}

int scan_barcode(int *barcode, size_t size)
{
    get_character(&barcode[0]);
}

int rectify_codebar(int *barcode, size_t size)
/*
This function rectifies the codebar length read by the reader, as it may have
upto 5 percent of error.

@returns: 1 if it was successfully rectified, else 0
*/
{
    const int empty_key = -1, empty_value = 0;
    const float error = .05;

    // Create an empty hash table
    int keys[size];
    int values[size];
    initialize_array(keys, size, empty_key);
    initialize_array(values, size, empty_value);

    // Fill all the values
    for (int i = 0; i < size; i++)
        insert(keys, values, barcode[i], size);

    // Get the wide and narrow value
    wide_and_narrow = get_wide_and_narrow(keys, values, size);

    // Check if the wide bar is two times wider than the narrow bar
    if (*wide_and_narrow != *(wide_and_narrow + 1) * 2)
    {
        // Maybe it is a badcode
        printf("Maybe it is a bad code, I don't know and I have to test it\n");
        return 0;
    }

    // Rectify all width with errors
    for (int i = 0; i < size; i++)
    {
        // The barcode length matches with the standard values
        if (*(barcode + i) == *wide_and_narrow || *(barcode + i) == *(wide_and_narrow + 1))
            continue;
        else
        {
            // Rectify those values with a margin of error
            if (*(barcode + i) >= (float)*wide_and_narrow * (1 - error) && *(barcode + i) <= (float)*wide_and_narrow * (1 + error))
                *(barcode + i) = *wide_and_narrow;
            else if (*(barcode + i) >= (float)*(wide_and_narrow + 1) * (1 - error) && *(barcode + i) <= (float)*(wide_and_narrow + 1) * (1 + error))
                *(barcode + i) = *(wide_and_narrow + 1);
        }
    }

    return 1;
}