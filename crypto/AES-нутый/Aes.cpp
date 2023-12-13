#include <iostream>
#include <string>
#include <fstream>

// Matrix for replacing two-byte words in a function SubBytes
const unsigned char SBox[64][64] = {
    {0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76},
    {0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0},
    {0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15},
    {0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75},
    {0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84},
    {0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf},
    {0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8},
    {0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2},
    {0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73},
    {0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb},
    {0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79},
    {0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08},
    {0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a},
    {0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e},
    {0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf},
    {0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16}
};

// Matrix for replacing two-byte words in a function InvSubBytes
const unsigned char InvSBox[64][64] = {
    {0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb},
    {0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb},
    {0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e},
    {0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25},
    {0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92},
    {0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84},
    {0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06},
    {0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b},
    {0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73},
    {0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e},
    {0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b},
    {0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4},
    {0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f},
    {0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef},
    {0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61},
    {0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d}
};

// Matrix for creating a key schedule
const unsigned char Rcon[10][4] = {
    {0x01, 0x00, 0x00, 0x00},
    {0x02, 0x00, 0x00, 0x00},
    {0x04, 0x00, 0x00, 0x00},
    {0x08, 0x00, 0x00, 0x00},
    {0x10, 0x00, 0x00, 0x00},
    {0x20, 0x00, 0x00, 0x00},
    {0x40, 0x00, 0x00, 0x00},
    {0x80, 0x00, 0x00, 0x00},
    {0x1b, 0x00, 0x00, 0x00},
    {0x36, 0x00, 0x00, 0x00},
};

// Enum with availavble key sizes. 128 bit, 192 bit, 256 bit.
enum AES_KeySize
{
    AES_128 = 16,
    AES_192 = 24,
    AES_256 = 32
};

// Enum with available cypher modes. ECB, CBC, PCBC
enum AES_Mode
{
    ECB,
    CBC,
    PCBC,
    CFB,
    OFB
};

// Convert int to string with hex form of this number
template <class T>
std::string IntToHexForm(T a)
{
    std::string res;

    for (int i = 0; i < sizeof(T); i++)
    {
        int lowByte = a % 16;
        a /= 16;

        int highByte = a % 16;
        a /= 16;

        if (highByte > 9)
            res += 'a' + highByte - 10;
        else
            res += '0' + highByte;

        if (lowByte > 9)
            res += 'a' + lowByte - 10;
        else
            res += '0' + lowByte;
    }

    return res;
}

// Convert plain text to hex text
std::string RegularStringToHexRepresentation(const std::string& str)
{
    std::string res;
    for (auto it : str)
        res += IntToHexForm((unsigned char)it);
    return res;
}

// Convert hex to plain text
std::string HexRepresentationToRegularString(const std::string& str)
{
    if (str.length() % 2 != 0)  return "";

    std::string res;
    unsigned char hi, low;
    for (int i = 0; i < str.length(); i += 2)
    {
        if (str[i] >= '0' && str[i] <= '9') hi = str[i] - '0';
        if (str[i] >= 'a' && str[i] <= 'f') hi = str[i] - 'a' + 10;
        if (str[i] >= 'A' && str[i] <= 'F') hi = str[i] - 'A' + 10;

        if (str[i + 1] >= '0' && str[i + 1] <= '9') low = str[i + 1] - '0';
        if (str[i + 1] >= 'a' && str[i + 1] <= 'f') low = str[i + 1] - 'a' + 10;
        if (str[i + 1] >= 'A' && str[i + 1] <= 'F') low = str[i + 1] - 'A' + 10;

        res += hi * 16 + low;
    }
    return res;
}

// The function performs xor for the corresponding string characters
inline std::string XorString(const std::string& str1, const std::string& str2)
{
    if (str1.length() != str2.length()) return "";

    std::string res;

    for (int i = 0; i < str1.length(); i++)
        res += str1[i] ^ str2[i];

    return res;
}

