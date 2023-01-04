#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h> 
#include <time.h>


float giveRandom() { 
    srand((int) clock());
    int i; 
    int lower = 1;
    int upper = 100;
    float num = (rand() % (upper - lower + 1)) + lower; 
    return num/100;
} 

void choose_random_word(char selected[128]) {
    FILE *f;
    size_t lineno = 1;
    size_t selectlen;
    char current[128];
    selected[0] = '\0'; 

    f = fopen("dictionary.txt", "r"); 
    while (fgets(current, sizeof(current), f)) {
        if (giveRandom() > 0.9951) {
            strcpy(selected, current);
            if(((int) clock())%51==0)
                break;
        }
    }
    fclose(f);
    selectlen = strlen(selected);
    if (selectlen > 0 && selected[selectlen-1] == '\n') {
        selected[selectlen-1] = '\0';
    }
    return;
}

int main() {
  int lives = 6;

  char answer[128] ;
  choose_random_word(answer);
  int N = strlen(answer);
  int mask[N];
  for (int i=0; i < N; ++i) {
      if(tolower(answer[i])=='a' || tolower(answer[i])=='e' || tolower(answer[i])=='i' || tolower(answer[i])=='o' || tolower(answer[i])=='u')
        mask[i] = 1;
      else
        mask[i] = 0;
  }

  int gameover = 0;
  int won = 1;
  while (! gameover) {
    printf("The word is : ");
    for(int j=0; j < N; ++j) {
      if (mask[j]) {
        printf("%c", answer[j]);
      }
      else {
        printf("*");
      }
    }
    printf("\n");

    char guess;
    printf("Your guess is : ");
    fflush(stdout);
    scanf(" %c", &guess);
    int won_round = 0;
    for(int k=0; k < N; ++k) {
      if (answer[k] == toupper(guess) || answer[k] == tolower(guess)) {
	    mask[k] = 1;
        won_round = 1;
      }
    }

    if(won_round == 0){
        lives--;
        printf("Your guess is wrong. You have %d lives remaining. \n", lives);
    } else {
        printf("Your guess is right.\n");
    }

    gameover = 1;
    for(int m = 0; m < N; ++m) {
      if (!mask[m]) {
        gameover = 0;
        break;
      }
    }

    if(lives==0){
        won = 0;
        gameover = 1;
    }
  }

  if(won==1)
    printf("Victory! The word is \"%s\".\n", answer);
  else
    printf("Sorry! You loose, The word is \"%s\".\n", answer);

  return 0;
}