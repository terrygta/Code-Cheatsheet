##Traverse directory trees
The following function uses os.walk to iterate through files in a specific folder, and uses regular expression to find the required files.<br>
```python
import os
import re

def findFiles (path, pattern):
  result = []
  for root, dirs, files in os.walk(path):
		for file in files:
			fullPath=os.path.join(root, file)
			if re.match(pattern, fullPath):
				result.append (fullPath)
  return result
```