// Calculate PKCS#7 padding to data string
inline std::string CalculateDataPadding(const std::string& data)
{
    int paddingLength = 16 - (data.length() % 16);

    std::string res;

    for (int i = 0; i < paddingLength; i++)
        res += paddingLength;

    return res;
}

// Add PKCS#7 padding to key string
inline std::string AddPaddingToKey(AES_KeySize keySize, std::string key)
{
    if (key.length() == keySize) return key;
    if (key.length() > keySize) return key.substr(0, keySize);

    std::string res;

    for (int i = 0; i < (keySize - key.length()); i++)
        res += (keySize - key.length());

    return key + res;
}

// Remove PKCS#7 padding from string
inline void RemovePaddingFromData(std::string& str)
{
    unsigned char paddingLength = str.back();
    for (int i = 0; i < paddingLength; ++i) str.pop_back();
}

// Galois Field (256) multiplication of two bytes
unsigned char GaloisMul(unsigned char a, unsigned char b)
{
    unsigned char p = 0;

    for (int counter = 0; counter < 8; counter++)
    {
        if ((b & 1) != 0)
            p ^= a;

        bool hi_bit_set = (a & 0x80) != 0;

        a <<= 1;

        if (hi_bit_set)
            a ^= 0x1B; /* x^8 + x^4 + x^3 + x + 1 */

        b >>= 1;
    }

    return p;
}

// Process 16 bytes in 4x4 matrix with unsigned chars. Change unsigned chars to chars from const SBox matrix
inline void SubBytes(unsigned char* mat)
{
    for (int i = 0; i < 16; i++)
        mat[i] = SBox[mat[i] / 16][mat[i] % 16];
}

// Process 16 bytes in 4x4 matrix with unsigned chars. Change unsigned chars to chars from const InvSBox matrix
inline void InvSubBytes(unsigned char* mat)
{
    for (int i = 0; i < 16; i++)
        mat[i] = InvSBox[mat[i] / 16][mat[i] % 16];
}

// Process 16 bytes in 4x4 matrix with unsigned chars. Circular shift of elements to the left. 0 line << 0. 1 line << 1. 2 line << 2. 3 line << 3.
inline void ShiftRows(unsigned char* mat)
{
    // Second line shifts on 1 to left
    unsigned char tmp1 = mat[4];
    mat[4] = mat[5]; mat[5] = mat[6]; mat[6] = mat[7]; mat[7] = tmp1;

    // Third line shifts on 2 left
    unsigned char tmp2 = mat[9]; tmp1 = mat[8];
    mat[8] = mat[10]; mat[9] = mat[11]; mat[10] = tmp1; mat[11] = tmp2;

    // Fourth line shifts on 3 left or thar equls shift on 1 right
    tmp1 = mat[15];
    mat[15] = mat[14]; mat[14] = mat[13]; mat[13] = mat[12]; mat[12] = tmp1;
}

// Process 16 bytes in 4x4 matrix with unsigned chars. Circular shift of elements to the right. 0 line >> 0. 1 line >> 1. 2 line >> 2. 3 line >> 3.
inline void InvShiftRows(unsigned char* mat)
{
    // Second line shifts on 1 to right
    unsigned char tmp1 = mat[7];
    mat[7] = mat[6]; mat[6] = mat[5]; mat[5] = mat[4]; mat[4] = tmp1;

    // Third line shifts on 2 right
    unsigned char tmp2 = mat[9]; tmp1 = mat[8];
    mat[8] = mat[10]; mat[9] = mat[11]; mat[10] = tmp1; mat[11] = tmp2;

    // Fourth line shifts on 3 right or thar equls shift on 1 left
    tmp1 = mat[12];
    mat[12] = mat[13]; mat[13] = mat[14]; mat[14] = mat[15]; mat[15] = tmp1;
}

