# Python certifi: How to Use SSL Certificate in Python
# https://appdividend.com/2022/06/01/python-certifi

import certifi
import requests

#url = 'https://api.github.com'
url = 'https://mast.stsci.edu/portal/Mashup/Clients/Mast/Portal.html'
certfile = 'certicate.pem'

try:
  print('Checking connection to URL...')
  test = requests.get(url)
  print('Connection to URL OK.')
except requests.exceptions.SSLError as err:
  print('SSL Error. Adding custom certs to Certifi store...')
  cafile = certifi.where()
  with open(certfile, 'rb') as infile:
    customca = infile.read()
  with open(cafile, 'ab') as outfile:
    outfile.write(customca)
  print('That might have worked.')
