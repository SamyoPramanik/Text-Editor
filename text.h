#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stack>
#include "iGraphics.h"
using namespace std;

#define ll long long int
#define maxrc 50
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
void insert(char, ll, ll, ll);
void backspace(ll, ll, ll);
void save();
void printtext();
void draw_btns();
void showtext();
bool validmove(ll, ll);
void movecursor(ll, ll);
void move_left();
void move_right();
void move_up();
void move_down();
void move_in_line(ll, ll);
void arrange();
void printstring();
void find15();
void remove14(ll, ll);
void remove15(ll, ll);
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

    // printf("\nundo string =%s\n", newstr);
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

void insert(char ch, ll lrow, ll lcol, ll call_arrange)
{
    if (call_arrange == 1)
        commitchange();
    char *first = &str[0][0];

    for (ll i = maxrc * maxrc - 2; i >= lrow * maxrc + lcol; i--)
        *(first + i) = *(first + i - 1);

    str[lrow][lcol] = ch;
    if (call_arrange == 1)
    {
        arrange();
        printstring();

        if (ch == 15)
            movecursor(row + 1, 0);
        else
            move_right();
    }
}

void backspace(ll lrow, ll lcol)
{
    if (lrow == 0 && lcol == 0)
        return;

    commitchange();

    char *first = &str[0][0];

    if (*(first + maxrc * lrow + lcol - 1) == 14)
    {
        find15();
        return;
    }

    if (*(first + maxrc * lrow + lcol) == 15 && lcol == 0)
    {
        remove15(lrow, lcol);
        arrange();
        move_in_line(lrow - 1, maxrc);
        return;
    }

    for (ll i = lrow * maxrc + lcol; i < maxrc * maxrc; i++)
        *(first + i - 1) = *(first + i);

    *(first + maxrc * maxrc - 1) = 16;

    arrange();
    move_left();
}

void remove15(ll lrow, ll lcol)
{
    char *first = &str[0][0];
    for (ll i = lrow * maxrc + lcol; i < maxrc * maxrc; i++)
        *(first + i) = *(first + i + 1);
}

void find15()
{
    char *first = &str[0][0];
    ll lrow = row - 1;
    ll lcol = maxrc - 1;
    for (ll i = maxrc - 1; i >= 0; i--)
    {
        if (*(first + maxrc * lrow + i) == 15)
        {
            remove15(lrow, i);
            movecursor(lrow, i);
            arrange();
            return;
        }
    }
}

void remove14(ll lrow, ll lcol)
{
    char *first = &str[0][0];
    for (ll i = lrow * maxrc + lcol; i < maxrc * maxrc; i++)
        *(first + i) = *(first + i + 1);

    *(first + maxrc * maxrc - 1) = 16;
}

void arrange()
{
    char *first = &str[0][0];

    for (ll currow = 0; currow < maxrc; currow++)
        for (ll curcol = 0; curcol < maxrc; curcol++)
        {
            if (*(first + currow * maxrc + curcol) == 14)
            {
                remove14(currow, curcol);
                curcol--;
            }

            else if (*(first + currow * maxrc + curcol) == 15)
            {
                for (ll inscol = curcol + 1; inscol < maxrc; inscol++)
                    insert(14, currow, inscol, 0);
                currow++;
                curcol = -1;
            }
            // printstring();
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
            if (str[i][j] == 14 || str[i][j] == 15 || str[i][j] == 16)
                s[0] = ' ';
            else
                s[0] = str[i][j];
            s[1] = '\0';
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
    movecursor(0, 0);

    printf("\ncnt = %lld\n", cnt);
}

void printstring()
{
    // for (int i = 0; i < maxrc; i++)
    // {
    //     for (int j = 0; j < maxrc; j++)
    //     {
    //         printf("%03d ", str[i][j]);
    //     }
    //     printf("\n");
    // }
}

bool validmove(ll lrow, ll lcol)
{
    if (lrow > maxrc || lcol > maxrc)
        return false;

    if (lrow == 0 && lcol == 0)
        return true;

    if (lcol < 0)
        return false;
    if (lrow < 0)
        return false;

    char *first = &str[0][0];

    if (*(first + lrow * maxrc + lcol) == 15)
    {
        return true;
    }

    if (*(first + lrow * maxrc + lcol) == 14)
    {
        return false;
    }

    if (*(first + lrow * maxrc + lcol - 1) == 14 && *(first + lrow * maxrc + lcol) != 14)
    {
        return true;
    }

    if (*(first + lrow * maxrc + lcol - 1) != 16 && *(first + lrow * maxrc + lcol) == 16)
    {
        return true;
    }

    if (*(first + lrow * maxrc + lcol) != 14 && *(first + lrow * maxrc + lcol) != 15 && *(first + lrow * maxrc + lcol) != 16)
    {
        return true;
    }
    return false;
}

void movecursor(ll lrow, ll lcol)
{
    row = lrow;
    col = lcol;
    curx = textarealeft - 3 + charwidth * col;
    cury = textareatop - 2 - charheight * row;
}

void move_left()
{
    if (col == 0)
        move_in_line(row - 1, maxrc - 1);

    else if (validmove(row, col - 1))
        movecursor(row, col - 1);
}

void move_right()
{
    if (str[row][col] == 15 || col == maxrc)
    {
        if (str[row + 1][0] == 15)
        {
            movecursor(row + 1, 0);
        }
        else
            movecursor(row + 1, 1);
    }

    else if (validmove(row, col + 1))
        movecursor(row, col + 1);
}

void move_up()
{
    if (row == 0)
        return;
    move_in_line(row - 1, col);
}

void move_down()
{
    move_in_line(row + 1, col);
}

void move_in_line(ll lrow, ll lcol)
{
    bool allvalid;
    for (ll curcol = 0; curcol <= lcol; curcol++)
    {
        if (validmove(lrow, curcol) && !validmove(lrow, curcol + 1))
        {
            allvalid = false;
            movecursor(lrow, curcol);
            return;
        }
        else if (validmove(lrow, curcol) && validmove(lrow, curcol + 1))
            allvalid = true;
        else
            allvalid = false;

        if (allvalid)
            movecursor(lrow, lcol);
    }
}