from cs50 import get_int
from math import modf

creditCardNumber = get_int("Credit card: ")

# i have to keep the origial credit card number because i wil change the value of creditCardNumber in code
originalCreditCardNumber = creditCardNumber

sumOfDigitsThatWasMultipliedByTwo = 0

sumOfOtherDigits = 0

countOfDigits = 0

product = 0

currentDigit = 0

while creditCardNumber > 0:
    countOfDigits += 1

    # Using the logic that Brian have explained
    currentDigit = creditCardNumber % 10

    # if modulo returns zero, i am in a second-to-last digit
    if (countOfDigits % 2 == 0):
        product = (currentDigit * 2)

        # this loop sum the digits of the product
        while product > 0:
            sumOfDigitsThatWasMultipliedByTwo += product % 10

            product = modf(product / 10)[1]
    else:
        sumOfOtherDigits += currentDigit

    # this is a important section of code. Here i am making(?) a integer division that will ignore the decimal part.
    # this means that the second-to-last digit now is the last one, so i can repeat the loop logic again
    creditCardNumber = modf(creditCardNumber / 10)[1]

# this divisor will be used to discovery the two first digits of the credit card number
divisor = pow(10, (countOfDigits - 2))

twoInitialDigits = modf(originalCreditCardNumber / divisor)[1]

firstDigit = modf(twoInitialDigits / 10)[1]

valid = ((sumOfDigitsThatWasMultipliedByTwo + sumOfOtherDigits) % 10) == 0

if (not valid):
    print("INVALID")
elif (countOfDigits == 15 and (twoInitialDigits == 34 or twoInitialDigits == 37)):
    print("AMEX")
elif (countOfDigits == 16 and (twoInitialDigits == 51 or twoInitialDigits == 52 or twoInitialDigits == 53
                               or twoInitialDigits == 54 or twoInitialDigits == 55)):
    print("MASTERCARD")
elif ((countOfDigits == 13 or countOfDigits == 16) and (firstDigit == 4)):
    print("VISA")
else:
    print("INVALID")