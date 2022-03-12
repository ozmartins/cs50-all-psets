from cs50 import get_int


def piramid(quantity, base):
    if quantity > 0:
        piramid(quantity - 1, base)
        print(" " * (base - quantity) + "#" * quantity, end="")
        print("  ", end="")
        print("#" * quantity)


while True:
    quantity = get_int("Height: ")
    if quantity > 0 and quantity < 9:
        break


piramid(quantity, quantity)