import pygame
import math
from pygame import mixer

class Bullet():
    
    def __init__(self, initialX, initialY):
        self.x = initialX + 16
        self.y = initialY - 20
        self.changeY = 0.3
        self.bulletImg = pygame.image.load("bullet.png")
        self.laser = mixer.Sound("laser.wav")
        self.collision = mixer.Sound("explosion.wav")

    def moveBullet(self):
        self.y -= self.changeY
