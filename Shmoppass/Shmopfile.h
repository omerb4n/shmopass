#include <stdio.h>
#include <stdbool.h>

#define PASSWORD_LEN 16

#define FILE_NAME "..\\EncryptedFiles\\SECRET_SHIT.shmp"
#define FILE_MAXIMUM_SIZE 1024 * 2
#define FILE_NAME_MAXIMUM_LEN 256

#define HEADER "Hail SHMOP!\n"
#define HEADER_LEN sizeof(HEADER) - 1

extern const char iv[];

bool is_password_valid(char * password);

unsigned int read_file(char * name, char * file_buffer);
bool write_file(char * name, char * content, unsigned int len);