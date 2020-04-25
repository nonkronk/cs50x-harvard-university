# Import regex
import re
import math

# Get CC num input from the user
# Get user input
while True:
    num = input("Number: ")
    if re.match("^(?=.+)(?:[1-9]\d*|0)?(?:\.\d+)?$", num) is not None:
        break

# Finds out length of Card num
len_num = len(num)

# Define variable for calculating
num = int(num)
count = math.floor(len_num / 2)
num_scale = 10
val = 0

# Calculate from second-to-last digit
for i in range(count):
    sec_digit = (math.floor(num / num_scale)) % 10
    each_val = sec_digit * 2
    if (each_val >= 10):
        each_val = (each_val % 10) + 1
    val += each_val
    if (i == count - 1):
        digit0 = sec_digit
    num_scale *= 100

# Redefine few variable for another calculating
num_scale = 1
count = len_num - math.floor(len_num / 2)

# Calculate with the val of the other digits
for j in range(count):
    digit = (math.floor(num / num_scale)) % 10
    val += digit
    if (j == count - 1):
        digit1 = digit
    num_scale *= 100

# Define variable for validating
check = val % 10

# Validate last digit in the val
if check == 0:
    if len_num == 15:
        if (digit1 == 3):
            if (digit0 == 4 or digit0 == 7):
                print("AMEX")
            else:
                print("INVALID")
        else:
            print("INVALID")

    elif len_num == 13:
        if (digit1 == 4):
            print("VISA")
        else:
            print("INVALID")

    elif len_num == 16:
        if (digit0 == 4):
            print("VISA")
        elif (digit0 == 5):
            if (digit1 >= 1 and digit1 <= 5):
                print("MASTERCARD")
            else:
                print("INVALID")
        else:
            print("INVALID")
    else:
        print("INVALID")
else:
    print("INVALID")