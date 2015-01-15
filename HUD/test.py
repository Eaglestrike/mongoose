from threading import Thread
import cv2
import pygame
import numpy as np
import time
clock = pygame.time.Clock()
def runA():
    global img
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
    pygame.init()
    screen = pygame.display.set_mode((1200,900))
    bath = -160
    running = True
    r = 34
    g = 139
    b = 34
    timer = 0
    timing = True
    font=pygame.font.Font(None,100)
    percent = 100
    count = 0
    cy = -750
    up = False
    down = False
    battery = pygame.image.load("images/battery.png").convert_alpha()
    skin1 = pygame.image.load("images/claw.png").convert_alpha()
    
    
    roboarm = skin1
    while running:
        screen.fill((255,255,255))
        
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            if event.type == pygame.KEYDOWN:
                
                if event.key == pygame.K_UP:
                    up = True
                if event.key == pygame.K_DOWN:
                    down = True
            if event.type == pygame.KEYUP:
                
                if event.key == pygame.K_UP:
                    up = False
                if event.key == pygame.K_DOWN:
                    down = False
        if cy >= -300:
            down = False
        if cy <= -1200:
            up = False
        if up:
            cy -= 1
        if down:
            cy += 1
        pygame.draw.rect(screen, ((0,0,0)), (950,0,250,900), 0)
        pygame.draw.rect(screen, ((0,0,0)), (0,0,250,900), 0)
        battext=font.render(str(percent) + ("%"), 1,(255,255,255))
        screen.blit(battery,(1000,50))
        pygame.draw.rect(screen, ((r,g,b)), (1010,240,80,bath), 0)
        screen.blit(roboarm,(50,cy))
        
        screen.blit(battext, (1000, 250))
        screen.blit(img,(300,0))
    
    
                    
       
        if bath >= -80:
            r = 255
            g = 215
            b = 0
        if bath >= -40:
            r = 178
            g = 34
            b = 34
        if bath >= -1:
            timing = False
        if timing:
            if timer == 100:
                bath += 1.6
                timer = 0
                percent -= 1
        if timing:
            timer += 1
        pygame.display.flip()
        clock.tick(60)
    pygame.quit()

if __name__ == "__main__":
    t1 = Thread(target = runA)
    t2 = Thread(target = runB)
    t1.setDaemon(True)
    t2.setDaemon(True)
    t1.start()
    t2.start()
    while True:
        pass
