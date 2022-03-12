from cs50 import get_string

text = get_string("Text: ")

letters = 0

words = 0

sentences = 0

for letter in text:
    if ((letter >= 'A' and letter <= 'Z') or (letter >= 'a' and letter <= 'z')):
        letters += 1

    if (letter == ' '):
        words += 1

    if (letter == '.' or letter == '!' or letter == '?'):
        sentences += 1

if (text[len(text) - 1] != ' '):
    words += 1

lettersPer100Words = letters / words * 100

sentencesPer100Words = sentences / words * 100

index = 0.0588 * lettersPer100Words - 0.296 * sentencesPer100Words - 15.8

if index < 1:
    print("Before Grade 1")
elif (index >= 16):
    print("Grade 16+")
else:
    print(f"Grade {round(index)}")