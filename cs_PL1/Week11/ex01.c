#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct diary {
    int year;
    int month;
    int day;
    char title[200];
    struct diary *prev;
    struct diary *next;
} Diary;

typedef struct diaries {
    struct diary *head;
    struct diary *tail;
} Diaries;

Diaries init_list(void){
  Diaries s;
  s.head= NULL;
  s.tail= NULL;
  return s;
}

void print(Diaries s){
  if (s.head!=NULL && s.tail !=NULL){
    Diary *tmp;
    for (tmp= s.head; tmp!=NULL; tmp= tmp->next){
      printf("%d / %d / %d : %s \n", tmp->day, tmp->month, tmp->year, tmp->title);
    }
  }
  else {
      printf("Emtpy list!\n");
  }
  printf("\n");
}

Diaries delete_all(Diaries s){
  if (s.head!=NULL && s.tail !=NULL){
    Diary *tmp1, *tmp2;
    tmp1 = s.head; 
    for (; tmp1!=NULL; tmp1= tmp2) {
        tmp2= tmp1->next;
        free(tmp1);
    }
  }
  return init_list();
}

Diaries push_back(Diaries s, int year, int month, int day, char title[]){
  Diary *new_diary= malloc(sizeof(*new_diary));
  new_diary->year= year;
  new_diary->month= month;
  new_diary->day= day;
  new_diary->next= NULL;
  strcpy(new_diary->title, title);
  
  if (s.head == NULL && s.tail == NULL){
    new_diary->prev= NULL;
    s.head= new_diary;
    s.tail= new_diary;
  }
  else{
    new_diary->prev= s.tail;
    s.tail->next= new_diary;
    s.tail= new_diary;
  }
  return s;
}

Diaries push_front(Diaries s, int year, int month, int day, char title[]){
  Diary *new_diary= malloc(sizeof(*new_diary));
  new_diary->year= year;
  new_diary->month= month;
  new_diary->day= day;
  new_diary->prev= NULL;
  strcpy(new_diary->title, title);
  
  if (s.head == NULL && s.tail == NULL){
    new_diary->next= NULL;
    s.head= new_diary;
    s.tail= new_diary;
  }
  else{
    new_diary->next= s.head;
    s.head->prev= new_diary;
    s.head= new_diary;
  }
  return s;
}

Diaries pop_back(Diaries s){
  if (s.head == NULL && s.tail == NULL){
    return init_list();
  }
  else if( s.head == s.tail  ){
    free(s.tail);
    return init_list();
  }
  Diary *tmp;
  tmp= s.tail;
  s.tail= s.tail->prev;
  s.tail->next= NULL;
  free(tmp);
  	
  return s;
}

Diaries pop_front(Diaries s){
  if (s.head == NULL && s.tail == NULL){
    return init_list();
  }
  else if( s.head == s.tail  ){
    free(s.tail);
    return init_list();
  }
  Diary *tmp;
  tmp= s.head;
  s.head= s.head->next;
  s.head->prev= NULL;
  free(tmp);
	
  return s;
}

int compareDate(int year1, int month1, int day1, int year2, int month2, int day2) {
    if (year1<year2){
        return -1;
    }
    else if (year1>year2){
        return 1;
    }
    else {
        if (month1<month2){
            return -1;
        }
        else if (month1>month2) {
            return 1;
        }
        else {
            if (day1<day2) {
                return -1;
            }
            else if (day1>day2) {
                return 1;
            }
            else{
                return 0;
            }
        }
    }
    return 0;
}

Diaries insert(Diaries s, int year, int month, int day, char title[]){
  Diary *new_diary= malloc(sizeof(*new_diary));
  new_diary->year= year;
  new_diary->month= month;
  new_diary->day= day;
  new_diary->prev= NULL;
  new_diary->next= NULL;
  strcpy(new_diary->title, title);

  if (s.head == NULL && s.tail == NULL){
    s.head= new_diary;
    s.tail= new_diary;
  }
  else {
    Diary *cur= s.head;
    while (cur!=NULL) {
        if (compareDate(cur->year, cur->month, cur->day, new_diary->year, new_diary->month, new_diary->day)== 1)
            break;
        else
            cur= cur->next;
    }
    if (cur==NULL) {
        new_diary->prev= s.tail;
        s.tail->next= new_diary;
        s.tail= new_diary;
    }
    else if (cur==s.head) {
        new_diary->next= s.head;
        s.head->prev= new_diary;
        s.head= new_diary;
    }
    else {
        new_diary->next= cur;
        new_diary->prev= cur->prev;
        cur->prev->next= new_diary;
        cur->prev= new_diary;
    }
  }
  return s;
}

int main(void){
  Diaries s = init_list();

  print(s);

  s = push_back(s,1926, 12, 25, "Showa period start!");
  s = push_front(s, 1912, 7, 30, "Taisho period start!");
  s = push_back(s, 1989, 1, 7, "Heisei period start!");
  s = push_back(s, 2019, 5, 1, "Reiwa period start!");
  print(s);

  s = insert(s, 0, 0, 0, "Jesus Christ!");
  s = insert(s, 2020, 5, 5, "Whatever!");
  s = insert(s, 1945, 2, 10, "World War ended!");
  print(s);

  s = pop_front(s);
  print(s);

  s = pop_back(s);
  print(s);

  s = pop_front(s);
  print(s);

  s = delete_all(s);
  print(s);
}
