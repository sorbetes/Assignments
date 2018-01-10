import socket
import binascii
import struct
import sys
import time
import random
from time import sleep

serverName = 'localhost'
serverPort = 8210
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect((serverName, serverPort))

file = open("newfile.txt", "w")							#create file
line = 'bts613sg'
for x in range(0, 1500):
	file.write(line + '\n') #write to file
	line = ''.join(random.sample((line), len((line))))
file.close()

SeqNo = 1;												#for header
poly = "04C11DB7"										#polynomial in hex, 32bit
polyint = int(poly, 16)									#hex string to int

file1 = open('newfile.txt')								#open file containing alphanumeric characters
payload = file1.readline()								#read line from file

while payload:											#while there's still a line to be read
	#-------------append FCS to payload
	binaryvalue = bin(int(binascii.hexlify(payload), 16))
	print 'payload in binary:----', binaryvalue

	#concactenate
	frame = str(binaryvalue)+str(32*'0')

	#get remainder
	inbinary = int(frame, base = 2)
	remainder = (inbinary%polyint)
	print '-------remainder:-----', bin(remainder)

	#new payload
	newpayload = str(binaryvalue)+str("{0:032b}".format(remainder))
	#-------------bit stuffing
	# length = len(newpayload)
	# charNo = 0
	# y = 0
	# while (y < length-1):
	# 	noOne = 0

	# 	while (newpayload[charNo] == '1') and (noOne < 5):
	# 		noOne+=1
	# 		y+=1
	# 		charNo+=1

	# 	if (noOne == 5):
	# 		newpayload = newpayload[:charNo] + '0' + newpayload[charNo:]	#stuff 0
	# 		noOne = 0

	# 	noOne = 0
	# 	charNo+=1
	# 	y+=1
	#-------------send
	values = (SeqNo, newpayload, remainder)
	packer = struct.Struct('I 105s I')
	packed_data = packer.pack(*values)
	
 	#print 'SENDING: "%s"' % binascii.hexlify(packed_data), values
 	client_socket.sendall(packed_data)

 	while client_socket.recv(2048) != "ack":
 		print "waiting for ack"
 		client_socket.sendall(packed_data)
	
	print "ack received!"
	SeqNo += 1;
	sleep(5)
	payload = file1.readline()

file1.close()
client_socket.close()

