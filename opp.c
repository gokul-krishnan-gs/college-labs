#include <stdio.h>
#include <string.h>

void main() {
    char stack[20], ip[20], opt[10][10][1], ter[10];
    int i, j, k, n, top = 0, row = -1, col = -1;

    for (i = 0; i < 20; i++) {
        stack[i] = 0;
        ip[i] = 0;
    }

    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            opt[i][j][0] = 0;
        }
    }

    printf("Enter the number of terminals: ");
    scanf("%d", &n);

    printf("Enter the terminals: ");
    scanf("%s", ter);

    printf("Enter the table values:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("Enter the value for %c %c: ", ter[i], ter[j]);
            scanf("%s", opt[i][j]);
        }
    }

    printf("\nOPERATOR PRECEDENCE TABLE:\n");
    printf("\t");
    for (i = 0; i < n; i++) {
        printf("\t%c", ter[i]);
    }
    printf("\n");

    for (i = 0; i < n; i++) {
        printf("%c |", ter[i]);
        for (j = 0; j < n; j++) {
            printf("\t%c", opt[i][j][0]);
        }
        printf("\n");
    }

    stack[top] = '$';
    printf("\nEnter the input string (append with $): ");
    scanf("%s", ip);

    i = 0;
    printf("\nSTACK\t\tINPUT STRING\t\tACTION\n");
    printf("%s\t\t%s\t\t\n", stack, ip);

    while (i <= strlen(ip)) {
        row = col = -1;
        for (k = 0; k < n; k++) {
            if (stack[top] == ter[k]) row = k;
            if (ip[i] == ter[k]) col = k;
        }

        if (row == -1 || col == -1) {
            printf("\nString is not accepted\n");
            break;
        }

        if (stack[top] == '$' && ip[i] == '$') {
            printf("String is ACCEPTED\n");
            break;
        } else if (opt[row][col][0] == '<' || opt[row][col][0] == '=') {
            stack[++top] = ip[i];
            ip[i] = ' ';
            printf("Shift %c\n", stack[top]);
            i++;
        } else if (opt[row][col][0] == '>') {
            while (stack[top] != '<') {
                top--;
            }
            top--;
            printf("Reduce\n");
        } else {
            printf("\nString is not accepted\n");
            break;
        }

        printf("%s\t\t%s\t\t\n", stack, ip);
    }

    getchar();
}
