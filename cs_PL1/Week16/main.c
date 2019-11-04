#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*-------------------------------*/
/*------------ 10th -------------*/
/*-------------------------------*/

/*------------- 10-1-1 -------------*/
typedef struct data{
  char name[20];
  int score;
  struct data* next;
} student;

/*------------- 10-1-4 -------------*/
// The function append that adds one element to a circular linked list
student *append(student *List, char name[], int score){
    student *s;
    s = malloc(sizeof(student));
    strcpy(s->name, name);
    s->score = score;

    if( List == NULL ){
        List = s;
        List->next = List;
    }
    else {
        s->next = List;
        student *p = List;
        while(p->next != List) {
            p = p->next;
        }
        p->next = s;

    }
    return List;
}

/*------------- 10-1-5 -------------*/
// The function data that returns the score of the element of a circular linked list whose names match
int data(student *List, char name[]){
    student *s = List;
    do {
        if( strcmp(s->name, name) == 0 ){
            return s->score;
        }
        s = s->next;
    } while(s != List);    

    return -1;
}

/*------------- 10-1-6 -------------*/
// The function search that returns the element of a circular linked list whose names match
student *search(student *List, char name[]){
    if(List == NULL){
        return NULL;
    }

    student *s = List;
    do {
        if( strcmp(s->name, name) == 0 ){
            return s;
        }
        s = s->next;
    } while(s != List);    

    return NULL;
}


/*-------------------------------*/
/*------------ 16th -------------*/
/*-------------------------------*/

/*------------- 16-1-1 -------------*/
// Declare a pointer array to be a hash table
// ここを考える
static student *hashtable[111];
static int tablesize= 111;

/*------------- 16-1-2 -------------*/
// The function hash that returns a hash value for an argument string
int hash(char s[]){
  int i = 0;
  while (*s) {
    i+= *s++;
    //printf("%d", i);
  }
  return i%tablesize;
}

/*------------- 16-1-3 -------------*/
// The function init_hashtable that assigns NULL to all elements of the hash table
void init_hashtable(void){
  //printf("aa");
  for (int i = 0; i < tablesize; i++){
    hashtable[i]= NULL;
  }
}

/*------------- 16-1-4 -------------*/
// The function hsearch that returns the element of a hash table whose names match
student* hsearch(char name[]){
  int key= hash(name);
  return search(hashtable[key], name);
}

/*------------- 16-1-5 -------------*/
// The function hdata that returns the score of  the element of a hash table whose names match
int hdata(char name[]){
  student *s= hsearch(name);
  return s->score;
}

/*------------- 16-1-6 -------------*/
// The function create_key is a function for registering names and scores in the hash table
void create_key( char name[], int score){
  int key= hash(name);
  if (hashtable[key]!=NULL) {
    if (search(hashtable[key], name)!= NULL) {
      return;
    }
  }
  hashtable[key]= append(hashtable[key], name, score);
}

/*--------- 16-Extra-problem ---------*/

void delete_list(student *list){
  if (list==NULL)
    return;
  if (list->next==list){
    free(list);
    list= NULL;
    return;
  }
  student *p= list->next;
  while (p!=list){
    student *to_delete= p;
    p= p->next;
    free(to_delete);
  }
  free(p);
  list= NULL;

}

void hall_delete(void){
  for (int i=0; i<tablesize; i++){
    delete_list(hashtable[i]);
  }
}

/*-------------------------------*/
/*------------- main ------------*/
/*-------------------------------*/
int main(void){
  init_hashtable();	
	
  create_key("INIAD", 100);
  create_key("Jyoho", 20);
  create_key("Renke", 30);
  create_key("Engineer", 10);
  create_key("Toyo", 80);

  printf("%d , %d\n", hdata("INIAD"), hash("INIAD"));
  printf("%d , %d\n", hdata("Jyoho"), hash("Jyoho")); 
  printf("%d , %d\n", hdata("Renke"), hash("Renke"));
  printf("%d , %d\n", hdata("Engineer"), hash("Engineer"));
  printf("%d , %d\n", hdata("Toyo"), hash("Toyo"));
  printf("%d , %d\n", hdata("INIAD"), hash("INIAD"));

  hall_delete();
}

