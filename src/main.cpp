#include "class.h"
#include <string>
#include <fstream>

int PairCore::parser(int argc, char* argv[]) {
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
int gui_solve() {
	PairCore* paircore = new PairCore(GUI);
	return paircore->output1();
}
int command_solve() {
	char* argv[128];
	PairCore* paircore = new PairCore(COMMAND);
	ifstream input_command;
	input_command.open("command.pair");
	int argc = 0;
	string str;
	try {
		while (input_command.good()) {
			getline(input_command, str);
			argv[argc] = (char*)malloc(128 * sizeof(char));
			memcpy_s(argv[argc++],128, str.c_str(), 128);
		//	memcpy_s()
		}
		paircore->parser(argc, argv);
		int answer = 0;
		answer = paircore->output1();
		return answer;
	}
	catch (exception e) {
		return paircore->getError(e.what());
	}
}

int main(int argc, char* argv[]) {
	PairCore *pairCore = new PairCore(COMMAND);
	if (pairCore->parser(argc, argv)) {
		return -13;
	}
	return pairCore->output1();
	//cout<<gui_solve();

	//cout<<command_solve();
}