#include "..\Shmoppass\Shmopash.h"
#include "..\Shmoppass\Shmopfile.h"

#include "..\Shmoppass\aes.h"

#define MESSAGE_MAXIMUM_LEN (FILE_MAXIMUM_SIZE - (HASH_LEN + HEADER_LEN))

unsigned int encrypt_file_body(char* buf, int length, char * key, const char * iv) {
	unsigned char padding_bytes = 16 - length % 16;
	memset(buf + length, 0, padding_bytes);
	length += padding_bytes;
	struct AES_ctx context;
	AES_init_ctx_iv(&context, key, iv);
	AES_CBC_encrypt_buffer(&context, buf, length);
	return padding_bytes;
}

int main(int argc, char ** argv) {
	char message[MESSAGE_MAXIMUM_LEN + 1];
	char password[PASSWORD_LEN + 1];
	char file_buffer[FILE_MAXIMUM_SIZE];
	char * file_buffer_cur_index = file_buffer;

	printf("Enter message to encrypt:\n");
	if (!scanf_s("%[^'\n']s", message, MESSAGE_MAXIMUM_LEN)) {
		printf("The message you entered is too long\n");
	}

	printf("Enter password:\n");
	scanf_s("%16s", password, PASSWORD_LEN + 1);

	if (!is_password_valid(password)) {
		return -1;
	}

	// Append the password's hash
	shmoppash(password, file_buffer_cur_index);
	file_buffer_cur_index += HASH_LEN;
	
	// Of course all messages have start with the sacred words "Hail Shmop!".
	// Append header to message.
	char * file_message = file_buffer_cur_index;
	memcpy(file_message, HEADER, HEADER_LEN);
	file_buffer_cur_index += HEADER_LEN;

	unsigned int message_size = strlen(message) + 1;

	memcpy(file_buffer_cur_index, message, message_size);
	file_buffer_cur_index += message_size;
	file_buffer_cur_index += encrypt_file_body(file_message, HEADER_LEN + message_size, password, iv);
	
	if (!write_file(FILE_NAME, file_buffer, file_buffer_cur_index - file_buffer)) {
		return -1;
	}
	printf("Success!\n");
	return 0;
}