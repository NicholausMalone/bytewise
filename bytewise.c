#include <stdio.h>      /* printf */
#include <string.h>     /* strcat */
#include <stdlib.h>     /* strtol */
#include <math.h>

#define ISUNSIGNED(a) (a>=0 && ~a>=0)  // Imperfect way to determine if int is signed or unsigned

// Define boolean type if compiled as C code
#ifndef __cplusplus
typedef unsigned char bool;
static const bool False = 0;
static const bool True = 1;
#endif

/// <summary>
/// Determine the number of bits required to produce a given number.
/// </summary>
/// <param name="number">The number to measure bit length</param>
/// <returns>The bit length of the number</returns>
unsigned countBits(int num)
{
	bool isUnsigned = ISUNSIGNED(num);

	// If number is "0" then represent with 1 bit
	if (num == 0) return 1;

	// log function in base 2
	// take only integer part
	unsigned int num_of_bits = (int)log2(abs(num)) + 1;

	if (isUnsigned) {
		return num_of_bits;
	}
	else {
		return num_of_bits + 1;
	}
}

/// <summary>
/// This will print bits for any signed or unsigned integer.  This function assumes little endian and twos-complement for signed numbers.
/// </summary>
/// <param name="num">The number to print</param>
/// <param name="min_length">The minimum length of the bit array.  Can be used to add "0" padding. </param>
/// <returns>A string representing the bits in the number. </returns>
const char* bits_toString(int num, unsigned int min_length)
{
	unsigned int num_of_bits = countBits(num);
	unsigned int bits_to_print = max(num_of_bits, min_length);
	unsigned int string_mem_length = bits_to_print + 1;


	char* bits_string_p = (char*)malloc(string_mem_length);

	for (int i = 0; i < bits_to_print; i++) {
		if (num >> i & 0x1)
			bits_string_p[i] = '1';
		else 
			bits_string_p[i] = '0';
	}

	bits_string_p[bits_to_print] = '\0';

	return bits_string_p;
}

