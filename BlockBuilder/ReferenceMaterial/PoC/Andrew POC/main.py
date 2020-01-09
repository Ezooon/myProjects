from pyglet.gl import *
from pyglet.window import key 
from Window import *
from Model import *
from Player import *
import math

if __name__ == '__main__':
	window = Window(width=800,height=700,caption="BlockBuilder",resizable=True)
	glClearColor(0.5,0.7,1,1)
	glEnable(GL_DEPTH_TEST)
	pyglet.app.run()