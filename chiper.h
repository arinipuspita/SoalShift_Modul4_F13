#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char charList[] = "qE1~ YMUR2\"`hNIdPzi%^t@(Ao:=CQ,nx4S[7mHFye#aT6+v)DfKL$r?bkOGB>}!9_wV']jcp5JZ&Xl|\\8s;g<{3.u*W-0";
int key = 17;
char solved[100] = {'\0'};
char toBeSolved[100];

void Reset(){
    int i;
    for(i = 0; i < 100; i++){
        solved[i] = '\0';
    }
}

void ChiperSolve(int i)
{
    int j, k;
    if (i == 0)
    {
        for (j = 0; j < strlen(toBeSolved); j++)
        {
            if (toBeSolved[j] == '/')
                solved[j] = '/';
            else
            {
                for (k = 0; k < strlen(charList); k++)
                {
                    if (charList[k] == toBeSolved[j])
                    {
                        solved[j] = charList[(k + key) % strlen(charList)];
                    }
                }
            }
        }
        return;
    }
    else
    {
        for (j = 0; j < strlen(toBeSolved); j++)
        {
            if (toBeSolved[j] == '/')
                solved[j] = '/';
            else
            {
                for (k = 0; k < strlen(charList); k++)
                {
                    if (charList[k] == toBeSolved[j])
                    {
                        int temp  = (k - key);
                        if(temp < 0)
                            temp += strlen(charList);
                        solved[j] = charList[temp];
                    }
                }
            }
        }
    }
}