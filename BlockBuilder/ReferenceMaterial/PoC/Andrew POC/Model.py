from pyglet.gl import *
from pyglet.window import key 
import math

# A mapping from position to the texture of the block at that position.
# This defines all the blocks that are currently in the world.
class Model:

	#Method for loading textures
	def get_tex(self,file):
		tex = pyglet.image.load(file).texture

		#Makes the cube not blurry
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST)
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST)
		return pyglet.graphics.TextureGroup(tex)

	def createBlock(self,x,y,z):
		X,Y,Z = x+1,y+1,z+1
		tex_coords = ('t2f',(0,0, 1,0, 1,1, 0,1))
		#Create a batch 2d object using imported textures
		self.batch.add(4,GL_QUADS,self.side,('v3f',(x,y,z, x,y,Z, x,Y,Z, x,Y,z, )),tex_coords)
		self.batch.add(4,GL_QUADS,self.side,('v3f',(X,y,Z, X,y,z, X,Y,z, X,Y,Z, )),tex_coords)
		self.batch.add(4,GL_QUADS,self.bottom,('v3f',(x,y,z, X,y,z, X,y,Z, x,y,Z, )),tex_coords)
		self.batch.add(4,GL_QUADS,self.top,('v3f',(x,Y,Z, X,Y,Z, X,Y,z, x,Y,z, )),tex_coords)
		self.batch.add(4,GL_QUADS,self.side,('v3f',(X,y,z, x,y,z, x,Y,z, X,Y,z, )),tex_coords)
		self.batch.add(4,GL_QUADS,self.side,('v3f',(x,y,Z, X,y,Z, X,Y,Z, x,Y,Z, )),tex_coords)

	def __init__(self):

		#Load textures
		self.top = self.get_tex('grass_top.png')
		self.side = self.get_tex('grass_side.png')
		self.bottom = self.get_tex('dirt.png')

		self.batch = pyglet.graphics.Batch()

		#Create text coordinates

		#Create coordinates   
		for x in range(-50,50):
			for z in range(-50,50):
				self.createBlock(x,-2,z)

		level=-1
		x=5
		for i in range(0,5):
			area=x*x
			for y in range(10,area+10):
				for z in range(10,area+10):
					self.createBlock(z,level,y)
			level=level+1
			x=x-1

	def draw(self):
		self.batch.draw()