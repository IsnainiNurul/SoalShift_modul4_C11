#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char charList[] = "qE1~ YMUR2\"`hNIdPzi%^t@(Ao:=CQ,nx4S[7mHFye#aT6+v)DfKL$r?bkOGB>}!9_wV']jcp5JZ&Xl|\\8s;g<{3.u*W-0"; //karakter list yang akan digunakan
int key = 17;
char solved[100] = {'\0'};
char toBeSolved[100];

void Reset(){ // untuk mereset
    int i;
    for(i = 0; i < 100; i++){
        solved[i] = '\0';
    }
}

void ChiperSolve(int i)
{
    int j, k;
    if (i == 0) //jika enkripsi
    {
        for (j = 0; j < strlen(toBeSolved); j++) //looping sepanjang suku kata nama folder/file
        {
            if (toBeSolved[j] == '/') //jika '/' maka tetap '/'
                solved[j] = '/';
            else
            {
                for (k = 0; k < strlen(charList); k++) //mencari letak di charlist urutan keberapa
                {
                    if (charList[k] == toBeSolved[j]) //saat sudah ketemu
                    {
                        solved[j] = charList[(k + key) % strlen(charList)]; //ditambahkan 17 dan jika angkanya lebih dimodulo agar balik
                    }
                }
            }
        }
        return;
    }
    else
    {
        for (j = 0; j < strlen(toBeSolved); j++) // jika dekrip
        {
            if (toBeSolved[j] == '/') // jika / lanjut
                solved[j] = '/';
            else
            {
                for (k = 0; k < strlen(charList); k++)
                {
                    if (charList[k] == toBeSolved[j])
                    {
                        int temp  = (k - key); //pengurangan
                        if(temp < 0) //jika min
                            temp += strlen(charList); //karakter ditambah panjang charlist
                        solved[j] = charList[temp]; 
                    }
                }
            }
        }
    }
}

