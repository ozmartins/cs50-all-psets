import csv
import cs50
from sys import argv, exit

if len(argv) != 2:
    print("Usage: python import.py house_name")
    exit(1)

db = cs50.SQL("sqlite:///students.db")

rows = db.execute("SELECT * FROM students WHERE house like ? ORDER By last, first", argv[1])

for row in rows:
    middle = " " if type(row["middle"]) == type(None) else " " + row["middle"] + " "
    name = row["first"] + middle + row["last"]
    birth = row["birth"]

    print(f"{name}, born {birth}")