#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CALLS 10000
#define MAX_PHONE 10005

typedef struct {
    char phone[11];
    int calls;
    long long total_time;
} PhoneInfo;

PhoneInfo phones[MAX_CALLS];
int phone_count = 0;

int total_calls = 0;
int all_phone_correct = 1;

int exist_phone(char *phone) {
    for (int i = 0; i < phone_count; i++) {
        if (strcmp(phones[i].phone, phone) == 0)
            return i;
    }
    return -1;
}

int check_phone(char *phone) {
    if (strlen(phone) != 10)
        return 0;

    for (int i = 0; i < 10; i++) {
        if (phone[i] < '0' || phone[i] > '9')
            return 0;
    }

    return 1;
}

int time_to_sec(char *time) {
    int h, m, s;
    sscanf(time, "%d:%d:%d", &h, &m, &s);

    return h * 3600 + m * 60 + s;
}

int main(){
    char line[256];

    while (fgets(line,sizeof(line), stdin)) {
        if (line[0] == '#') break;

        char from[20], to[20], date[20], time_start[20], time_end[20];

        sscanf(line, "call %s %s %s %s %s", from, to, date, time_start, time_end);

        if (!check_phone(from) || !check_phone(to)){
            all_phone_correct = 0;
        }

        int duration = time_to_sec(time_end) - time_to_sec(time_start);

        int pos = exist_phone(from);

        if (pos == -1){
            strcpy(phones[phone_count].phone, from);
            phones[phone_count].calls = 1;
            phones[phone_count].total_time = duration;
            phone_count++;
        } else {
            phones[pos].calls++;
            phones[pos].total_time += duration;
        }

        total_calls++;
    }

    while (fgets(line, sizeof(line), stdin)) {
        if (line[0] == '#') break;

        char cmd[100];
        char phone[20];

        sscanf(line, "%s", cmd);

        if (strcmp(cmd, "?check_phone_number") == 0) {
            printf("%d\n", all_phone_correct);
        }
        else if (strcmp(cmd, "?number_total_calls") == 0) {
            printf("%d\n", total_calls);
        }
        else if (strcmp(cmd, "?number_calls_from") == 0) {
            sscanf(line, "%s %s", cmd, phone);
            int pos = exist_phone(phone);

            if (pos == -1)
                printf("0\n");
            else
                printf("%d\n", phones[pos].calls);
        }

        else if (strcmp(cmd, "?count_time_calls_from") == 0) {
            sscanf(line, "%s %s", cmd, phone);
            int pos = exist_phone(phone);

            if (pos == -1)
                printf("0\n");
            else
                printf("%lld\n", phones[pos].total_time);
            }
        }

    return 0;
}