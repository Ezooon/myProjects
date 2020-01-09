from pyglet.gl import *
from pyglet.window import key

import math
import random

class Model:

    #Function to open a texture file
    def get_tex(self, file):
        tex = pyglet.image.load(file).texture
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST)
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST)
        return pyglet.graphics.TextureGroup(tex)

    #Function that generates a block at the designated openGL coordinates
    def GenerateBlock(self,x,y,z):
        #adding texture coordinates to map to the model
        #texture origin is bottom left 0,0
        #always go bot-left, bot-right, top-right, top-left
        text_coords = ('t2f', (0,0, 1,0, 1,1, 0,1))

        #Displacement from given coordinates for block
        X,Y,Z = x+1, y+1, z+1

        '''
        4 is the number of corners per face and the number of cube_vertices
        our object is going to have.
        GL_QUADS defines the type of rendering in OpenGL, could also be
        triangles, polygonals, lines etc
        then define the points for the corners of a face and add color
        v3f means vertex3floats
        '''
        self.batch.add(4, GL_QUADS, self.side, ('v3f', (x,y,Z, X,y,Z, X,Y,Z, x,Y,Z, )), text_coords) #Front
        self.batch.add(4, GL_QUADS, self.side, ('v3f', (X,y,z, x,y,z, x,Y,z, X,Y,z, )), text_coords) #Back
        self.batch.add(4, GL_QUADS, self.side, ('v3f', (x,y,z, x,y,Z, x,Y,Z, x,Y,z, )), text_coords) #Left
        self.batch.add(4, GL_QUADS, self.side, ('v3f', (X,y,Z, X,y,z, X,Y,z, X,Y,Z, )), text_coords) #Right
        self.batch.add(4, GL_QUADS, self.top, ('v3f', (x,Y,Z, X,Y,Z, X,Y,z, x,Y,z, )), text_coords) #Top
        self.batch.add(4, GL_QUADS, self.bottom, ('v3f', (x,y,z, X,y,z, X,y,Z, x,y,Z, )), text_coords) #Bottom

    #Model constructor for a block
    def __init__(self):
        #Load grass block textures
        self.top = self.get_tex('grass_top.png')
        self.side = self.get_tex('grass_side.png')
        self.bottom = self.get_tex('dirt.png')

        #batch constructor
        self.batch = pyglet.graphics.Batch()

        #Generate Blocks based on some range
        for i in range(-25, 25):
            #Try making blocks randomly throughout the world
            x = random.randint(-50, 50)
            y = random.randint(3, 50)
            z = random.randint(-50,50)
            self.GenerateBlock(x,y,z)
            for j in range(-25, 25):
                self.GenerateBlock(i, -2, j)

    def draw(self):
        self.batch.draw()




class Player():

    #Set intial position and rotation for the player camera
    def __init__(self):
        self.position = [0,1,2]
        self.rotation = [0,0]

    #Function to move player camera when moving the mouse
    def mouse_motion(self,dx,dy):
        dx/=8
        dy/=8
        self.rotation[0]+=dy
        self.rotation[1]-=dx
        if self.rotation[0]>90:
            self.rotation[0] = 90
        elif self.rotation[0]<-90:
            self.rotation[0] = -90

    '''
    Updates every cycle
    Updates player position based on key presses
    Math needed to make motion more realistic
    Movement such as jumping still needs to be addedself
    Basic movement for observing the 3D space
    '''
    def update(self, dt, keys):
        s = dt*10
        rotationY = -self.rotation[1]/180*math.pi
        dx,dz = s*math.sin(rotationY), s*math.cos(rotationY)
        #Keep operations on same line for readability
        #Each Key is one line of code unless operation is long
        if keys[key.W]: self.position[0] += dx; self.position[2] -= dz
        if keys[key.S]: self.position[0] -= dx; self.position[2] += dz
        if keys[key.A]: self.position[0] -= dz; self.position[2] -= dx
        if keys[key.D]: self.position[0] += dz; self.position[2] += dx

        if keys[key.SPACE]:
            self.position[1] += s
        if keys[key.LSHIFT]:
            self.position[1] -= s




class Window(pyglet.window.Window):

    #Initialize the projection matrix to project 2D textures into 3D coordinate space
    def Projection(self):
        glMatrixMode(GL_PROJECTION)
        glLoadIdentity()

    #Initialize the Model Matrix that holds the current space containing vertices
    def Model(self):
        glMatrixMode(GL_MODELVIEW)
        glLoadIdentity()

    def set2d(self):
        self.Projection()
        gluOrtho2D(0, self.width,0,self.height)
        self.Model()
    #70 is fov, 0.05 is min render distance, 1000 is max render distance
    #width/height is just the aspect ratio
    def set3d(self):
        self.Projection()
        gluPerspective(70, self.width/self.height, 0.05, 1000)
        self.Model()

    def setLock(self, state): self.lock = state; self.set_exclusive_mouse(state)
    lock = False
    mouse_lock = property(lambda self:self.lock,setLock)


    ''' Window Constructor '''
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.set_minimum_size(500,400)
        self.keys = key.KeyStateHandler()
        self.push_handlers(self.keys)
        pyglet.clock.schedule(self.update)

        #Call constructor for model and player classes
        self.model = Model()
        self.player = Player()

    #Define operation when a mouse is moved
    def on_mouse_motion(self,x,y,dx,dy):
        if self.mouse_lock:
            self.player.mouse_motion(dx,dy)

    #Define window operation when certain keys are pressed
    def on_key_press(self, KEY, MOD):
        if KEY == key.ESCAPE:
            self.close()
        elif KEY == key.F:
            self.mouse_lock = not self.mouse_lock

    #Window updates based on the update from player
    def update(self, dt):
        self.player.update(dt, self.keys)

    #Called every cycle to clear the window and redraw it with the updated
    #Frame
    def on_draw(self):
        self.clear()
        self.set3d()
        rotation = self.player.rotation
        glRotatef(-rotation[0],1,0,0)
        glRotatef(-rotation[1],0,1,0)
        x, y, z = self.player.position
        glTranslatef(-x,-y,-z)
        self.model.draw()

def main():
    window = Window(width=100, height=300, caption="Group 28's Nasty Game", resizable = True)
    glClearColor(0.1,0.9,1,1)
    glEnable(GL_DEPTH_TEST)
    #Cull face removes the face of a texture on the back side
    glEnable(GL_CULL_FACE)
    pyglet.app.run()

if __name__ == '__main__':
    main()
