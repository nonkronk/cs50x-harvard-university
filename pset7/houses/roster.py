# Program to produce class roster
import cs50
import sys

# Connect to database
db = cs50.SQL("sqlite:///students.db")

# Check correct number of args
if len(sys.argv) != 2:
    print("Usage: python roster.py class")
    exit(1)

house = str(sys.argv[1])
database = db.execute("SELECT * FROM students WHERE house = ? ORDER BY last ASC, first ASC", house)
for row in database:
    first = row.get("first")
    middle = row.get("middle")
    last = row.get("last")
    birth = row.get("birth")
    if middle == None:
        print(f"{first} {last}, born {birth}")
    else:
        print(f"{first} {middle} {last}, born {birth}")

