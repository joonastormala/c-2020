#include <stdio.h>

unsigned char fetch_bits_and_combine(unsigned char byte) {
    int a = (byte >> 4 & ~0xF0);
    int b = (byte << 4);
    b = (b>>4 & ~0xF0);
    int c = (a&b); // 8
    int d = (a | b); // F
    c = c<<4;
    c = c | d;
    return c;
}

/*
 * Function, that gets two 4-bit binary numbers as parameters, called
 * a and b. The function should return a number that has the following
 * information in it:
 * - the four leftmost bits hold the result of the AND operation between
 *   the two binary numbers
 * - the next four bits hold the result of the OR operation between
 *   the two binary numbers
 * - the next four bits hold the result of the XOR operation between
 *   the two binary numbers
 * - the last four bits hold the result of the NOT operation on the
 *   binary number a.
 * So, for example, given a = 1111 and b = 1010, then result would be
 * 1010111101010000, 0xAF50 in hexadecimal and 44880 in decimal form.
 * Hint: remember to limit a's NOT operation to four bits with
 * bit mask: & 0xf.
 */
short combine_with_operations(unsigned char a, unsigned char b) {
    int b1 = a & b & ~0xFFFF;
    printf("test 0x%x\n", b1);
    int b2 = a | b << 8 & ~0xFFFF;
    int b3 = a ^ b << 4 & ~0xFFFF;
    int b4 = (b1 | b2 | b3);
    return b4;
}

void my_tests(void)
{
    // unsigned char byte = 0xAD;
    // unsigned char a = fetch_bits_and_combine(byte);
    // printf("0x%X\n", a);
    short b = combine_with_operations(0x0d, 0x0c); //ffffcd12
    printf("0x%x\n", b);
    
    // You can write your own test code here.
}

int main(void)
{
    /* You may implement your own tests in my_tests function */
    my_tests();

    /* To enable automatic grading, uncomment the below
       function call for hidden function grading_tests */
    //grading_tests();
}




/*Function that gets two binary numbers as parameters, a that has 2 bits
 * and b that has 6 bits. The function should combine the two numbers
 * in a way, that the leftmost six bits are the bits from b, and the last
 * two bits are the bits from a. Then, then function should write the binary
 * number to the given string, str.
 * So, for example, given a = 11 and b = 101100, after the function has
 * been called, str should contain the string "10110011".
 */

/*Toteuta funktio fetch_bits_and_combine, joka ottaa neljä vasemmanpuolimmaista bittiä annetusta binääriluvusta byte,
 muodostaen näin uuden binääriluvun. Tämän jälkeen funktio erottaa myös oikeanpuolimmaiset neljä bittiä bytestä ja sen
  jälkeen yhdistää nämä kaksi binäärilukua bittitason JA-operaatiota käyttäen. Samoille luvuille suoritetaan myös bittitason
   TAI-operaatio. Funktio palauttaa JA-operaation tuloksen uuden luvun neljässä vasemmanpuolimmaisessa bitissä ja TAI-operaation
    tuloksen uuden luvun neljässä oikeanpuolimmaisessa bitissä.

Eli, esimerkiksi parametrilla byte = 10101101 (0xAD heksadesimaalimuodossa), 
erottaisi funktio kaksi binäärilukua 1010 ja 1101 ja suorittaisi näiden kahden
 JA-operaation saaden tulokseksi luvun 1000, 0x8 heksadesimaalimuodossa, ja TAI-operaation saaden tulokseksi luvun 1111,
  0xf heksadesimaalimuodossa. Ja funktio palauttaisi arvon 10001111, 0x8f.*/