from pyglet.gl import *
from pyglet.window import key 
from Model import *
from Player import *
import math

class Window(pyglet.window.Window):

	def push(self,pos,rot): glPushMatrix(); glRotatef(-rot[0],1,0,0); glRotatef(-rot[1],0,1,0); glTranslatef(-pos[0],-pos[1],-pos[2],)
	def Projection(self): glMatrixMode(GL_PROJECTION); glLoadIdentity()
	def Model(self): glMatrixMode(GL_MODELVIEW); glLoadIdentity()
	def set2d(self): self.Projection(); gluOrtho2D(0,self.width,0,self.height); self.Model()
	def set3d(self): self.Projection(); gluPerspective(70,self.width/self.height,0.05,1000); self.Model()
	#Class for creating persepective

	#LOCK THE MOUSE
	def setLock(self,state): self.lock = state; self.set_exclusive_mouse(state)
	lock = False; mouse_lock = property(lambda self:self.lock,setLock)


	def __init__(self, *args, **kwargs):
		super().__init__(*args,**kwargs)
		#MIN SIZE OF WINDOW
		self.set_minimum_size(300,200)

		#stuff relating to keys and player
		self.keys=key.KeyStateHandler()
		self.push_handlers(self.keys)
		
		#need scheduling for player, clock keeps track of this
		pyglet.clock.schedule(self.update) 

		self.model = Model()
		self.player = Player((20,0.97,0.97),(-30,0))
		# Strafing is moving lateral to the direction you are facing,
		# e.g. moving to the left or right while continuing to face forward.


	#WHAT HAPPENS ON MOUSE MOTION
	def on_mouse_motion(self,x,y,dx,dy):
		if self.mouse_lock: self.player.mouse_motion(dx,dy)

	#WHAT HAPPENS WHNE EACH KEY IS PRESSED
	def on_key_press(self,KEY,MOD):
		if KEY == key.ESCAPE: self.close()
		elif KEY == key.E: self.mouse_lock = not self.mouse_lock

	#UPDATE PLAYER FUNCTION
	#called repeatedly by pyglet clock
	def update(self,dt):
		self.player.update(dt,self.keys)

	#Do these things on the window
	def on_draw(self):
		self.clear()
		self.set3d()
		self.push(self.player.pos,self.player.rot)
		self.model.draw()
		glPopMatrix()