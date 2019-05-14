#include "ciphers.h"
#include <stdio.h>
#include <stdlib.h>
/*
* Ibai Seco (251011373)
* this acts as the main method for the encryption functions
* it takes user input and converts the selected encryption
* decryption
* there are no special compilation instructions
*/

int main() {
	//variable declarations
        char caesarDecrypt[100], caesarCipher[100];
        char plaintext[100], keystring[100];
        double result[26];
        int option, key;

        printf("Input plaintext: \n");
        fgets(plaintext, 100, stdin);

        printf("\n");

        printf("Available Ciphers: \n");
        printf("1) Caesar\n");
        printf("2) Vigenere\n");

        printf("\n");

        printf("Select Cipher: ");
        scanf(" %d", &option);

        printf("\n");

        // if the user uses the caesar cipher
        if (option == 1) {
                //makes sure that the input key is an actual number
                printf("Input key as number: ");
                if(scanf(" %d", &key) != 1) {
                        printf("Error: bad key!\n");
                        return 1;
                }

                printf("\n");
                //returns the plaintext that the user has entered
                printf("Plaintext:\n");
                printf("%s", plaintext);

                printf("\n");
                //returns the encrypted plaintext
                printf("Ciphertext:\n");
                printf("%s", caesar_encrypt(plaintext, key));

                printf("\n");
                //returns the decrypted ciphertext
                printf("Decrypted plaintext:\n");
                printf("%s\n",caesar_decrypt(caesar_encrypt(plaintext, key),key));

                //function calls the frequency analysis
                freq_analysis(caesar_encrypt(plaintext, key), result);

                printf("Frequency Analysis: \n");
                //prints out the list of alphabetic letter
                char alpha[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M',
                'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
                int j;
                int counter = 25;
                for (j = 0; j <= counter; j++) {
                        printf("   %c", alpha[j]);
                }

                printf("\n");
                //prints out the frequency analysis numbers
                int i;
                for (i = 0; i <= counter; i++) {
                        printf(" %.1lf", result[i]);
                }

                printf("\n");
                //frees up the memory buffer
                free(caesar_encrypt(plaintext, key));
                free(caesar_decrypt(caesar_encrypt(plaintext, key), key));
        }

	//if the user enters the vigenere cipher
        else if (option == 2) {
                int result;
                char *u;
                printf("Input key as string:\n");
                scanf(" %99[^\n]", &keystring);
                keystring[strlen(keystring)] ='\0';

                //checks to make sure the keystring only has letters
                for (u = keystring; *u != '\0'; u++) {
                        result = isalpha(*u);
                        if (result == 0) {
                                printf("Error: bad key, invalid char!\n");
                                exit(EXIT_FAILURE);
                        }
                }

                printf("\n");
                //returns the plaintext
                printf("Plaintext:\n");
                printf("%s\n", plaintext);

                //returns the ciphertext
                printf("Ciphertext:\n");
                printf("%s\n", vigen_encrypt(plaintext, keystring));

                //returns the decrypted ciphertext
                printf("Decrypted plaintext:\n");
                printf("%s\n", vigen_decrypt(vigen_encrypt(plaintext, keystring), keystring));

                double vigenResult[26];
                freq_analysis(vigen_encrypt(plaintext, keystring), vigenResult);

                printf("Frequency Analysis: \n");
                //prints out the list of alphabetic letter
                char alpha[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M',
                'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
                int j;
                int counter = 25;
                for (j = 0; j <= counter; j++) {
                        printf("   %c  ", alpha[j]);
                }

                printf("\n");
                //prints out the frequency analysis numbers
                int i;
                for (i = 0; i <= counter; i++) {
                        printf("  %.1lf ", vigenResult[i]);
                }

                printf("\n");
                //frees up memory
                free(vigen_encrypt(plaintext, keystring));
                free(vigen_decrypt(vigen_encrypt(plaintext, keystring), keystring));

        }
	else {
              	printf("Error: bad selection!\n");
                return 1;
        }
	return 0;
}
