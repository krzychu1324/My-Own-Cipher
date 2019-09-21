#include <iostream>
#include <windows.h>
#include <time.h>
#include <string>

using namespace std;

int init() {
	int input;
	do {
		system("CLS");
		cout << "My Own Cipher by KM" << endl;
		cout << "1. Code text" << endl;
		cout << "2. Decode text" << endl;
		cout << "3. Exit" << endl;
		cout << "Insert option(integer): ";
		cin >> input;
	} while (input != 1 && input != 2 && input != 3);
	return input;
}

bool letters_only(string input) {
	int length = input.length();
	for (int i = 0; i < length; i++)
		if (!((input[i] >= 'a' && input[i] <= 'z') || input[i] == ' ')) return false;
	return true;
}

string init_code() {
	string input = "";
	do {
		system("CLS");
		cout << "Insert text(small latin letters [a-z] or space only): ";
		while(input == "") getline(cin, input);
	} while (!letters_only(input));
	return input;
}

string int_to_string(int input) {
	string result = "";
	string tmp = "";
	while (input > 0) {
		tmp += char(input % 10 + '0');
		input /= 10;
	}
	for (int i = tmp.length() - 1; i >= 0; i--)
		result += tmp[i];
	return result;
}

void code() {
	string input = init_code();

	//generate key and hash
	int key;
	string hash = "";
	string hash2 = "";
	key = rand() % 5 + 1;
	for (int i = 0; i < key; i++) {
		hash += char((rand() % 10) + '0');
		hash2 += char(((rand()+7) % 10) + '0');
	}

	//generate main content
	string main = "";
	int tmp;
	int length = input.length();
	for (int i = 0; i < length; i++) {
		if (input[i] == ' ') {
			main += "00";
			continue;
		}
		tmp = int(input[i]) - 'a' + key;
		if (tmp < 10) tmp += 90;
		main += int_to_string(tmp);
	}

	//generate final code
	string final = "";
	final += int_to_string(key);
	final += hash;
	final += main;
	final += hash2;

	//print final code
	cout << "Encrypted code: ";
	cout << final << endl;
	system("pause");
}

bool digits_only(string input) {
	int length = input.length();
	for (int i = 0; i < length; i++)
		if (!(input[i] >= '0' && input[i] <= '9')) return false;
	return true;
}

bool valid_code(string input) {
	int length = input.length();
	for (int i = 0; i < length; i++) {
		if (input[i] > '9' || input[i] < '0')
			return false;
	}
	int key = int(input[0] - '0');

	if ((length - 2 * key - 1) % 2 == 1)
		return false;
	return true;
}

string init_decode() {
	string input = "";
	do {
		system("CLS");
		cout << "Insert encrypted code: ";
		cin >> input;
	} while (!valid_code(input));
	return input;
}

int char_to_int(char input) {
	return int(input - '0');
}

void decode() {
	string input = init_decode();
	string main = "";
	string result = "";
	int tmp;
	int length = input.length();
	int key = int(input[0] - '0');
	
	//get main content
	for (int i = key + 1; i < length - key; i++)
		main += input[i];

	//decrypt main content
	length = main.length();
	for (int i = 0; i < length; i++) {
		if (main[i] == '0' && main[i + 1] == '0') {
			result += ' ';
			i++;
			continue;
		}
		tmp = char_to_int(main[i++]);
		tmp *= 10;
		tmp += char_to_int(main[i]);
		if (tmp >= 90) tmp -= 90;
		result += char(tmp + 'a' - key);
	}
	cout << "Decrypted code: ";
	cout << result << endl;
	system("pause");
}

int main()
{
	srand(time(NULL));
	int input;
	do {
		input = init();
		switch (input)
		{
		case 1:
			code();
			break;
		case 2:
			decode();
			break;
		default:
			break;
		}
	} while (input != 3);

	return 0;
}
