#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <bitset>

namespace Crypto{

	// Declaration of the Base64 and alphabet
  const std::string B64Alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
  const std::string HexPad = "0123456789ABCDEF";

	// Convert string into binary boolean vector
  std::vector<bool> Str2Bin(std::string s){
    std::vector<bool> Bin (s.length() * 8, 0);
    std::vector<bool>::reverse_iterator v = Bin.rbegin();
    unsigned int c = 0;
    unsigned int n;
    for (std::string::const_reverse_iterator it = s.crbegin(); it < s.crend(); ++it) {
      n = *it;
      while (n != 0) { *v++ = (n % 2 == 0 ? 0 : 1); n /= 2; c++; }
      v += 8 - c;
      c = 0;
    }
    return Bin;
  }

  // Hex representation of a string
  std::string Str2Hex(std::string s){
    std::stringstream HexStream;
    for (std::string::const_iterator it = s.cbegin(); it < s.cend(); ++it){
      HexStream << std::hex << (int)*it;
    }
    std::string Hex = HexStream.str();
    return Hex;
  }

  // String to Base64
  std::string Str2B64(std::string s){

	std::string B64;
	std::bitset<6> b;
  std::vector<bool> Bin = Str2Bin(s);

	// Compose padding string and append 0 bits to the Bin vector
	unsigned short k = 3 - s.length() % 3;
	std::string padding	(k, '=');
	for (int i = 0; i < 2 * k; i++) Bin.push_back(0);

	//read six bits at a time and encode them
	for (int j = 0; j < Bin.size() / 6; j++){
		b.set(5, Bin[j * 6]);
		b.set(4, Bin[j * 6 + 1]);
		b.set(3, Bin[j * 6 + 2]);
		b.set(2, Bin[j * 6 + 3]);
		b.set(1, Bin[j * 6 + 4]);
		b.set(0, Bin[j * 6 + 5]);
		unsigned long l = b.to_ulong();
		B64 += B64Alphabet[l];
	}
	B64 += padding;
	return B64;
  }
}
int main() {
  std::string s;
	std::cout << "Provide a string:" << std::endl;
	std::cin >> s;
  /*std::vector<bool> Bin = Crypto::Str2Bin(s);
  for (bool i: Bin) std::cout << i;
  std::cout << std::endl;
  std::string Hex = Crypto::Str2Hex(s);
  std::cout << Hex << std::endl;*/
  std::string B64 = Crypto::Str2B64(s);
  std::cout << B64 << std::endl;
  return 0;
}
