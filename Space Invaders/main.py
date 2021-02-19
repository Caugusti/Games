import pygame, time
from enemy import Enemy
from player import Player
from bullet import Bullet
from scoreboard import Scoreboard
from pygame import mixer

def updatePlayer(x, y):
    screen.blit(player.playerImg, (x, y))

def updateEnemy(x, y):
    screen.blit(enemy.alienImg, (x, y))

def updateBullet(x, y):
    screen.blit(bullet.bulletImg, (x, y))

def showScore(x, y):
    scoreTxt = score.updateScore()
    screen.blit(scoreTxt, (x, y))

running = True
playAgain = True
startGame = True

while playAgain:
    if startGame:
        pygame.init()
        score = Scoreboard()

        bulletArray = []
        enemyArray = []
        distanceX = 0
        distanceY = 0

        player = Player()
        enemy = Enemy()
        enemyArray.append(enemy)

        screen = pygame.display.set_mode((800, 600))
        pygame.display.set_caption("Space Invaders")
        background = pygame.image.load("background.jpg")

        mixer.music.load("background.wav")
        mixer.music.play(-1)

        pygame.display.set_icon(enemy.alienImg)
        startGame = False

    while running:
        screen.fill((0, 0, 0))
        screen.blit(background, (0, 0))

        if player.temp == player.second:
            enemy = Enemy()
            enemyArray.append(enemy)
            player.second += enemy.increase

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
                playAgain = False

            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_LEFT:
                    player.changeX = -0.2

                elif event.key == pygame.K_RIGHT:
                    player.changeX = 0.2

                elif event.key == pygame.K_SPACE:
                    bullet = Bullet(player.x, player.y)
                    bulletArray.append(bullet)
                    bullet.laser.play()
            
            elif event.type == pygame.KEYUP:
                if event.key == pygame.K_LEFT or event.key == pygame.K_RIGHT:
                    player.changeX = 0

        for bullet in bulletArray:
            updateBullet(bullet.x, bullet.y)
            bullet.moveBullet()

            for enemy in enemyArray:
                distanceX = abs(enemy.x - bullet.x)
                distanceY = abs(enemy.y - bullet.y)

                if distanceX <= 30 and distanceY <= 20:
                    bullet.collision.play()
                    bulletArray.remove(bullet)
                    enemyArray.remove(enemy)
                    score.value += 1

        for enemy in enemyArray:
            enemy.moveEnemy()
            updateEnemy(enemy.x, enemy.y)

            if enemy.y >= 450:
                gameOverTxt = score.gameOver()
                playAgainTxt = score.playAgain()
                screen.blit(gameOverTxt, (340, 280))
                screen.blit(playAgainTxt, (200, 320))
                running = False

        if score.value == score.levelUp:
            enemy.upgradeLevel(score.value)
            score.levelUp += score.increase

        player.checkBoundaries()
        updatePlayer(player.x, player.y)
        showScore(10, 10)

        player.temp += 1

        pygame.display.update()

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            playAgain = False

        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_SPACE:
                startGame = True
                running = True
            else:
                playAgain = False
    
    pygame.display.update()

    