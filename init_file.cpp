#include <stdio.h>

int main()
{
    FILE *fp = fopen("1.txt", "w");

    for (int i = 0; i < 20; i++)
        for (int j = 0; j < 20; j++)
        {
            fprintf(fp, "%c", 14);
        }
    fclose(fp);
}