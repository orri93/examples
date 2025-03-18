# import requi9red module
import sys
 
# append the path of the
# parent directory
sys.path.append("..")
 
# import method from sibling 
# module
from SiblingB import methodB
 
# call method
s = methodB()
print(s)
