##Split string with multiple delimiters
```python
import re

line = 'a     b  c'       #a string mixed with tabs and spaces
elements = re.split('\s+|\t',line)
```