/*
Signature key: 7C848198AE93D3BB

-----BEGIN PGP SIGNED MESSAGE-----
Hash: SHA256

*/
// Copyright © 2018 mpan; <https://mpan.pl/>; CC0 1.0 (THIS FILE!)

/**
 * Generates an unsigned integer value from its binary representation.
 * 
 * `BIN8` produces an expression that evaluates to an unsigned integer
 * from range [`0`, `255`]. The value is equal to the binary number described
 * by @p digits. The output is a constant expression.
 * 
 * @par Format
 * `BIN8` accepts three formats:
 * 
 *  -   All 8 digits together,
 *  -   Two 4-digit groups,
 *  -   Each digit separately.
 * 
 * Digits are either `0` or `1` and all 8 of them need to be supplied.
 * 
 * @par Examples
 * Producing an 8-bit value from 8 whitespace-separated digits:
 * 
 *      printf("%x = %x\n", 0xA5, BIN8(1 0 1 0 0 1 0 1));
 * 
 * Achieving the same output, using two 4-digit groups and a single 8-bit group:
 * 
 *      printf("%x = %x\n", 0xA5, BIN8(1010 0101));
 *      printf("%x = %x\n", 0xA5, BIN8(10100101));
 * 
 * @param [in] digits
 *      The binary digits to be converted, in one of the formats mentioned
 *      above.
 * 
 * @return
 *      A constant expression evaluating to the number represented by @p digits.
 * 
 * @author      mpan
 */
#define BIN8(digits) BIN8_COLLECT_PXPAND(BIN8_EAT8(digits))

#define BIN8_COLLECT_PXPAND(digits) BIN8_COLLECT(digits)

#define BIN8_COLLECT(b7, b6, b5, b4, b3, b2, b1, b0)\
      (((b7) << 7) | ((b6) << 6) | ((b5) << 5) | ((b4) << 4) | ((b3) << 3)\
      | ((b2) << 2) | ((b1) << 1) | (b0))

#define BIN8_EAT8(digits) BIN8_EAT8_##digits )
#define BIN8_EAT8_0 0, BIN8_EAT7(
#define BIN8_EAT8_1 1, BIN8_EAT7(

#define BIN8_EAT7(digits) BIN8_EAT7_##digits )
#define BIN8_EAT7_0 0, BIN8_EAT6(
#define BIN8_EAT7_1 1, BIN8_EAT6(

#define BIN8_EAT6(digits) BIN8_EAT6_##digits )
#define BIN8_EAT6_0 0, BIN8_EAT5(
#define BIN8_EAT6_1 1, BIN8_EAT5(

#define BIN8_EAT5(digits) BIN8_EAT5_##digits )
#define BIN8_EAT5_0 0, BIN8_EAT4(
#define BIN8_EAT5_1 1, BIN8_EAT4(

#define BIN8_EAT4(digits) BIN8_EAT4_##digits )
#define BIN8_EAT4_0 0, BIN8_EAT3(
#define BIN8_EAT4_1 1, BIN8_EAT3(

#define BIN8_EAT3(digits) BIN8_EAT3_##digits )
#define BIN8_EAT3_0 0, BIN8_EAT2(
#define BIN8_EAT3_1 1, BIN8_EAT2(

#define BIN8_EAT2(digits) BIN8_EAT2_##digits )
#define BIN8_EAT2_0 0, BIN8_EAT1(
#define BIN8_EAT2_1 1, BIN8_EAT1(

#define BIN8_EAT1(digits) BIN8_EAT1_##digits )
#define BIN8_EAT1_0 0 BIN8_FIN(
#define BIN8_EAT1_1 1 BIN8_FIN(

#define BIN8_FIN()

#define BIN8_EAT8_0000 0, 0, 0, 0, BIN8_EATQUAD4(
#define BIN8_EAT8_0001 0, 0, 0, 1, BIN8_EATQUAD4(
#define BIN8_EAT8_0010 0, 0, 1, 0, BIN8_EATQUAD4(
#define BIN8_EAT8_0011 0, 0, 1, 1, BIN8_EATQUAD4(
#define BIN8_EAT8_0100 0, 1, 0, 0, BIN8_EATQUAD4(
#define BIN8_EAT8_0101 0, 1, 0, 1, BIN8_EATQUAD4(
#define BIN8_EAT8_0110 0, 1, 1, 0, BIN8_EATQUAD4(
#define BIN8_EAT8_0111 0, 1, 1, 1, BIN8_EATQUAD4(
#define BIN8_EAT8_1000 1, 0, 0, 0, BIN8_EATQUAD4(
#define BIN8_EAT8_1001 1, 0, 0, 1, BIN8_EATQUAD4(
#define BIN8_EAT8_1010 1, 0, 1, 0, BIN8_EATQUAD4(
#define BIN8_EAT8_1011 1, 0, 1, 1, BIN8_EATQUAD4(
#define BIN8_EAT8_1100 1, 1, 0, 0, BIN8_EATQUAD4(
#define BIN8_EAT8_1101 1, 1, 0, 1, BIN8_EATQUAD4(
#define BIN8_EAT8_1110 1, 1, 1, 0, BIN8_EATQUAD4(
#define BIN8_EAT8_1111 1, 1, 1, 1, BIN8_EATQUAD4(

