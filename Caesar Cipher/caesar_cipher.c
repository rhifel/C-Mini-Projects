#include <stdio.h>
#include <ctype.h>
#include <string.h>

void encrypt(char *text, int key), decrypt(char *text, int key);

int main(void)
{
    char message[100];
    int key, choice;

    printf("Enter a message: ");
    fgets(message, sizeof(message), stdin);

    message[strcspn(message, "\n")] = 0;

    printf("Enter shift key: ");
    scanf("%d", &key);
    key %= 26;

    printf("Choose [1]->encrypt or [2]->decrypt: ");
    scanf("%d", &choice);

    // Encryption
    if (choice == 1)
    {
        encrypt(message, key);
        printf("Encrypted message: %s\n", message);
    }

    // Decryption
    else if (choice == 2)
    {
        decrypt(message, key);
        printf("Decrypted message: %s\n", message);
    }

    else
    {
        printf("Invalid Choice!");
    }

    return 0;
}

void encrypt(char *text, int key)
{
    while (*text)
    {
        if (isalpha(*text))
        {
            char base = isupper(*text) ? 'A' : 'a';
            *text = (*text - base + key) % 26 + base;
        }
        text++;
    }
}

void decrypt(char *text, int key)
{
    while (*text)
    {
        if (isalpha(*text))
        {
            char base = isupper(*text) ? 'A' : 'a';
            *text = (*text - base - key + 26) % 26 + base;
        }
        text++;
    }
}