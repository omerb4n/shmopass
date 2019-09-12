/****************************************************************************
 * Copyright (C) 2019 by Shmoppie                                           *
 *                                                                          *
 * This file is part of Shmoppass.                                          *
 *                                                                          *
 *   ShmoppieD is free software: you can redistribute it and/or modify it   *
 *   under the terms of the GNU Lesser General Public License as published  *
 *   by the Free Software Foundation, either version 3 of the License, or   *
 *   (at your option) any later version.                                    *
 *																			*
 *   ....																	*
 *	 Legal shit bla bla bla                                                 *
 *   ...                                                                    *
 *                                                                          *
 *   ShmoppieD is used for decrypting files that were encrypted with        *
 *   ShmoppieE. As known, ShmoppieE encrypts a file with a 16 characters    *
 *   length password, constructed of: name of an animal (8 characters),     *
 *	 name of a color (4 bytes) and 4 digits known only to the man who       *
 *	 encrypted the file (4 bytes). Because the 4 last digits suppose to     *
 *	 be written NOWHERE, they are not hashed as well.                       *
 *   By default, ShmoppieD reads tries to decrypt the file in               *
 *   "Shmoppass\EncryptedFiles\SECRET_SHIT.shmp"                            *     
 ****************************************************************************/


#include "..\Shmoppass\Shmopash.h"
#include "..\Shmoppass\Shmopfile.h"

#include "..\Shmoppass\aes.h"

bool decrypt_file_body(char* buf, int length, char * key, char * iv) {
	struct AES_ctx context;
	AES_init_ctx_iv(&context, key, iv);
	AES_CBC_decrypt_buffer(&context, buf, length);

	// Check the file header
	if (memcmp(buf, HEADER, HEADER_LEN)) {
		printf("The shmp header was not found");
		return false;
	}
	return true;
}

bool validate_password_hash(char * password, char * file_buffer) {
	// Hash the password
	char hash[HASH_LEN + 1];
	if (!shmoppash(password, hash)) {
		printf("hash function failed:(\n");
		return false;
	}

	// Check the hash
	printf("Hash value: %.15s\n", hash);
	if (memcmp(hash, file_buffer, HASH_LEN) == 0) {
		printf("success!\n");
		return true;
	}
	else {
		printf("Wrong password :(\n");
		return false;
	}
}

void print_file() {
	return true;
}

int main() {
	char file_buffer[FILE_MAXIMUM_SIZE];
	char password[PASSWORD_LEN + 1];
	int file_size;

	file_size = read_file(FILE_NAME, file_buffer);
	if (file_size == 0) {
		return -1;
	}

	printf("Enter password:\n");
	scanf_s("%16s", password, PASSWORD_LEN + 1);

	if (!is_password_valid(password)) {
		return -1;
	}
	
	// validate that the password's hash is valid
	if (!validate_password_hash(password, file_buffer)) {
		return -1;
	}
	// Hash of the password is correct, the last 4 characters of the password were not hashed.
	// They are known only to the man who encrypted the file.
	
	char * file_body = file_buffer + HASH_LEN;
	char file_body_size = file_size - HASH_LEN - 1;
	if (!decrypt_file_body(file_body, file_body_size, password, iv)) {
		printf("Decryption failed, maybe the last 4 digits are wrong:(\n");
		return 0;
	}
	
	printf("\n%s\n\n", file_body);
	return 0;
}