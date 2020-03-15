#include "class.h"
#include <string>
#include <fstream>

string input = "";
string output = "";

int parser(int argc, char* argv[]) {

	if (argc == 3) {
		string s1(argv[1]);
		if (s1 == "-i") {
			input = string(argv[2]);
		}
		else if (s1 == "-o") {
			output = string(argv[2]);
		}
		else {
			return 1;
		}
	}
	else if (argc == 5) {
		string s1(argv[1]);
		string s2(argv[3]);
		if (s1 == s2) {
			return 1;
		}
		else {
			if (s1 == "-i") {
				input = string(argv[2]);
			}
			else if (s1 == "-o") {
				output = string(argv[2]);
			}
			else {
				return 1;
			}
			if (s2 == "-i") {
				input = string(argv[4]);
			}
			else if (s2 == "-o") {
				output = string(argv[4]);
			}
			else {
				return 1;
			}
		}
	}
	else if (argc != 1) {
		return 1;
	}
	return 0;
}

int main(int argc, char* argv[]) {
	if (parser(argc, argv)) {
		return 1;
	}

}