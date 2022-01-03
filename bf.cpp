#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <map>

// Human Readable BrainFuck Interpreter

std::string clear(std::string s) {
	std::string res = "";
	int op = 0, cl = 0;

	for (char c : s) {
		if (
			c == '<' || c == '>' ||
			c == '.' || c == ',' ||
			c == '[' || c == ']' ||
			c == '+' || c == '-'
		) res += c;
		if (c == '[') op++; else
		if (c == ']') cl++;
	}

	if (op != cl) {
		std::cout << "Syntax error\n";
		exit(1);
	}
	return res;
}

std::map <int, int> pairs;

void run(std::string s) {
	
	long long pos = 0;
	std::vector <char> v(65536, 0);
	
	std::stack <int> brackets;
	for (int i = 0; i < (int)s.size(); i++) {
		if (s[i] == '[') brackets.push(i); else
		if (s[i] == ']') {
			pairs[i] = brackets.top();
			pairs[brackets.top()] = i;
			brackets.pop();
		}
	}

	for (int i = 0; i < (int)s.size(); i++) {
		switch (s[i]) {
			case '>': pos++; break;
			case '<': pos--; break;
			case '+': v[pos]++; break;
			case '-': v[pos]--; break;
			case '.': std::cout << v[pos]; break;
			case ',': std::cin  >> v[pos]; break;
			case '[': if (v[pos]==0) i = pairs[i]; break;
			case ']': if (v[pos]!=0) i = pairs[i]; break;
		}
	}
	std::cout << "\n";
	
}

int main(int argc, char* argv[]) {

	if (argc > 3) {
		std::cout << "Input error\n";
		return 1;
	}
	if (argc == 2) {
		std::string arg = std::string(argv[1]);
		if (arg == "--version") {
			std::cout 
			<< "The one and only version of Lrapava's BrainFuck interpreter.\n"
			<< "No new versions will be released.\n"
			<< "For use by any volunteer who is willing to fuck their brain.\n";
			return 0;
		}
		if (arg == "--help" || arg == "-h") {
			std::cout 
			<< "BrainFuck is a programming language created by Urban Müller in 1993.\n"
			<< "\n"
			<< "--help | -h    Prints this message and exits.\n"
			<< "--version      Prints version of the program and exits.\n"
			<< "-f [path]      Interprets code at [path] as BrainFuck code.\n"
			<< "[text]         Interprets the [text] as BrainFuck code.\n"
			<< "\n"
			<< "stdin          After running the program with no additional paramaters,\n"
			<< "               standard input will be interpreted as BrainFuck code.\n"
			<< "               This lets the program accept piped input.\n"
			<< "\n"
			<< "Have a bad day :)\n";
			return 0;
		}
		run(clear(arg));
		return 0;
	}

	auto stream = &std::cin;
	std::ifstream file;
	
	if (argc == 3) {
		if (std::string(argv[1]) != "-f") {
			std::cout << "Input error\n";
			return 1;
		}
		std::string path = std::string(argv[2]);
		file.open(path);
		if (!file.is_open()) {
			std::cout << "File not found.\n";
			return 1;
		}
		stream = &file;
	}
	
	std::string code = "", s;
	while (std::getline(*stream, s))
		code += s;
	run(clear(code));
}
