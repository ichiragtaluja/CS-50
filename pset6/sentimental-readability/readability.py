# TODO
from cs50 import get_string


def main():

    # Get input as a text
    text = get_string("Text: ")

    # Count number of letters
    letters = total_letters(text)

    # Count number of words
    words = total_words(text)

    # Count number of sentences
    sentences = total_sentences(text)

    # Calculate grade
    l = (letters / words) * 100

    f = (sentences / words) * 100

    g = round((0.0588 * l) - (0.296 * f) - 15.8)

    if g > 16:
        print("Grade 16+")
    elif g < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {g}")


# Print grade
def total_letters(text):
    n = 0
    for i in text:
        if i.isalpha():
            n += 1
        else:
            n += 0
    return n


def total_words(text):
    m = 1
    for j in text:
        if (j == " "):
            m += 1
        else:
            m += 0
    return m


def total_sentences(text):
    s = 0
    for r in text:
        if (r == '!' or r == '?' or r == '.'):
            s += 1
        else:
            s += 0
    return s


if __name__ == "__main__":
    main()