COMP116: Lab 8
Eli Dow

Overall, fuzzer.py is a fuzz testing that determines if the url
http://www.cs.tufts.edu/comp/120/hackme.php?token=Foodler has a XXS vulnerability.
Fuzzing is an automated software testing technique to throw invalid or unexpected
data at a computer program. The fuzzing is done through the urllib.request module and
urlopen function. Through this function, the program performs a HTTP get request to the given url and inserts a payload
(alert) into the token field of that URL. This results in the payload coming up in the response of that request, meaning
that there was a vulnerability.

Only the basic requirements were completed.

I discussed possible ways to make an HTTP get request with Jerry Wang. I also got help from
an anonymous student on piazza.

This assignment took me 3 hours. It took 2 hours to try to get the requests module to work, and 1 hour for the
rest of the assignment.