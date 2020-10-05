#include <iostream>
#include <fstream>
#include <thread>

using namespace std;

// Initializes the given array elements to 0
void _initalize(unsigned long long array[])
{
    for (short i = 0; i < 256; i++)
        array[i] = 0;
}

// Insertion Sort
void _insertion(unsigned long long array[], short start, short end)
{
    unsigned long long temp;
    short j;

    for (short i = start; i < end; i++)
    {
        j = i;

        while (array[j] > array[j + 1])
        {
            temp = array[j + 1];
            array[j + 1] = array[j];
            array[j--] = temp;
        }
    }
}

// Uses the frequency table to sort character arrays in non-decreasing frequencies
char* _merge(unsigned long long lookUp[], char left[], char right[], short size)
{
    // Output array
    char out[size * 2];
    short i = 0;
    short j = 0;
    short k = 0;

    while (i < size && j < size)
    {
        // Compare frequency of the left and right array
        if (lookUp[left[i]] <= lookUp[right[j]])
            out[k++] = lookUp[left[i++]];
     
        else
            out[k++] = lookUp[right[j++]];
    }

    // Fill the remaining elements
    while (i < size)
        out[k++] = lookUp[left[i++]];
    
    while (j < size)
        out[k++] = lookUp[right[j++]];
    
    return out;
}

// Outputs character array in non-decreasing frequencies using the look up table
// Sorts using Merge sort
char* _sort(unsigned long long lookUp[], short left = 0, short right = 256)
{
    if (left < right)
    {
        short mid = (left + right) / 2;
        
        char *l = _sort(lookUp, left, mid);
        char *r = _sort(lookUp, mid + 1, right);

        return _merge(lookUp, l, r, right / 2);
    }
}

void compress(string path)
{
    // Array which stores the count of individual characters
    // nth element stores count of character with ASCII value of n
    unsigned long long count[256];

    // Initialize array to zero in a seperate thread
    thread t1(_initalize, count);

    // Temperary variable to store data
    char c;
    ifstream fin;

    fin.open(path);

    // Wait for thread to finish process
    t1.join();

    while (!fin.eof())
    {
        // Read 1 byte of data
        fin.read(&c, 1);
        
        // Since char is signed (-128 to 127) we add 128 to make it positive
        // Cannot use unsigned char as fstream::read requires char* as parameter
        count[(int)c + 128]++;
    }

    fin.close();
    
    // Last character is counted twice, remove the duplicate
    count[(int)c + 128]--;

    char* s = _sort(count);
    for (int i = 0; i < 25; i++)
    {
        cout << s[i] << endl;
    }
    
}

int main()
{
    compress("test.txt");
    
    return 0;
}