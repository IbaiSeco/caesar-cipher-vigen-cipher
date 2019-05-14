#include "ciphers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
* Ibai Seco (251011373)
* This c file holds the functions for the caesar_encrypt,
* caesar_decrypt, vigen_encrypt, vigen_decrypt, and freq_analysis
*/

/* shifts each plaintext character a certain key amount */
char * caesar_encrypt(char *plaintext, int key) {
        // pointer definitions
        char *a, *b, *q, *p, *copy =
        (char *) malloc( (strlen(plaintext) + 1) * sizeof(char) );

        //allocates memory for new pointer array
        char *uppercopy = (char *) malloc( (strlen(plaintext) + 1) * sizeof(char) );

        //If there is an error allocating memory for pointer arrays
        if (uppercopy == NULL || copy == NULL) {
                printf("Error allocating memory!");
                exit(EXIT_FAILURE);
        }

        //copies the plaintext to uppercopy created an uppercase plaintext
	       for (p = plaintext, q = uppercopy; *p != '\0'; p++, q++) {
                *q = toupper(*p);
        }
	       *(uppercopy + strlen(plaintext)) = '\0';

        //adds the keys to the letters to create the ciphertext
        for (b = uppercopy, a = copy; *b != '\0';b++, a++) {
                if (*b >= 'A' && *b <= 'Z') {
                        *b = *b + (key % 26);
                        if (*b > 'Z') {
                                *b = *b - 'Z' + 'A' - 1;
                        }
                        else if (*b < 'A') {
                                *b = *b + 'Z' - 'A' + 1;
                        }
                }
                *a = *b;
        }

	*(copy + strlen(plaintext)) = '\0';
        return copy;
}

//decrypts the encrypted cipher message
char * caesar_decrypt(char *ciphertext, int key) {
        char *a, *b, *copy =
        (char *) malloc( (strlen(ciphertext) + 1) * sizeof(char) );

        //If there is an error allocating memory for pointer arrays
        if (copy == NULL) {
                printf("Error allocating memory!");
                exit(EXIT_FAILURE);
        }

        //changes the ciphertext back to plaintext by shifting by the key amount
	       for (b = ciphertext, a = copy; *b != '\0';b++, a++) {
                if (*b >= 'A' && *b <= 'Z') {
                        *b = *b - (key % 26);
                        if (*b > 'Z') {
                                *b = *b - 'Z' + 'A' - 1;
                        }
                        else if (*b < 'A') {
                                *b = *b + 'Z' - 'A' + 1;
                        }
                }
                *a = *b;
        }
	       *(copy + strlen(ciphertext)) = '\0';
        return copy;
}

// vigen_encrypt encrypts using using a key amount for the position of the letter
char * vigen_encrypt(char *plaintext, char *key) {
        char *j, *k, *m, *n, *q, *p, *a, *b, *ciphertext =
        (char *) malloc( (strlen(plaintext) + 1) * sizeof(char) );

        char *padkey =
        (char *) malloc( (strlen(plaintext) + 1) * sizeof(char) );

        char *uppercopy =
        (char *) malloc( (strlen(plaintext) + 1) * sizeof(char) );

        //If there is an error allocating memory for pointer arrays
        if (ciphertext == NULL || padkey == NULL) {
                printf("Error allocating memory!");
                exit(EXIT_FAILURE);
        }

	       for (b = plaintext, a = padkey; *b != '\0';a++, b++) {
                *a = *b;
        }
	       *(padkey + strlen(plaintext) - 1) = '\0';

         //this is for padding the key to the length of the plaintext
        for (p = key, q = padkey; *q != '\0';p++, q++) {
                if (*p == '\0') {
                        p = key;
                }
                *q = toupper(*p);
        }

        //this is to change the plaintext to all uppercase
	       for (m = plaintext, n = uppercopy; *m != '\0'; m++, n++) {
                *n = toupper(*m);
        }

        //the shift
	       for (j = uppercopy, k = padkey; *j != '\0'; j++, k++) {
                if (*j >= 'A' && *j <= 'Z') {
                        *j = *j + (*k - 'A');
                        if (*j > 'Z') {
                                *j = *j - 'Z' + 'A' - 1;
                        }
                }
                *k = *j;
        }
	return padkey;
}


// decrypts the plaintext message instead of encrypting it
char * vigen_decrypt(char *ciphertext, char *key) {
        char *j, *k, *m, *n, *q, *p, *a, *b, *plaintext =
        (char *) malloc( (strlen(ciphertext) + 1) * sizeof(char) );

        char *padkey =
        (char *) malloc( (strlen(ciphertext) + 1) * sizeof(char) );


        if (plaintext == NULL || padkey == NULL) {
                printf("Error allocating memory!");
                exit(EXIT_FAILURE);
        }

	       for (b = ciphertext, a = padkey; *b != '\0';a++, b++) {
                *a = *b;
        }
	       *(padkey + strlen(ciphertext) - 1) = '\0';

        for (p = key, q = padkey; *q != '\0';p++, q++) {
                if (*p == '\0') {
                        p = key;
                }
                *q = toupper(*p);
        }

	       for (j = ciphertext, k = padkey; *j != '\0'; j++, k++) {
                if (*j >= 'A' && *j <= 'Z') {
                        *j = *j - (*k - 'A');
                        if (*j < 'A') {
                                *j = *j + 'Z' - 'A' + 1;
                        }
                }
                *k = *j;
        }
	return padkey;
}

//computes the average of amount of each letter in the plaintext
void freq_analysis(char *ciphertext, double letters[26]) {
        char *q, test, *p;
        int number, length;

        length = 0;

        //counts the amount of characters in the alphabet
        for (p = ciphertext; *p != '\0'; p++) {
                if (isalpha(*p)) {
                        length++;
                }
        }

        //counts the amount of each letter in the ciphertext
        for (test = 'A', number = 0; test <= 'Z'; test++, number++){
                double count = 0;
                for (q = ciphertext; *q != '\0'; q++) {
                        if (*q == test){
                                count++;
                         }
                }
                *(letters+number) = (count / length) * 100;
        }
}
