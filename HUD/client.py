from threading import Thread
import cv2
import pygame
import numpy as np
import time
import socket as socket

clock = pygame.time.Clock()
def runA():
    global img
    print("running a")
    c = cv2.VideoCapture(0)
    
    In=1
    
    
    
    def cvimage_to_pygame(image):
        """Convert cvimage into a pygame image"""
        return pygame.image.frombuffer(image.tostring(), image.shape[1::-1],
                                       "RGB")
    
    
    
    while(1):
        _,f = c.read()
        #cv2.imshow('e2',f)
        
        imgf = cv2.cvtColor(f, cv2.COLOR_BGR2RGB); 
        img = cvimage_to_pygame(imgf)
 # update the display
 # only three images per second
        In += 1
        if cv2.waitKey(5)==27:
            break
        clock.tick(60)
    cv2.destroyAllWindows()

def runB():
    global clawpos

    pygame.init()
    screen = pygame.display.set_mode((1200,900))
    bath = -160
    running = True
    img = pygame.image.load("images/webcam.png").convert_alpha()
    r = 46 
    g = 204
    b = 113
    timer = 0
    timing = True
    font=pygame.font.Font(None,100)
    batteryf = pygame.font.Font(None, 50)
    percent = 100
    count = 0
    cy = -750
    up = False
    down = False
    battery = pygame.image.load("images/battery.png").convert_alpha()
    skin1 = pygame.image.load("images/claw.png").convert_alpha()
    clawclosed = pygame.image.load("images/clawclosed.png").convert_alpha()
    clawskin = skin1

    timea = 2
    timeb = 30
    timekeep = 0
    skarm = ("")
    while running:
        
        print(clawpos)

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
        if clawpos >= 3:
            clawpos = 3
        if clawpos <= 1:
            clawpos = 1
        if clawpos == 1:
            if cy > -550:
                cy -= 10
                  
            if cy < -550:
                cy += 10
                  
        if clawpos == 2:
            if cy > -825:
                cy -= 10
                  
            if cy < -825:
                cy += 10
                  
        if clawpos == 3:
            if cy > -1100:
                cy -= 10
                  
            if cy < -1100:
                cy += 10
                  
        

        battext=batteryf.render(str(percent) + ("%"), 1,(255,255,255))
        timer1=font.render(str(timea) + ":" + str(skarm) + str(timeb), 1,(255,255,255))
        screen.blit(battery,(1025,50))
        pygame.draw.rect(screen, ((r,g,b)), (1030,244,90,bath), 0)
        screen.blit(clawskin,(35,cy))
        screen.blit(img, (285, 100))
        
        screen.blit(battext, (1047, 150))
        screen.blit(timer1,(550,600))
        if timekeep >= 300:
            timeb -=1
            timekeep = 0
        if timeb <10:
            skarm = ("0")
        if timeb <= 0:
           timeb = 59
           skarm = ("")
           timea -=1
        if bath >= -80:
            r = 241
            g = 196
            b = 15 
        if bath >= -40:
            r = 192
            g = 57
            b = 43  
        if bath >= -1:
            timing = False
        if timing:
            if timer == 100:
                bath += 1.6
                timer = 0
                percent -= 1
        if timing:
            timer += 1
        timekeep += 1
        pygame.display.flip()
    pygame.quit()
def runC():
    print('running c')
    global clawpos
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
           


if __name__ == "__main__":
    t1 = Thread(target = runA)
    t2 = Thread(target = runC)
    t3 = Thread(target = runB)

    t1.setDaemon(True)
    t2.setDaemon(True)
    t3.setDaemon(True)
    t1.start()
    t2.start()
    t3.start()
    while True:
        pass