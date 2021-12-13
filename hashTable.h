int insert(int *keys_array, int *values_array, int new_key, size_t size);
int initialize_array(int *keys_array, size_t size, int value);
int *get_wide_and_narrow(int *keys_array, int *values_array, size_t size);
void swap(int *x_pointer, int *y_pointer);

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