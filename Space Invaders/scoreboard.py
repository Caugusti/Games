import pygame

class Scoreboard():

    def __init__(self):
        self.value = 0
        self.levelUp = 5
        self.increase = 5
        self.font = pygame.font.Font('freesansbold.ttf', 32)

    def updateScore(self):
        return self.font.render("Score: " + str(self.value), True, (255, 255, 255))

    def gameOver(self):
        return self.font.render("Game Over!", True, (255, 255, 255))

    def playAgain(self):
        return self.font.render("Press 'Space' to play again.", True, (255, 255, 255))