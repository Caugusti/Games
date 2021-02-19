# Blackjack Code 

import random
import os
from art import logo

def get_card():
    """Returns a random card from the deck."""
    cards = [11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10]

    return random.choice(cards)

new_game = False

def start_newGame():
    global new_game

    if input("Do you want to play a game of Blackjack? Type 'y' or 'n': ") == 'y':
        new_game = True
    else:
        new_game = False

def get_anotherCard():
    global anotherCard
    global bet

    if bank >= (bet*2):
        type_result = input("Type 'y' to get another card (Hit), type 'n' to stand, or type 'd' to bet twice and get another card (Double): ")
    else:
        type_result = input("Type 'y' to get another card (Hit), type 'n' to stand: ")

    if type_result == 'y':
        anotherCard = True

    elif type_result == 'd':
        anotherCard = True
        bet *= 2

    else:
        anotherCard = False

def define_bet():
    global bet

    bet = int(input(f"Bank: ${bank}. How much do you want to bet? $")) 

start_newGame()
bank = 1000

while new_game:
    user = []
    computer = []
    os.system('cls||clear')
    print(logo)

    define_bet()

    if bet > bank or bet == 0:
        print("Invalid bet. Please enter a new value.")
        define_bet()

    for i in range(0, 2):
        user.append(get_card())
        computer.append(get_card())

    print(f"Your cards: {user}, current score: {sum(user)}")
    print(f"Computer's first card: {computer[0]} \n")

    if sum(user) == 21:
        bank += bet
        print(f"Your final hand: {user}, final score: {sum(user)}")
        print(f"Computer's final hand: {computer}, final score: {sum(computer)} \n")
        print("Blackjack! You win!")

    elif sum(computer) == 21:
        bank -= bet
        print(f"Your final hand: {user}, final score: {sum(user)}")
        print(f"Computer's final hand: {computer}, final score: {sum(computer)} \n")
        print("Lose, opponent has Blackjack!")

    else:
        get_anotherCard()

        if anotherCard:
            if 11 in user:
                index = user.index(11)
                user[index] = 1

        while anotherCard:
            user.append(get_card())

            if sum(user) == 21:
                anotherCard = False

            elif sum(user) > 21:
                anotherCard = False

            else:
                print(f"Your cards: {user}, current score: {sum(user)}")
                print(f"Computer's first card: {computer[0]} \n")
                get_anotherCard()
        
        while sum(user) < 17:
            if 11 in user:
                index = user.index(11)
                user[index] = 1

            user.append(get_card())
        
        while sum(computer) < 17:
            if 11 in computer:
                index = computer.index(11)
                computer[index] = 1

            computer.append(get_card())

        print(f"Your final hand: {user}, final score: {sum(user)}")
        print(f"Computer's final hand: {computer}, final score: {sum(computer)} \n")

        if sum(user) > 21:
            bank -= bet
            print("You went over. You lose!")

        elif sum(computer) > 21:
            bank += bet
            print("Opponent went over. You win!")

        elif sum(user) == 21:
            bank += bet
            print("Blackjack! You win!")

        elif sum(computer) == 21:
            bank -= bet
            print("Lose, opponent has Blackjack!")
        
        elif sum(user) == sum(computer):
            print("Draw!")
        
        elif sum(user) > sum(computer):
            bank += bet
            print("You win!")

        else:
            bank -= bet
            print("You lose!")

    print(f"Bank: ${bank}")

    if bank == 0:
        print("House wins!")
    else:
        start_newGame()
