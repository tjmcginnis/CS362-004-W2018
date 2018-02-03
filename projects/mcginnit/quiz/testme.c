#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    /**
     * Since we have the constraint of testme reaching
     * the error case in less than 5 minutes, the
     * input pool should be limited.
     *
     * I chose an input pool containing only the
     * characters that appear in the conditional 
     * statements in testme, since that would
     * guarantees full statement coverage,
     * but also increases the chances of
     * testme reaching the error case
     * in less than 5 minutes
     */
    char *input_pool = "[{({ ax})]rest";
    return input_pool[rand() % strlen(input_pool)];
}

char *inputString()
{
    /**
     * generate a random 5 character string using
     * inputChar.
     */
    int i;
    static char s[6] = "abcde\0";

    for (i = 0; i < 5; i++) {
      s[i] = inputChar();
    }

    return s;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
