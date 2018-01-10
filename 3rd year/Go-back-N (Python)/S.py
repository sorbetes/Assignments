import socket
import binascii
import struct
import sys



host = 'localhost'
port = 8210
address = (host, port)

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind(address)
server_socket.listen(5)

file = open("FILE1.txt", "w")                                       #create file to write received data

poly = "04C11DB7" 
poly = int(poly, 16)

unpacker = struct.Struct('I 105s I')

print "Listening for client . . ."
conn, address = server_socket.accept()
print "Connected to client at ", address
        
while True:
    output = conn.recv(unpacker.size);
    #print 'RECEIVED: "%s"' % binascii.hexlify(output)
    if output:
        print "Message received from client:"
        unpacked_data = unpacker.unpack(output)
        print unpacked_data
        header, payload, trailer = unpacked_data
        #--------remove bit stuffing
        # length = len(payload)
        # charNo = 0
        # y = 0
        # while (y < length-1):
        #     noOne = 0

        #     while (payload[charNo] == '1') and (noOne < 5):
        #         noOne+=1
        #         y+=1
        #         charNo+=1

        #     if (noOne == 5):
        #         payload = payload[:charNo] + payload[charNo+2:]    #remove 0 after 5 bits
        #         noOne = 0
        #         length =- 1

        #     noOne = 0
        #     charNo+=1
        #     y+=1
        #---------
	
        y = (payload[2:].count(''))-31                              #count length of payload
	    print 'payload in binary:----', str(bin(int(payload[:y], 2)))        
	    frame = str(bin(int(payload[:y], 2)))+str(32*'0')

        #get remainder
        inbinary = int(frame[2:], base = 2)        
        remainder = (inbinary%poly)
	    print '-------remainder:-----', bin(remainder)

        while (remainder != int(trailer)):
            conn.send("nak")#SEND NAK
            if output:
                print "Message received from client:"
                unpacked_data = unpacker.unpack(output)
                print unpacked_data
                header, payload, trailer = unpacked_data
                #-----remove bit stuffing
                # length = len(payload)
                # charNo = 0
                # y = 0
                # while (y < length-1):
                #     noOne = 0

                #     while (payload[charNo] == '1') and (noOne < 5):
                #         noOne+=1
                #         y+=1
                #         charNo+=1

                #     if (noOne == 5):
                #         payload = payload[:charNo] + payload[charNo+2:]    #remove 0 after 5 bits
                #         noOne = 0
                #         length =- 1

                #     noOne = 0
                #     charNo+=1
                #     y+=1
                #-----
                y = (payload[2:].count(''))-31
		print 'print payload in binary:----', str(bin(int(payload[:y], 2)))
                frame = str(bin(int(payload[:y], 2)))+str(32*'0')

                #get remainder
                inbinary = int(frame[2:], base = 2)
                remainder = (inbinary%poly)
		print '-------remainder:-----', bin(remainder)

        conn.send("ack")
        datax = int(payload[:y], 2)
        datay = binascii.unhexlify('%x' %datax)

        file.write(datay)
        
conn.close()