#define BIN8_EATQUAD4(digits) BIN8_EATQUAD4_##digits )
#define BIN8_EATQUAD4_0000 0, 0, 0, 0 BIN8_FIN(
#define BIN8_EATQUAD4_0001 0, 0, 0, 1 BIN8_FIN(
#define BIN8_EATQUAD4_0010 0, 0, 1, 0 BIN8_FIN(
#define BIN8_EATQUAD4_0011 0, 0, 1, 1 BIN8_FIN(
#define BIN8_EATQUAD4_0100 0, 1, 0, 0 BIN8_FIN(
#define BIN8_EATQUAD4_0101 0, 1, 0, 1 BIN8_FIN(
#define BIN8_EATQUAD4_0110 0, 1, 1, 0 BIN8_FIN(
#define BIN8_EATQUAD4_0111 0, 1, 1, 1 BIN8_FIN(
#define BIN8_EATQUAD4_1000 1, 0, 0, 0 BIN8_FIN(
#define BIN8_EATQUAD4_1001 1, 0, 0, 1 BIN8_FIN(
#define BIN8_EATQUAD4_1010 1, 0, 1, 0 BIN8_FIN(
#define BIN8_EATQUAD4_1011 1, 0, 1, 1 BIN8_FIN(
#define BIN8_EATQUAD4_1100 1, 1, 0, 0 BIN8_FIN(
#define BIN8_EATQUAD4_1101 1, 1, 0, 1 BIN8_FIN(
#define BIN8_EATQUAD4_1110 1, 1, 1, 0 BIN8_FIN(
#define BIN8_EATQUAD4_1111 1, 1, 1, 1 BIN8_FIN(

