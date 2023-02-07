#include <stdio.h>

int main()
{
    FILE *fin, *fout;
    fin = fopen("files/1.txt", "r");
    fout = fopen("files/2.txt", "w");
    char ch;
    while (true)
    {
        ch = fgetc(fin);
        if (ch == EOF)
            break;

        printf("%c", ch);
        fputc(ch, fout);
    }
    printf("file copied successfully\n");
    fclose(fin);
    fclose(fout);
}