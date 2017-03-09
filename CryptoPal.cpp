#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <bitset>

namespace Encrypt{

	// Declaration of the Base64 and alphabet
  const std::string B64pad = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

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
    std::stringstream B64Stream;
    std::string B64;
    std::string padding;

    for (std::string::const_iterator it = s.cbegin(); it < s.cend(); ++it){
      switch (s.cend() - it){
        case 1:
          B64Stream << B64pad.at((*it & 0xFC) >> 2);
          B64Stream << B64pad.at((*it++ & 0x03) << 4);
          break;
        case 2:
          B64Stream << B64pad.at((*it & 0xFC) >> 2);
          B64Stream << B64pad.at((*it++ & 0x03) << 4 | (*it & 0xF0) >> 4);
          B64Stream << B64pad.at((*it++ & 0x0F) << 2);
          break;
        default:
          B64Stream << B64pad.at((*it & 0xFC) >> 2);
          B64Stream << B64pad.at((*it++ & 0x03) << 4 | (*it & 0xF0) >> 4);
          B64Stream << B64pad.at((*it++ & 0x0F) << 2 | (*it & 0xC0) >> 6);
          B64Stream << B64pad.at((*it & 0x3F));
      }
    }
    if (s.length() % 3 != 0){
      padding.assign(3 - s.length() % 3, '=');
      B64 = B64Stream.str() + padding;
    } else {
      B64 = B64Stream.str();
    }
    return B64;
  }

  /*std::string Hex2B64(std::string s){

  }*/

}

int main() {
  std::string s;
  std::cout << "Provide a string:" << std::endl;
  std::cin >> s;
  std::string B64 = Encrypt::Str2B64(s);
  std::cout << B64 << std::endl;
  return 0;
}
