##decimal -> bin, oct, hex
bin(), oct() and hex() are the python built-in functions that can convert the given decimal number into respective number systems. These functions take an integer (in decimal) and return a string. <br>
```python
num = 31
numBin = bin(dec) #'0b11111'
numOct = oct(dec) #'037'
numHex = hex(dec) #'0x1f'
```
##bin, oct, hex -> decimal
int(numStr, base) can be used to convert binary, octal and hexadecimal in string format to a decimal integer.<br>
```python
binStr = '0b11111'
num = int(binStr, 2)
octStr = '037'
num2 = int(octStr, 8)
hexStr = '0x1f'
num3 = int(hexStr, 16)
```