// Process 16 bytes in 4x4 matrix with unsigned chars. Make GF(2^8) operations
inline void MixColumns(unsigned char* mat)
{
    unsigned char a, b, c, d;
    // Mix every four columns
    for (int i = 0; i < 4; i++)
    {
        // Transformation matrix:
        // 2 3 1 1
        // 1 2 3 1
        // 1 1 2 3
        // 3 1 1 2
        a = GaloisMul(2, mat[i]) ^ GaloisMul(3, mat[4 + i]) ^ mat[8 + i] ^ mat[12 + i];
        b = mat[i] ^ GaloisMul(2, mat[4 + i]) ^ GaloisMul(3, mat[8 + i]) ^ mat[12 + i];
        c = mat[i] ^ mat[4 + i] ^ GaloisMul(2, mat[8 + i]) ^ GaloisMul(3, mat[12 + i]);
        d = GaloisMul(3, mat[i]) ^ mat[4 + i] ^ mat[8 + i] ^ GaloisMul(2, mat[12 + i]);

        mat[i] = a;
        mat[4 + i] = b;
        mat[8 + i] = c;
        mat[12 + i] = d;
    }
}

// Process 16 bytes in 4x4 matrix with unsigned chars. Make GF(2^8) operations
inline void InvMixColumns(unsigned char* mat)
{
    unsigned char a, b, c, d;
    // Mix every four columns
    for (int i = 0; i < 4; i++)
    {
        // Transformation matrix:
        // 14 11 13 9
        // 9 14 11 13
        // 13 9 11 13
        // 11 13 9 14
        a = GaloisMul(14, mat[i]) ^ GaloisMul(11, mat[4 + i]) ^ GaloisMul(13, mat[8 + i]) ^ GaloisMul(9, mat[12 + i]);
        b = GaloisMul(9, mat[i]) ^ GaloisMul(14, mat[4 + i]) ^ GaloisMul(11, mat[8 + i]) ^ GaloisMul(13, mat[12 + i]);
        c = GaloisMul(13, mat[i]) ^ GaloisMul(9, mat[4 + i]) ^ GaloisMul(14, mat[8 + i]) ^ GaloisMul(11, mat[12 + i]);
        d = GaloisMul(11, mat[i]) ^ GaloisMul(13, mat[4 + i]) ^ GaloisMul(9, mat[8 + i]) ^ GaloisMul(14, mat[12 + i]);

        mat[i] = a;
        mat[4 + i] = b;
        mat[8 + i] = c;
        mat[12 + i] = d;
    }
}

