#include "matrix.h"
#include <stdbool.h>

matrix_t matrix_create(int rows, int cols) { 
  
  matrix_t *m = malloc(sizeof(struct matrix));
  m->cols = cols;
  m->rows = rows;
  m->elts = malloc(rows*cols*sizeof(double));
  return *m;
}

double matrix_get(matrix_t m, int r, int c) { 
  /* TODO */
  assert(r < m.rows && c < m.cols);
  return m.elts[m.cols*r + c];
}

void matrix_set(matrix_t m, int r, int c, double d) { 
  assert(r < m.rows && c < m.cols);
  m.elts[m.cols*r + c] = d;
}


void matrix_free(matrix_t m) { 
  /* TODO */
  free(m.elts);

}

matrix_t matrix_multiply(matrix_t m1, matrix_t m2) { 
  matrix_t m = {m1.rows, m2.cols, NULL};
  double *melts = malloc(m1.rows * m2.cols * sizeof(double));
  for(int i =0; i<m1.rows; i++)
  {
    for(int j=0; j<m2.cols;j++)
    {
      double sum = 0;
      for(int k = 0; k<m1.cols; k++)
      {
        sum += m1.elts[i*m1.cols + k] * m2.elts[k*m2.cols + j];
      }
      melts[i*m2.cols + j] = sum;
    }
  }
  m.elts = melts;
  return m;
}



matrix_t matrix_transpose(matrix_t m) { 
  
  matrix_t t = matrix_create(m.cols, m.rows);
  for(int i = 0; i<m.cols; i++)
  {
    for(int j =0; j<m.rows; j++)
    {
      t.elts[i*m.rows + j] = m.elts[j*m.cols+i];
    }
  }
  return t;
}

matrix_t matrix_multiply_transposed(matrix_t m1, matrix_t m2) { 
  assert(m1.cols == m2.cols);
  /* TODO */
  matrix_t m = {m1.rows, m2.rows, NULL};
  double *melts = malloc(m1.rows * m2.rows * sizeof(double));
  for(int i =0; i<m1.rows; i++)
  {
    for(int j=0; j<m2.rows;j++)
    {
      double sum = 0;
      for(int k = 0; k<m1.cols; k++)
      {
        sum += m1.elts[i*m1.cols + k] * m2.elts[j*m2.cols + k];
      }
      melts[i*m2.rows + j] = sum;
    }
  }
  m.elts = melts;
  return m;
}

matrix_t matrix_multiply_fast(matrix_t m1, matrix_t m2) { 
  matrix_t m2T = matrix_transpose(m2);
  matrix_t result = matrix_multiply_transposed(m1,m2T);
  matrix_free(m2T);
  return result;
}

void matrix_print(matrix_t m) { 
  for (int i = 0; i < m.rows; i++) { 
    for (int j = 0; j < m.cols; j++) { 
      printf("%g\t", matrix_get(m, i, j));
    }
    printf("\n");
  }
  printf("\n");
}