/// <summary>
/// This will return a unsigned integer value that represents the result of setting data bits to "1" that are indicated by the mask.
/// </summary>
/// <param name="mask">The mask representing which bits in the data to set.</param>
/// <param name="data">The data to modify.</param>
/// <returns>The modified data with the masked bits set to "1".</returns>
unsigned int setBits(int data, int mask)
{
	unsigned int setMaskBits = 0;
	unsigned int data_num_bits = countBits(data);
	unsigned int mask_num_bits = countBits(mask);
	unsigned int num_of_bits = max(data_num_bits, mask_num_bits);

	for (unsigned int i = 0; i < num_of_bits; i++) {
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

/// <summary>
/// This will return a unsigned integer value that represents the result of clearing data bits to "0" that are indicated by the mask.
/// </summary>
/// <param name="mask">The mask representing which bits in the data to clear.</param>
/// <param name="data">The data to modify.</param>
/// <returns>The modified data with the masked bits cleared to "0".</returns>
unsigned int clearBits(int data, int mask)
{
	unsigned int clearMaskBits = 0;
	unsigned int data_num_bits = countBits(data);
	unsigned int mask_num_bits = countBits(mask);
	unsigned int num_of_bits = max(data_num_bits, mask_num_bits);

	for (unsigned int i = 0; i < num_of_bits; i++) {
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

/// <summary>
/// This will return a unsigned integer value that represents the result of toggling data bits to the opposite value, "0" or "1", the bits toggled are indicated by the mask. 
/// </summary>
/// <param name="mask">The mask representing which bits in the data to toggle.</param>
/// <param name="data">The data to modify.</param>
/// <returns>The modified data with the masked bits toggled.</returns>
unsigned int toggleBits(int data, int mask)
{
	unsigned int toggledMaskBits = 0;
	unsigned int data_num_bits = countBits(data);
	unsigned int mask_num_bits = countBits(mask);
	unsigned int num_of_bits = max(data_num_bits, mask_num_bits);

	for (unsigned int i = 0; i < num_of_bits; i++) {
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

/// <summary>
/// This is a helper function used to determine the maximum value of an unsigned integer with the given bit length.
/// </summary>
/// <param name="num_of_bits">The bit length of an unsigned integer.</param>
/// <returns>The maximum value for an unsigned int of bit length.</returns>
unsigned int get_max_uint(unsigned int bit_length) {

	float base = 2.0;
	unsigned int max_int_value = pow(base, bit_length) - 1.0;

	return max_int_value;
}

/// <summary>
/// This is a helper function used to determine the minimum value of an unsigned integer with the given bit length.
/// </summary>
/// <param name="num_of_bits">The bit length of an unsigned integer.</param>
/// <returns>This function will always return "0" as it is always the minimum value of an unsigned int.</returns>
unsigned int get_min_uint(unsigned int bit_length) {
	return 0;
}

/// <summary>
/// This is a helper function used to determine the maximum value of an signed integer with the given bit length.
/// </summary>
/// <param name="num_of_bits">The bit length of an signed integer.</param>
/// <returns>The maximum value for an signed int of bit length.</returns>
signed int get_max_sint(unsigned int bit_length) {

	float base = 2.0;
	signed int max_int_value = pow(base, bit_length -1.0) - 1.0;

	return max_int_value;
}

/// <summary>
/// This is a helper function used to determine the maximum value of an signed integer with the given bit length.
/// </summary>
/// <param name="num_of_bits">The bit length of an signed integer.</param>
/// <returns>The minimum value for an signed int of bit length.</returns>
signed int get_min_sint(unsigned int bit_length) {

	float base = 2.0;
	signed int min_int_value = -pow(base, bit_length - 1.0);

	return min_int_value;
}

/// <summary>
/// This is a helper function used to determine the maximum value of an unsigned integer with the given bit length.
/// </summary>
/// <param name="num_of_bits">The bit length of an unsigned integer.</param>
/// <returns>The maximum value for an unsigned int of bit length.</returns>
unsigned int signed_to_unsigned(signed int num) {
	unsigned int num_of_bits = countBits(num);
	signed int max_int = get_max_sint(num_of_bits);
	return num + (max_int + 1);
}

/// <summary>
/// Simple function to round a number up to the nearest multiple of the given number.  This will only work on positive numbers.
/// </summary>
/// <param name="numToRound">The number that should be rounded up.</param>
/// <param name="multiple">The integer multiple that it should be rounded to.</param>
/// <returns>The positive number rounded up to the nearest multiple.</returns>
unsigned int roundUp(unsigned int numToRound, unsigned int multiple)
{
	if (multiple == 0)
		return numToRound;

	int remainder = numToRound % multiple;
	if (remainder == 0)
		return numToRound;

	return numToRound + multiple - remainder;
}

/// <summary>
/// The main function.  Use as an example of how to use these functions.
/// </summary>
/// <returns></returns>
int main()
{
	// Using variables instead of User Input for this example

	signed int userInput1_Mask = 8388607;	// 0b011111111111111111111111 (two's complement)
	//signed int userInput1_Mask = 0;		  // 0b000000000000000000000000 (two's complement)
	//signed int userInput1_Mask = -6803358;  // 0b100110000011000001100010 (two's complement)
	//signed int userInput1_Mask = -8388608;  // 0b100000000000000000000000
	//signed int userInput1_Mask = 4095;      //0b000000000000111111111111
	//signed int userInput2_Data = -6803358;  // 0b100110000011000001100010 (two's complement)
	signed int userInput2_Data = 4095;      //0b000000000000111111111111

	// Determine the largest number of bits to describe number given by user
	unsigned int mask_num_of_bits = countBits(userInput1_Mask);
	unsigned int data_num_of_bits = countBits(userInput2_Data);

	unsigned int bits_to_print = max(mask_num_of_bits, data_num_of_bits);

	// Round the bits to print to the nearest byte (8 bits)
	bits_to_print = roundUp(bits_to_print, 8);

	char* bits_output;


	printf("User Mask:      ");
	bits_output = bits_toString(userInput1_Mask, bits_to_print);
	printf("%s\n", bits_output);

	printf("User Data:      ");
	bits_output = bits_toString(userInput2_Data, bits_to_print);
	printf("%s\n", bits_output);

	printf("Bitwise Set:    ");
	unsigned int result1 = setBits(userInput2_Data, userInput1_Mask);
	bits_output = bits_toString(result1, bits_to_print);
	printf("%s\n", bits_output);;

	printf("Bitwise Clear:  ");
	unsigned int result2 = clearBits(userInput2_Data, userInput1_Mask);
	bits_output = bits_toString(result2, bits_to_print);
	printf("%s\n", bits_output);

	printf("Bitwise Toggle: ");
	unsigned int result3 = toggleBits(userInput2_Data, userInput1_Mask);
	bits_output = bits_toString(result3, bits_to_print);
	printf("%s\n", bits_output);

}
