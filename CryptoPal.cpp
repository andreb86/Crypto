#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <bitset>
/*
class Crypto {

protected:
  int value;
  std::string ClearText;
  std::string CypherText;
  const std::string Pad = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
  const std::string HexPad = "0123456789ABCDEF";
  std::vector<bool> Bin;
  std::string EncodedB64;
  std::bitset<6> b;

public:
  Crypto() :value(0) {};
  Crypto(const std::string s) :ClearText(s) {this -> Bin.resize(ClearText.length() * 8, 0);}
  ~Crypto(){};

  // Print the clear text on screen
  void GetClearText() {
    std::cout << ClearText << std::endl;
  }
  
  // Returns an array with the indexes of the pad
  void Str2Bin() {
    unsigned int c = 0;
    unsigned int n;
    std::vector<bool>::reverse_iterator v = Bin.rbegin();
    for (std::string::reverse_iterator it = ClearText.rbegin(); it < ClearText.rend(); ++it) {
      n = *it;
      while (n != 0) { *v++ = (n % 2 == 0 ? 0 : 1); n /= 2; c++; }
      v += 8 - c;
      c = 0;
    }
    for (bool i : Bin) std::cout << i;
  }

  // Convert from binary to base64
  void Bin2Base64() {
    int c = 5;
    unsigned long int t;
    for (bool v : Bin) {
      while (c--) {
	b.set(c, v);
	if (c == 0){
	  t = b.to_ulong();
	  EncodedB64 += Pad[t];
	  c = 5;
	  b.reset();
	}
      }
      std::cout << EncodedB64 << std::endl;
    }
  }
};*/

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
  
  // Base64 Encoding
  std::string Str2B64(std::string s){
    std::string B64;
    std::vector<bool> Bin = Str2Bin(s);
    std::string padding(s.length() % 3, "=");  
  }
}
int main() {
  std::string s = "CI";
  std::vector<bool> Bin = Crypto::Str2Bin(s);
  for (bool i: Bin) std::cout << i;
  std::cout << std::endl;
  std::string Hex = Crypto::Str2Hex(s);
  std::cout << Hex;
  return 0;
}
