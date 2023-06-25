#include <stdio.h>
#include <cs50.h>
#include <string.h>

typedef struct
{
    string name;
    string number;
}
person;

int main(void)
{
    person people[2];

    people[0].name = "Chirag";
    people[0].number = "9717239115";

    people[1].name = "Shivi";
    people[1].number = "9996313639";

    for (int i = 0; i < 2; i ++)
    {
        if ((strcmp(people[i].name, "Chirag")) == 0)
        {
            printf("%s\n", people[i].number);
            return 0;
        }
    }
    printf("Not found\n");
    return 1;
}