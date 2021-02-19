import pygame
import random

class Enemy():

    def __init__(self):
        self.x = random.randint(0, 740)
        self.y = 50
        self.changeY = 0.05
        self.alienImg = pygame.image.load("alien64.png")
        self.increase = 4000

    def moveEnemy(self):
        self.y += self.changeY

    def upgradeLevel(self, score):
        if score >= 30:
            self.changeY += 0.05
            self.increase -= 100
        else:
            self.increase -= 200
        