// Process 16 bytes in 4x4 matrix with unsigned chars. Kreate key shedule
inline std::string KeyExpansion(AES_KeySize keySize, const std::string& key)
{
    int keySheduleLength, Nk;
    switch (keySize)
    {
    case AES_128: keySheduleLength = 44; Nk = 4; break;
    case AES_192: keySheduleLength = 52; Nk = 6; break;
    case AES_256: keySheduleLength = 60; Nk = 8; break;
    }

    std::string KeyShedule = key;

    for (int i = Nk; i < keySheduleLength; i++)
    {
        // Get previous column element
        unsigned char w[4] = { (unsigned char)KeyShedule[i * 4 - 4], (unsigned char)KeyShedule[i * 4 - 3], (unsigned char)KeyShedule[i * 4 - 2], (unsigned char)KeyShedule[i * 4 - 1] };

        // Check if column multiply for 4
        if (i % Nk == 0)
        {
            // Circular shift in column
            unsigned char tmp = w[0];
            w[0] = w[1]; w[1] = w[2]; w[2] = w[3]; w[3] = tmp;

            // Change unsigned chars to chars in const SBox matrix
            w[0] = SBox[w[0] / 16][w[0] % 16];
            w[1] = SBox[w[1] / 16][w[1] % 16];
            w[2] = SBox[w[2] / 16][w[2] % 16];
            w[3] = SBox[w[3] / 16][w[3] % 16];

            // Xoring
            w[0] = w[0] ^ Rcon[i / Nk - 1][0] ^ KeyShedule[i * 4 - Nk * 4];
            w[1] = w[1] ^ Rcon[i / Nk - 1][1] ^ KeyShedule[i * 4 - Nk * 4 + 1];
            w[2] = w[2] ^ Rcon[i / Nk - 1][2] ^ KeyShedule[i * 4 - Nk * 4 + 2];
            w[3] = w[3] ^ Rcon[i / Nk - 1][3] ^ KeyShedule[i * 4 - Nk * 4 + 3];
        }
        else
        {
            if (keySize == AES_256 && (i + 4) % 8 == 0)
            {
                // Change unsigned chars to chars in const SBox matrix
                w[0] = SBox[w[0] / 16][w[0] % 16];
                w[1] = SBox[w[1] / 16][w[1] % 16];
                w[2] = SBox[w[2] / 16][w[2] % 16];
                w[3] = SBox[w[3] / 16][w[3] % 16];
            }

            // Xoring
            w[0] = w[0] ^ KeyShedule[i * 4 - Nk * 4];
            w[1] = w[1] ^ KeyShedule[i * 4 - Nk * 4 + 1];
            w[2] = w[2] ^ KeyShedule[i * 4 - Nk * 4 + 2];
            w[3] = w[3] ^ KeyShedule[i * 4 - Nk * 4 + 3];
        }

        KeyShedule += w[0];
        KeyShedule += w[1];
        KeyShedule += w[2];
        KeyShedule += w[3];
    }

    return KeyShedule;
}

// This function simply does a bitwise xor of each element of the string mat1 with the corresponding element of the string mat2
inline void AddRoundKey(unsigned char* state, const std::string& key)
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            state[j * 4 + i] = state[j * 4 + i] ^ (unsigned char)key[i * 4 + j];
}

// Encrypts 64 bytes block using AES algo
inline std::string AES_EncryptStep(const std::string& data, const std::string& keyShedule, int roundsCount)
{
    unsigned char state[4][4];

    // Save data from string to state matrix
    for (int j = 0; j < 4; j++)
        for (int k = 0; k < 4; k++)
            state[k][j] = data[j * 4 + k];

    AddRoundKey(&state[0][0], keyShedule.substr(0, 16));
    for (int j = 1; j < roundsCount; j++)
    {
        SubBytes(&state[0][0]);
        ShiftRows(&state[0][0]);
        MixColumns(&state[0][0]);
        AddRoundKey(&state[0][0], keyShedule.substr(j * 16, 16));
    }

    SubBytes(&state[0][0]);
    ShiftRows(&state[0][0]);
    AddRoundKey(&state[0][0], keyShedule.substr(keyShedule.length() - 16, 16));

    // Save data from state matrix to string
    std::string res;
    for (int j = 0; j < 4; j++)
        for (int k = 0; k < 4; k++)
            res += state[k][j];

    return res;
}

