# Program to import student data into a database
import sys
import csv
import cs50

# Connect to database
db = cs50.SQL("sqlite:///students.db")

# Check correct number of args
if len(sys.argv) != 2:
    print("Usage: python import.py characters.csv")
    exit(1)

# Read csv file
with open(str(sys.argv[1])) as csvfile:
    reader = csv.DictReader(csvfile)
    # Read each row on csv file
    for row in reader:
        first = row['name'].split()[0]
        # Return None if students doesn't have middle name
        if len(row['name'].split()) == 3:
            middle = row['name'].split()[1]
        else:
            middle = None
        last = row['name'].split()[-1]
        house = row['house']
        birth = row['birth']
        # Insert into database
        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)", first, middle, last, house, birth)