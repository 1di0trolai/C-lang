#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SUBMIT 100005
#define MAX_ID 100005

typedef struct {
    char id[20];
    int submits_err;
    long long total_point;
}SubmitInfo;

SubmitInfo ids[MAX_SUBMIT];
int id_count = 0;

int submit_times[MAX_SUBMIT];
int total_submits = 0;
int num_submits_err = 0;

int exist_id(char *id){
    for (int i = 0; i < id_count; i++){
        if (strcmp(ids[i].id, id) == 0) return i;
    }
    return -1;
}

int time_to_sec(char *time) {
    int h, m, s;
    sscanf(time, "%d:%d:%d", &h, &m, &s);

    return h * 3600 + m * 60 + s;
}

int main(){
    char line[256];

    while (fgets(line, sizeof(line), stdin)){
        if (line[0] == '#') break;
        
        char from[20], prob[20], time[20], stat[20];
        int point;
        sscanf(line, "%s %s %s %s %d", from, prob, time, stat, &point);

        int dura = time_to_sec(time);
        submit_times[total_submits] = dura;
        int pos = exist_id(from);

        if (pos == -1){
            strcpy(ids[id_count].id, from);
            if (strcmp(stat, "ERR") == 0) ids[id_count].submits_err = 1;
            else ids[id_count].submits_err = 0;
            ids[id_count].total_point = point;
            id_count++;
        } else {
            if (strcmp(stat, "ERR") == 0) ids[pos].submits_err++;
            ids[pos].total_point += point;
        }

        if (strcmp(stat, "ERR") == 0) num_submits_err++;
        total_submits++;
    }
    
    while (fgets(line, sizeof(line), stdin)) {
        if (line[0] == '#') break;

        char cmd[100], id[20], time_start[20], time_end[20];

        sscanf(line, "%s", cmd);

        if (strcmp(cmd, "?total_number_submissions") == 0) {
            printf("%d\n", total_submits); 
        } else if (strcmp(cmd, "?number_error_submision") == 0) {
            printf("%d\n", num_submits_err);
        } else if (strcmp(cmd, "?number_error_submision_of_user") == 0) {
            sscanf(line, "%s %s", cmd, id);
            int pos = exist_id(id);
            if (pos == -1) printf("0\n");
            else printf("%d\n", ids[pos].submits_err);
        } else if (strcmp(cmd, "?total_point_of_user") == 0) {
            sscanf(line, "%s %s", cmd, id);
            int pos = exist_id(id);
            if (pos == -1) printf("0\n");
            else printf("%lld\n", ids[pos].total_point);
        } else if (strcmp(cmd, "?number_submission_period") == 0) {
            sscanf(line, "%s %s %s", cmd, time_start, time_end);
            int start = time_to_sec(time_start);
            int end = time_to_sec(time_end);
            int cnt = 0;
            for (int i = 0; i < total_submits; i++){
                if (submit_times[i] >= start && submit_times[i] <= end) {
                    cnt++;
                }
            }
            printf("%d\n", cnt);
        }    
    }
    
    return 0;
}