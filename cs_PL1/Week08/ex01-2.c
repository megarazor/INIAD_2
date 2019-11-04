#include <stdio.h>

typedef struct student{
  char* name;
  int math;
  int physics;
  int economics;
} student;

int math_max(student a, student b){
    return a.math > b.math;
}

int math_min(student a, student b){
  return a.math < b.math;
}

int physics_max(student a, student b){
  return a.physics > b.physics;
}

int physics_min(student a, student b){
  return a.physics < b.physics;
}

int economics_max(student a, student b){
  return a.economics > b.economics;
}

int economics_min(student a, student b){
  return a.economics < b.economics;
}

student search(const student A[], int size, int (*p)(student, student)){
  student value = A[0];
  for (int i = 1; i < size; i++){
    if ((*p)(A[i], value)) {
      value = A[i];
    }
  }
  return value;
}

void print(student tmp){
  printf("%s, Math: %d, Phys: %d, Eco: %d\n", tmp.name, tmp.math, tmp.physics, tmp.economics);
}

int main(void){
  student A[5] = {
   {"INIAD", 95, 80, 95},
   {"Jyoho", 75, 82, 65},
   {"Toyo", 65, 79, 93},
   {"Renke", 68, 91, 43},
   {"Info", 70, 98, 45},
  };
  int size = sizeof(A)/sizeof(A[0]);

  print(search(A, size, math_max));
  print(search(A, size, physics_min));
  print(search(A, size, economics_min));
}
