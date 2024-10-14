//NFA TO DFA
#include<string.h>
#include <stdio.h>

char st[20][20]={"A0A","A1A","A1B","B0C","B1C"};
char istates[20],result[20],state[20],sym[3]="01",states[20][20];

int ns,nt;

int main()
{
    int r=0;
    printf("Enter number of states");
    scanf("%d",&ns);

    printf("Enter number of transitions");
    scanf("%d",&nt);

    printf("Enter initial states");
    scanf("%s",istates);
    strcpy(states[r++],istates);
    printf("\t\t%c\t%c",sym[0],sym[1]);
    for(int x=0;x<r;x++)
    {
        printf("\n");
        printf("%s\t|\t",states[x]);
    for(int l=0;l<strlen(sym);l++)
    {
        int p=0;
    for(int i=0;i<strlen(states[i]);i++)
    {
        char state=states[x][i];
    for(int j=0;j<nt;j++)
    {
        char state1=st[j][0],input=st[j][1],state2=st[j][2];
        if(state==state1&&input==sym[l])
        {
            result[p++]=state2;
    }
    }
    }

    result[p++]="\0";

    int f=0;

    for(int a=0;a<r;a++)
    {
        if(strcmp(states[a],result)==0)
        {
            f=1;
            break;
        }
    }

    if(f==0)
    {
    strcpy(states[r++],result);
    }
    printf("%s\t",result);
    }

    }

return 0;

}


