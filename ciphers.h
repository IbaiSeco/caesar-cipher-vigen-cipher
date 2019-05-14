/* a header file containing function prototypes for each function in
* ciphers.c as well as any macro-defined constants. Should be protected
* from being included multiple times.
*/

char * caesar_encrypt(char *plaintext, int key);

char * caesar_decrypt(char *ciphertext, int key);

char * vigen_encrypt(char *plaintext, char *key);

char * vigen_decrypt(char *ciphertext, char *key);

void freq_analysis(char *ciphertext, double letters[26]);
