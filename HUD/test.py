<<<<<<< HEAD
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
=======
import socket
HOST="10.1.14.2"
PORT=5801
readbuffer = ""
s=socket.socket( )
while(True):
    try:
        
        s.connect((HOST, PORT))
        serverstat = True
        while(True):
          


            try:
                
                readbuffer = readbuffer+s.recv(1024).decode('utf-8')
               
              
                temp = str.split(readbuffer, "\n")
         
                readbuffer=temp.pop( )
                for line in temp:
                    
                    line = str.rstrip(line)
                    line = str.split(line)
                    print(line)
            except:
                print("error")
    except:
        #print("Server not running")
        serverstat=False
>>>>>>> ff84527da1b5c27169665c8984792fe437e3fbcb
