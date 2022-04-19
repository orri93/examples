# Python program to read
# json file
# See https://www.geeksforgeeks.org/read-json-file-using-python/


import json

# Opening JSON file
f = open('data.json')

# returns JSON object as
# a dictionary
data = json.load(f)
# Syntax:
#   json.loads(jsonstring)        # for Json string
#   json.loads(fileobject.read()) # for fileobject

# Iterating through the json
# list
for i in data['emp_details']:
  print(i)

# Closing file
f.close()
