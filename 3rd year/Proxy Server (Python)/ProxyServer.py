import urllib3, certifi, os.path, thread, time
from urllib3 import PoolManager, Timeout
import socket, sys, string, ssl, re
from socket import *
from urlparse import urlparse

proxyServerPort = 8000
proxyServerSocket = socket(AF_INET,SOCK_STREAM)
proxyServerSocket.bind(('localhost', proxyServerPort))
proxyServerSocket.listen(5)
print 'The proxy server is ready to receive...'

http = urllib3.PoolManager(		
	num_pools = 10,				#number of connection pools to cache before discarding the least recently used pool
	cert_reqs='CERT_REQUIRED',	#for https, get certificate	
	ca_certs=certifi.where(),
	)

# def new_request(url):								#thread to make a new request
# 	file1 = open(file_name + ".txt", "w")			#create file to place data on / cache it
# 	a = http.request('GET', url)
# 	data1 = a.data
# 	file1.write(data1)								#data written on text file / cached
# 	file1.close()
# 	thread.start_new_thread(send_data, (data1, ))	#go to thread to send the data to web client


# def send_data(data1):								#thread to send data to web client
# 	connectionSocket.send(data1)

blocked_list = []				
a = raw_input("Would you like to block any URLs? (y/n) ")	#ask user for urls to be blocked
while (a == 'y'):
	b = raw_input("Enter URL to block: (in www.abc.com format)")
	blocked_list.append(b)

	a = raw_input("Would you like to block any other URLs? (y/n) ")

print "Blocked URL(s): ", blocked_list

while 1:
	
	try:
		connectionSocket, addr = proxyServerSocket.accept()
		requestData = connectionSocket.recv(1024)

		# Match Regular Expression
		first_line = requestData.split('\n')[0] #First line of data, where URL is

		loc_ = first_line.find('443')			#Check if '443' is attached to end of URL

		if (loc_ > 0):							#If yes, Remove '443'
			url = first_line.split(' ')[1]		#Split URL from first line
			url = url.split(':')[0]
			url = 'https://' + url
			output = urlparse(url)

		else:
			url = first_line.split(' ')[1]		#Split URL from first line
			output = urlparse(url)

		if (output.hostname) in blocked_list:	#Check if URL is blocked
			print 'Blocked URL'

		else:
			#WITH THREADING AND CACHING------------
			# file_name = (output.hostname).split('.')[1]			#create a file name using URL
			# in_cache = os.path.isfile(file_name) 				#if the file is inside the folder
			# if (in_cache == True):								#ie if it is cached
			# 	file1 = open(file_name + ".txt")				#open the file
			# 	data1 = file1.read()						
			# 	file1.close()									
			# 	thread.start_new_thread(send_data, (data1, ))	#send the file to send_data thread where it will be
			# else:												#sent back to web client
			# 	thread.start_new_thread(new_request, (url, ))	#go to thread to make a new request
			#---------------------------------------

			a = http.request('GET', url)
			data1 = a.data
			connectionSocket.send(data1)

	except KeyboardInterrupt:
		connectionSocket.close()
		proxyServerSocket.close()
		print "\nProxy Server Shutting Down"
		print "BYYYYEEEEEE !!"
		sys.exit(1)

	#proxyServerSocket.close()


