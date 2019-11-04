#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct diaries{
        int year;
        int month;
        int day;
        char title[200];
        struct diaries *next;
} Diaries;

Diaries* push_back(Diaries *list, int year, int month, int day, char title[]){
   Diaries *diary;
   diary= malloc(sizeof(*diary));
   diary->year= year;
   diary->month= month;
   diary->day= day;
   strcpy(diary->title, title);
   diary->next= NULL;
   
   if (list == NULL){
       return diary;
   }
   else {
       Diaries *cur= list;
       while (cur->next!= NULL){
           cur= cur->next;
       }
       cur->next= diary;
   }
   return list;
}

Diaries* push_front( Diaries *list, int year, int month, int day, char title[] ){
   Diaries *diary;
   diary= malloc(sizeof(*diary));
   diary->year= year;
   diary->month= month;
   diary->day= day;
   strcpy(diary->title, title);
   if (list==NULL){
       return diary;
   }
   else {
       diary->next= list;
       list= diary;
   }
   return diary;
}

void print(Diaries *list){
   Diaries *diary;
   if (list==NULL){
       printf("NULL list\n");
       return;
   }
	 
   for (diary= list; diary!=NULL; diary= diary->next){
      printf("%d / %d / %d  \n", diary->day, diary->month, diary->year);
      printf("%s\n", diary->title);
   }
}

void delete_all(Diaries *list){
    Diaries *cur= list, *next;
    while (cur!=NULL){
        next= cur->next;
        free(cur);
        cur= next;
    }
}

int main(void){
   Diaries *list = NULL;
	 
   /* Add a diary to the end of the list */
   list = push_back(list, 1912, 7, 30, "Taisho period start!");
   print(list);
   printf("\n");
   list = push_back(list, 1926, 12, 25, "Showa period start!");
   print(list);
   printf("\n");
   list = push_back(list, 1989, 1, 7, "Heisei period start!");
   print(list);
   printf("\n");
   list = push_front(list, 0, 0, 0, "Jesus is born.");
   
   /* Display all diaries */
   print(list);
   printf("\n");
	 
   /* Delete all diaries */
   delete_all(list);
}
