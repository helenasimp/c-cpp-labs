#include <stdlib.h>
#include <stdio.h>
#include "re.h"

arena_t create_arena(int size) { 
  arena_t arena = malloc(sizeof(struct arena));
  arena->size = size;
  arena->current = 0;
  arena->ptrs = malloc(size*sizeof(Regexp));
  return arena;
}

void arena_free(arena_t a) { 
  free(a->ptrs);
  free(a);
}

Regexp *re_alloc(arena_t a) { 
  if(a->current < a->size)
  {
    Regexp *r = a->ptrs + a->current;
    a->current = a->current+1;
    return r;
  }
  return NULL;
}

Regexp *re_chr(arena_t a, char c) { 
  Regexp *r = re_alloc(a);
  if(r==NULL) return r;
  r->type = CHR;
  r->data.chr = c;
  return r;
}

Regexp *re_alt(arena_t a, Regexp *r1, Regexp *r2) { 
  Regexp *r = re_alloc(a);
  if(r==NULL) return r;
  r->type = ALT;
  r->data.pair.fst = r1;
  r->data.pair.snd = r2;
  return r;
}

Regexp *re_seq(arena_t a, Regexp *r1, Regexp *r2) { 
  Regexp *r = re_alloc(a);
  if(r==NULL) return r;
  r->type = SEQ;
  r->data.pair.fst = r1;
  r->data.pair.snd = r2;
  return r;
}

int re_match(Regexp *r, char *s, int i) { 
  if(r != NULL)
  {
    if(r->type == CHR)
    {
        if(r->data.chr == s[i]) return i+1;
    }
    else if(r->type == ALT)
    {
        int case1 = re_match(r->data.pair.fst,s,i);
        if (case1 > -1) return case1;
        else return re_match(r->data.pair.snd, s, i);
    }
    else
    {
        int case1 = re_match(r->data.pair.fst,s,i);
        if (case1>-1) return re_match(r->data.pair.snd,s,case1);
    }
  }
  return -1;
}



void re_print(Regexp *r) { 
  if (r != NULL) { 
    switch (r->type) {
    case CHR: 
      printf("%c", r->data.chr);
      break;
    case SEQ:
      if (r->data.pair.fst->type == ALT) { 
	printf("(");
	re_print(r->data.pair.fst);
	printf(")");
      } else {
	re_print(r->data.pair.fst);
      }
      if (r->data.pair.snd->type == ALT) { 
	printf("(");
	re_print(r->data.pair.snd);
	printf(")");
      } else {
	re_print(r->data.pair.snd);
      }
      break;
    case ALT:
      re_print(r->data.pair.fst);
      printf("+");
      re_print(r->data.pair.snd);
      break;
    }
  } else { 
    printf("NULL");
  }
}    


      
  
