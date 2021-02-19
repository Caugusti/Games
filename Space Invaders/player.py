import pygame

class Player():

    def __init__(self):
        self.x = 370
        self.y = 480
        self.changeX = 0
        self.playerImg = pygame.image.load("player.png")
        self.temp = 0
        self.second = 4000

    def checkBoundaries(self):
        self.x += self.changeX
        
        if self.x <= 0:
            self.x = 0
            
        elif self.x >= 740:
            self.x = 740