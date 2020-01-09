from pyglet.gl import *
from pyglet.window import key 
from Model import *
import math

class Player:
	def __init__(self,pos, rot):
		self.pos = pos
		self.rot = rot
		self.pos = list(pos)
		self.rot = list(rot)

	def mouse_motion(self,dx,dy):
		dx/=8; dy/=8; self.rot[0]+=dy; self.rot[1]-=dx
		if self.rot[0]>90: self.rot[0] = 90
		elif self.rot[0]<-90: self.rot[0] = -90	

	#gets repeatedly called by pyglet clock
	def update(self,dt,keys):

		s = dt*10
		rotY = -self.rot[1]/180*math.pi
		dx,dz = s*math.sin(rotY),s*math.cos(rotY)
		if keys[key.W]: self.pos[0]+=dx; self.pos[2]-=dz
		if keys[key.S]: self.pos[0]-=dx; self.pos[2]+=dz
		if keys[key.A]: self.pos[0]-=dz; self.pos[2]-=dx
		if keys[key.D]: self.pos[0]+=dz; self.pos[2]+=dx

		if keys[key.SPACE]: 
			if (not (self.pos[0] > 50 or self.pos[0] < -50 or self.pos[2] > 50 or self.pos[2] < -50)) and (self.pos[1] <= -4 ):
				self.pos[1]+=s
			elif (not (self.pos[0] > 50 or self.pos[0] < -50 or self.pos[2] > 50 or self.pos[2] < -50)) and (self.pos[1] >= 0.5 ):
				self.pos[1]+=s
			elif ((self.pos[0] > 50 or self.pos[0] < -50 or self.pos[2] > 50 or self.pos[2] < -50)):
				self.pos[1]+=s
			else:
				self.pos[1]=self.pos[1]

		if keys[key.LSHIFT]: 
			if (not (self.pos[0] > 50 or self.pos[0] < -50 or self.pos[2] > 50 or self.pos[2] < -50)) and (self.pos[1] <= 1 ):
				self.pos[1]=self.pos[1]
			else:
				self.pos[1]-=s