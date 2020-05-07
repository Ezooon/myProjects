"""
This example is identical to the standard turret in tank.py, except the Player
now follows the mouse and fires with the left mouse button; instead of using
the keyboard.

"""

import os
import sys
import math
import pygame as pg
from laser import Laser
from player import Player
import socket


CAPTION = "Tank Turret: Mousse"
SCREEN_SIZE = (1200, 500)
BACKGROUND_COLOR = (50, 50, 50)
COLOR_KEY = (255, 0, 255)
PLAYER_SPEED = 5
BUFFER_SIZE = 204800

class Control(object):
    def __init__(self):

        host = ''
        port = 9002
        self.s = socket.socket()
        self.s.connect((host,port))


        self.screen = pg.display.get_surface()
        self.screen_rect = self.screen.get_rect()
        self.done = False
        self.clock = pg.time.Clock()
        self.fps = 60.0
        self.keys = pg.key.get_pressed()
        self.player1 = Player((250,250))
        self.player2 = Player((800,250))
        self.objects = pg.sprite.Group()
        self.objectsP2 = pg.sprite.Group()
        self.inputs = {}
        self.FPS = 60

    def event_loop(self):
        self.inputs['fire']=0 #assume no click
        for event in pg.event.get():
            self.keys = pg.key.get_pressed()

            if event.type == pg.QUIT or self.keys[pg.K_ESCAPE]:
                self.done = True

            elif event.type == pg.MOUSEBUTTONDOWN and event.button == 1:
                self.inputs['fire'] = 1

            elif event.type == pg.MOUSEMOTION:
                self.player1.get_angle(event.pos)
            #self.player2.get_event(event, self.objects)

        ''' Send player movememnt to server '''
        key = pg.key.get_pressed()
        self.inputs['xpos']=self.player1.getxRect()
        self.inputs['ypos']=self.player1.getyRect()
        self.inputs['center'] = self.player1.rect.center
        self.inputs['angle']=self.player1.getAngle()
        self.inputs['R']=key[pg.K_d]
        self.inputs['L']=key[pg.K_a]
        self.inputs['U']=key[pg.K_w]
        self.inputs['D']=key[pg.K_s]

        #if not all(value == 0 for value in self.inputs.values()):
        self.s.send(str(self.inputs).encode())

    def update(self):


        ''' Update movement based on server '''
        data = self.s.recv(BUFFER_SIZE).decode()
        data = eval(data)

        self.player1.setxRect(data['xpos'])
        self.player1.setyRect(data['ypos'])
        self.objects.update(self.screen_rect)

        self.player2.setxRect(data['xposP2'])
        self.player2.setyRect(data['yposP2'])
        self.player2.set_angle(data['angleP2'])
        self.objectsP2.update(self.screen_rect)

        if data['fire']:
            self.objects.add(Laser(data['center'], data['angle'], True))

        if data['fireP2']:
            self.objectsP2.add(Laser(data['centerP2'], data['angleP2'],False))

        self.FPS = data['FPS']

    def draw(self):
        self.screen.fill(BACKGROUND_COLOR)
        self.player1.draw(self.screen)
        self.player2.draw(self.screen)
        self.objects.draw(self.screen)
        self.objectsP2.draw(self.screen)

    def display_fps(self):
        """Show the program's FPS in the window handle."""
        #fps=self.clock.get_fps()
        caption = "{} - FPS: {:.2f}".format(CAPTION, self.FPS)
        pg.display.set_caption(caption)

    def main_loop(self):
        """"Same old story."""
        while not self.done:
            self.event_loop()
            self.update()
            self.draw()
            hits = pg.sprite.spritecollide(self.player2, self.objects, True, pg.sprite.collide_mask)
            hit2 = pg.sprite.spritecollide(self.player1, self.objectsP2, True, pg.sprite.collide_mask)
            pg.display.flip()
            #self.clock.tick(self.fps)
            self.display_fps()


if __name__ == "__main__":
    #os.environ['SDL_VIDEO_CENTERED'] = '1'
    pg.init()
    #flags = pg.DOUBLEBUF | pg.HWSURFACE | pg.FULLSCREEN
    flags = pg.DOUBLEBUF | pg.HWSURFACE
    pg.display.set_caption(CAPTION)
    pg.display.set_mode(SCREEN_SIZE, flags)
    run_it = Control()
    run_it.main_loop()
    pg.quit()
    sys.exit()