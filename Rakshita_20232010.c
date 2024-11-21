#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// void malloc_a_double_pointer(int **arr, int num_of_rows, int num_of_columns) {
//   arr = malloc(num_of_rows * sizeof(int*));
//   for(int assigning_index = 0; assigning_index < num_of_rows; assigning_index++) {
//     arr[assigning_index] = malloc(num_of_columns * sizeof(int));
//   }
// }

int flagger(int *removed_or_not, int n_treats) {
  int counter = 0;
  for(int index_to_pick = 0; index_to_pick < n_treats; index_to_pick++) {
    if (removed_or_not[index_to_pick] == 1) {
      counter = 1;
    }
  }
  return counter;
}

void assign_all_0_2d(int num_row, int num_col, int **matrix_2d) {
  for(int outer_index = 0; outer_index < num_row; outer_index++) {
    for(int inner_index = 0; inner_index < num_col; inner_index++) {
      matrix_2d[outer_index][inner_index] = 0;
    }
  }
}

void assign_all_1d(int length_of_arr, int *matrix_1d, int int_to_assign) {
  for(int ind = 0; ind < length_of_arr; ind++) {
    matrix_1d[ind] = int_to_assign;
  }
}

int main() {
  FILE *file_ptr1;
  file_ptr1 = fopen("./a.txt", "r");

  int n_treats;
  int m_dep;

  fscanf(file_ptr1, "%i %i\n", &n_treats, &m_dep);

  // int m_dependencies_arr[m_dep][2];
  int **m_dependencies_arr = NULL;

  // malloc_a_double_pointer(m_dependencies_arr, m_dep, 2);
  m_dependencies_arr = malloc(m_dep * sizeof(int*));
  for(int assigning_index = 0; assigning_index < m_dep; assigning_index++) {
    m_dependencies_arr[assigning_index] = malloc(2 * sizeof(int));
  }

  assign_all_0_2d(m_dep, 2, m_dependencies_arr);

  for (int index = 0; index < m_dep; index++) {
    fscanf(file_ptr1, "%i %i\n", &m_dependencies_arr[index][0], &m_dependencies_arr[index][1]);
  }

  fclose(file_ptr1);

  // int adj_matrix[n_treats][n_treats];
  // int arr_after_kahn_algo_to_print[n_treats][n_treats];
  int **adj_matrix = NULL;
  int **arr_after_kahn_algo_to_print = NULL;

  // malloc_a_double_pointer(adj_matrix, n_treats, n_treats);
  adj_matrix = malloc(n_treats * sizeof(int*));
  for(int assigning_index = 0; assigning_index < n_treats; assigning_index++) {
    adj_matrix[assigning_index] = malloc(n_treats * sizeof(int));
  }
  // malloc_a_double_pointer(arr_after_kahn_algo_to_print, n_treats, n_treats);
  arr_after_kahn_algo_to_print = malloc(n_treats * sizeof(int*));
  for(int assigning_index = 0; assigning_index < n_treats; assigning_index++) {
    arr_after_kahn_algo_to_print[assigning_index] = malloc(n_treats * sizeof(int));
  }

  assign_all_0_2d(n_treats, n_treats, adj_matrix);
  assign_all_0_2d(n_treats, n_treats, arr_after_kahn_algo_to_print);

  for(int count = 0; count < m_dep; count++) {
    adj_matrix[m_dependencies_arr[count][0] - 1][m_dependencies_arr[count][1] - 1] = 1;
  }

  // int removed_or_not[n_treats];
  int *removed_or_not = NULL;
  removed_or_not = malloc(n_treats * sizeof(int));
  assign_all_1d(n_treats, removed_or_not, 1);

  // int to_remove_arr[n_treats];
  int *to_remove_arr = NULL;
  to_remove_arr = malloc(n_treats * sizeof(int));
  int round_count = 0;

  while (flagger(removed_or_not, n_treats)) {
    assign_all_1d(n_treats, to_remove_arr, 0);

    for(int first_index = 0; first_index < n_treats; first_index++) {
      if (removed_or_not[first_index] == 1) {
        int point_r = 0;

        for(int second_index = 0; second_index < n_treats; second_index++) {
          if(adj_matrix[second_index][first_index] == 1) {
            point_r = 1;
          }
        }

        if(point_r == 0) {
          to_remove_arr[first_index] = 1;
        }
      }
    }

    int final_count = 0;
    for(int final_ind = 0; final_ind < n_treats; final_ind++) {
      if(to_remove_arr[final_ind] == 1) {
        arr_after_kahn_algo_to_print[round_count][final_count] = final_ind + 1;
        removed_or_not[final_ind] = 0;
        final_count++;

        for(int inner_final_index = 0; inner_final_index < n_treats; inner_final_index++) {
          adj_matrix[final_ind][inner_final_index] = 0;
        }
      }
    }
    round_count += 1;
  }

  FILE *file_ptr2 = fopen("./b.txt", "w");
  if (file_ptr2 == NULL) {
    printf("File is empty \n");
  }

  fprintf(file_ptr2, "%d\n", round_count);

  for(int out_ind = 0; out_ind < round_count; out_ind++) {
    for(int in_ind = 0; in_ind < n_treats; in_ind++) {
      if(arr_after_kahn_algo_to_print[out_ind][in_ind] != 0) {
        fprintf(file_ptr2, "%d ", arr_after_kahn_algo_to_print[out_ind][in_ind]);
      }
    }
    fprintf(file_ptr2, "\n");
  }

  fclose(file_ptr2);
}
