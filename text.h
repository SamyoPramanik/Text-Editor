#include <stdio.h>
#include <string.h>
#define ll long long int
FILE *fin;
char str[50][103];
ll line = 0, cnt = 0, i = 0, j = 0, k = 0;

void moveleft()
{
}

void moveright()
{
}

void save()
{
}

void printtext()
{
    // for (ll i = 0; i <= line; i++)
    //     iText(15, 446 - 15 * i, str[i]);
}

void showtext()
{
    cnt = j = k = line = 0;
    fin = fopen("1.txt", "r+");
    while (1)
    {
        char ch = fgetc(fin);
        if (ch == EOF)
        {
            str[j][k] = '|';
            break;
        }

        else
        {
            printf("%c", ch);
            str[j][k++] = ch;
            printf("\nj= %d k = %d\n", j, k);
            cnt++;
            if (cnt % 100 == 0)
            {
                printf("\nnewline\n");
                j++;
                k = 0;
                line++;
            }
        }
    }

    printf("line = %d cnt = %d", line, cnt);

    for (ll i = 0; i <= line; i++)
        printf("%s\n", str[i]);
}
