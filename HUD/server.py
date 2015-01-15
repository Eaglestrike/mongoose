import socket
import sys
import time
# Create a TCP/IP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# Bind the socket to the port
server_address = ('localhost', 1114)
print(sys.stderr, 'starting up on %s port %s' % server_address)
sock.bind(server_address)
# Listen for incoming connections
sock.listen(1)

while True:
    # Wait for a connection
    print(sys.stderr, 'waiting for a connection')
    connection, client_address = sock.accept()
    print(sys.stderr, 'connection from', client_address)
     #Receive the data in small chunks and retransmit it
    while True:
        connection.send(bytes("3 -160\n", "utf-8"))
        time.sleep(2)
        connection.send(bytes("2 -60\n", "utf-8"))
        time.sleep(2)
        connection.send(bytes("1 -25\n", "utf-8"))
        time.sleep(2)



        