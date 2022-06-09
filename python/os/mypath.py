# How do I get the path of the Python script I am running in?
# https://stackoverflow.com/questions/595305/how-do-i-get-the-path-of-the-python-script-i-am-running-in

import os
import sys

print(__file__)
print(os.path.realpath(__file__))
print(os.path.abspath(__file__))
print(os.path.dirname(__file__))

# Real Path will first resolve any symbolic links in the path, and then return the absolute path.
print(os.path.realpath(os.path.dirname(__file__)))

# Abs Path returns the absolute path, but does NOT resolve symlinks in its argument.
print(os.path.abspath(os.path.dirname(__file__)))

print(sys.argv[0])
