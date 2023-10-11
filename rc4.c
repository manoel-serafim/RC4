#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 256

typedef struct RC4_KEY_S {
    unsigned char S[256];
} RC4_KEY;

void RC4_key(RC4_KEY *rc4_key, const unsigned char *key, int keylength) {
    for (int i = 0; i < 256; i++) {
        rc4_key->S[i] = (unsigned char)i;
    }

    int j = 0;
    for (int i = 0; i < 256; i++) {
        j = (j + rc4_key->S[i] + key[i % keylength]) % 256;
        unsigned char temp = rc4_key->S[i];
        rc4_key->S[i] = rc4_key->S[j];
        rc4_key->S[j] = temp;
    }
}

void RC4_encrypt(const RC4_KEY *rc4_key, const unsigned char *plaintext, int plaintext_length, unsigned char *ciphertext) {
    unsigned char S[256];
    for (int i = 0; i < 256; i++) {
        S[i] = rc4_key->S[i];
    }

    int i = 0, j = 0;

    for (int k = 0; k < plaintext_length; k++) {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        unsigned char temp = S[i];
        S[i] = S[j];
        S[j] = temp;

        unsigned char n = S[(S[i] + S[j]) % 256];

        ciphertext[k] = plaintext[k] ^ n;
    }
}

int main() {
    unsigned char plaintext[MAX_LENGTH];
    unsigned char key[MAX_LENGTH];
    unsigned char ciphertext[MAX_LENGTH];

    RC4_KEY rc4_key;

    printf("Enter plaintext: ");
    scanf("%s", plaintext);

    printf("Enter key: ");
    scanf("%s", key);

    int plaintext_length = strlen(plaintext);
    int key_length = strlen(key);

    RC4_key(&rc4_key, key, key_length);

    RC4_encrypt(&rc4_key, plaintext, plaintext_length, ciphertext);

    printf("Ciphertext (in hexadecimal format): ");
    for (int k = 0; k < plaintext_length; k++) {
        printf("%02x:", ciphertext[k]);
    }

    return 0;
}
