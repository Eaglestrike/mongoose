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
                
                readbuffer = readbuffer+s.recv(1024).decode('utf-8')
               
              
                temp = readbuffer.split("\n")
         
                readbuffer=temp.pop( )
                print temp
            #except:
            #    print("error")
    #except:
    #    sprint("Server not running")
    #    serverstat=False