#define BIN8_EAT8_00000000 0, 0, 0, 0, 0, 0, 0, 0 BIN8_FIN(
#define BIN8_EAT8_00000001 0, 0, 0, 0, 0, 0, 0, 1 BIN8_FIN(
#define BIN8_EAT8_00000010 0, 0, 0, 0, 0, 0, 1, 0 BIN8_FIN(
#define BIN8_EAT8_00000011 0, 0, 0, 0, 0, 0, 1, 1 BIN8_FIN(
#define BIN8_EAT8_00000100 0, 0, 0, 0, 0, 1, 0, 0 BIN8_FIN(
#define BIN8_EAT8_00000101 0, 0, 0, 0, 0, 1, 0, 1 BIN8_FIN(
#define BIN8_EAT8_00000110 0, 0, 0, 0, 0, 1, 1, 0 BIN8_FIN(
#define BIN8_EAT8_00000111 0, 0, 0, 0, 0, 1, 1, 1 BIN8_FIN(
#define BIN8_EAT8_00001000 0, 0, 0, 0, 1, 0, 0, 0 BIN8_FIN(
#define BIN8_EAT8_00001001 0, 0, 0, 0, 1, 0, 0, 1 BIN8_FIN(
#define BIN8_EAT8_00001010 0, 0, 0, 0, 1, 0, 1, 0 BIN8_FIN(
#define BIN8_EAT8_00001011 0, 0, 0, 0, 1, 0, 1, 1 BIN8_FIN(
#define BIN8_EAT8_00001100 0, 0, 0, 0, 1, 1, 0, 0 BIN8_FIN(
#define BIN8_EAT8_00001101 0, 0, 0, 0, 1, 1, 0, 1 BIN8_FIN(
#define BIN8_EAT8_00001110 0, 0, 0, 0, 1, 1, 1, 0 BIN8_FIN(
#define BIN8_EAT8_00001111 0, 0, 0, 0, 1, 1, 1, 1 BIN8_FIN(
#define BIN8_EAT8_00010000 0, 0, 0, 1, 0, 0, 0, 0 BIN8_FIN(
#define BIN8_EAT8_00010001 0, 0, 0, 1, 0, 0, 0, 1 BIN8_FIN(
#define BIN8_EAT8_00010010 0, 0, 0, 1, 0, 0, 1, 0 BIN8_FIN(
#define BIN8_EAT8_00010011 0, 0, 0, 1, 0, 0, 1, 1 BIN8_FIN(
#define BIN8_EAT8_00010100 0, 0, 0, 1, 0, 1, 0, 0 BIN8_FIN(
#define BIN8_EAT8_00010101 0, 0, 0, 1, 0, 1, 0, 1 BIN8_FIN(
#define BIN8_EAT8_00010110 0, 0, 0, 1, 0, 1, 1, 0 BIN8_FIN(
#define BIN8_EAT8_00010111 0, 0, 0, 1, 0, 1, 1, 1 BIN8_FIN(
#define BIN8_EAT8_00011000 0, 0, 0, 1, 1, 0, 0, 0 BIN8_FIN(
#define BIN8_EAT8_00011001 0, 0, 0, 1, 1, 0, 0, 1 BIN8_FIN(
#define BIN8_EAT8_00011010 0, 0, 0, 1, 1, 0, 1, 0 BIN8_FIN(
#define BIN8_EAT8_00011011 0, 0, 0, 1, 1, 0, 1, 1 BIN8_FIN(
#define BIN8_EAT8_00011100 0, 0, 0, 1, 1, 1, 0, 0 BIN8_FIN(
#define BIN8_EAT8_00011101 0, 0, 0, 1, 1, 1, 0, 1 BIN8_FIN(
#define BIN8_EAT8_00011110 0, 0, 0, 1, 1, 1, 1, 0 BIN8_FIN(
#define BIN8_EAT8_00011111 0, 0, 0, 1, 1, 1, 1, 1 BIN8_FIN(
#define BIN8_EAT8_00100000 0, 0, 1, 0, 0, 0, 0, 0 BIN8_FIN(
#define BIN8_EAT8_00100001 0, 0, 1, 0, 0, 0, 0, 1 BIN8_FIN(
#define BIN8_EAT8_00100010 0, 0, 1, 0, 0, 0, 1, 0 BIN8_FIN(
#define BIN8_EAT8_00100011 0, 0, 1, 0, 0, 0, 1, 1 BIN8_FIN(
#define BIN8_EAT8_00100100 0, 0, 1, 0, 0, 1, 0, 0 BIN8_FIN(
#define BIN8_EAT8_00100101 0, 0, 1, 0, 0, 1, 0, 1 BIN8_FIN(
#define BIN8_EAT8_00100110 0, 0, 1, 0, 0, 1, 1, 0 BIN8_FIN(
#define BIN8_EAT8_00100111 0, 0, 1, 0, 0, 1, 1, 1 BIN8_FIN(
#define BIN8_EAT8_00101000 0, 0, 1, 0, 1, 0, 0, 0 BIN8_FIN(
#define BIN8_EAT8_00101001 0, 0, 1, 0, 1, 0, 0, 1 BIN8_FIN(
#define BIN8_EAT8_00101010 0, 0, 1, 0, 1, 0, 1, 0 BIN8_FIN(
#define BIN8_EAT8_00101011 0, 0, 1, 0, 1, 0, 1, 1 BIN8_FIN(
#define BIN8_EAT8_00101100 0, 0, 1, 0, 1, 1, 0, 0 BIN8_FIN(
#define BIN8_EAT8_00101101 0, 0, 1, 0, 1, 1, 0, 1 BIN8_FIN(
#define BIN8_EAT8_00101110 0, 0, 1, 0, 1, 1, 1, 0 BIN8_FIN(
#define BIN8_EAT8_00101111 0, 0, 1, 0, 1, 1, 1, 1 BIN8_FIN(
#define BIN8_EAT8_00110000 0, 0, 1, 1, 0, 0, 0, 0 BIN8_FIN(
#define BIN8_EAT8_00110001 0, 0, 1, 1, 0, 0, 0, 1 BIN8_FIN(
#define BIN8_EAT8_00110010 0, 0, 1, 1, 0, 0, 1, 0 BIN8_FIN(
#define BIN8_EAT8_00110011 0, 0, 1, 1, 0, 0, 1, 1 BIN8_FIN(
#define BIN8_EAT8_00110100 0, 0, 1, 1, 0, 1, 0, 0 BIN8_FIN(
#define BIN8_EAT8_00110101 0, 0, 1, 1, 0, 1, 0, 1 BIN8_FIN(
#define BIN8_EAT8_00110110 0, 0, 1, 1, 0, 1, 1, 0 BIN8_FIN(
#define BIN8_EAT8_00110111 0, 0, 1, 1, 0, 1, 1, 1 BIN8_FIN(
#define BIN8_EAT8_00111000 0, 0, 1, 1, 1, 0, 0, 0 BIN8_FIN(
#define BIN8_EAT8_00111001 0, 0, 1, 1, 1, 0, 0, 1 BIN8_FIN(
#define BIN8_EAT8_00111010 0, 0, 1, 1, 1, 0, 1, 0 BIN8_FIN(
#define BIN8_EAT8_00111011 0, 0, 1, 1, 1, 0, 1, 1 BIN8_FIN(
#define BIN8_EAT8_00111100 0, 0, 1, 1, 1, 1, 0, 0 BIN8_FIN(
#define BIN8_EAT8_00111101 0, 0, 1, 1, 1, 1, 0, 1 BIN8_FIN(
#define BIN8_EAT8_00111110 0, 0, 1, 1, 1, 1, 1, 0 BIN8_FIN(
#define BIN8_EAT8_00111111 0, 0, 1, 1, 1, 1, 1, 1 BIN8_FIN(
#define BIN8_EAT8_01000000 0, 1, 0, 0, 0, 0, 0, 0 BIN8_FIN(
#define BIN8_EAT8_01000001 0, 1, 0, 0, 0, 0, 0, 1 BIN8_FIN(
#define BIN8_EAT8_01000010 0, 1, 0, 0, 0, 0, 1, 0 BIN8_FIN(
#define BIN8_EAT8_01000011 0, 1, 0, 0, 0, 0, 1, 1 BIN8_FIN(
#define BIN8_EAT8_01000100 0, 1, 0, 0, 0, 1, 0, 0 BIN8_FIN(
#define BIN8_EAT8_01000101 0, 1, 0, 0, 0, 1, 0, 1 BIN8_FIN(
#define BIN8_EAT8_01000110 0, 1, 0, 0, 0, 1, 1, 0 BIN8_FIN(
#define BIN8_EAT8_01000111 0, 1, 0, 0, 0, 1, 1, 1 BIN8_FIN(
#define BIN8_EAT8_01001000 0, 1, 0, 0, 1, 0, 0, 0 BIN8_FIN(
#define BIN8_EAT8_01001001 0, 1, 0, 0, 1, 0, 0, 1 BIN8_FIN(
#define BIN8_EAT8_01001010 0, 1, 0, 0, 1, 0, 1, 0 BIN8_FIN(
#define BIN8_EAT8_01001011 0, 1, 0, 0, 1, 0, 1, 1 BIN8_FIN(
#define BIN8_EAT8_01001100 0, 1, 0, 0, 1, 1, 0, 0 BIN8_FIN(
#define BIN8_EAT8_01001101 0, 1, 0, 0, 1, 1, 0, 1 BIN8_FIN(
#define BIN8_EAT8_01001110 0, 1, 0, 0, 1, 1, 1, 0 BIN8_FIN(
#define BIN8_EAT8_01001111 0, 1, 0, 0, 1, 1, 1, 1 BIN8_FIN(
#define BIN8_EAT8_01010000 0, 1, 0, 1, 0, 0, 0, 0 BIN8_FIN(
#define BIN8_EAT8_01010001 0, 1, 0, 1, 0, 0, 0, 1 BIN8_FIN(
#define BIN8_EAT8_01010010 0, 1, 0, 1, 0, 0, 1, 0 BIN8_FIN(
#define BIN8_EAT8_01010011 0, 1, 0, 1, 0, 0, 1, 1 BIN8_FIN(
#define BIN8_EAT8_01010100 0, 1, 0, 1, 0, 1, 0, 0 BIN8_FIN(
#define BIN8_EAT8_01010101 0, 1, 0, 1, 0, 1, 0, 1 BIN8_FIN(
#define BIN8_EAT8_01010110 0, 1, 0, 1, 0, 1, 1, 0 BIN8_FIN(
#define BIN8_EAT8_01010111 0, 1, 0, 1, 0, 1, 1, 1 BIN8_FIN(
#define BIN8_EAT8_01011000 0, 1, 0, 1, 1, 0, 0, 0 BIN8_FIN(
#define BIN8_EAT8_01011001 0, 1, 0, 1, 1, 0, 0, 1 BIN8_FIN(
#define BIN8_EAT8_01011010 0, 1, 0, 1, 1, 0, 1, 0 BIN8_FIN(
#define BIN8_EAT8_01011011 0, 1, 0, 1, 1, 0, 1, 1 BIN8_FIN(
#define BIN8_EAT8_01011100 0, 1, 0, 1, 1, 1, 0, 0 BIN8_FIN(
#define BIN8_EAT8_01011101 0, 1, 0, 1, 1, 1, 0, 1 BIN8_FIN(
#define BIN8_EAT8_01011110 0, 1, 0, 1, 1, 1, 1, 0 BIN8_FIN(
#define BIN8_EAT8_01011111 0, 1, 0, 1, 1, 1, 1, 1 BIN8_FIN(
#define BIN8_EAT8_01100000 0, 1, 1, 0, 0, 0, 0, 0 BIN8_FIN(
#define BIN8_EAT8_01100001 0, 1, 1, 0, 0, 0, 0, 1 BIN8_FIN(
#define BIN8_EAT8_01100010 0, 1, 1, 0, 0, 0, 1, 0 BIN8_FIN(
#define BIN8_EAT8_01100011 0, 1, 1, 0, 0, 0, 1, 1 BIN8_FIN(
#define BIN8_EAT8_01100100 0, 1, 1, 0, 0, 1, 0, 0 BIN8_FIN(
#define BIN8_EAT8_01100101 0, 1, 1, 0, 0, 1, 0, 1 BIN8_FIN(
#define BIN8_EAT8_01100110 0, 1, 1, 0, 0, 1, 1, 0 BIN8_FIN(
#define BIN8_EAT8_01100111 0, 1, 1, 0, 0, 1, 1, 1 BIN8_FIN(
#define BIN8_EAT8_01101000 0, 1, 1, 0, 1, 0, 0, 0 BIN8_FIN(
#define BIN8_EAT8_01101001 0, 1, 1, 0, 1, 0, 0, 1 BIN8_FIN(
#define BIN8_EAT8_01101010 0, 1, 1, 0, 1, 0, 1, 0 BIN8_FIN(
#define BIN8_EAT8_01101011 0, 1, 1, 0, 1, 0, 1, 1 BIN8_FIN(
#define BIN8_EAT8_01101100 0, 1, 1, 0, 1, 1, 0, 0 BIN8_FIN(
#define BIN8_EAT8_01101101 0, 1, 1, 0, 1, 1, 0, 1 BIN8_FIN(
#define BIN8_EAT8_01101110 0, 1, 1, 0, 1, 1, 1, 0 BIN8_FIN(
#define BIN8_EAT8_01101111 0, 1, 1, 0, 1, 1, 1, 1 BIN8_FIN(
#define BIN8_EAT8_01110000 0, 1, 1, 1, 0, 0, 0, 0 BIN8_FIN(
#define BIN8_EAT8_01110001 0, 1, 1, 1, 0, 0, 0, 1 BIN8_FIN(
#define BIN8_EAT8_01110010 0, 1, 1, 1, 0, 0, 1, 0 BIN8_FIN(
#define BIN8_EAT8_01110011 0, 1, 1, 1, 0, 0, 1, 1 BIN8_FIN(
#define BIN8_EAT8_01110100 0, 1, 1, 1, 0, 1, 0, 0 BIN8_FIN(
#define BIN8_EAT8_01110101 0, 1, 1, 1, 0, 1, 0, 1 BIN8_FIN(
#define BIN8_EAT8_01110110 0, 1, 1, 1, 0, 1, 1, 0 BIN8_FIN(
#define BIN8_EAT8_01110111 0, 1, 1, 1, 0, 1, 1, 1 BIN8_FIN(
#define BIN8_EAT8_01111000 0, 1, 1, 1, 1, 0, 0, 0 BIN8_FIN(
#define BIN8_EAT8_01111001 0, 1, 1, 1, 1, 0, 0, 1 BIN8_FIN(
#define BIN8_EAT8_01111010 0, 1, 1, 1, 1, 0, 1, 0 BIN8_FIN(
#define BIN8_EAT8_01111011 0, 1, 1, 1, 1, 0, 1, 1 BIN8_FIN(
#define BIN8_EAT8_01111100 0, 1, 1, 1, 1, 1, 0, 0 BIN8_FIN(
#define BIN8_EAT8_01111101 0, 1, 1, 1, 1, 1, 0, 1 BIN8_FIN(
#define BIN8_EAT8_01111110 0, 1, 1, 1, 1, 1, 1, 0 BIN8_FIN(
#define BIN8_EAT8_01111111 0, 1, 1, 1, 1, 1, 1, 1 BIN8_FIN(
#define BIN8_EAT8_10000000 1, 0, 0, 0, 0, 0, 0, 0 BIN8_FIN(
#define BIN8_EAT8_10000001 1, 0, 0, 0, 0, 0, 0, 1 BIN8_FIN(
#define BIN8_EAT8_10000010 1, 0, 0, 0, 0, 0, 1, 0 BIN8_FIN(
#define BIN8_EAT8_10000011 1, 0, 0, 0, 0, 0, 1, 1 BIN8_FIN(
#define BIN8_EAT8_10000100 1, 0, 0, 0, 0, 1, 0, 0 BIN8_FIN(
#define BIN8_EAT8_10000101 1, 0, 0, 0, 0, 1, 0, 1 BIN8_FIN(
#define BIN8_EAT8_10000110 1, 0, 0, 0, 0, 1, 1, 0 BIN8_FIN(
#define BIN8_EAT8_10000111 1, 0, 0, 0, 0, 1, 1, 1 BIN8_FIN(
#define BIN8_EAT8_10001000 1, 0, 0, 0, 1, 0, 0, 0 BIN8_FIN(
#define BIN8_EAT8_10001001 1, 0, 0, 0, 1, 0, 0, 1 BIN8_FIN(
#define BIN8_EAT8_10001010 1, 0, 0, 0, 1, 0, 1, 0 BIN8_FIN(
#define BIN8_EAT8_10001011 1, 0, 0, 0, 1, 0, 1, 1 BIN8_FIN(
#define BIN8_EAT8_10001100 1, 0, 0, 0, 1, 1, 0, 0 BIN8_FIN(
#define BIN8_EAT8_10001101 1, 0, 0, 0, 1, 1, 0, 1 BIN8_FIN(
#define BIN8_EAT8_10001110 1, 0, 0, 0, 1, 1, 1, 0 BIN8_FIN(
#define BIN8_EAT8_10001111 1, 0, 0, 0, 1, 1, 1, 1 BIN8_FIN(
#define BIN8_EAT8_10010000 1, 0, 0, 1, 0, 0, 0, 0 BIN8_FIN(
#define BIN8_EAT8_10010001 1, 0, 0, 1, 0, 0, 0, 1 BIN8_FIN(
#define BIN8_EAT8_10010010 1, 0, 0, 1, 0, 0, 1, 0 BIN8_FIN(
#define BIN8_EAT8_10010011 1, 0, 0, 1, 0, 0, 1, 1 BIN8_FIN(
#define BIN8_EAT8_10010100 1, 0, 0, 1, 0, 1, 0, 0 BIN8_FIN(
#define BIN8_EAT8_10010101 1, 0, 0, 1, 0, 1, 0, 1 BIN8_FIN(
#define BIN8_EAT8_10010110 1, 0, 0, 1, 0, 1, 1, 0 BIN8_FIN(
#define BIN8_EAT8_10010111 1, 0, 0, 1, 0, 1, 1, 1 BIN8_FIN(
#define BIN8_EAT8_10011000 1, 0, 0, 1, 1, 0, 0, 0 BIN8_FIN(
#define BIN8_EAT8_10011001 1, 0, 0, 1, 1, 0, 0, 1 BIN8_FIN(
#define BIN8_EAT8_10011010 1, 0, 0, 1, 1, 0, 1, 0 BIN8_FIN(
#define BIN8_EAT8_10011011 1, 0, 0, 1, 1, 0, 1, 1 BIN8_FIN(
#define BIN8_EAT8_10011100 1, 0, 0, 1, 1, 1, 0, 0 BIN8_FIN(
#define BIN8_EAT8_10011101 1, 0, 0, 1, 1, 1, 0, 1 BIN8_FIN(
#define BIN8_EAT8_10011110 1, 0, 0, 1, 1, 1, 1, 0 BIN8_FIN(
#define BIN8_EAT8_10011111 1, 0, 0, 1, 1, 1, 1, 1 BIN8_FIN(
#define BIN8_EAT8_10100000 1, 0, 1, 0, 0, 0, 0, 0 BIN8_FIN(
#define BIN8_EAT8_10100001 1, 0, 1, 0, 0, 0, 0, 1 BIN8_FIN(
#define BIN8_EAT8_10100010 1, 0, 1, 0, 0, 0, 1, 0 BIN8_FIN(
#define BIN8_EAT8_10100011 1, 0, 1, 0, 0, 0, 1, 1 BIN8_FIN(
#define BIN8_EAT8_10100100 1, 0, 1, 0, 0, 1, 0, 0 BIN8_FIN(
#define BIN8_EAT8_10100101 1, 0, 1, 0, 0, 1, 0, 1 BIN8_FIN(
#define BIN8_EAT8_10100110 1, 0, 1, 0, 0, 1, 1, 0 BIN8_FIN(
#define BIN8_EAT8_10100111 1, 0, 1, 0, 0, 1, 1, 1 BIN8_FIN(
#define BIN8_EAT8_10101000 1, 0, 1, 0, 1, 0, 0, 0 BIN8_FIN(
#define BIN8_EAT8_10101001 1, 0, 1, 0, 1, 0, 0, 1 BIN8_FIN(
#define BIN8_EAT8_10101010 1, 0, 1, 0, 1, 0, 1, 0 BIN8_FIN(
#define BIN8_EAT8_10101011 1, 0, 1, 0, 1, 0, 1, 1 BIN8_FIN(
#define BIN8_EAT8_10101100 1, 0, 1, 0, 1, 1, 0, 0 BIN8_FIN(
#define BIN8_EAT8_10101101 1, 0, 1, 0, 1, 1, 0, 1 BIN8_FIN(
#define BIN8_EAT8_10101110 1, 0, 1, 0, 1, 1, 1, 0 BIN8_FIN(
#define BIN8_EAT8_10101111 1, 0, 1, 0, 1, 1, 1, 1 BIN8_FIN(
#define BIN8_EAT8_10110000 1, 0, 1, 1, 0, 0, 0, 0 BIN8_FIN(
#define BIN8_EAT8_10110001 1, 0, 1, 1, 0, 0, 0, 1 BIN8_FIN(
#define BIN8_EAT8_10110010 1, 0, 1, 1, 0, 0, 1, 0 BIN8_FIN(
#define BIN8_EAT8_10110011 1, 0, 1, 1, 0, 0, 1, 1 BIN8_FIN(
#define BIN8_EAT8_10110100 1, 0, 1, 1, 0, 1, 0, 0 BIN8_FIN(
#define BIN8_EAT8_10110101 1, 0, 1, 1, 0, 1, 0, 1 BIN8_FIN(
#define BIN8_EAT8_10110110 1, 0, 1, 1, 0, 1, 1, 0 BIN8_FIN(
#define BIN8_EAT8_10110111 1, 0, 1, 1, 0, 1, 1, 1 BIN8_FIN(
#define BIN8_EAT8_10111000 1, 0, 1, 1, 1, 0, 0, 0 BIN8_FIN(
#define BIN8_EAT8_10111001 1, 0, 1, 1, 1, 0, 0, 1 BIN8_FIN(
#define BIN8_EAT8_10111010 1, 0, 1, 1, 1, 0, 1, 0 BIN8_FIN(
#define BIN8_EAT8_10111011 1, 0, 1, 1, 1, 0, 1, 1 BIN8_FIN(
#define BIN8_EAT8_10111100 1, 0, 1, 1, 1, 1, 0, 0 BIN8_FIN(
#define BIN8_EAT8_10111101 1, 0, 1, 1, 1, 1, 0, 1 BIN8_FIN(
#define BIN8_EAT8_10111110 1, 0, 1, 1, 1, 1, 1, 0 BIN8_FIN(
#define BIN8_EAT8_10111111 1, 0, 1, 1, 1, 1, 1, 1 BIN8_FIN(
#define BIN8_EAT8_11000000 1, 1, 0, 0, 0, 0, 0, 0 BIN8_FIN(
#define BIN8_EAT8_11000001 1, 1, 0, 0, 0, 0, 0, 1 BIN8_FIN(
#define BIN8_EAT8_11000010 1, 1, 0, 0, 0, 0, 1, 0 BIN8_FIN(
#define BIN8_EAT8_11000011 1, 1, 0, 0, 0, 0, 1, 1 BIN8_FIN(
#define BIN8_EAT8_11000100 1, 1, 0, 0, 0, 1, 0, 0 BIN8_FIN(
#define BIN8_EAT8_11000101 1, 1, 0, 0, 0, 1, 0, 1 BIN8_FIN(
#define BIN8_EAT8_11000110 1, 1, 0, 0, 0, 1, 1, 0 BIN8_FIN(
#define BIN8_EAT8_11000111 1, 1, 0, 0, 0, 1, 1, 1 BIN8_FIN(
#define BIN8_EAT8_11001000 1, 1, 0, 0, 1, 0, 0, 0 BIN8_FIN(
#define BIN8_EAT8_11001001 1, 1, 0, 0, 1, 0, 0, 1 BIN8_FIN(
#define BIN8_EAT8_11001010 1, 1, 0, 0, 1, 0, 1, 0 BIN8_FIN(
#define BIN8_EAT8_11001011 1, 1, 0, 0, 1, 0, 1, 1 BIN8_FIN(
#define BIN8_EAT8_11001100 1, 1, 0, 0, 1, 1, 0, 0 BIN8_FIN(
#define BIN8_EAT8_11001101 1, 1, 0, 0, 1, 1, 0, 1 BIN8_FIN(
#define BIN8_EAT8_11001110 1, 1, 0, 0, 1, 1, 1, 0 BIN8_FIN(
#define BIN8_EAT8_11001111 1, 1, 0, 0, 1, 1, 1, 1 BIN8_FIN(
#define BIN8_EAT8_11010000 1, 1, 0, 1, 0, 0, 0, 0 BIN8_FIN(
#define BIN8_EAT8_11010001 1, 1, 0, 1, 0, 0, 0, 1 BIN8_FIN(
#define BIN8_EAT8_11010010 1, 1, 0, 1, 0, 0, 1, 0 BIN8_FIN(
#define BIN8_EAT8_11010011 1, 1, 0, 1, 0, 0, 1, 1 BIN8_FIN(
#define BIN8_EAT8_11010100 1, 1, 0, 1, 0, 1, 0, 0 BIN8_FIN(
#define BIN8_EAT8_11010101 1, 1, 0, 1, 0, 1, 0, 1 BIN8_FIN(
#define BIN8_EAT8_11010110 1, 1, 0, 1, 0, 1, 1, 0 BIN8_FIN(
#define BIN8_EAT8_11010111 1, 1, 0, 1, 0, 1, 1, 1 BIN8_FIN(
#define BIN8_EAT8_11011000 1, 1, 0, 1, 1, 0, 0, 0 BIN8_FIN(
#define BIN8_EAT8_11011001 1, 1, 0, 1, 1, 0, 0, 1 BIN8_FIN(
#define BIN8_EAT8_11011010 1, 1, 0, 1, 1, 0, 1, 0 BIN8_FIN(
#define BIN8_EAT8_11011011 1, 1, 0, 1, 1, 0, 1, 1 BIN8_FIN(
#define BIN8_EAT8_11011100 1, 1, 0, 1, 1, 1, 0, 0 BIN8_FIN(
#define BIN8_EAT8_11011101 1, 1, 0, 1, 1, 1, 0, 1 BIN8_FIN(
#define BIN8_EAT8_11011110 1, 1, 0, 1, 1, 1, 1, 0 BIN8_FIN(
#define BIN8_EAT8_11011111 1, 1, 0, 1, 1, 1, 1, 1 BIN8_FIN(
#define BIN8_EAT8_11100000 1, 1, 1, 0, 0, 0, 0, 0 BIN8_FIN(
#define BIN8_EAT8_11100001 1, 1, 1, 0, 0, 0, 0, 1 BIN8_FIN(
#define BIN8_EAT8_11100010 1, 1, 1, 0, 0, 0, 1, 0 BIN8_FIN(
#define BIN8_EAT8_11100011 1, 1, 1, 0, 0, 0, 1, 1 BIN8_FIN(
#define BIN8_EAT8_11100100 1, 1, 1, 0, 0, 1, 0, 0 BIN8_FIN(
#define BIN8_EAT8_11100101 1, 1, 1, 0, 0, 1, 0, 1 BIN8_FIN(
#define BIN8_EAT8_11100110 1, 1, 1, 0, 0, 1, 1, 0 BIN8_FIN(
#define BIN8_EAT8_11100111 1, 1, 1, 0, 0, 1, 1, 1 BIN8_FIN(
#define BIN8_EAT8_11101000 1, 1, 1, 0, 1, 0, 0, 0 BIN8_FIN(
#define BIN8_EAT8_11101001 1, 1, 1, 0, 1, 0, 0, 1 BIN8_FIN(
#define BIN8_EAT8_11101010 1, 1, 1, 0, 1, 0, 1, 0 BIN8_FIN(
#define BIN8_EAT8_11101011 1, 1, 1, 0, 1, 0, 1, 1 BIN8_FIN(
#define BIN8_EAT8_11101100 1, 1, 1, 0, 1, 1, 0, 0 BIN8_FIN(
#define BIN8_EAT8_11101101 1, 1, 1, 0, 1, 1, 0, 1 BIN8_FIN(
#define BIN8_EAT8_11101110 1, 1, 1, 0, 1, 1, 1, 0 BIN8_FIN(
#define BIN8_EAT8_11101111 1, 1, 1, 0, 1, 1, 1, 1 BIN8_FIN(
#define BIN8_EAT8_11110000 1, 1, 1, 1, 0, 0, 0, 0 BIN8_FIN(
#define BIN8_EAT8_11110001 1, 1, 1, 1, 0, 0, 0, 1 BIN8_FIN(
#define BIN8_EAT8_11110010 1, 1, 1, 1, 0, 0, 1, 0 BIN8_FIN(
#define BIN8_EAT8_11110011 1, 1, 1, 1, 0, 0, 1, 1 BIN8_FIN(
#define BIN8_EAT8_11110100 1, 1, 1, 1, 0, 1, 0, 0 BIN8_FIN(
#define BIN8_EAT8_11110101 1, 1, 1, 1, 0, 1, 0, 1 BIN8_FIN(
#define BIN8_EAT8_11110110 1, 1, 1, 1, 0, 1, 1, 0 BIN8_FIN(
#define BIN8_EAT8_11110111 1, 1, 1, 1, 0, 1, 1, 1 BIN8_FIN(
#define BIN8_EAT8_11111000 1, 1, 1, 1, 1, 0, 0, 0 BIN8_FIN(
#define BIN8_EAT8_11111001 1, 1, 1, 1, 1, 0, 0, 1 BIN8_FIN(
#define BIN8_EAT8_11111010 1, 1, 1, 1, 1, 0, 1, 0 BIN8_FIN(
#define BIN8_EAT8_11111011 1, 1, 1, 1, 1, 0, 1, 1 BIN8_FIN(
#define BIN8_EAT8_11111100 1, 1, 1, 1, 1, 1, 0, 0 BIN8_FIN(
#define BIN8_EAT8_11111101 1, 1, 1, 1, 1, 1, 0, 1 BIN8_FIN(
#define BIN8_EAT8_11111110 1, 1, 1, 1, 1, 1, 1, 0 BIN8_FIN(
#define BIN8_EAT8_11111111 1, 1, 1, 1, 1, 1, 1, 1 BIN8_FIN(

/*

-----BEGIN PGP SIGNATURE-----

iQEzBAEBCAAdFiEERGuTZCqWmv5+0VD7fISBmK6T07sFAlt1pAUACgkQfISBmK6T
07uHbQf/SPf4q0+NP8G2ex39LTdV8PAuVdsi7xVrygYZghfoYywnp5DN2nPwL1H5
COjJ4LCKuKyRnCbi/JmfSZCOpcW4TJwdK229W1OiE7zLmXI4aP/noo/7aFKaQ29a
FcJvijrpqwRvCEk9KN4QZROY7na8ys+fkqBXf5HpgNodA8uzFVEVeY8tUJly6PGa
T4oejtm4+/f/HxbAd+HJgZ9ge0OwlTPW5hEHAYz2M0uSJdqDRN29dbFxN6de4i6V
Jzv8ZMUgU3qaU108aHKARgHCEIsQbPXuhBDzyxuRfIDskgtDEapE8bXf1alTU7Hd
6fAuvSTztKlOOsBZLj8iOsIyQH2nvw==
=hXPL
-----END PGP SIGNATURE-----
*/