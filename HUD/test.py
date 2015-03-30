
import socket
HOST="10.1.14.2"
PORT=5802
readbuffer = ""
s=socket.socket( )
while(True):
    #try:
        
        s.connect((HOST, PORT))
        serverstat = True
        while(True):
          


            #try:
                
                #readbuffer = readbuffer+s.recv(1024).decode('utf-8')
                readbuffer = s.recv(1024)
                
                temp = readbuffer.split("\n")
                
                toprint="test"
                print(toprint)
                toprint = "".join(temp)
                print(toprint)
                print toprint.split()
            #except:
            #    print("error")
    #except:
    #    sprint("Server not running")
    #    serverstat=False
