##int -> hex in byte format
```c++
#include <stdint.h>

void intToHex(int value, uint8_t* buf, int bufSize)
{
  uint8_t* ptr = reinterpret_cast<uint8_t*>(&value);
  ptr += (bufSize - 1);
  for (int i = 0; i < bufSize; i++)
  {
    buf[i] = *ptr;
    ptr--;
  }
}
```
##int -> oct and hex using stringstream
```c++
#include <sstream>
#include <iomanip>

int main()
{
  int value = 31;
  std::stringstream stream;
  
  //31 -> 37
  stream << std::oct << value;
  std::string valueOctStr = stream.str();
  
  //clear the stringstream buffer
  stream.str(std::string());
  stream.clear();
  
  //31 -> 01F
  stream << std::setfill ('0') << std::setw(3) << std::uppercase << std::hex << value;
  std::string valueHexStr = stream.str();
  return 0;
}
```
##unsigned int -> bin using bitset
```c++
#include <bitset>

using namespace std;

int main()
{
  int val = 31;
  string binary = bitset<32>(val).to_string(); //to 32 bits binary
  return 0;
}
```
##oct and hex -> int using stringstream
```c++
#include <sstream>
#include <iomanip>

int main()
{
  int val = 0;
  std::stringstream stream;
  stream << "0x01F";
  stream >> std::hex >> val;  //val = 31
  
  //clear the stringstream buffer
  stream.str(std::string());
  stream.clear();
  
  stream << "31";
  stream >> std::oct >> val;  //val = 25
  
  return 0;
}
```
##bin -> unsigned int using bitset
```c++
#include <bitset>

int main()
{
  unsigned int number = std::bitset<32>(std::string("10101010")).to_ulong();
  return 0;
}
```