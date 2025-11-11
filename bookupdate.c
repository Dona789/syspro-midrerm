// bookupdate.c
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int  id;
    char title[50];
    char author[50];
    int  year;
    int  borrow_cnt;
    int  borrowed;
} Book;

int main(void){
    int op, target_id;
    if (scanf("%d %d", &op, &target_id) != 2) return 1;

    FILE *fp = fopen("db.dat", "rb+");
    if (!fp) return 1;

    Book b;
    int found = 0;
    while (fread(&b, sizeof(Book), 1, fp) == 1){
        if (b.id == target_id){
            found = 1;
            long pos = ftell(fp) - (long)sizeof(Book); // 현재 레코드 시작 위치
            if (op == 0) { // 대출
                if (b.borrowed == 1) {
                    printf("대출 불가: '%s'는 이미 대출중입니다.\n", b.title);
                } else {
                    b.borrowed = 1;
                    b.borrow_cnt += 1;
                    fseek(fp, pos, SEEK_SET);
                    fwrite(&b, sizeof(Book), 1, fp);
                    printf("대출 완료: '%s' (대출횟수 %d)\n", b.title, b.borrow_cnt);
                }
            } else if (op == 1) { // 반납
                if (b.borrowed == 0) {
                    printf("반납 불필요: '%s'는 대출중이 아닙니다.\n", b.title);
                } else {
                    b.borrowed = 0;
                    fseek(fp, pos, SEEK_SET);
                    fwrite(&b, sizeof(Book), 1, fp);
                    printf("반납 완료: '%s'\n", b.title);
                }
            }
            break;
        }
    }
    if (!found) printf("ID %d 레코드를 찾을 수 없습니다.\n", target_id);
    fclose(fp);
    return 0;
}

