import socket
import sys
import time
import random
# Create a TCP/IP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# Bind the socket to the port
server_address = ('localhost', 1115)
print('starting up on %s port %s' % server_address)
sock.bind(server_address)
# Listen for incoming connections
pdp = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]

sock.listen(1)

while True:
    # Wait for a connection
    print('waiting for a connection')
    connection, client_address = sock.accept()
    print('connection from', client_address)
     #Receive the data in small chunks and retransmit it
    timem=0
    while True:
        portcount=0
        for port in pdp:
            pdp[portcount] = random.randrange(0,3)
            portcount+=1

        #print(pdp[0])
        connection.send(bytes("1 -160 "+str(timem)+" "+str(pdp[0])+" "+str(pdp[1])+" "+str(pdp[2])+" "+str(pdp[3])+" "+str(pdp[4])+" "+str(pdp[5])+" "+str(pdp[6])+" "+str(pdp[7])+" "+str(pdp[8])+" "+str(pdp[9])+" "+str(pdp[10])+" "+str(pdp[11])+" "+str(pdp[12])+" "+str(pdp[13])+" "+str(pdp[14])+" "+str(pdp[15])+" "+"\n", "utf-8"))
        timem+=1
        time.sleep(1)
        portcount=0
        for port in pdp:
            pdp[portcount] = random.randrange(0,3)
            portcount+=1
        connection.send(bytes("2 -60 "+str(timem)+" "+str(pdp[0])+" "+str(pdp[1])+" "+str(pdp[2])+" "+str(pdp[3])+" "+str(pdp[4])+" "+str(pdp[5])+" "+str(pdp[6])+" "+str(pdp[7])+" "+str(pdp[8])+" "+str(pdp[9])+" "+str(pdp[10])+" "+str(pdp[11])+" "+str(pdp[12])+" "+str(pdp[13])+" "+str(pdp[14])+" "+str(pdp[15])+" "+"\n", "utf-8"))
        timem+=1
        time.sleep(1)
        portcount=0
        for port in pdp:
            pdp[portcount] = random.randrange(0,3)
            portcount+=1
        connection.send(bytes("3 -25 "+str(timem)+" "+str(pdp[0])+" "+str(pdp[1])+" "+str(pdp[2])+" "+str(pdp[3])+" "+str(pdp[4])+" "+str(pdp[5])+" "+str(pdp[6])+" "+str(pdp[7])+" "+str(pdp[8])+" "+str(pdp[9])+" "+str(pdp[10])+" "+str(pdp[11])+" "+str(pdp[12])+" "+str(pdp[13])+" "+str(pdp[14])+" "+str(pdp[15])+" "+"\n", "utf-8"))
        timem+=1
        time.sleep(1)
        portcount=0
        for port in pdp:
            pdp[portcount] = random.randrange(0,3)
            portcount+=1
        connection.send(bytes("4 -160 "+str(timem)+" "+str(pdp[0])+" "+str(pdp[1])+" "+str(pdp[2])+" "+str(pdp[3])+" "+str(pdp[4])+" "+str(pdp[5])+" "+str(pdp[6])+" "+str(pdp[7])+" "+str(pdp[8])+" "+str(pdp[9])+" "+str(pdp[10])+" "+str(pdp[11])+" "+str(pdp[12])+" "+str(pdp[13])+" "+str(pdp[14])+" "+str(pdp[15])+" "+"\n", "utf-8"))
        timem+=1
        time.sleep(1)
        portcount=0
        for port in pdp:
            pdp[portcount] = random.randrange(0,3)
            portcount+=1
        connection.send(bytes("5 -60 "+str(timem)+" "+str(pdp[0])+" "+str(pdp[1])+" "+str(pdp[2])+" "+str(pdp[3])+" "+str(pdp[4])+" "+str(pdp[5])+" "+str(pdp[6])+" "+str(pdp[7])+" "+str(pdp[8])+" "+str(pdp[9])+" "+str(pdp[10])+" "+str(pdp[11])+" "+str(pdp[12])+" "+str(pdp[13])+" "+str(pdp[14])+" "+str(pdp[15])+" "+"\n", "utf-8"))
        timem+=1
        time.sleep(1)
        portcount=0
        for port in pdp:
            pdp[portcount] = random.randrange(0,3)
            portcount+=1
        connection.send(bytes("6 -25 "+str(timem)+" "+str(pdp[0])+" "+str(pdp[1])+" "+str(pdp[2])+" "+str(pdp[3])+" "+str(pdp[4])+" "+str(pdp[5])+" "+str(pdp[6])+" "+str(pdp[7])+" "+str(pdp[8])+" "+str(pdp[9])+" "+str(pdp[10])+" "+str(pdp[11])+" "+str(pdp[12])+" "+str(pdp[13])+" "+str(pdp[14])+" "+str(pdp[15])+" "+"\n", "utf-8"))
        timem+=1
        time.sleep(1)
