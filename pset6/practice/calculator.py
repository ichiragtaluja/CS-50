import csv

houses = {
    "h": 0,
    "u": 0,
    "i": 0,
    "t": 0,
    "r": 0
}

with open("phonebook.csv", "r") as file:
    reader = csv.reader(file)
    next(reader)
    for row in reader:
        house = row[1]
        houses[house] += 1

for i in houses:
    count = houses[i]
    print(f"{i}: {count}")




