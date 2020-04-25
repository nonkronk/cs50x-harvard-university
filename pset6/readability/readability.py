
# Main Program


def main():
    text = input("Text: ")
    letter = count_letters(text)
    word = count_words(text)
    sentence = count_sentences(text)
    grade = cl_index(letter, word, sentence)

    # print grade
    if grade >= 16:
        print("Grade 16+")
    elif grade < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {grade}")

# count letters


def count_letters(s):
    count = 0
    for i in range(len(s)):
        c = s[i]
        if c.isalpha() == True:
            count += 1
    return count

# count words


def count_words(s):
    count = 0
    for i in range(len(s)):
        if s[i] == ' ':
            count += 1
    return count + 1

# count sentences


def count_sentences(s):
    count = 0
    for i in range(len(s)):
        if s[i] == '.' or s[i] == '!' or s[i] == '?':
            count += 1
    return count

# Coleman-Liau index formula


def cl_index(l, w, s):
    l = float(l)
    w = float(w)
    s = float(s)
    la = 100 / w * l
    sa = 100 / w * s

    index = (0.0588 * la) - (0.296 * sa) - 15.8
    index = round(index)

    return index


# Run main program
main()
