# Import regex
import re

# Get user input
while True:
    owed = input("Change owed: ")
    if re.match("^(?=.+)(?:[1-9]\d*|0)?(?:\.\d+)?$", owed) is not None:
        owed = float(owed)
        break

# Convert owed to int dollars
dollars = int(owed)

# Convert dollars to cents
cents = int(dollars * 100 + round((owed - dollars) * 100))

# Define variable to represent coins used
coins = 0

# Calculate
while (cents >= 25):
    cents -= 25
    coins += 1
while (cents >= 10):
    cents -= 10
    coins += 1
while (cents >= 5):
    cents -= 5
    coins += 1
while (cents >= 1):
    cents -= 1
    coins += 1

# Print fewest coins possible
print(f"{coins}")
