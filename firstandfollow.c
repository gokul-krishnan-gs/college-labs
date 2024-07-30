#include <stdio.h>
#include <string.h>
#include <ctype.h>

int n, m = 0;
char a[10][10], f[10];
int firstDone[26], followDone[26];

void follow(char c);
void first(char c);

int main() {
    int z;
    char c;
    printf("Enter the number of productions:\n");
    scanf("%d", &n);
    printf("Enter the productions:\n");
    for (int i = 0; i < n; i++)
        scanf("%s", a[i]);

    do {
        m = 0;
        printf("Enter the element whose FIRST and FOLLOW are to be found: ");
        scanf(" %c", &c);

        memset(firstDone, 0, sizeof(firstDone));
        first(c);
        printf("FIRST(%c) = {", c);
        for (int i = 0; i < m; i++)
            printf("%c", f[i]);
        printf("}\n");

        m = 0;
        memset(followDone, 0, sizeof(followDone));
        follow(c);
        printf("FOLLOW(%c) = {", c);
        for (int i = 0; i < m; i++)
            printf("%c", f[i]);
        printf("}\n");

        printf("Continue (0/1)? ");
        scanf("%d", &z);
    } while (z == 1);

    return 0;
}

void first(char c) {
    if (!isupper(c)) {
        if (strchr(f, c) == NULL) {
            f[m++] = c;
        }
        return;
    }
    
    for (int k = 0; k < n; k++) {
        if (a[k][0] == c) {
            if (a[k][2] == '$') {
                if (strchr(f, '$') == NULL) {
                    f[m++] = '$';
                }
            } else {
                for (int j = 2; j < strlen(a[k]); j++) {
                    if (!isupper(a[k][j])) {
                        if (strchr(f, a[k][j]) == NULL) {
                            f[m++] = a[k][j];
                        }
                        break;
                    } else {
                        if (!firstDone[a[k][j] - 'A']) {
                            firstDone[a[k][j] - 'A'] = 1;
                            int tempM = m;
                            first(a[k][j]);
                            for (int l = tempM; l < m; l++) {
                                if (f[l] == '$') {
                                    if (strchr(f, '$') == NULL) {
                                        f[m++] = '$';
                                    }
                                    continue;
                                }
                            }
                            if (strchr(f, '$') == NULL) break;
                        }
                    }
                }
            }
        }
    }
}

void follow(char c) {
    if (a[0][0] == c && strchr(f, '$') == NULL) f[m++] = '$';

    for (int i = 0; i < n; i++) {
        for (int j = 2; j < strlen(a[i]); j++) {
            if (a[i][j] == c) {
                if (a[i][j + 1] != '\0') {
                    int tempM = m;
                    first(a[i][j + 1]);
                    for (int k = tempM; k < m; k++) {
                        if (f[k] == '$') {
                            if (a[i][0] != c && !followDone[a[i][0] - 'A']) {
                                followDone[a[i][0] - 'A'] = 1;
                                follow(a[i][0]);
                            }
                        }
                    }
                } else if (a[i][j + 1] == '\0' && c != a[i][0]) {
                    if (!followDone[a[i][0] - 'A']) {
                        followDone[a[i][0] - 'A'] = 1;
                        follow(a[i][0]);
                    }
                }
            }
        }
    }
}
