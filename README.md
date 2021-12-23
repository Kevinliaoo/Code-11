<h1 align="center">Computer Programming</h1>
<h2 align="center">Final project</h2>
</br>
</br>
<p align="center">Kevin Liao</p>
<p align="center">廖習善</p>
</br>
</br>

## Introduction

Code 11 is a barcode system for encoding characters, primarily used in labeling telecommunications equipment. Our mission is to write a program that decodes the information obtained by scanning a barcode detected by a reader.

## Encoding system

Code 11 encodes each character of the message independently, each character is represented by five adjacent bars of different widths, alternating between dark and light color, each individual character is separated by a narrow light bar. To enable error detection, there are two check characters, C and K characters, whose values are calculated with a formula. Finally, the code is preceded and proceded by a start stop character to indicate where the message starts and ends.

## Decoding algorithm

The first step is to get the input data, that is stored in an external file. The data is stored in the following structure: It starts with an integer number m that indicates the number of bars (either narrow or wide) detected by the barcode reader, the code is followed by the m integers, representing the width of each bar of the message detected by the reader. If the integer m happens to be 0, this indicates that there are no more messages to be transmitted.
In order to get the message, first reads the integer m, then, it reads the following m integers, representing the message, and stores the result in an m size array.
Since the barcode scanner is not perfect, it can have an error margin of 5% of the actual value, so the first step after getting the message is to “rectify” it, in order to do so, I created a function (rectify_codebar) that iterates all over the array and stores the bar width value and it’s frequency in a hash table, assuming that the scanner rarely makes an error, I take the two most repeated values of the table and check if the biggest one is two times the smallest one, if so, I take those values as the narrow and width bar size, once I get them, all values that are within a 5% range of error respect to the actual size are corrected, then I convert all wide bars to 1 and all narrow bars to 0. If the previous step couldn’t be done, it means that the code is incorrectly encoded, and will display a “bad code” error message.
Once the pre-work is successfully done, here is when the decoding process starts, the function scan_barcode is in charge of it. But as the barcode scanner can be held either on the front side or backwards, this causes the possibility for the message to be read on the wrong way, so the first step while scanning is to check the value of the first character, knowing the fact that every massage should start with the start stop character (00110), and this character in the opposite way coincides with the character 4 (01100), before scanning the code, I have to check if the first character is the character 4, if so, I have to revert all the message to read it from back to front. The decoding process consists in reading each 5 bars character one by one, each one separated by a narrow light bar, and storing the characters in a char array (string) with a predetermined size (calculated using the m value). At the end of each message, there are two special characters (C and K), these are responsible for error checking, and it’s values can be calculated using the data decoded from the message, this means that the value of the characters C and K depends on the previous data, and if something is changed, these last two characters will also be changed, so I first calculate these values one by one using the formula, and if the C or K value decoded does not match with the expected value, this means that these values are incorrect, and the program will throw either a “bad C” or “bad K” error, depending on the character evaluated. If neither the C character or the K character had any errors, then the message was successfully decoded, and the final result is copied to the output string (passed as parameter to the function), given this value, the program is able to print the result in the console.

## Software design architecture

The code is organized on various functions, each of them responsible for a specific task.
In the main function, there is a while loop in charge of reading the m digit of each piece of data, until it reads a 0 and ends the program.
After the m is read, the function build_codebar is called, which is in charge of reading the following m characters and storing the result in an array.
Once the data is read, the function rectify_codebar converts the wide bars and narrow bars to 1 and 0 respectively. In order to do so, I used a hash table to store each bar width and it’s associated frequency value, and the most repeated two values are supposed to be the wide and narrow bars.
The function scan_barcode is the core of the program, it’s function is to decode the message and store the result in a string. A complimentary function used here is the function get_character, that reads five bars width and gets the decoded value.
Finally, the function prints the message on the console and scans the next m character, in order to decode the next message, and the while loop iterates all over again.
