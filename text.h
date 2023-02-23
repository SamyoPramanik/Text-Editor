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
ll charheight = 14;   // 14
ll charwidth = 12;    // 12
ll textarealeft = 15; // 15
ll textareatop = 400; // 400
ll line = 0, cnt = 0, i = 0, j = 0, k = 0, r = 0, c = 0, curx = textarealeft - 3, cury = textareatop - 2, row, col, rr = 255, gg = 255, bb = 255, show_cursor = 1;

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

void cngcursor();
void commitchange();
void undo();
void movecursor_click(int, int);
void insert(char);
void backspace();
void save();
void printtext();
void draw_btns();
void showtext();
bool validmove(ll, ll);
void movecursor(ll, ll);

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
    char *chngstr = (char *)malloc(maxrc * maxrc * sizeof(char));

    char *firstpos = chngstr;

    char *first = &str[0][0];
    while (*first)
        *chngstr++ = *first++;
    printf("\nsize=%d\nstr==", strlen(firstpos));
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
        *(first + i) = 14;

    printf("\nundo string =%s\n", newstr);
    for (ll i = 1; i <= maxrc * maxrc; i++)
        *first++ = *newstr++;

    free(current.stt);

    st.pop();
}

void movecursor_click(int mx, int my)
{
    ll lrow = (int)floor((textareatop + charheight - my) * 1.0 / charheight);
    ll lcol = (int)ceil((mx - textarealeft) * 1.0 / charwidth);

    if (validmove(lrow, lcol))
        movecursor(lrow, lcol);
}

void insert(char ch)
{
    commitchange();
    char *first = &str[0][0];

    for (ll i = maxrc * maxrc - 2; i >= row * maxrc + col; i--)
        *(first + i) = *(first + i - 1);

    str[row][col] = ch;
    if (col % maxrc == 0 && col > 0)
        movecursor(row + 1, 1);
    else
        movecursor(row, col + 1);
}

void backspace()
{
    if (row == 0 && col == 0)
        return;

    commitchange();

    char *first = &str[0][0];
    for (ll i = row * maxrc + col; i < maxrc * maxrc; i++)
        *(first + i - 1) = *(first + i);

    *(first + maxrc * maxrc - 1) = 14;
    if (col == 0)
        movecursor(row - 1, maxrc - 1);
    else
        movecursor(row, col - 1);
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
            if (str[i][j] == 14)
                s[0] = ' ';
            else
                s[0] = str[i][j];
            s[1] = '\0';
            // printf("%s", s);
            iText(textarealeft + charwidth * j, textareatop - charheight * i, s);
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
    for (ll readch = 1; readch <= maxrc * maxrc; readch++)
    {
        char ch = fgetc(fin);
        str[r][c++] = ch;
        if (readch % maxrc == 0)
        {
            r++;
            c = 0;
        }
    }
    fclose(fin);

    strcpy(alert, "File opened");

    printf("\ncnt = %lld\n", cnt);

    for (int i = 0; i < maxrc; i++)
    {
        for (int j = 0; j < maxrc; j++)
        {
            printf("%c", str[i][j]);
        }
        printf("\n");
    }
}

bool validmove(ll lrow, ll lcol)
{
    printf(" lrow=%lld lcol=%lld\n", lrow, lcol);
    if (lrow > maxrc || lcol > maxrc)
        return false;

    if (lrow == 0 && lcol == 0)
        return true;

    if (lcol < 0)
        return false;
    if (lrow < 0)
        return false;

    if (str[lrow][lcol - 1] == 14)
        return false;

    return true;
}

void movecursor(ll lrow, ll lcol)
{
    row = lrow;
    col = lcol;
    curx = textarealeft - 3 + charwidth * col;
    cury = textareatop - 2 - charheight * row;
}