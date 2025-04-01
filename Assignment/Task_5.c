#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    char *name;
    int happinessLevel;
} Member;

typedef struct {
    Member* members;
    int numMembers;
    int happinessLevel;
} Group;

Group* splitGroups(Member* const members, int numMembers, int standardLevel);

int main() {
    Member members[] = {
        {"Alice", 5},
        {"Bob", 7},
        {"Charlie", 3},
        {"David", 8},
        {"Eve", 6},
        {"Frank", 4},
        {"Grace", 9},
        {"Henry", 2},
    };

    int standardHappinessLevel = 10;

    Group* groups = splitGroups(members, 8, standardHappinessLevel);

    for (int i = 0; i < 3; i++) {
        printf("Group %d (Happiness level: %d): ", i + 1, groups[i].happinessLevel);
        for (int j = 0; j < groups[i].numMembers; j++) {
            printf("%s ", groups[i].members[j].name);
        }
        printf("\n");
    }
    free(groups);
}

//solve

int cmp_happinessLevel(const void* v1, const void* v2) {
    Member *p1 = (Member*) v1;
    Member *p2 = (Member*) v2;
    if (p2 -> happinessLevel > p1 -> happinessLevel) return 1;
    else if (p2 -> happinessLevel < p1 -> happinessLevel) return -1;
    else return 0;
}

Group* splitGroups(Member* const members, int numMembers, int standardLevel) {
    Group* groups;
    groups = (Group*)malloc(numMembers * sizeof(Group));

    int total = 0;
    for (int i = 0; i < numMembers; i++) {
        total += members[i].happinessLevel;
    }
    if (total < standardLevel) return NULL;

    qsort(members, numMembers, sizeof(* members), cmp_happinessLevel);

    int num_Group = 0, visit;
    bool check[numMembers];

    for (int i = 0; i < numMembers; i++) {
        check[i] = false;
    }

    for (int i = 0; i < numMembers; i++) {
        groups[num_Group].members = (Member*)malloc(sizeof(Member) * numMembers);
        if (members[i].happinessLevel >= standardLevel) {
            groups[num_Group].members[0] = members[i];
            groups[num_Group].numMembers = 1;
            groups[num_Group].happinessLevel = members[i].happinessLevel;
            char *new_str = (char*)malloc(sizeof(char) * 50);
            strcpy(new_str, "Happy ");
            strcat(new_str, members[i].name);
            groups[num_Group].members[0].name = new_str;
            check[i] = true;
        } 
        else if (!check[i]) {
            int delta_min = 10000000;
            Member sample_members[numMembers * 5];
            groups[num_Group].members[0] = members[i];

            char *new_str = (char*)malloc(sizeof(char) * 50);
            strcpy(new_str, "Happy ");
            strcat(new_str, members[i].name);
            groups[num_Group].members[0].name = new_str;
            check[i] = true;
            
            for (int mask = 1; mask < (1<<(numMembers - i)); mask++) {
                int sum_Level = members[i].happinessLevel;
                bool flag = false;
                int sample_index = 1;

                for (int bit = 0; bit < numMembers - i; bit++) {
                    if ((mask >> bit) & 1) {
                        if (check[numMembers - bit - 1]) flag = true;
                    }
                }
                
                if (flag) continue;
                
                for (int bit = 0; bit < numMembers - i; bit++) {
                    if ((mask >> bit) & 1) {
                        sum_Level += members[numMembers - bit - 1].happinessLevel;
                        sample_members[sample_index] = members[numMembers - bit - 1];
                        sample_index++;
                    }
                }
                
                if (sum_Level >= standardLevel && sum_Level < delta_min) {
                    delta_min = sum_Level;
                    groups[num_Group].numMembers = sample_index;
                    groups[num_Group].happinessLevel = sum_Level;
                    visit = mask;
                    for (int index = 1; index < sample_index; index++) {
                        groups[num_Group].members[index] = sample_members[index];
                        char *new_str = (char*)malloc(sizeof(char) * 50);
                        strcpy(new_str, "Happy ");
                        strcat(new_str, sample_members[index].name);
                        groups[num_Group].members[index].name = new_str;
                    }
                }
            }

            for (int i = 0; i < numMembers; i++) {
                if ((visit >> i) & 1) check[numMembers - i - 1] = true;
            }
            
        }
        num_Group++;
    }
    return groups;
}