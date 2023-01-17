#include <iostream>
#include <random>
#include <windows.h>
#include <string>

#include <Cipher.h>

#define STATUS_RUN		0x1
#define STATUS_EXIT		0x0

#define WELCOME_MESSAGE "Welcome to cipher++\n\nCommands:\n-c <string>	--encode text\n-d <string>	--decode text\n-q         	--quit\n\n==============================================================\n\n"
#define NEW_LINE "\n\n--------------------------------------------------------------\n\n"

int PROGRAM_STATUS = STATUS_RUN;

char 
custom_get_opt(const std::string& arg) {
	if (arg.size() < 2) {
		return 0;
	}

	if (arg[0] != '-') {
		return arg[0];
	}

	return arg[1];
}

void
set_clipboard_win(std::string input) {

	const char* input_cstr = input.c_str();
	const size_t input_len = strlen(input_cstr) + 1;

	HGLOBAL glob = GlobalAlloc(GMEM_MOVEABLE, input_len);

	if (glob == nullptr) {
		std::cout << "GlobalAlloc Failed - Exit 1\n";
		exit(EXIT_FAILURE);
	}

	LPVOID glob_void = GlobalLock(glob);

	if (glob_void == nullptr) {
		std::cout << "GlobalLock Failed - Exit 1\n";
		exit(EXIT_FAILURE);
	}

	memcpy(glob_void, input_cstr, input_len);
	GlobalUnlock(glob);
	OpenClipboard(0);
	EmptyClipboard();
	SetClipboardData(CF_TEXT, glob);
	CloseClipboard();
}

int 
main() {

	std::string input_buffer;
	std::string line_content;
	std::string ciph;
	std::string deciph;

	std::cout << WELCOME_MESSAGE;

	while (PROGRAM_STATUS) {

		std::getline(std::cin, input_buffer);
		char opt = custom_get_opt(input_buffer);

		char* input_buffer_cstr = (char*) input_buffer.c_str();
		line_content = input_buffer_cstr + 3;

		std::cout << std::endl;

	
		switch (opt) {
			case 'q':
				PROGRAM_STATUS = STATUS_EXIT;
				break;

			case 'c':
				ciph = cipher_main(line_content);
				std::cout << ciph << NEW_LINE;
				set_clipboard_win(ciph);
				break;

			case 'd':
				std::cout << decipher_main(line_content) << NEW_LINE;
				break;

			default:
				std::cout << "Unrecognized Option " << opt << NEW_LINE;
		}
	
	}

	exit(EXIT_SUCCESS);
}