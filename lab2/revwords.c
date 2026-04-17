#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "revwords.h"

void reverse_substring(char str[], int start, int end) { 
  int i,j;
  char c;
  for( i=start,j=end; i<j; i++,j--)
  {
     c = str[i], str[i] = str[j], str[j]=c;
  }
}


int find_next_start(char str[], int len, int i) { 
  int found = 0;
  while((found==0) && (i<len))
  {
    if (65<=str[i] && str[i]<=122) found=1;
    else i++;
  }
  if (i<len) return i;
  else return -1;
}

int find_next_end(char str[], int len, int i) {
  int found = 0;
  while((found==0) && (i<len))
  {
    if (65<=str[i] && str[i]<=122) i++;
    else found=1;
  }
  if (i<len) return i;
  else return len;
  
}

void reverse_words(char s[], int len) { 
  int i=0;
  int start, end;
  while(i != -1)
  {
    start = find_next_start(s,len,i);
    end = find_next_end(s,len,start);
    printf("%d and %d ",start,end);
    if(start>=0)
    {
      reverse_substring(s,start,end-1);
    }
    i = end;

  }
}
