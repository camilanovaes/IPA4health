
#execfile("/home/pi/HARDWARE/MFRC522-python/hello.py")

import sys
import subprocess

s2_out = subprocess.check_output([sys.executable, "hello.py", "oi"])

#print s2_out
