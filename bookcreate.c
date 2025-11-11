// bookcreate.c
// 입력으로 여러 책 정보를 받아서,
// "대출 가능한 책(is_borrowed == 0)"만 db.dat에 저장하는 프로그램

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int  id;
    char title[64];
    char author[64];
    int  year;
    int  loan_count;
    int  is_borrowed;   // 0 = 대출 가능, 1 = 대출 중
} Book;

int parse_bool(const char *s) {
    // True/true/1 => 1,   False/false/0 => 0
    char buf[16];
    int i;
    for (i = 0; s[i] && i < 15; i++)
        buf[i] = tolower((unsigned char)s[i]);
    buf[i] = '\0';

    if (strcmp(buf, "true") == 0) return 1;
    if (strcmp(buf, "1") == 0) return 1;
    return 0; // 나머지는 False로 처리
}

int main(void) {
    FILE *fp = fopen("db.dat", "wb");
    if (!fp) {
        perror("db.dat");
        return 1;
    }

    Book b;
    char borrowed_str[16];

    // 입력 예:
    // 1 1984 George 1949 7 False
    // 2 Luster Raven 2020 3 True
    // 3 Hamnet Maggie 2020 0 False
    // 4 theWish Nocholas 2021 2 true
    while (scanf("%d %63s %63s %d %d %15s",
                 &b.id, b.title, b.author,
                 &b.year, &b.loan_count, borrowed_str) == 6) {

        b.is_borrowed = parse_bool(borrowed_str);

        if (b.is_borrowed == 0) {
            // 대출 가능 책만 저장
            fwrite(&b, sizeof(Book), 1, fp);
        }
    }

    fclose(fp);
    return 0;
}

