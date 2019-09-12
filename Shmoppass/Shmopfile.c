#include "Shmopfile.h"
#include "Shmopash.h"

const char iv[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f };

bool is_password_valid(char * password) {
	// Check password length
	if (strlen(password) != PASSWORD_LEN) {
		printf("passcode length should be %d bytes\n", PASSWORD_LEN);
		return false;
	}
	return true;
}

unsigned int read_file(char * path, char * file_buffer) {
	signed char c;
	FILE *file;
	unsigned int file_size = 0;

	if (fopen_s(&file, path, "rb") == 0) {
		file_size = fread_s(file_buffer,FILE_MAXIMUM_SIZE, 1, FILE_MAXIMUM_SIZE, file);
		fclose(file);
	}
	else {
		printf("Failed Reading file.\n");
		return 0;
	}
	if (file_size < HASH_LEN + 1) {
		printf("No stored hash was found in the file.\n");
		return 0;
	}
	return file_size;
}

bool write_file(char * path, char * content, unsigned int len) {

	FILE *file;
	if (!fopen_s(&file, path, "w+")) {
		for (unsigned int i = 0; i < len; i++) {
			char a = content[i];
			fprintf(file, "%c", content[i]);
		}
	}
	else {
		printf("Error opening file!\n");
		return false;
	}
	fclose(file);
	return true;
}