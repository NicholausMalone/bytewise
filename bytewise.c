#include <stdio.h>      /* printf */
#include <string.h>     /* strcat */
#include <stdlib.h>     /* strtol */
#include <math.h>

#define NUM_OF_BITS 24		// Set the number of bits for this program

// Assumes little endian
void printBits(unsigned int num, unsigned int num_of_bits)
{
	// Max bit should never be greater than NUM_OF_BITS
	int starting_bit_index = (num_of_bits - 1);
	int ending_bit_index = starting_bit_index - (num_of_bits - 1);

	for (int i = starting_bit_index; i > ending_bit_index; i--) {
		if (num >> i & 0x1) putchar('1');
		else putchar('0');
	}
}

unsigned int setBits(unsigned int mask, unsigned int data)
{
	unsigned int setMaskBits = 0;

	for (unsigned int i = 0; i < NUM_OF_BITS; i++) {
		// Shift mask to the right and get LSB
		unsigned int mask_bit = (mask & (1 << i)) >> i;
		// Shift data to the right and get LSB
		unsigned int data_bit = (data & (1 << i)) >> i;

		// set bit if masked: (OR)
		unsigned int set_bit = data_bit || mask_bit;

		// Build the bit array into an unsigned integer
		setMaskBits += set_bit * (int)pow(2.0, (float)i);

	}

	return setMaskBits;
}

unsigned int clearBits(unsigned int mask, unsigned int data)
{
	unsigned int clearMaskBits = 0;

	for (unsigned int i = 0; i < NUM_OF_BITS; i++) {
		// Shift mask to the right and get LSB
		unsigned int mask_bit = (mask & (1 << i)) >> i;
		// Shift data to the right and get LSB
		unsigned int data_bit = (data & (1 << i)) >> i;

		// clear bit if masked : (NOT AND)
		unsigned int clear_bit = (data_bit && !mask_bit);

		// Build the bit array into an unsigned integer
		clearMaskBits += clear_bit * (int)pow(2.0, (float)i);

	}

	return clearMaskBits;
}

unsigned int toggleBits(unsigned int mask, unsigned int data)
{
	unsigned int toggledMaskBits = 0;

	for (unsigned int i = 0; i < NUM_OF_BITS; i++) {
		// Shift mask to the right and get LSB
		unsigned int mask_bit = (mask & (1 << i)) >> i;
		// Shift data to the right and get LSB
		unsigned int data_bit = (data & (1 << i)) >> i;

		// toggle bit if masked: (XOR)
		unsigned int toggled_bit = data_bit ^ mask_bit;

		// Build the bit array into an unsigned integer
		toggledMaskBits += toggled_bit * (int)pow(2.0, (float)i);

	}

	return toggledMaskBits;
}

int main()
{
	// Using variables instead of User Input for this example
	
	float max_25bits = (float)NUM_OF_BITS;
	float max_24bits = (float)(NUM_OF_BITS-1);
	float base = 2.0;
	signed int max_24uint_value = pow(base, max_24bits) - 1;
	signed int max_25uint_value = pow(base, max_25bits) - 1;

	//signed int userInput1_Mask = 8388607;	// 0b011111111111111111111111 (two's complement)
	//signed int userInput1_Mask = 0;		  // 0b000000000000000000000000 (two's complement)
	//signed int userInput1_Mask = -6803358;  // 0b100110000011000001100010 (two's complement)
	//signed int userInput1_Mask = -8388608;  // 0b100000000000000000000000
	signed int userInput1_Mask = 4095;      //0b000000000000111111111111
	signed int userInput2_Data = -6803358;  // 0b100110000011000001100010 (two's complement)

	// Validate User Input
	// 24-bit signed integer max value is  8,388,607 or 0b011111111111111111111111 (two's complement)
	// 24-bit signed integer min value is -8,388,608 or 0b100000000000000000000000 (two's complement)
	if (userInput1_Mask > max_24uint_value || userInput1_Mask < -(max_24uint_value+1)) {
		printf("User must provide a valid 24-bit signed integer as mask.");
		return 0;
	}

	if (userInput1_Mask > max_24uint_value || userInput1_Mask < -(max_24uint_value + 1)) {
		printf("User must provide a valid 24-bit signed integer as data.");
		return 0;
	}

	// Convert to their unsigned 25-bit forms for bitwise manipulation, 
	// unsigned values range from 0 to 16,777,215, which is 25 bits of 1s (0b111111111111111111111111)
	unsigned int userInput1_Mask_u = userInput1_Mask;						    // 0b0011111111111111111111111 = 8,388,607
	unsigned int userInput2_Data_u = userInput2_Data + (max_25uint_value + 1);	// 0b0100110000011000001100010 = 9,973,858 (9973858)

	printf("User Mask:      ");
	printBits(userInput1_Mask_u, NUM_OF_BITS);
	printf("\n");

	printf("User Data:      ");
	printBits(userInput2_Data_u, NUM_OF_BITS);
	printf("\n");

	printf("Bitwise Set:    ");
	unsigned int result1 = setBits(userInput1_Mask_u, userInput2_Data_u);
	printBits(result1, NUM_OF_BITS);
	printf("\n");

	printf("Bitwise Clear:  ");
	unsigned int result2 = clearBits(userInput1_Mask_u, userInput2_Data_u);
	printBits(result2, NUM_OF_BITS);
	printf("\n");

	printf("Bitwise Toggle: ");
	unsigned int result3 = toggleBits(userInput1_Mask_u, userInput2_Data_u);
	printBits(result3, NUM_OF_BITS);
	printf("\n");

}
