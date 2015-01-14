import pygame
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
timea = 2
timeb = 30

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

    pygame.draw.rect(screen, ((0,0,0)), (900,0,300,900), 0)
    pygame.draw.rect(screen, ((0,0,0)), (0,0,300,900), 0)
    pygame.draw.rect(screen, ((0,0,0)), (0,600,1200,300),0)
    battext=font.render(str(percent) + ("%"), 1,(255,255,255))
    timer1=font.render(str(timea) + ":" + str(timeb), 1,(255,255,255))
    screen.blit(battery,(1000,50))
    pygame.draw.rect(screen, ((r,g,b)), (1010,240,80,bath), 0)
    screen.blit(roboarm,(50,cy))
    
    screen.blit(battext, (1000, 250))
    screen.blit(timer1,(550,600))

                
   
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
pygame.quit()
