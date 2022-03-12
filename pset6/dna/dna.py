from sys import argv, exit
import csv
import re


def main():
    check_args()
    persons = load_persons()
    sequence = load_dna_sequence()
    match = search(persons, sequence)
    if match:
        print(match.name)
    else:
        print("No match")


def search(persons, sequence):
    for p in persons:
        match_count = 0
        for s in p.strs:
            # if the str is AGATC and expected repetion is 3, then search_string will be AGATCAGATCAGATC
            search_string = s * int(p.strs[s])

            # look for the first occurence of search_string
            position = sequence.find(search_string)

            # i will use this position to check if there is a occurrence of the str after the found string
            # if there an ocurrence, then we haven't a match
            position_after_the_found_string = position + len(search_string)

            text_after_the_found_string = sequence[position_after_the_found_string: position_after_the_found_string + len(s)]

            if position != -1 and text_after_the_found_string != s:
                match_count += 1
        if match_count == len(p.strs):
            return p


def check_args():
    if len(argv) != 3:
        print("Usage: python dna.py str_count_file_name dna_sequece_file_name")
        exit()


def load_persons():
    str_file = open(argv[1], "r")
    reader = csv.reader(str_file)

    strs = []
    persons = []
    line = 0

    for row in reader:
        col_count = 0
        for col in row:
            if line == 0:
                if col_count > 0:
                    strs.append(col)
            else:
                if col_count == 0:
                    persons.append(Person(col, {}))
                else:
                    persons[line-1].strs.update({strs[col_count-1]: col})
            col_count += 1
        line += 1

    str_file.close()

    return persons


def load_dna_sequence():
    dna_file = open(argv[2], "r")
    sequence = dna_file.read()
    dna_file.close()
    return sequence


class Person:
    def __init__(self, name, strs):
        self.name = name
        self.strs = strs


main()