// Encryption function. The data and key will be aligned using the algorithm PKCS#7
// If the key is greater than the value specified in keySize, the first keySize bits or keySize/8 characters will be taken from it
// If the any other mode than ECB set IV must be set
std::string AES_Encrypt(AES_KeySize keySize, AES_Mode aes_mode, const std::string& data, std::string key, std::string IV = "")
{
    if (data.length() == 0 || key.length() == 0 || (aes_mode != ECB && IV.length() == 0))
    {
        if (data.length() == 0)
            std::cerr << "In AES_Encrypt function: Data length cannot be zero" << std::endl;

        if (key.length() == 0)
            std::cerr << "In AES_Encrypt function: Key length cannot be zero" << std::endl;

        if (aes_mode == CBC && IV.length() == 0)
            std::cerr << "In AES_Encrypt function: IV(initialization vector) length cannot be zero" << std::endl;

        throw;
    }

    int roundsCount;
    switch (keySize)
    {
    case AES_128: roundsCount = 10; break;
    case AES_192: roundsCount = 12; break;
    case AES_256: roundsCount = 14; break;
    }

    key = AddPaddingToKey(keySize, key);
    IV = AddPaddingToKey(AES_128, IV);

    std::string stateIV = IV;
    std::string keyShedule = KeyExpansion(keySize, key);
    std::string res;

    for (int i = 0; i <= data.length() / 16; i++)
    {   
        std::string cycleData; 
        std::string dataChunk;

        if (i == data.length() / 16)
            cycleData = data.substr(i * 16) + CalculateDataPadding(data);
        else
            cycleData = data.substr(i * 16, 16);

        switch (aes_mode)
        {
        case ECB: dataChunk = cycleData; break;
        case CBC: dataChunk = XorString(stateIV, cycleData); break;
        case PCBC: dataChunk = XorString(stateIV, cycleData); break;
        case CFB: dataChunk = stateIV; break;
        case OFB: dataChunk = stateIV; break;
        }

        std::string state = AES_EncryptStep(dataChunk, keyShedule, roundsCount);

        switch (aes_mode)
        {
        case ECB: res += state; break;
        case CBC:
            stateIV = state;
            res += state;
            break;
        case PCBC:
            stateIV = XorString(state, cycleData);
            res += state;
            break;
        case CFB:
            stateIV = XorString(state, cycleData);
            res += stateIV;
            break;
        case OFB:
            stateIV = state;
            res += XorString(state, cycleData);
            break;
        }
    }

    return res;
}

// Decrypts 64 bytes block using AES algo
inline std::string AES_DecryptStep(const std::string& data, const std::string& keyShedule, int roundsCount)
{
    unsigned char state[4][4];

    // Save data from string to state matrix
    for (int j = 0; j < 4; j++)
        for (int k = 0; k < 4; k++)
            state[k][j] = data[j * 4 + k];

    AddRoundKey(&state[0][0], keyShedule.substr(keyShedule.length() - 16));

    for (int j = 1; j < roundsCount; j++)
    {
        InvShiftRows(&state[0][0]);
        InvSubBytes(&state[0][0]);
        AddRoundKey(&state[0][0], keyShedule.substr((roundsCount - j) * 16, 16));
        InvMixColumns(&state[0][0]);
    }

    InvShiftRows(&state[0][0]);
    InvSubBytes(&state[0][0]);
    AddRoundKey(&state[0][0], keyShedule.substr(0, 16));

    // Save data from state matrix to string
    std::string res;
    for (int j = 0; j < 4; j++)
        for (int k = 0; k < 4; k++)
            res += state[k][j];

    return res;
}

// Encryption function. The data and key will be aligned using the algorithm PKCS#7
// If the any other mode than ECB set IV must be set
std::string AES_Decrypt(AES_KeySize keySize, AES_Mode aes_mode, const std::string& data, std::string key, std::string IV = "")
{
    if (data.length() == 0 || key.length() == 0 || (aes_mode != ECB && IV.length() == 0))
    {
        if (data.length() == 0)
            std::cerr << "In AES_Decrypt function: Data length cannot be zero" << std::endl;

        if (key.length() == 0)
            std::cerr << "In AES_Decrypt function: Key length cannot be zero" << std::endl;

        if (aes_mode == CBC && IV.length() == 0)
            std::cerr << "In AES_Decrypt function: IV(initialization vector) length cannot be zero" << std::endl;

        throw;
    }

    int roundsCount;
    switch (keySize)
    {
    case AES_128: roundsCount = 10; break;
    case AES_192: roundsCount = 12; break;
    case AES_256: roundsCount = 14; break;
    }

    key = AddPaddingToKey(keySize, key);
    IV = AddPaddingToKey(AES_128, IV);

    std::string stateIV = IV;
    std::string keyShedule = KeyExpansion(keySize, key);
    std::string res;

    for (int i = 0; i < data.length() / 16; i++)
    {
        std::string cycleData = data.substr(i * 16, 16);
        std::string dataChunk;

        switch (aes_mode)
        {
        case ECB: dataChunk = cycleData; break;
        case CBC: dataChunk = cycleData; break;
        case PCBC: dataChunk = cycleData; break;
        case CFB: dataChunk = stateIV; break;
        case OFB: dataChunk = stateIV; break;
        }

        std::string state;

        switch (aes_mode)
        {
        case ECB:
        case CBC:
        case PCBC: state = AES_DecryptStep(dataChunk, keyShedule, roundsCount); break;
        case CFB:
        case OFB: state = AES_EncryptStep(dataChunk, keyShedule, roundsCount); break;
        }

        switch (aes_mode)
        {
        case ECB: res += state; break;
        case CBC:
            res += XorString(stateIV, state);
            stateIV = cycleData;
            break;
        case PCBC:
            stateIV = XorString(stateIV, state);
            res += stateIV;
            stateIV = XorString(stateIV, dataChunk);
            break;
        case CFB:
            res += XorString(state, cycleData);
            stateIV = cycleData;
            break;
        case OFB:
            stateIV = state;
            res += XorString(state, cycleData);
            break;
        }
    }

    RemovePaddingFromData(res);
    return res;
}

