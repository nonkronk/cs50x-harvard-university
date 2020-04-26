import sys
import csv

# Identified person based on DNA


def main():

    # Check correct number of args
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        exit(1)

    # Read csv file
    csv_file = csv.DictReader(open(str(sys.argv[1])))

    # Read txt file
    with open(str(sys.argv[2])) as f:
        txt = str(f.read())
        # Populate SRTs into variables
        agatc = compute(txt, "AGATC")
        aatg = compute(txt, "AATG")
        tatc = compute(txt, "TATC")
        t6ct = compute(txt, "TTTTTTCT")
        tctag = compute(txt, "TCTAG")
        gata = compute(txt, "GATA")
        ga3 = compute(txt, "GAAA")
        tctg = compute(txt, "TCTG")
    
    # Define matched DNA
    person = None
    # Check / compare computed txt with csv 
    for row in csv_file:
        # With large.csv
        if (agatc * aatg * tatc * t6ct * tctag * gata * ga3 * tctg) != 0:
            if (agatc == int(row["AGATC"]) and
                t6ct == int(row["TTTTTTCT"]) and
                aatg == int(row["AATG"]) and
                tctag == int(row["TCTAG"]) and
                gata == int(row["GATA"]) and
                tatc == int(row["TATC"]) and
                    ga3 == int(row["GAAA"]) and int(row["TCTG"]) == tctg):
                person = row["name"]
        # With small.csv
        elif (agatc == int(row["AGATC"]) and
                aatg == int(row["AATG"]) and tatc == int(row["TATC"])):
            person = row["name"]
        
    # Print result
    if person != None:
        print(person)
    else:
        print("No match")   

# Calculate SRTs


def compute(txt, s):
    min = 0
    max = 0
    i = 0
    while i < len(txt):
        if txt[i:(i + len(s))] == s:
            j = i
            while j < len(txt):
                if txt[j: (j + (len(s)))] == s:
                    min += 1
                else:
                    i = j - 1
                    if min > max:
                        max = min
                    min = 0
                    break
                j += len(s)
        i += 1
    return max


# Run the program
main()

