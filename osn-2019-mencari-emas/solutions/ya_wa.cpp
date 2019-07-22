#include <bits/stdc++.h>
using namespace std;

int main() {
    int r, c, q, x;
    int a[6];
    int ra[6], ca[6];

    scanf("%d%d%d", &r, &c, &q);

    printf("? 1 1\n"); fflush(stdout);
    scanf("%d", &a[0]);

    printf("? %d 1\n", r); fflush(stdout);
    scanf("%d", &a[1]);

    printf("? 1 %d\n", c); fflush(stdout);
    scanf("%d", &a[2]);

    printf("? %d %d\n", r, c); fflush(stdout);
    scanf("%d", &a[3]);

    int dx;
    dx = ((1 + a[0]) - (r - a[1])) / 2;
    ra[0] = 1 + a[0] - dx;
    ca[0] = 1 + dx;
    // cerr << dx << " " << ra[0] << " " << ca[0] << "\n";

    dx = ((1 + a[0]) - (c - a[2])) / 2;
    ra[1] = 1 + dx;
    ca[1] = 1 + a[0] - dx;
    // cerr << dx << " " << ra[1] << " " << ca[1] << "\n";

    dx = ((1 + a[1]) - (c - a[3])) / 2;
    ra[2] = r - dx;
    ca[2] = 1 + a[1] - dx;
    // cerr << dx << " " << ra[2] << " " << ca[2] << "\n";

    dx = ((1 + a[2]) - (r - a[3])) / 2;
    ra[3] = 1 + a[2] - dx;
    ca[3] = c - dx;
    // cerr << dx << " " << ra[3] << " " << ca[3] << "\n";

    if (1 <= ra[0] && ra[0] <= r && 1 <= ca[0] && ca[0] <= c) {
        printf("? %d %d\n", ra[0], ca[0]); fflush(stdout);
        scanf("%d", &a[4]);

        if (a[4] == 0) {
            printf("! %d %d %d %d\n", ra[0], ca[0], ra[3], ca[3]);
        } else {
            printf("! %d %d %d %d\n", ra[1], ca[1], ra[2], ca[2]);
        }
        fflush(stdout);
    } else {
        printf("! %d %d %d %d\n", ra[1], ca[1], ra[2], ca[2]);
    }

    return 0;
}