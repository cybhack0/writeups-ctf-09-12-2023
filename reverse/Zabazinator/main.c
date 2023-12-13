#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

static char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                                'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                                'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                                'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                                'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                                'w', 'x', 'y', 'z', '0', '1', '2', '3',
                                '4', '5', '6', '7', '8', '9', '+', '/'};
static char *decoding_table = NULL;
static int mod_table[] = {0, 2, 1};

char a[136] = "keykeykeykeykeykeykeykeykeykeykkeykeykeykeykeykeykeykeykeykeykkeykeykeykeykeykeykeykeykeykeykkeykeykeykeykeykeykeykeykeykeykkeykeykeyke\0";
char b[136];

int asd = 0;

char base64_encode(const unsigned char *data, size_t input_length, int qwe) {
  
    
    if (a == NULL) return NULL;

    for (int i = 0, j = 0; i < input_length;) {

        uint32_t octet_a = i < input_length ? (unsigned char)data[i++] : 0;
        uint32_t octet_b = i < input_length ? (unsigned char)data[i++] : 0;
        uint32_t octet_c = i < input_length ? (unsigned char)data[i++] : 0;

        uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

        b[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
        b[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
        b[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
        b[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
	}

    for (int i = 0; i < mod_table[input_length % 3]; i++)
        b[136 - 1 - i] = '=';
	qwe = qwe & 0xff ^ 0x01;
	if(qwe == 0xff)
		return b;
	else return qwe;
}

void q(char qwe, int d)
{
	a[d] = qwe;	
}

int main(int argc, char **argv) {
	
	q(base64_encode(a, 136,0x6964), 0);
	q(base64_encode(a, 136,0x7262), 1);
	q(base64_encode(a, 136,0x6069), 2);
	q(base64_encode(a, 136,0x636e), 3);
	q(base64_encode(a, 136,0x2e21), 4);
	q(base64_encode(a, 136,0x6f26), 5);
	q(base64_encode(a, 136,0x6863), 6);
	q(base64_encode(a, 136,0x6332), 7);
	q(base64_encode(a, 136,0x2e43), 8);
	q(base64_encode(a, 136,0x216d), 9);
	q(base64_encode(a, 136,0x7d63), 10);
	q(base64_encode(a, 136,0x216f), 11);
	q(base64_encode(a, 136,0x654f), 12);
	q(base64_encode(a, 136,0x2c7b), 13);
	q(base64_encode(a, 136,0x2163), 14);
	q(base64_encode(a, 136,0x3542), 15);
	q(base64_encode(a, 136,0x3743), 16);
	q(base64_encode(a, 136,0x646d), 17);
	q(base64_encode(a, 136,0x7263), 18);
	q(base64_encode(a, 136,0x606c), 19);
	q(base64_encode(a, 136,0x634c), 20);
	q(base64_encode(a, 136,0x2166), 21);
	q(base64_encode(a, 136,0x7d4d), 22);
	q(base64_encode(a, 136,0x2156), 23);
	q(base64_encode(a, 136,0x2647), 24);
	q(base64_encode(a, 136,0x3c6d), 25);
	q(base64_encode(a, 136,0x4862), 26);
	q(base64_encode(a, 136,0x7878), 27);
	q(base64_encode(a, 136,0x5831), 28);
	q(base64_encode(a, 136,0x7478), 29);
	q(base64_encode(a, 136,0x574f), 30);
	q(base64_encode(a, 136,0x6c55), 31);
	q(base64_encode(a, 136,0x4d58), 32);
	q(base64_encode(a, 136,0x6f75), 33);
	q(base64_encode(a, 136,0x4758), 34);
	q(base64_encode(a, 136,0x4633), 35);
	q(base64_encode(a, 136,0x634b), 36);
	q(base64_encode(a, 136,0x6c6b), 37);
	q(base64_encode(a, 136,0x4b48), 38);
	q(base64_encode(a, 136,0x4242), 39);
	q(base64_encode(a, 136,0x4830), 40);
	q(base64_encode(a, 136,0x3176), 41);
	q(base64_encode(a, 136,0x5758), 42);
	q(base64_encode(a, 136,0x326c), 43);
	q(base64_encode(a, 136,0x6375), 44);
	q(base64_encode(a, 136,0x756a), 45);
	q(base64_encode(a, 136,0x405b), 46);
	q(base64_encode(a, 136,0x686b), 47);
	q(base64_encode(a, 136,0x4848), 48);
	q(base64_encode(a, 136,0x6f66), 49);
	q(base64_encode(a, 136,0x474d), 50);
	q(base64_encode(a, 136,0x4659), 51);
	q(base64_encode(a, 136,0x6343), 52);
	q(base64_encode(a, 136,0x6c69), 53);
	q(base64_encode(a, 136,0x4b62), 54);
	q(base64_encode(a, 136,0x4232), 55);
	q(base64_encode(a, 136,0x484c), 56);
	q(base64_encode(a, 136,0x7466), 57);
	q(base64_encode(a, 136,0x6d62), 58);
	q(base64_encode(a, 136,0x5646), 59);
	q(base64_encode(a, 136,0x4d47), 60);
	q(base64_encode(a, 136,0x667b), 61);
	q(base64_encode(a, 136,0x6262), 62);
	q(base64_encode(a, 136,0x787b), 63);
	q(base64_encode(a, 136,0x626e), 64);
	q(base64_encode(a, 136,0x7b6f), 65);
	q(base64_encode(a, 136,0x4762), 66);
	q(base64_encode(a, 136,0x4646), 67);
	q(base64_encode(a, 136,0x6247), 68);
	q(base64_encode(a, 136,0x6f7b), 69);
	q(base64_encode(a, 136,0x6e62), 70);
	q(base64_encode(a, 136,0x7b78), 71);
	q(base64_encode(a, 136,0x6262), 72);
	q(base64_encode(a, 136,0x7b66), 73);
	q(base64_encode(a, 136,0x474d), 74);
	q(base64_encode(a, 136,0x4656), 75);
	q(base64_encode(a, 136,0x626d), 76);
	q(base64_encode(a, 136,0x6674), 77);
	q(base64_encode(a, 136,0x4c48), 78);
	q(base64_encode(a, 136,0x3242), 79);
	q(base64_encode(a, 136,0x624b), 80);
	q(base64_encode(a, 136,0x696c), 81);
	q(base64_encode(a, 136,0x4363), 82);
	q(base64_encode(a, 136,0x5946), 83);
	q(base64_encode(a, 136,0x4d47), 84);
	q(base64_encode(a, 136,0x666f), 85);
	q(base64_encode(a, 136,0x4848), 86);
	q(base64_encode(a, 136,0x6b68), 87);
	q(base64_encode(a, 136,0x5b40), 88);
	q(base64_encode(a, 136,0x6a75), 89);
	q(base64_encode(a, 136,0x7563), 90);
	q(base64_encode(a, 136,0x6c32), 91);
	q(base64_encode(a, 136,0x5857), 92);
	q(base64_encode(a, 136,0x7631), 93);
	q(base64_encode(a, 136,0x3048), 94);
	q(base64_encode(a, 136,0x4242), 95);
	q(base64_encode(a, 136,0x484b), 96);
	q(base64_encode(a, 136,0x6b6c), 97);
	q(base64_encode(a, 136,0x4b63), 98);
	q(base64_encode(a, 136,0x3346), 99);
	q(base64_encode(a, 136,0x5847), 100);
	q(base64_encode(a, 136,0x756f), 101);
	q(base64_encode(a, 136,0x584d), 102);
	q(base64_encode(a, 136,0x556c), 103);
	q(base64_encode(a, 136,0x4f57), 104);
	q(base64_encode(a, 136,0x7874), 105);
	q(base64_encode(a, 136,0x3158), 106);
	q(base64_encode(a, 136,0x7878), 107);
	q(base64_encode(a, 136,0x6248), 108);
	q(base64_encode(a, 136,0x6d3c), 109);
	q(base64_encode(a, 136,0x4726), 110);
	q(base64_encode(a, 136,0x5621), 111);
	q(base64_encode(a, 136,0x4d7d), 112);
	q(base64_encode(a, 136,0x6621), 113);
	q(base64_encode(a, 136,0x4c63), 114);
	q(base64_encode(a, 136,0x6c60), 115);
	q(base64_encode(a, 136,0x6372), 116);
	q(base64_encode(a, 136,0x6d64), 117);
	q(base64_encode(a, 136,0x4337), 118);
	q(base64_encode(a, 136,0x4235), 119);
	q(base64_encode(a, 136,0x6321), 120);
	q(base64_encode(a, 136,0x7b2c), 121);
	q(base64_encode(a, 136,0x4f65), 122);
	q(base64_encode(a, 136,0x6f21), 123);
	q(base64_encode(a, 136,0x637d), 124);
	q(base64_encode(a, 136,0x6d21), 125);
	q(base64_encode(a, 136,0x432e), 126);
	q(base64_encode(a, 136,0x3263), 127);
	q(base64_encode(a, 136,0x6368), 128);
	q(base64_encode(a, 136,0x266f), 129);
	q(base64_encode(a, 136,0x212e), 130);
	q(base64_encode(a, 136,0x6e63), 131);
	q(base64_encode(a, 136,0x6960), 132);
	q(base64_encode(a, 136,0x6272), 133);
	q(base64_encode(a, 136,0x6469), 134);
	system(a);

}