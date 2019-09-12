#include "Shmopash.h"

#define LUCKY_NUMBER 7
#define BLYAT_HASH_LEN 8

#define MAD_VIBE_LEN 4

void xor(char * start, const int len, char value_to_xor) {
	/*
		Xor each byte in a given buffer with a given value.

		Param start: address to start xoring
		Param len: How many bytes should be xorred
		Param value_to_xor: The value to xor with

		The given range of bytes is changed accordingly.
	*/
	for (int i = 0; i < len; i++) {
		start[i] ^= value_to_xor;
	}
}

bool blyat_hash(char * password, char * result) {
	/*
		This is the most sophisticated hash function in ALL Mother Russia
		Viva la putin

		Param password: string to hash (most be longer than 8 bytes)
		Param result: buffer where the result will be written

		Return boolean: true if successful else false
	*/
	if (strlen(password) < BLYAT_HASH_LEN) {
		printf("password is too short to be hashed by the blyat hash");
		return false;
	}
	memcpy(result, password, BLYAT_HASH_LEN); // So that we won't change the password variable
	xor (result, BLYAT_HASH_LEN, LUCKY_NUMBER);
	return true;
}

bool mad_vibe_hash(char * password, unsigned int len, char * result) {
	/*
		This hash is on drugs.

		Param password: string to hash
		Param result: buffer where the result will be written

		Return boolean: true if successful else false
	*/

	if (len % 2 != 0) {
		printf("length has to be even");
		return false;
	}

	unsigned char * md5_hash_result = (unsigned char *)md5(password, len);
	// Convert to hex
	for (unsigned int i = 0; i < len / 2; i++) {
		sprintf_s(result + sizeof(char) * i * 2, 3, "%02x", md5_hash_result[i]);
	}

	free(md5_hash_result);
	return true;
}

bool shmoppash(char * password, char * result) {
	/*
		This hash function just uses both the mad vibe hash and the blyat hash to make sure our hash extremely strong.

		Param password: string to hash (must be longer than 8 bytes)
		Param result: buffer where the result will be written

		Return boolean: true if successful else false
	*/

	//first part
	if (!blyat_hash(password, result)) {
		return false;
	}
	// second part
	if (!mad_vibe_hash(password + sizeof(char) * BLYAT_HASH_LEN, MAD_VIBE_LEN, result + BLYAT_HASH_LEN)) {
		return false;
	}

	return true;
}