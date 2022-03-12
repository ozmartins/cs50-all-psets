from cs50 import get_float
from math import floor

change = 0.0

while True:
    change = get_float("How much change I owe?\n")
    if change > 0:
        break

changeInCents = round(change * 100)

coins = 0

quotient = 0

divisor = 0

while changeInCents > 0:
    if (changeInCents >= 25):
        divisor = 25
    elif (changeInCents >= 10):
        divisor = 10
    elif (changeInCents >= 5):
        divisor = 5
    else:
        divisor = 1

    quotient = floor(changeInCents / divisor)

    coins += quotient

    changeInCents -= quotient * divisor

print(f"{coins}")