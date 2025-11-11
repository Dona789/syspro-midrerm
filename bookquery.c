// bookquery.c
// 사용법: ./bookquery <mode>
// mode = 0 : 모든 책 출력
// mode = 1 : 대출 가능한 책만 출력

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int  id;
    char title[64];
    char author[64];
    int  year;
    int  loan_count;
    int  is_borrowed;   // 0 = 가능, 1 = 대출중
} Book;

void print_book(Book *b) {
    printf("%-4d %-12s %-12s %-6d %-6d %-6s\n",
           b->id,
           b->title,
           b->author,
           b->year,
           b->loan_count,
           b->is_borrowed ? "True" : "False");
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "사용법: %s <mode>\nmode: 0(전체), 1(대출가능)\n", argv[0]);
        return 1;
    }

    int mode = atoi(argv[1]);  // 0 또는 1

    FILE *fp = fopen("db.dat", "rb");
    if (!fp) {
        perror("db.dat");
        return 2;
    }

    Book b;

    printf("ID   Title        Author       Year   Count  Borrow\n");
    printf("--------------------------------------------------------\n");

    while (fread(&b, sizeof(Book), 1, fp) == 1)
    {
        if (mode == 0) {
            // 모든 책 출력
            print_book(&b);
        }
        else if (mode == 1) {
            // 대출 가능한 책만 출력
            if (b.is_borrowed == 0)
                print_book(&b);
        }
    }

    fclose(fp);
    return 0;
}

