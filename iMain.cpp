#include "text.h"

/*
    function iDraw() is called again and again by the system.
*/
void iDraw()
{
    iClear();
    iSetColor(255, 255, 255);
    iText(12, 500, alert, GLUT_BITMAP_8_BY_13);
    iRectangle(10, 10, 900, 410);
    printtext();
    draw_btns();
    iSetColor(rr, gg, bb);
    iFilledRectangle(curx, cury, 2, charheight);
}

/*
    function iMouseMove() is called when the user presses and drags the mouse.
    (mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
    // place your codes here

    /*
        function iMouse() is called when the user presses/releases the mouse.
        (mx, my) is the position where the mouse pointer is.
    */
}
void iMouse(int button, int state, int mx, int my)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        printf("\nx=%d y=%d", mx, my);

        if (mx >= 950 && my >= 370 && mx <= 1200 && my <= 410)
            showtext();

        else if (mx >= 930 && my >= 310 && mx <= 1180 && my <= 350)
        {
            save();
        }

        else if (mx >= 930 && my >= 250 && mx <= 1120 && my <= 350)
        {
            undo();
        }

        else
        {
            if (mx <= 910 && my <= 410)
            {
                movecursor_click(mx, my);
            }
        }
    }
}

/*
    function iKeyboard() is called whenever the user hits a key in keyboard.
    key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
    if ((key >= '!' && key <= 'z') || key == ' ')
    {
        insert(key, row, col);
    }
    else if (key == '\b')
    {
        backspace(row, col);
    }
    printf("curx= = %lld cury = %lld\n", curx, cury);
}

/*
    function iSpecialKeyboard() is called whenver user hits special keys like-
    function keys, home, end, pg up, pg down, arraows etc. you have to use
    appropriate constants to detect them. A list is:
    GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
    GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
    GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
    GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{
    if (key == GLUT_KEY_UP)
        move_up();

    else if (key == GLUT_KEY_DOWN)
        move_down();

    else if (key == GLUT_KEY_LEFT)
        move_left();

    else if (key == GLUT_KEY_RIGHT)
        move_right();

    printf("row=%lld col=%lld", row, col);
}

int main()
{
    for (ll i = 0; i < maxrc; i++)
        for (ll j = 0; j < maxrc; j++)
            str[i][j] = 14;

    iSetTimer(800, cngcursor);
    iInitialize(1200, 720, "Text Editor");
    return 0;
}
