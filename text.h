#include <stdio.h>
#include <string.h>
#include <math.h>
#define ll long long int
FILE *fin;
char str[10][10];
ll line = 0, cnt = 0, i = 0, j = 0, k = 0, r = 0, c = 0, curx = 12, cury = 398, row, col, rr = 255, gg = 255, bb = 255, show_cursor = 1;

void cngcursor()
{
    if (show_cursor == 1)
    {
        rr = gg = bb = 0;
        show_cursor = 0;
    }
    else
    {
        rr = gg = bb = 255;
        show_cursor = 1;
    }
}

void insert(char ch)
{
    cnt++;
    char *first = &str[0][0];

    for (ll i = cnt; i >= row * 5 + col; i--)
        *(first + i) = *(first + i - 1);

    str[row][col]=ch;
}

void moveright()
{
}

void save()
{
}

void printtext()
{
    for (int i = 0; i <= r; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            char s[2];
            s[0] = str[i][j];
            s[1] = '\0';
            // printf("%s", s);
            iText(15 + 12 * j, 400 - 14 * i, s);
        }
    }
}

void draw_btns()
{
    iSetColor(100, 200, 100);
    iFilledRectangle(930, 370, 250, 40);
    iSetColor(255, 255, 255);
    iText(1030, 380, "Open", GLUT_BITMAP_TIMES_ROMAN_24);
    iSetColor(100, 200, 100);
    iFilledRectangle(930, 310, 250, 40);
    iSetColor(255, 255, 255);
    iText(1030, 320, "Save", GLUT_BITMAP_TIMES_ROMAN_24);
}

void showtext()
{
    cnt = r = c = 0;
    fin = fopen("1.txt", "r");
    while (true)
    {
        char ch = fgetc(fin);
        if (ch == EOF)
            break;

        else
        {
            cnt++;
            str[r][c++] = ch;
            if (cnt % 10 == 0)
            {
                r++;
                c = 0;
            }
        }
    }

    printf("\ncnt = %lld\n", cnt);

    for (int i = 0; i <= r; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            printf("%c", str[i][j]);
        }
        printf("\n");
    }
}
