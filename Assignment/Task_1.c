#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    int happinessLevel;
} Member;
typedef struct {
    Member* members;
    int numMembers;
    int happinessLevel;
} Group;
Group createGroup(Member* members, int numMembers, int happinessLevel) 
{
    Group newGroup;
    newGroup.members = (Member*)malloc(numMembers * sizeof(Member));
    memcpy(newGroup.members, members, numMembers * sizeof(Member));
    newGroup.numMembers = numMembers;
    newGroup.happinessLevel = happinessLevel;
    return newGroup;
}
Group* splitGroups(Member* const members, int numMembers, int standardLevel) 
    {
    if (numMembers == 0) 
        return NULL;
    Group* groups = (Group*)malloc(numMembers * sizeof(Group)); 
    if (!groups) 
        return NULL; 
    int groupCount = 0;
    int currentHappiness = 0;
    int startIndex = 0;

    for (int i = 0; i < numMembers; i++) 
    {
        currentHappiness += members[i].happinessLevel;
        if (currentHappiness >= standardLevel) 
        {
            groups[groupCount] = createGroup(&members[startIndex], i - startIndex + 1, currentHappiness);
            for (int j = startIndex; j <= i; j++) 
            {
                char* happyName = (char*)malloc(strlen("Happy ") + strlen(members[j].name) + 1);
                strcpy(happyName, "Happy ");
                strcat(happyName, members[j].name);
                members[j].name = happyName; 
                groups[groupCount].members[j - startIndex].name = happyName; 
            }
            groupCount++;
            startIndex = i + 1; 
            currentHappiness = 0; 
        }
    }
    return groups; 
}
int main(){
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

    int standardHappinessLevel = 12;

    Group* groups = splitGroups(members, 8, standardHappinessLevel);

    for (int i = 0; i < 3; i++) {
        printf("Group %d (Happiness level: %d): ", i + 1, groups[i].happinessLevel);
        for (int j = 0; j < groups[i].numMembers; j++) {
            printf("%s ", groups[i].members[j].name);
        }
        printf("\n");
    }
free(groups);
return 0;
}