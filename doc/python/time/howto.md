##Convert date string to timestamp from 1970
```python
import time

someday = '2015-3-30 15:40:08'
somedaySec = time.mktime(time.strptime(someday, '%Y-%m-%d %H:%M:%S'))
```
##Convert timestamp from 1970 to date string
```python
import datetime

somedaySec = 2147483647
someday = datetime.fromtimestamp(somedaySec).strftime('%Y-%m-%d %H:%M:%S')
```
