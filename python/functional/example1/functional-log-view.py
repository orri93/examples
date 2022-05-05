import collections
import urllib.request
import re
 
# Read the log file, split into lines
logurl = "https://raw.githubusercontent.com/elastic/examples/master/Common%20Data%20Formats/apache_logs/apache_logs"
logfile = urllib.request.urlopen(logurl).read().decode("utf8")
lines = logfile.splitlines()
 
# using regular expression to extract IP address and status code from a line
def ip_and_code(logline):
  m = re.match(r'([\d\.]+) .*? \[.*?\] ".*?" (\d+) ', logline)
  return (m.group(1), m.group(2))
 
print(ip_and_code(lines[0]))

def is404(pair):
  return pair[1] == "404"
def getIP(pair):
  return pair[0]
def count_ip(count_item):
  ip, count = count_item
  return (count, ip)

# transform each line into (IP address, status code) pair
ipcodepairs = map(ip_and_code, lines)
# keep only those with status code 404
pairs404 = filter(is404, ipcodepairs)
# extract the IP address part from each pair
ip404 = map(getIP, pairs404)
# count the occurrences, the result is a dictionary of IP addresses map to the count
ipcount = collections.Counter(ip404)
# convert the (IP address, count) tuple into (count, IP address) order
countip = map(count_ip, ipcount.items())
# find the tuple with the maximum on the count
print(max(countip))
