import csv
import cs50
from sys import argv, exit

if len(argv) != 2:
    print("Usage: python import.py file_name.csv")
    exit(1)

db = cs50.SQL("sqlite:///students.db")

db.execute("delete from students")

with open(argv[1], "r") as characters:

    reader = csv.DictReader(characters)

    for row in reader:

        names = row["name"].split(" ")

        first = names[0]

        if len(names) == 2:

            middle = ""

            last = names[1]

            db.execute("insert into students (first, last, house, birth) values (?,?,?,?)", first, last, row["house"], row["birth"])

        elif len(names) == 3:

            middle = names[1]

            last = names[2]

            db.execute("insert into students (first, middle, last, house, birth) values (?,?,?,?,?)",
                       first, middle, last, row["house"], row["birth"])
