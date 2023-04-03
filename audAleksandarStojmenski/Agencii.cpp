#include <stdio.h>
#include <string.h>

typedef struct Patuvanje{
char destinacija[100];
float cena;
int daliLet;
int brDenovi;
}Patuvanje;


typedef struct Agencija{
char ime[100];
char lokacija[100];
Patuvanje patuvanja[50];
int n;
}Agencija;

void print(Agencija a)
{
    printf("%s %s\n",a.ime, a.lokacija);
    for(int i=0;i<a.n;i++)
    {
        printf("%s %d %.2f\n",a.patuvanja[i].destinacija,
               a.patuvanja[i].brDenovi,
               a.patuvanja[i].cena);
    }
}

void najeftina_ponuda(Agencija niza[], int n, int daliLet)
{
    int flag = 1;
    int min;
    int minIndex;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<niza[i].n;j++)
        {
            if(niza[i].patuvanja[j].daliLet == daliLet
               && flag == 1)
            {
                flag =0;
                min = niza[i].patuvanja[j].cena
                minIndex = i;
            }
            if(niza[i].patuvanja[j].daliLet == daliLet
               && (niza[i].patuvanja[j].cena )<=min)
            {
                min = niza[i].patuvanja[j].cena;
                minIndex = i;
            }
        }
    }
    printf("Najeftina ponuda ima agencijata:\n%s %s\nNajniskata cena iznesuva: %d",
           niza[minIndex].ime,niza[minIndex].lokacija,
           min);
}
int main()
{
     Agencija s[100];
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        int brPatuvanja;
        scanf("%s %s",s[i].ime,s[i].lokacija);
        scanf("%d",&brPatuvanja);
        s[i].n = brPatuvanja;
        for(int j=0;j<brPatuvanja;j++)
        {
            scanf("%s",s[i].patuvanja[j].destinacija);
            scanf("%f",&s[i].patuvanja[j].cena);
            scanf("%d",&s[i].patuvanja[j].daliLet);
            scanf("%d",&s[i].patuvanja[j].brDenovi);
        }
    }
    int daliLet;
    scanf("%d",&daliLet);
    for(int i=0;i<n;i++)
    {
        print(s[i]);

    }
    najeftina_ponuda(s, n,daliLet);

    return 0;

}
