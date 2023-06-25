# TODO
from cs50 import get_int

while True:
    height = get_int("Height: ")
    if (height > 0 and height < 9):
        break

for i in range(height):
    for j in range(height - 1 - i):
        print(" ", end="")
    for t in range(i + 1):
        print("#", end="")
    for s in range(2):
        print(" ", end="")
    for d in range(i + 1):
        print("#", end="")
    print()