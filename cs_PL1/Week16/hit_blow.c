#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int Random(int minvalue, int maxvalue){
  static int RAND_SEED_FLAG;
  if (RAND_SEED_FLAG == 0){
    srand((unsigned int)time(NULL));
    RAND_SEED_FLAG = 1;
  }
  return minvalue + (int)(rand()*(maxvalue - minvalue + 1.0)/(1.0 + RAND_MAX));
}

int* create_random(){
  int Num[4];
  Num[0] = Random(0,9);
  int flag;
  for (int i = 1; i < 4; i++){
    while(1){
      int flag = 0;
      int tmp = Random(0,9);
      for (int j = 0; j < i; j++){
        if (tmp == Num[j]){
          flag = 1;
        }
      }
      if (flag == 0){
        Num[i] = tmp;
        break;
      }
    }
  }
  return Num;
}

int main(void){
  int input;
  int flag;
  int Num[4];
  int In[4];
  int hit = 0;
  int blow = 0;
  while (1){
    printf("Please input 4 numbers: ");
    scanf("%d", &input);
    if (input/10000 != 0) continue;
    // Convert input to array of digits
    int k = 1000;
    for (int i = 0; i < 4; i++){
      Num[i] = input/k;
      input %= k;
      k /= 10;
    }
    
    // Check if input is 4 different digits
    flag = 0;
    for (int i = 0; i < 3; i++){
      for (int j = i+1; j < 4; j++){
        if (Num[i] == Num[j]){
          flag = 1;
        }
      }
    }
    if (flag == 1) continue;

    // Solve
    //asf

    // Check hits and blows
    for (int i= 0; i<=3; i++){
        if (Num[i]==In[i]) {
            hit++;
        }
        else {
            for (int j= 0; j<=3; j++){
                if (i!=j){
                    if (Num[i]==In[j]) {
                        blow++;
                    }
                }
            }
        }
    }
    printf("Hit: %d", hit);
    printf("  Blow: %d\n", blow);

    if (hit == 4){
        printf("Ay congratulations!\n");
        break;
    }

    hit = 0;
    blow = 0;
  }
}
