# TODO
from cs50 import get_int
while True:
    # assign height
    height = get_int("Height: ")
    # checkk if height is in provided range
    if (height > 0 and height < 9):
        break
# programm for new line
for i in range(height):
    for j in range(height - i - 1):
        print(" ", end='')
    for t in range(i + 1):
        print("#", end='')
    print()
print()
print()

