# Import regex
import re

# Condition loop
while True:
    height = input("Height: ")
    if re.match("^([1-8])", height) is not None:
        height = int(height)
        break

# Builds mario blocks
for i in range(height):
    for j in range(height - 1, 0, -1):
        if (j > i):
            print(" ", end="")
    for k in range(i + 1):
        print("#", end="")
    print("  ", end="")
    for l in range(i + 1):
        print("#", end="")
    print("")
