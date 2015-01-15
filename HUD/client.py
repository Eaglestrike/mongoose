import pygame
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
percent = 100
count = 0
cy = -750
up = False
down = False
battery = pygame.image.load("images/battery.png").convert_alpha()
skin1 = pygame.image.load("images/claw.png").convert_alpha()
clawclosed = pygame.image.load("images/clawclosed.png").convert_alpha()
clawskin = skin1
clawpos = 1
timea = 2
timeb = 30
timekeep = 0
skarm = ("")
while running:
    screen.fill((255,255,255))
    
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
            print ("yas")
        if cy < -550:
            cy += 10
            print ("yas")
    if clawpos == 2:
        if cy > -825:
            cy -= 10
            print ("yas")
        if cy < -825:
            cy += 10
            print ("yas")
    if clawpos == 3:
        if cy > -1100:
            cy -= 10
            print ("yas")
        if cy < -1100:
            cy += 10
            print ("yas")
    pygame.draw.rect(screen, ((127, 140, 141)), (1000,0,200,900), 0)
    pygame.draw.rect(screen, ((127, 140, 141)), (0,0,200,900), 0)
    pygame.draw.rect(screen, ((127, 140, 141)), (0,600,1200,300),0)
    battext=font.render(str(percent) + ("%"), 1,(255,255,255))
    timer1=font.render(str(timea) + ":" + str(skarm) + str(timeb), 1,(255,255,255))
    screen.blit(battery,(1025,50))
    pygame.draw.rect(screen, ((r,g,b)), (1030,244,90,bath), 0)
    screen.blit(clawskin,(35,cy))
    
    screen.blit(battext, (1025, 250))
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
