import socket
import pygame as pg
import time
import json


PLAYER_SPEED = 5
LASER_SPEED = 6
BUFFER_SIZE = 204800


def Main():
	clock = pg.time.Clock()
	fps = 60

	host = ''
	p1Port = 9002
	p2Port = 9003

	p1 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	p2 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

	p1.bind((host,p1Port))
	p2.bind((host,p2Port))


	p1.listen(1)
	p2.listen(1)
	print("Waiting for P1 on:", host, p1Port)
	print("Waiting for P2 on:", host, p2Port)
	connP1, addrP1 = p1.accept()
	print("Connection from P1 at: " + str(addrP1))
	connP2, addrP2 = p2.accept()
	print("Connection from P2 at: " + str(addrP2))

	while True:
		p1Data = connP1.recv(BUFFER_SIZE).decode()
		p2Data = connP2.recv(BUFFER_SIZE).decode()
		if not (p1Data or p2Data):
			break
		p1Data = eval(p1Data)
		p2Data = eval(p2Data)


		if p1Data['R']:
			p1Data['xpos']+=PLAYER_SPEED
		if p1Data['L']:
			p1Data['xpos']-=PLAYER_SPEED
		if p1Data['U']: 
			p1Data['ypos']-=PLAYER_SPEED
		if p1Data['D']:
			p1Data['ypos']+=PLAYER_SPEED

		if p2Data['R']:
			p2Data['xpos']+=PLAYER_SPEED
		if p2Data['L']:
			p2Data['xpos']-=PLAYER_SPEED
		if p2Data['U']: 
			p2Data['ypos']-=PLAYER_SPEED
		if p2Data['D']:
			p2Data['ypos']+=PLAYER_SPEED

		p1Data['xposP2']=p2Data['xpos']
		p1Data['yposP2']=p2Data['ypos']
		p1Data['centerP2']=p2Data['center']
		p1Data['angleP2']=p2Data['angle']
		p1Data['fireP2']=p2Data['fire']

		p2Data['xposP1']=p1Data['xpos']
		p2Data['yposP1']=p1Data['ypos']
		p2Data['centerP1']=p1Data['center']
		p2Data['angleP1']=p1Data['angle']
		p2Data['fireP1']=p1Data['fire']

		#print(p1Data)

		FPS = clock.get_fps()
		p1Data['FPS'] = FPS
		p2Data['FPS'] = FPS

		connP1.send(str(p1Data).encode())
		connP2.send(str(p2Data).encode())
		clock.tick(fps)
		#print(clock.get_fps(), end='\r')

	connP1.close()
	connP2.close()

if __name__ == '__main__':
	Main()

