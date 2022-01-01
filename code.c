#include <stdio.h>
#include <string.h>

// Prototype declarations
int insert(int *keys_array, int *values_array, int new_key, size_t size);
int initialize_array(int *keys_array, size_t size, int value);
int *get_wide_and_narrow(int *keys_array, int *values_array, size_t size);
void swap(int *x_pointer, int *y_pointer);
int rectify_codebar(int *barcode, size_t size);
void print_codebar(int *barcode, size_t size);
char get_character(int *starting_position);
int get_char_weight(char character);
void copy_string(char *source, char *destination, size_t size);
void scan_barcode(int *barcode, char *output, size_t size);
void build_codebar(FILE *filePtr, int output[], size_t size);

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
    const char *filename = "test.txt";

    FILE *file_pointer = fopen(filename, "r");

    if (file_pointer == NULL)
        printf("File could not be opened.\n");
    else
    {
        int case_number = 1;
        int res; // Size of the barcode
        fscanf(file_pointer, "%d", &res);

        while (res != 0)
        {
            // Build the barcode
            int barcode[res];
            char output[100];
            // Get the barcode from the file
            build_codebar(file_pointer, barcode, res);
            // Rectify the barcode
            rectify_codebar(barcode, res);
            // Get the scanning result
            scan_barcode(barcode, output, res);
            // Print the result in console
            printf("Case %d: %s\n", case_number, output);

            case_number++;

            // Read the size of the next barcode
            fscanf(file_pointer, "%d", &res);
        }
    }
}

void build_codebar(FILE *filePtr, int output[], size_t size)
/*
This function reads a codebar from a file, given it's size.
*/
{
    for (int i = 0; i < size; i++)
        fscanf(filePtr, "%d", &output[i]);
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

void scan_barcode(int *barcode, char *output, size_t size)
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

    // The message does not start with the start/stop character
    if (get_character(barcode) != character_value[11])
    {
        copy_string(error_messages[2], output, strlen(error_messages[2]));
        return;
    }

    // Number of characters in the barcode
    size_t char_nums = (size - encoding_length) / (encoding_length + 1);
    // This is the decoded code (The response)
    char code[char_nums + 1];
    size_t code_index = 0;

    for (int i = encoding_length + 1; i < size; i += encoding_length + 1)
    {
        // The character-separating narrow light bar was not detected
        if (barcode[i - 1] != 0)
        {
            copy_string(error_messages[2], output, strlen(error_messages[2]));
            return;
        }

        char next_char = get_character(&barcode[i]);

        // Get a wrong character
        if (next_char == character_value[12])
        {
            copy_string(error_messages[2], output, strlen(error_messages[2]));
            return;
        }

        // C checking
        if (i == size - 2 * (encoding_length + 1) - encoding_length)
        {
            if (next_char == character_value[10])
            {
                copy_string(error_messages[0], output, strlen(error_messages[0]));
                return;
            }

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
            {
                copy_string(error_messages[0], output, strlen(error_messages[0]));
                return;
            }
        }

        // K checking
        else if (i == size - encoding_length - (encoding_length + 1))
        {
            if (next_char == character_value[10])
            {
                copy_string(error_messages[1], output, strlen(error_messages[1]));
                return;
            }

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
            {
                copy_string(error_messages[1], output, strlen(error_messages[1]));
                return;
            }
        }

        // Check if the last character is a start/stop character
        else if (i == size - encoding_length && next_char != character_value[11])
        {
            copy_string(error_messages[2], output, strlen(error_messages[2]));
            return;
        }

        // Add each character to the response
        code[code_index] = next_char;
        code_index++;
    }

    code[code_index - 3] = '\0';
    copy_string(code, output, strlen(code));
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
        // Maybe it is a badcode
        return 0;

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

void copy_string(char *source, char *destination, size_t size)
/*
Copy a string to another
*/
{
    int i = 0;
    for (i = 0; i < size; i++)
    {
        *(destination + i) = *(source + i);
    }

    *(destination + i) = '\0';
}

// ----- Functions to make a pair of arrays work as a hash table -----

int insert(int *keys_array, int *values_array, int new_key, size_t size)
/*
Increment the value of a key in a hash table.
A -1 on the keys_array means an empty space

@returns: 1 if successfuly inserted a new value in the hash table
*/
{
    size_t limit = 0; // integer indicating the index of the last element stored in the hash table

    for (int i = 0; i < size; i++)
    {
        if (keys_array[i] == new_key)
        {
            values_array[i]++;
            return 1;
        }

        if (keys_array[limit] == -1)
        {
            keys_array[limit] = new_key;
            values_array[limit] = 1;
            return 1;
        }

        limit++;
    }

    return 0;
}

int initialize_array(int *keys_array, size_t size, int value)
/*
Initialize all the values of an array with a value.

The hash table takes -1 as an empty key value, so it is necessary to initialize the key array to -1.
*/
{
    for (int i = 0; i < size; i++)
    {
        keys_array[i] = -1;
    }
    return 1;
}

int *get_wide_and_narrow(int *keys_array, int *values_array, size_t size)
/*
This function gets the wide and narrow bar size by makig a bubble sort and returns it in an array
*/
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size - 1 - i; j++)
        {
            if (values_array[j] > values_array[j + 1])
            {
                swap(&values_array[j], &values_array[j + 1]);
                swap(&keys_array[j], &keys_array[j + 1]);
            }
        }
    }

    return &keys_array[size - 2];
}

// ----- Functions to make a pair of arrays work as a hash table -----

void swap(int *x_pointer, int *y_pointer)
/*
Swap function used for bubble sort.
*/
{
    int temp = *x_pointer;
    *x_pointer = *y_pointer;
    *y_pointer = temp;
}