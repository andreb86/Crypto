#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <bitset>
using namespace std;

class Crypto {

protected:
	int value;
	string ClearText;
	string CypherText;
	const string Pad = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	const string HexPad = "0123456789ABCDEF";
	vector<bool> Bin;

public:
	Crypto() :value(0) {};
	Crypto(const string s) :ClearText(s) {};

	// Print the clear text on screen
	void GetClearText(void) {
		cout << ClearText << endl;
	}

	// Returns an array with the indexes of the pad
	void Str2Bin() {
		this -> Bin.resize(ClearText.length() * 8, 0);
		int c = 0;
		vector<bool>::reverse_iterator v = Bin.rbegin();
		for (string::reverse_iterator it = ClearText.rbegin(); it < ClearText.rend();++it) {
			int n = *it;
			while (n != 0) { *(++v) = (n % 2 == 0 ? 0 : 1); n /= 2;	++c; }
			if (c%8 != 0) {v += (c%8)-1;}
		}
	}

	// Convert from binary to base64
	void Bin2Base64() {

	}
};

int main() {
  Crypto PWD("c");
  PWD.GetClearText();
  PWD.Str2Bin();
  return 0;
}
