import os
import sys
import math
import pygame as pg

COLOR_KEY = (0, 0, 0)


class Laser(pg.sprite.Sprite):
    """
    A class for our laser projectiles. Using the pygame.sprite.Sprite class
    this time, though it is just as easily done without it.
    """
    def __init__(self, location, angle, friendly):
        """
        Takes a coordinate pair, and an angle in degrees. These are passed
        in by the Turret class when the projectile is created.
        """

        TURRET = pg.image.load("BULLET.png").convert()
        TURRET.set_colorkey(COLOR_KEY)
        pg.sprite.Sprite.__init__(self)
        if friendly:
            self.original_laser = TURRET.subsurface((21,32,10,6))
        else:
            self.original_laser = TURRET.subsurface((21,14,10,6))
        self.angle = -math.radians(angle)
        self.image = pg.transform.rotate(self.original_laser, angle)
        self.rect = self.image.get_rect(center=location)
        self.move = [self.rect.x, self.rect.y]
        self.speed_magnitude = 10
        self.speed = (self.speed_magnitude*math.cos(self.angle),
                      self.speed_magnitude*math.sin(self.angle))
        self.done = False
        self.mask = pg.mask.from_surface(self.image)

    def update(self, screen_rect):
        """
        Because pygame.Rect's can only hold ints, it is necessary to hold
        the real value of our movement vector in another variable.
        """
        self.move[0] += self.speed[0]
        self.move[1] += self.speed[1]
        self.rect.topleft = self.move
        self.remove(screen_rect)

    def remove(self, screen_rect):
        """If the projectile has left the screen, remove it from any Groups."""
        if not self.rect.colliderect(screen_rect):
            self.kill()

    def getFloatxPos(self):
        return self.move[0]

    def getFloatyPos(self):
        return self.move[1]