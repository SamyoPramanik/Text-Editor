#include <stdio.h>
#include <string.h>
#define ll long long int
FILE *fin;
ll curpos = 0, line = 0;

char str[50][103];

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
    for(ll i=0;i<line;i++)
    {
        iText(25+i,446,str[i]);
    }
}

void showtext()
{
    line=0;
    ll j = 0, k = 0, cnt = 0;
    fin = fopen ("1.txt", "r+");
    while (true)
    {
        char ch = fgetc (fin);
        if (ch == EOF)
        {
            str[j][k] = '|';
            break;
        }
        else if (cnt != 0 && (cnt % 100 == 0) || ch == '\n')
        {
            j++;
            line++;
        }
        else
        {
            str[j][k++] = ch;
            printf("j=%d k=%d %c\n",j,k,ch);
            cnt++;
        }


    }
    printf ("%s\n", str[0]);
    printf("line=%d",line);
    for(int i=0;i<line;i++)
        printf("%s\n",str[i]);
}
