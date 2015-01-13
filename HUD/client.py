import socket
import pygame
import threading
#clientsocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
#clientsocket.connect(('10.1.14.2', 5800))

#socketbuffer = ""
pygame.init()
screen = pygame.display.set_mode((1200, 900))
pygame.display.set_caption('HUD')
pygame.mouse.set_visible(0)
screenrun = True

battery = 12
bat = False

while screenrun:
	#readbuffer = readbuffer+clientsocker.recv(1024)
	#temp = str.split(readbuffer, "\n")
	#readbuffer=temp.pop( )
	screen.fill((0,0,0))
	pygame.display.flip()
	pygame.draw.rect(screen,((255,0,0)), (0,0,50,50), 100 )
pygame.quit()