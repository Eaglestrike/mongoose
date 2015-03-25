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