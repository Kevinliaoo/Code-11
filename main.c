#include <stdio.h>
#include <string.h>
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

const size_t number_of_characters = 13;
char character_value[13] = {
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '-',
    'S', // Start/Stop
    'X'  // Not found
};

// Global variables
enum bar_color color_flag = black;
const size_t encoding_length = 5;

// Array storing two values, [ wide, narrow ]
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
If none of the characters in the table were identified, returns an 'X'.

@param *starting_position: Pointer to the first character
*/
{

    // 0
    if (*starting_position == 0)
    {
        // 0 0
        if (*(starting_position + 1) == 0)
        {
            // 0 0 0
            if (*(starting_position + 2) == 0)
            {
                // 0 0 0 0
                if (*(starting_position + 3) == 0)
                {
                    // 0 0 0 0 1
                    if (*(starting_position + 4) == 1)
                        return character_value[9];
                }
                // 0 0 0 1
                else
                {
                    // 0 0 0 1 1
                    if (*(starting_position + 4) == 1)
                        return character_value[2];
                }
            }
            // 0 0 1
            else
            {
                // 0 0 1 0
                if (*(starting_position + 3) == 0)
                {
                    // 0 0 1 0 0
                    if (*(starting_position + 4) == 0)
                        return character_value[10];
                    // 0 0 1 0 1
                    else
                        return character_value[6];
                }
                // 0 0 1 1
                else
                {
                    if (*(starting_position + 4) == 0)
                        return character_value[11];
                }
            }
        }
        // 0 1
        else
        {
            // 0 1 0
            if (*(starting_position + 2) == 0)
            {
                // 0 1 0 0
                if (*(starting_position + 3) == 0)
                {
                    // 0 1 0 0 1
                    if (*(starting_position + 4) == 1)
                        return character_value[7];
                }
            }
            // 0 1 1
            else
            {
                // 0 1 1 0
                if (*(starting_position + 3) == 0)
                {
                    // 0 1 1 0 0
                    if (*(starting_position + 4) == 0)
                        return character_value[4];
                }
            }
        }
    }
    // 1
    else
    {
        // 1 0
        if (*(starting_position + 1) == 0)
        {
            // 1 0 0
            if (*(starting_position + 2) == 0)
            {
                // 1 0 0 0
                if (*(starting_position + 3) == 0)
                {
                    // 1 0 0 0 0
                    if (*(starting_position + 4) == 0)
                        return character_value[0];
                    // 1 0 0 0 1
                    else
                        return character_value[8];
                }
                // 1 0 0 1
                else
                {
                    // 1 0 0 1 0
                    if (*(starting_position + 4) == 0)
                        return character_value[1];
                }
            }
            // 1 0 1
            else
            {
                // 1 0 1 0
                if (*(starting_position + 3) == 0)
                {
                    // 1 0 1 0 0
                    if (*(starting_position + 4) == 0)
                        return character_value[3];
                }
            }
        }
        // 1 1
        else
        {
            // 1 1 0
            if (*(starting_position + 2) == 0)
            {
                // 1 1 0 0
                if (*(starting_position + 3) == 0)
                {
                    // 1 1 0 0 0
                    if (*(starting_position + 4) == 0)
                        return character_value[5];
                }
            }
        }
    }

    return character_value[12];
}

int scan_barcode(int *barcode, size_t size)
{
    char firstChar = get_character(&barcode[0]);

    // Check if the barcode is reversed (The Start/Stop code coincides with the 4)
    if (get_character(barcode) == character_value[4])
    {
        // Reverse the barcode
        for (int i = 0; i < size / 2; i++)
            swap(&barcode[i], &barcode[size - 1 - i]);
    }
    return 1;
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
        if (*(barcode + i) == *wide_and_narrow)
            *(barcode + i) = 1;
        else if (*(barcode + i) == *(wide_and_narrow + 1))
            *(barcode + i) = 0;
        else
        {
            // Rectify those values with a margin of error
            if (*(barcode + i) >= (float)*wide_and_narrow * (1 - error) && *(barcode + i) <= (float)*wide_and_narrow * (1 + error))
                *(barcode + i) = 1;
            else if (*(barcode + i) >= (float)*(wide_and_narrow + 1) * (1 - error) && *(barcode + i) <= (float)*(wide_and_narrow + 1) * (1 + error))
                *(barcode + i) = 0;
        }
    }

    return 1;
}