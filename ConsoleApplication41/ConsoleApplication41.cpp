/*
github: Full Burrows–Wheeler transform

*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

void print(vector<string> input) {
	for (string value : input) {
		cout << value << ", ";
	}
}

string rotate(string word) {
	string tmp = "^";
	tmp += word;
	tmp += "|";
	vector<string> output;
	for (int i = 0; i < tmp.size(); i++) {
		tmp += tmp[0];
		tmp.erase(tmp.begin());
		output.push_back(tmp);
	}
	sort(output.begin(), output.end());
	string output1 = "";
	for (string word : output) {
		output1 += word[word.size()-1];
	}
	return output1;
}

string compress(string long_string) {
	string output = "";
	char current_ch = long_string[0];

	int len = 0;
	for (char ch : long_string) {
		if (ch == current_ch) {
			len++;
		}
		else {
			output += current_ch;
			output += to_string(len);
			len = 1;
			current_ch = ch;
		}
	}
	output += current_ch;
	output += to_string(len);
	return output;
}
string decode(string word) {
	int len = word.size();
	vector<string> words(len, "");
	for (int k = 0; k < len; k++) {
		for (int i = 0; i < len; i++) {		
			words[i].insert(words[i].begin(), word[i]);

		}
		sort(words.begin(), words.end());
	}
	
	return words[len-1];
}
vector<string> to_vector(string word) {
	vector<string> output;
	string number = "";
	for (char ch : word) {
		if (ch >= '0' && ch <= '9') {
			number += ch;
		}
		else {
			string tmp = "";
			tmp += ch;
			output.push_back(number);
			output.push_back(tmp);
			number = "";
		}
	}
	
	output.erase(output.begin());
	output.push_back(number);
	
	return output;
}
string decode_compress(string word)
{
	vector<string> tmp = to_vector(word);
	string output = "";
	for (int i = 0; i + 1 < tmp.size(); i+=2) {
		for (int o = 0; o < stoi(tmp[i + 1]); o++) {
			output += tmp[i];
		}
	}
	return output;
}
int main()
{
	string original = "BANANA";
	for (int i = 0; i != 5; ++i) {
		original += original;
	}

	string wb_string = rotate(original);
	string compressed_string = compress(wb_string);


	string decoded_string = decode_compress(compressed_string);
	string final_string = decode(wb_string);

	cout << "Original words:" << original << "\n";
	cout << "Sending words:" << compressed_string << "\n";
	cout << "Final words:" << final_string << "\n";


	return 0;
}