#include <stdio.h>
#include <string.h>
#include "hashTable.h"

// Prototype declarations
int rectify_codebar(int *barcode, size_t size);
void print_codebar(int *barcode, size_t size);
char get_character(int *starting_position);
int get_char_weight(char character);
char *scan_barcode(int *barcode, size_t size);

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

char *error_messages[3] = {
    "bad C",
    "bad K",
    "bad code"};

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
    char *response = scan_barcode(test_data_1, test_size_1);
    printf("The response is: %s\n", response);
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

int get_char_weight(char character)
/*
This function returns the weight associated with each character.
Used for calculating C and K error detection
*/
{
    switch (character)
    {
    case '0':
        return 0;
    case '1':
        return 1;
    case '2':
        return 2;
    case '3':
        return 3;
    case '4':
        return 4;
    case '5':
        return 5;
    case '6':
        return 6;
    case '7':
        return 7;
    case '8':
        return 8;
    case '9':
        return 9;
    case '-':
        return 10;
    // This should not happen
    default:
        return 0;
    }
}

char *scan_barcode(int *barcode, size_t size)
/*
This function scans a barcode

@param barcode: Barcode converted to 0 and 1
@returns: The decoded code or the error message
*/
{
    // Check if the barcode is reversed (The Start/Stop code coincides with the 4)
    if (get_character(barcode) == character_value[4])
    {
        // Reverse the barcode
        for (int i = 0; i < size / 2; i++)
            swap(&barcode[i], &barcode[size - 1 - i]);
    }

    if (get_character(barcode) != character_value[11])
        return error_messages[2];

    // Number of characters in the barcode
    size_t char_nums = (size - encoding_length) / (encoding_length + 1);
    // This is the decoded code (The response)
    char code[char_nums + 1];
    size_t code_index = 0;

    for (int i = encoding_length + 1; i < size; i += encoding_length + 1)
    {
        // The character-separating narrow light bar was not detected
        if (barcode[i - 1] != 0)
            return error_messages[2];

        char next_char = get_character(&barcode[i]);

        // C checking
        if (i == size - 2 * (encoding_length + 1) - encoding_length)
        {
            if (next_char == character_value[10])
                return error_messages[0];
            int expected_C = 0;
            for (int j = 1; j <= code_index; j++)
            {
                int weight = get_char_weight(code[j - 1]);
                int number = ((code_index - j) % 10 + 1) * weight;
                expected_C += number;
            }
            expected_C %= 11;

            // Using the weight in order to compare two integers
            if (expected_C != get_char_weight(next_char))
                return error_messages[0];
        }

        // K checking
        else if (i == size - encoding_length - (encoding_length + 1))
        {
            if (next_char == character_value[10])
                return error_messages[1];

            int expected_K = 0;
            // The C character us excluded
            int n = code_index - 1;
            for (int j = 1; j <= code_index; j++)
            {
                int weight = get_char_weight(code[j - 1]);
                int number = ((n - j + 1) % 9 + 1) * weight;
                expected_K += number;
            }
            expected_K %= 11;

            // Using the weight in order to compare two integers
            if (expected_K != get_char_weight(next_char))
                return error_messages[1];
        }

        // Check if the last character is a start/stop character
        else if (i == size - encoding_length && next_char != character_value[11])
            return error_messages[2];

        // Add each character to the response
        code[code_index] = next_char;
        code_index++;
    }

    code[code_index - 3] = '\0';

    printf("The returning code is: %s\n", code);
    return "The code";
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