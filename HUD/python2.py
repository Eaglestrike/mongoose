
from threading import Thread
import math, pygame, time
import socket as socket
from urllib2 import urlopen
clock = pygame.time.Clock()
global aspect, status, armstat, armcalstat, elevstat, elevcalstat, matchtime
armstat = "False"
armcalstat = "True"
elevstat = "False"
elevcalstat = "True"




    
def runDisplay():
    print("Running Display Thread")
    
    serverstat = False
    matchtime = 0

    
    timem="2:30"
    
    pygame.init()
    screen = pygame.display.set_mode((320,240))
    pygame.display.set_caption("HUD")
    
    aspect = float(screen.get_width())/1200
    float(aspect)
    #pygame.display.toggle_fullscreen()
    running = True
    font=pygame.font.Font(None,int(800*aspect))
    


    while running:
        txtstatus = (255, 255, 255)
        status = (46, 204, 113)
        if armstat == "True" and elevstat == "True":
            status = (192, 57, 43)       
        if armstat == "True" and elevstat == "False":
            status = (142, 68, 173)
        if armstat == "False" and elevstat == "True":
            status = (211, 84, 0)
        if armcalstat == "False" and elevcalstat == "False":
            status = (52, 73, 94)
        if armcalstat == "True" and elevcalstat == "False":
            status = (241, 196, 15)
        if armcalstat == "False" and elevcalstat == "True":
            status = (41, 128, 185)
        if armcalstat == "False" and elevcalstat == "False" and elevstat == "True" and armstat == "True":
            status = (236, 240, 241)
            txtstatus = (0, 0, 0)
        screen.fill(status)
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE:
                    pygame.display.toggle_fullscreen()
        
        timer1=font.render(timem, 1,txtstatus)
       
        
        
        
        screen.blit(timer1,(screen.get_width()/2*aspect,screen.get_height()/2*aspect))
        
        timetemp=matchtime

        timem = str(timetemp//60)+":"+str(timetemp%60)


        

    

        pygame.display.flip()
    pygame.quit()
def runBackend():
    print("Running Backend Thread")
    serverstat=False
    HOST="10.1.14.2"
    PORT=5802
    readbuffer = ""
    s=socket.socket( )
    while(True):
        try: 
            s.connect((HOST, PORT))
            serverstat = True
            while(True):
                    readbuffer = s.recv(1024)
                    print readbuffer
                    temp = readbuffer.split("\n")
                    temp="".join(temp)
                    temp=temp.split()
                    armstat = temp[0]
                    armcalstat = temp[1]
                    elevstat = temp[2]
                    elevcalstat = temp[3]
                    matchtime = temp[4]
        except:

            serverstat=False
           

#um
if __name__ == "__main__":

    t1 = Thread(target = runBackend)


    t3 = Thread(target = runDisplay)

    t1.setDaemon(True)

    t3.setDaemon(True)
    t1.start()

    t3.start()
    while True:
        pass
