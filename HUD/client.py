from threading import Thread
import math
import pygame
import numpy as np
import time
import socket as socket
global vision
import cv2
from urllib.request import urlopen
vision = True
clock = pygame.time.Clock()
def runA():
    while(True):
            global img
            print("running a")
            
            def cvimage_to_pygame(image):
                """Convert cvimage into a pygame image"""
                return pygame.image.frombuffer(image.tostring(), image.shape[1::-1],
                                               "RGB")
            stream=urlopen('http://127.0.0.1:8080/?action=stream')
            buff=b''
            while True:
                buff+=stream.read(8112)
                a = buff.find(b'\xff\xd8')
                b = buff.find(b'\xff\xd9')
                if a!=-1 and b!=-1:
                    jpg = buff[a:b+2]
                    buff= buff[b+2:]
                    i = cv2.imdecode(np.fromstring(jpg, dtype=np.uint8),1)
                    imgf=cv2.cvtColor(i, cv2.COLOR_BGR2RGB)
                    #imgf = cv2.resize(imgf,None,fx=.5, fy=.5, interpolation = cv2.INTER_CUBIC)
                    img=cvimage_to_pygame(imgf)
                    clock.tick(60)
                    if cv2.waitKey(1) ==27:
                        exit(0)   
                        
                        
            
            
            

    
 # u    pdate the display
 # o    nly three images per second


        #except:
            print("Vision not ready or working")
    
def runB():
    global clawpos
    global bath
    percent=0
    timem="2:30"
    clawpos=0
    pygame.init()
    screen = pygame.display.set_mode((1200,900))
    bath = -160
    running = True
    
    r = 46 
    g = 204
    b = 113
    timer = 0
    timing = True
    font=pygame.font.Font(None,100)
    batteryf = pygame.font.Font(None, 50)

    count = 0
    cy = -750
    up = False
    down = False
    battery = pygame.image.load("images/battery.png").convert_alpha()
    skin1 = pygame.image.load("images/claw.png").convert_alpha()
    clawclosed = pygame.image.load("images/clawclosed.png").convert_alpha()
    clawskin = skin1


    timekeep = 0
    skarm = ("")
    while running:
        


        screen.fill((127, 140, 141))
        
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            if event.type == pygame.KEYDOWN:
                
                if event.key == pygame.K_UP:
                    clawpos += 1
                if event.key == pygame.K_DOWN:
                    clawpos -= 1
                if event.key == pygame.K_SPACE:
                    clawskin = clawclosed
            if event.type == pygame.KEYUP:
                
                if event.key == pygame.K_UP:
                    up = False
                if event.key == pygame.K_DOWN:
                    down = False
                if event.key == pygame.K_SPACE:
                    clawskin = skin1
        if cy >= -300:
            down = False
        if cy <= -1200:
            up = False
        if up:
            cy -= 1
        if down:
            cy += 1
        if clawpos >= 6:
            clawpos = 6
        if clawpos <= 1:
            clawpos = 1
        if clawpos == 1:
            if cy > -550:
                cy -= 10
                  
            if cy < -550:
                cy += 10
                  
        if clawpos == 2:
            if cy > -683:
                cy -= 10
                  
            if cy < -683:
                cy += 10
                  
        if clawpos == 3:
            if cy > -816:
                cy -= 10
                  
            if cy < -816:
                cy += 10
        if clawpos == 4:
            if cy > -949:
                cy -= 10
                  
            if cy < -949:
                cy += 10
                  
        if clawpos == 5:
            if cy > -1082:
                cy -= 10
                  
            if cy < -1082:
                cy += 10
                  
        if clawpos == 6:
            if cy > -1215:
                cy -= 10
                  
            if cy < -1215:
                cy += 10
                  
        

        battext=batteryf.render(str(percent) + ("%"), 1,(255,255,255))
        timer1=font.render(timem, 1,(255,255,255))
        screen.blit(battery,(1025,50))
        pygame.draw.rect(screen, ((r,g,b)), (1030,244,90,bath), 0)
        screen.blit(clawskin,(35,cy))
        
        
        screen.blit(battext, (1047, 150))
        screen.blit(timer1,(550,600))
        try:
            screen.blit(img, (285, 100))
        except:
            pass
        timetemp=150-matchtime

        timem = str(timetemp//60)+":"+str(timetemp%60)


        if bath >= -2000:
                r = 46 
                g = 204
                b = 113
                if bath > -80:
                    r = 241
                    g = 196
                    b = 15 
                    if bath >= -40:
                        r = 192
                        g = 57
                        b = 43  

        
        percent = math.floor(bath/-1.6)

        pygame.display.flip()
    pygame.quit()
def runC():
    print('running c')
    global clawpos
    global bath
    global matchtime
    HOST="127.0.0.1"
    PORT=1114
    readbuffer = ""
    s=socket.socket( )
    s.connect((HOST, PORT))
    while(True):
        readbuffer = readbuffer+s.recv(2).decode("UTF-8")
        temp = str.split(readbuffer, "\n")

        readbuffer=temp.pop( )
        for line in temp:
            line = str.rstrip(line)
            line = str.split(line)
            clawpos = int(line[0])
            bath = int(line[1])
            matchtime=int(line[2])
           


if __name__ == "__main__":

    t1 = Thread(target = runC)

    t2 = Thread(target = runA)
    t3 = Thread(target = runB)

    t1.setDaemon(True)
    t2.setDaemon(True)
    t3.setDaemon(True)
    t1.start()
    t2.start()
    t3.start()
    while True:
        pass