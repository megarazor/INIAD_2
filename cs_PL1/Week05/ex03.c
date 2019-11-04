#include <stdio.h>

int main(void){
  FILE * fp =  fopen("text_copy.txt", "r") ; // text_copy.txt

  fseek(fp, 0, SEEK_END);
  int filesize = ftell(fp);
  fseek(fp, 0, SEEK_SET);
	
  printf("File size = %d\n", filesize);
	
  fclose(fp);
}
