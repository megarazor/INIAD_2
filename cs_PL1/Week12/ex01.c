#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum gender {Man, Woman};
enum profession {Student, Company, PartTime, Others};
enum twoselect {No, Yes};

struct questionnaire {
    enum gender Gender;
    int Age;
    enum profession Profession;
    enum twoselect LiveInAkabane;
    enum twoselect OverTwenty;
};

struct questionnaire List[100];
int maxid = 0;

void addquestionnaire(){
    int tmp;
    int flag= 1;
    do {
        flag= 1;
        printf("What is your gender?(Man: 0, Woman: 1)\n");
        scanf("%d", &tmp);
        if (tmp!=Man && tmp!=Woman)
            flag= 0;
        else
            List[maxid].Gender= tmp;

        printf("What is your age?\n");
        scanf("%d", &tmp);
        if (tmp<0)
            flag= 0;
        else
            List[maxid].Age = tmp;

        printf("What is your profession?(Student: 0, Company worker: 1, Part-time worker: 2, Others: 3)\n");
        scanf("%d", &tmp);
        if (tmp!=Student && tmp!=Company && tmp!=PartTime && tmp!=Others)
            flag= 0;
        else
            List[maxid].Profession= tmp;

        printf("Do you live in Akabane?(No: 0, Yes: 1)\n");
        scanf("%d", &tmp);
        if (tmp!=No && tmp!=Yes)
            flag= 0;
        else
            List[maxid].LiveInAkabane= tmp;

        printf("Are you over 20 years old?(No: 0, Yes: 1)\n");
        scanf("%d", &tmp);
        if (tmp!=No && tmp!=Yes)
            flag= 0;
        else if ((List[maxid].Age>=20 && tmp==No) || (List[maxid].Age<20 && tmp==Yes))
            flag= 0;
        else
            List[maxid].OverTwenty= tmp; 
        
        if (flag==1)
            maxid++;
        }
    while (flag==0);
}

void print(){
    for (int i = 0; i < maxid; i++){
      printf("Gender: ");
      switch(List[i].Gender){
        case Man:
          printf("Man\n");
          break;
        case Woman:
          printf("Woman\n");
          break;
      }

      printf("Age: %d\n", List[i].Age);

      printf("Profession: ");
      switch(List[i].Profession){
        case Student:
          printf("Student\n");
          break;
        case Company:
          printf("Company worker\n");
          break;
        case PartTime:
          printf("Part-time worker\n");
          break;
        case Others:
          printf("Others\n");
          break;          
      }

      printf("Live in Akabane: ");
      switch(List[i].LiveInAkabane){
        case No:
          printf("No\n");
          break;
        case Yes:
          printf("Yes\n");
          break;
      }

      printf("Over 20 years old: ");
      switch(List[i].OverTwenty){
        case No:
          printf("No\n\n");
          break;
        case Yes:
          printf("Yes\n\n");
          break;
      }
    }
}

void profrate() {
    int flag= 1, tmp;
    enum profession prof;
    do {
        flag= 1;
        printf("What is the profession to calculate the ratio? (Student: 0, Company worker: 1, Part-time worker: 2, Others: 3)\n");
        scanf("%d", &tmp);
        prof= tmp;
        if (prof!=Student && prof!=Company && prof!=PartTime && prof!=Others)
            flag= 0;
    }
    while (flag==0);
            
    int count= 0;
    for (int i= 0; i<maxid; i++) {
        if (List[i].Profession==prof)
            count++;
    }
    printf("Ratio of ");
    switch(prof) {
        case Student:
            printf("students ");
            break;
        case Company:
            printf("company workers ");
            break;
        case PartTime:
            printf("part-time workers ");
            break;
        case Others:
            printf("other professions ");
            break;
    }
    
    printf("in the List: %f percent.\n", ((count*1.0)/(maxid*1.0))*100.0);
    /* printf("Prof: %d\n", prof);
    printf("Count: %d\n", count);
    printf("Total: %d\n", maxid);  */
}

int main(void){
  char command[100];
  
  while(1){
    printf("\nPlease input a command: Add, Print, ProfRate, Exit\n>>> ");
    scanf("%s", command);
		
    if (strcmp("Add", command)==0) addquestionnaire();
    else if (strcmp("Print", command)==0) print();
    else if (strcmp("ProfRate", command)==0) profrate();
    else if (strcmp("Exit", command)==0) break;
  }
}
