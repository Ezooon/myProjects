import os
import sys
import math
import pygame as pg
from laser import Laser
import socket

COLOR_KEY = (255, 255, 255)

class Player(pg.sprite.Sprite):
    def __init__(self, location):

        """Location is an (x,y) coordinate pair."""
        TURRET = pg.image.load("SHIP.png").convert()
        TURRET.set_colorkey(COLOR_KEY)
        pg.sprite.Sprite.__init__(self)
        self.original_barrel = TURRET.subsurface((68,14,35,34))
        self.original_barrel = pg.transform.rotate(self.original_barrel, -90)
        self.barrel = self.original_barrel.copy()
        self.rect = self.barrel.get_rect(center=location)
        self.angle = self.get_angle(pg.mouse.get_pos())

    def get_angle(self, mouse):
        """
        Find the new angle between the center of the Turret and the mouse.
        """
        offset = (mouse[1]-self.rect.centery, mouse[0]-self.rect.centerx)
        self.angle = -math.degrees(math.atan2(*offset))
        #print(self.angle, self.rect.center)
        self.barrel = pg.transform.rotate(self.original_barrel, self.angle)
        self.rect = self.barrel.get_rect(center=self.rect.center)
        self.mask = pg.mask.from_surface(self.barrel)

    def set_angle(self,angle):
        self.barrel = pg.transform.rotate(self.original_barrel, angle)
        self.rect = self.barrel.get_rect(center=self.rect.center)
        self.mask = pg.mask.from_surface(self.barrel)


    def draw(self, surface):
        """Draw base and barrel to the target surface."""
        surface.blit(self.barrel, self.rect)   

    def getAngle(self):
        return self.angle

    def getxRect(self):
        return self.rect.x

    def setxRect(self, xval):
        self.rect.x = xval

    def getyRect(self):
        return self.rect.y

    def setyRect(self, yval):
        self.rect.y = yval