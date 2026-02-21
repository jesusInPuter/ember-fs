#include <stdio.h>

int main() {

  FILE *the_file = fopen("yes.txt", "r");

  long current_pointer;

  current_pointer = ftell(the_file);
  //
  // int charc = fgetc(the_file);
  //
  // printf("the current pointer is indexing the locaiotn of this char on "
  //        "the_file %c \n",
  //        charc);
  //
  // fseek(the_file, 0, SEEK_CUR);
  //
  // current_pointer = ftell(the_file);
  //
  // int charc1 = fgetc(the_file);
  //
  // printf("the current pointer is indexing the locaiotn of this char on "
  //        "the_file %c \n",
  //        charc1);
  //
  // fseek(the_file, 1, SEEK_CUR);
  //
  // current_pointer = ftell(the_file);
  //
  // int charc2 = fgetc(the_file);
  //
  // printf("the current pointer is indexing the locaiotn of this char on "
  //        "the_file %c \n",
  //        charc2);
  //
  // fseek(the_file, 54, SEEK_SET);
  // current_pointer = ftell(the_file);
  //
  // int charc3 = fgetc(the_file);

  // printf("the current pointer is indexing the locaiotn of this char on "
  //        "the_file %c \n",
  //        charc3);
  fseek(the_file, -5, SEEK_END);

  for (int i = 0; i < 5; i++) {
    int b = fgetc(the_file);
    printf("%c", b);
  }

  // printf("%c",
  //        char7);
  //
  // fseek(the_file, 0, SEEK_SET);
  // int boi;
  //
  // while ((boi = fgetc(the_file)) != EOF) {
  //   printf("%c", boi);
  // }

  // while (fgetc(the_file) != EOF) {
  //   int boi = fgetc(the_file);
  //   printf("%c", boi);
  // }
  return 0;
}
