from cs50 import get_string
from sys import exit

while True:
    name = get_string("Whats your name?\n")
    if name != "":
        print(f"hello, {name}")
        exit(0)