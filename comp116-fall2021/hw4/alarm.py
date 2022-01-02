#!/usr/bin/python3

from scapy.all import *
import argparse
import base64

incident_number = 0
user_pass_list = []

# prints the alarm message given the packet, incident type, protocol, and payload
def alarm(packet, incident, protocol, payload):

	# global variables and local variables
	global incident_number
	global user_pass_list
	output = ""
	incident_number += 1

	# generate correct alarm statement
	if(payload == ""):
		output = "%s is detected from %s (%s)!" % (incident, packet[0][IP].src, protocol)
	else:
		output = "%s is detected from %s (%s) (%s)!" % (incident, packet[0][IP].src, protocol, payload)

	# print alert if not username-password combination or if it is a new username-password combination
	if payload == "":
		print("ALERT #%s: %s" % (incident_number, output))
	elif output not in user_pass_list:
		print("ALERT #%s: %s" % (incident_number, output))
		user_pass_list.append(output)
	else:
		incident_number -= 1


# analyze packet for 6 possible incidents
def packetcallback(packet):
	try:

		# global variables
		global incident_number
		global user_FTP					# for FTP passwords, only make alert when we read password (we have username)
		global pass_FTP

		# check only packets that are TCP
		if packet.haslayer(TCP):

			# check NULL scan
			if packet[TCP].flags == "":
				alarm(packet, "NULL scan", "TCP", "")

			# check FIN scan
			if packet[TCP].flags == "F":
				alarm(packet, "FIN scan", "TCP", "")

			# check Xmas scan
			if packet[TCP].flags == "FPU":
				alarm(packet, "Xmas scan", "TCP", "")

			# check Usernames and passwords sent in-the-clear via HTTP, FTP, and IMAP
			if packet.haslayer(Raw):
				# retrieving payload
				payload = packet[TCP].load.decode("ascii").strip()

				# check HTTP username and passwords
				if packet[0][TCP].dport == 80:
					if "Authorization: Basic" in payload:
						for line in payload.splitlines():
							# if authorization basic is found, use base64 to decode credentials
							if "Authorization: Basic" in line:
								encoded_cred = line.split("Authorization: Basic ")[1]
								decoded_cred = str(base64.b64decode(encoded_cred))
								user_http = ""
								pass_http = ""
								for i in range(len(decoded_cred)):
									if decoded_cred[i] == ":":
										user_http = decoded_cred[2:i]
										pass_http = decoded_cred[i+1:-1]
										break
								user_pass_http = "username:" + user_http + ", password:" + pass_http
								alarm(packet, "Usernames and passwords sent in-the-clear", "HTTP", user_pass_http)

				# FTP username and passwords
				if packet[TCP].dport == 21:
					if "USER" in payload:
						user_FTP = payload.split("USER")[1].strip()
					if "PASS" in payload:
						pass_FTP = payload.split("PASS")[1].strip()
						user_pass_FTP = "username:" + user_FTP + ", password:" + pass_FTP
						alarm(packet, "Usernames and passwords sent in-the-clear", "FTP", user_pass_FTP)
						user_FTP = ""
						passw_FTP = ""

				# IMAP username and passwords
				if packet[TCP].dport == 143:
					if "LOGIN" in payload:
						splitted = payload.split()
						user_imap = splitted[2]
						pass_imap = splitted[3][1:-1]
						user_pass_imap = "username:" + user_imap + ", password:" + pass_imap
						alarm(packet, "Usernames and passwords sent in-the-clear", "IMAP", user_pass_imap)


			# check Nikto scan
			if packet[TCP].dport == 80 and packet.haslayer(Raw):
				payload = packet[TCP].load.decode("ascii").strip()
				if "Nikto" in payload:
					alarm(packet, "Nikto scan", "HTTP", "")

			# check Remote Desktop Protocol
			if packet[TCP].dport == 3389 and packet.haslayer(Raw):
				alarm(packet, "RDP scan", "TCP", "")

	except:
		pass

parser = argparse.ArgumentParser(description='A network sniffer that identifies basic vulnerabilities')
parser.add_argument('-i', dest='interface', help='Network interface to sniff on', default='eth0')
parser.add_argument('-r', dest='pcapfile', help='A PCAP file to read')
args = parser.parse_args()
if args.pcapfile:
	try:
		print("Reading PCAP file %(filename)s..." % {"filename" : args.pcapfile})
		sniff(offline=args.pcapfile, prn=packetcallback)
	except:
		print("Sorry, something went wrong reading PCAP file %(filename)s!" % {"filename" : args.pcapfile})
else:
	print("Sniffing on %(interface)s... " % {"interface" : args.interface})
	try:
		sniff(iface=args.interface, prn=packetcallback)
	except:
		print("Sorry, can\'t read network traffic. Are you root?")