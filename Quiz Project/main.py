from question_model import Question
from data import question_data
from quiz_brain import QuizBrain
import os

question_bank = []

for quest in question_data:
    question = Question(quest["question"], quest["correct_answer"])
    question_bank.append(question)

quiz = QuizBrain(question_bank)

os.system('cls||clear')

while quiz.still_has_questions():
    quiz.next_question()

print("You've completed the Quiz!")
print(f"Your final score was: {quiz.score}/{quiz.question_number}.")
