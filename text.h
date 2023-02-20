#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stack>
#include "iGraphics.h"
using namespace std;

#define ll long long int
#define maxrc 20
FILE *fin;
char str[maxrc][maxrc];
char alert[100];
ll line = 0, cnt = 0, i = 0, j = 0, k = 0, r = 0, c = 0, curx = 12, cury = 398, row, col, rr = 255, gg = 255, bb = 255, show_cursor = 1;

struct state
{
    char *stt;
    int curx, cury, row, col;

    state(char *stt_, int curx_, int cury_, int row_, int col_)
    {
        stt = stt_;
        curx = curx_;
        cury = cury_;
        row = row_;
        col = col_;
    }
};

stack<state> st;

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

void commitchange()
{
    char *chngstr = (char *)malloc(maxrc * maxrc);
    char *firstpos = chngstr;
    char *first = &str[0][0];
    while (*first)
        *chngstr++ = *first++;
    *chngstr = '\0';
    printf("\nchanged string =%s\n", firstpos);

    st.push(state(firstpos, curx, cury, row, col));
    printf("stack size=%d\n", st.size());
}

void undo()
{
    if (st.empty())
        return;
    printf("undo called\n");
    char *first = &str[0][0];
    cnt = strlen(first);

    state current = st.top();
    char *newstr = current.stt;
    curx = current.curx;
    cury = current.cury;
    row = current.row;
    col = current.col;

    for (int i = 0; i < maxrc * maxrc; i++)
        *(first + i) = '\0';

    printf("\nundo string =%s\n", newstr);
    while (*newstr)
        *first++ = *newstr++;

    free(current.stt);

    st.pop();
}

void movecursor(int mx, int my)
{
    row = (int)floor((414 - my) * 1.0 / 14);
    if (row > maxrc)
        row = maxrc;
    cury = 398 - 14 * row;

    col = (int)ceil((mx - 15) * 1.0 / 12);
    if (col > maxrc)
        col = maxrc;
    curx = 12 + 12 * col;
}

void insert(char ch)
{
    commitchange();
    cnt++;
    char *first = &str[0][0];

    for (ll i = cnt; i >= row * maxrc + col; i--)
        *(first + i) = *(first + i - 1);

    str[row][col] = ch;
    if (col % maxrc == 0 && col > 0)
    {
        col = 1;
        row++;
        curx = 24;
        cury -= 14;
    }
    else
    {
        col++;
        curx += 12;
    }
}

void backspace()
{
    if (row == 0 && col == 0)
        return;

    commitchange();

    char *first = &str[0][0];
    for (ll i = row * maxrc + col; i < cnt; i++)
        *(first + i - 1) = *(first + i);

    *(first + cnt - 1) = '\0';

    for (int i = cnt; i < maxrc * maxrc; i++)
        *(first + i) = '\0';

    cnt--;
    if (col == 0)
    {
        col = maxrc - 1;
        row--;
        curx = 12 * maxrc;
        cury += 14;
    }
    else
    {
        col--;
        curx -= 12;
    }
}

void save()
{
    fin = fopen("1.txt", "w");
    fprintf(fin, "%s", str);
    fclose(fin);
    strcpy(alert, "File saved");
}

void printtext()
{
    for (int i = 0; i < maxrc; i++)
    {
        for (int j = 0; j < maxrc; j++)
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
    iSetColor(100, 200, 100);
    iFilledRectangle(930, 250, 250, 40);
    iSetColor(255, 255, 255);
    iText(1030, 260, "Undo", GLUT_BITMAP_TIMES_ROMAN_24);
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
            if (cnt % maxrc == 0)
            {
                r++;
                c = 0;
            }
        }
    }

    fclose(fin);

    strcpy(alert, "File opened");

    printf("\ncnt = %lld\n", cnt);

    for (int i = 0; i <= r; i++)
    {
        for (int j = 0; j < maxrc; j++)
        {
            printf("%c", str[i][j]);
        }
        printf("\n");
    }
}