// Encryption function. The data and key will be aligned using the algorithm PKCS#7
// If the key is greater than the value specified in keySize, the first keySize bits or keySize/8 characters will be taken from it
// If the any other mode than ECB set IV must be set
// Return true if encryption was succesfully, otherwise return false
bool AES_EncryptFile(std::string sourceFileName, std::string destinationFileName, AES_KeySize keySize, AES_Mode aes_mode, std::string key, std::string IV = "")
{
    std::ifstream sourceFile(sourceFileName, std::ios::binary | std::ios::ate);
    if (!sourceFile.is_open()) return false;

    uint64_t fileLen = sourceFile.tellg();
    sourceFile.seekg(0);

    std::ofstream destinationFile(destinationFileName, std::ios::binary);
    if (!destinationFile.is_open()) return false;

    if (fileLen == 0 || key.length() == 0 || (aes_mode != ECB && IV.length() == 0))
    {
        if (fileLen == 0)
            std::cerr << "In AES_Encrypt function: File cannot be empty" << std::endl;

        if (key.length() == 0)
            std::cerr << "In AES_Encrypt function: Key length cannot be zero" << std::endl;

        if (aes_mode == CBC && IV.length() == 0)
            std::cerr << "In AES_Encrypt function: IV(initialization vector) length cannot be zero" << std::endl;

        throw;
    }

    int roundsCount;
    switch (keySize)
    {
    case AES_128: roundsCount = 10; break;
    case AES_192: roundsCount = 12; break;
    case AES_256: roundsCount = 14; break;
    }

    key = AddPaddingToKey(keySize, key);
    IV = AddPaddingToKey(AES_128, IV);

    std::string stateIV = IV;
    std::string keyShedule = KeyExpansion(keySize, key);

    for (int i = 0; i <= fileLen / 16; ++i)
    {
        std::string fileData;
        char chars[16];

        if (i == fileLen / 16)
        {
            sourceFile.read(chars, fileLen % 16);
            fileData = std::string(chars, fileLen % 16);
            fileData += CalculateDataPadding(fileData);
        }
        else
        {
            sourceFile.read(chars, 16);
            fileData = std::string(chars, 16);
        }

        std::string dataChunk;

        switch (aes_mode)
        {
        case ECB: dataChunk = fileData; break;
        case CBC: dataChunk = XorString(stateIV, fileData); break;
        case PCBC: dataChunk = XorString(stateIV, fileData); break;
        case CFB: dataChunk = stateIV; break;
        case OFB: dataChunk = stateIV; break;
        }

        std::string state = AES_EncryptStep(dataChunk, keyShedule, roundsCount);

        switch (aes_mode)
        {
        case ECB: destinationFile << state; break;
        case CBC:
            stateIV = state;
            destinationFile << state;
            break;
        case PCBC:
            stateIV = XorString(state, fileData);
            destinationFile << state;
            break;
        case CFB:
            stateIV = XorString(state, fileData);
            destinationFile << stateIV;
            break;
        case OFB:
            stateIV = state;
            destinationFile << XorString(state, fileData);
            break;
        }
    }

    return true;
}

