#include <stdio.h>
#include <string.h>
#include <ctype.h>

int k_count = 0, i_count = 0, str_count = 0;

void keyword(char str[10]) {
    if (strcmp("for", str) == 0 || strcmp("printf", str) == 0 ||
        strcmp("while", str) == 0 || strcmp("do", str) == 0 ||
        strcmp("int", str) == 0 || strcmp("float", str) == 0 ||
        strcmp("char", str) == 0 || strcmp("double", str) == 0 ||
        strcmp("static", str) == 0 || strcmp("switch", str) == 0 ||
        strcmp("case", str) == 0 || strcmp("include", str) == 0) {
        printf("\n%s is a keyword\n", str);
        k_count++;
    } else {
        printf("\n%s is an identifier\n", str);
        i_count++;
    }
}

int main() {
    FILE *f1, *f2, *f3;
    char c, str[100];
    int num[100], lineno = 0, tokenvalue = 0, i = 0, j = 0, k = 0, count = 0, s_count = 0;

    f1 = fopen("input.txt", "r");
    f2 = fopen("identifier.txt", "w");
    f3 = fopen("special_char.txt", "w");

    if (!f1 || !f2 || !f3) {
        printf("Error opening file.\n");
        return 1;
    }

    printf("\nString literals found\n\n");
    while ((c = getc(f1)) != EOF) {
        if (isdigit(c)) {
            tokenvalue = c - '0';
            c = getc(f1);
            while (isdigit(c)) {
                tokenvalue = tokenvalue * 10 + (c - '0');
                c = getc(f1);
            }
            num[i++] = tokenvalue;
            ungetc(c, f1);
            count = i;
        } else if (isalpha(c)) {
            putc(c, f2);
            c = getc(f1);
            while (isalnum(c) || c == '_' || c == '$') {
                putc(c, f2);
                c = getc(f1);
            }
            putc(' ', f2);
            ungetc(c, f1);
        } else if (c == '"') {
            k = 0;
            str[k++] = c;
            c = getc(f1);
            while (c != '"' && c != EOF) {
                str[k++] = c;
                c = getc(f1);
            }
            str[k++] = c; 
            str[k] = '\0';
            printf("%s\n", str);
            str_count++;
        } else if (c == ' ' || c == '\t') {
            
        } else if (c == '\n') {
            lineno++;
        } else {
            putc(c, f3);
            s_count++;
        }
    }

    fclose(f2);
    fclose(f3);
    fclose(f1);

    printf("\nThe numbers in the program are: ");
    for (i = 0; i < count; i++)
        printf(" %d\t", num[i]);

	printf("\n\n");

    printf("\nThe keywords & identifiers are: ");
    printf("\n\n");
    f2 = fopen("identifier.txt", "r");
    k = 0;
    while ((c = getc(f2)) != EOF) {
        if (c != ' ')
            str[k++] = c;
        else {
            str[k] = '\0';
            keyword(str);
            k = 0;
        }
    }
    fclose(f2);

    printf("\nThe special characters are: ");
    f3 = fopen("special_char.txt", "r");
    while ((c = getc(f3)) != EOF) {
        printf("%c", c);
    }
    fclose(f3);

    printf("\nTotal number of lines: %d\n\n", lineno);
    printf("\nCount of numbers: %d\n\n", count);
    printf("\nTotal number of keywords: %d\n\n", k_count);
    printf("\nTotal number of identifiers: %d\n\n", i_count);
    printf("\nTotal number of special characters: %d\n\n", s_count);
    printf("\nTotal number of string literals: %d\n\n", str_count);

    return 0;
}
