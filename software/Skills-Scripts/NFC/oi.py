


import time

with open('Data.txt', 'r') as arq:
    data = arq.readlines()

time.sleep(3)    
print data
print type(data)