// Encryption function. The data and key will be aligned using the algorithm PKCS#7
// If the any other mode than ECB set IV must be set
// Return true if encryption was succesfully, otherwise return false
bool AES_DecryptFile(std::string sourceFileName, std::string destinationFileName, AES_KeySize keySize, AES_Mode aes_mode, std::string key, std::string IV = "")
{
    std::ifstream sourceFile(sourceFileName, std::ios::binary | std::ios::ate);
    if (!sourceFile.is_open()) return false;

    uint64_t fileLen = sourceFile.tellg();
    sourceFile.seekg(0);

    std::ofstream destinationFile(destinationFileName, std::ios::binary);
    if (!destinationFile.is_open()) return false;

    if (fileLen == 0 || key.length() == 0 || (aes_mode != ECB && IV.length() == 0))
    {
        if (fileLen == 0)
            std::cerr << "In AES_Decrypt function: File cannot be empty" << std::endl;

        if (key.length() == 0)
            std::cerr << "In AES_Decrypt function: Key length cannot be zero" << std::endl;

        if (aes_mode == CBC && IV.length() == 0)
            std::cerr << "In AES_Decrypt function: IV(initialization vector) length cannot be zero" << std::endl;

        throw;
    }

    int roundsCount;
    switch (keySize)
    {
    case AES_128: roundsCount = 10; break;
    case AES_192: roundsCount = 12; break;
    case AES_256: roundsCount = 14; break;
    }

    key = AddPaddingToKey(keySize, key);
    IV = AddPaddingToKey(AES_128, IV);

    std::string stateIV = IV;
    std::string keyShedule = KeyExpansion(keySize, key);

    for (int i = 0; i < fileLen / 16; i++)
    {
        char chars[16];
        sourceFile.read(chars, 16);
        std::string fileData = std::string(chars, 16);

        std::string dataChunk;
        std::string writingData;

        switch (aes_mode)
        {
        case ECB: dataChunk = fileData; break;
        case CBC: dataChunk = fileData; break;
        case PCBC: dataChunk = fileData; break;
        case CFB: dataChunk = stateIV; break;
        case OFB: dataChunk = stateIV; break;
        }

        std::string state;

        switch (aes_mode)
        {
        case ECB:
        case CBC:
        case PCBC: state = AES_DecryptStep(dataChunk, keyShedule, roundsCount); break;
        case CFB:
        case OFB: state = AES_EncryptStep(dataChunk, keyShedule, roundsCount); break;
        }

        switch (aes_mode)
        {
        case ECB: writingData = state; break;
        case CBC:
            writingData = XorString(stateIV, state);
            stateIV = fileData;
            break;
        case PCBC:
            stateIV = XorString(stateIV, state);
            writingData = stateIV;
            stateIV = XorString(stateIV, dataChunk);
            break;
        case CFB:
            writingData = XorString(state, fileData);
            stateIV = fileData;
            break;
        case OFB:
            stateIV = state;
            writingData = XorString(state, fileData);
            break;
        }

        if (i == (fileLen - 16) / 16)
        {
            RemovePaddingFromData(writingData);
            if (writingData.length() != 0)
                destinationFile << writingData;
        }
        else
            destinationFile << writingData;
    }

    return true;
}

int main()
{
    // File encryption
    std::cout << "File encryption: data to data.enc" << std::endl;
    if (!AES_EncryptFile("data", "data.enc", AES_256, ECB, "file key", "file iv"))
        std::cout << "Failed to create file" << std::endl;
}