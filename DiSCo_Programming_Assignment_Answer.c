#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main () {
  FILE *file_ptr;
  file_ptr = fopen("a.txt", "r");

  int input_initial[2];
  fscanf(file_ptr, "%i %i\n", &input_initial[0], &input_initial[1]);

  int m_dependencies_final_1st_indices[input_initial[1]];
  int m_dependencies_final_2nd_indices[input_initial[1]];

  for (int index = 0; index < input_initial[1]; index++) {
    fscanf(file_ptr, "%i %i\n", &m_dependencies_final_1st_indices[index], &m_dependencies_final_2nd_indices[index]);
  }

  fclose(file_ptr);

  int arr_after_kahn_algo_to_print[input_initial[0]][input_initial[0]]; // square matrix of N rows and N columns

  int impossible_step = -1;

  for (int outer_index = 0; outer_index < input_initial[0]; outer_index++) {
    for (int inner_index = 0; inner_index < input_initial[0]; inner_index++) {
      arr_after_kahn_algo_to_print[outer_index][inner_index] = impossible_step;
    }
  }

  int in_degrees[input_initial[0]];
  for(int initializer = 0; initializer < input_initial[0]; initializer++){
    in_degrees[initializer] = 0;
  }

  for(int count = 0; count < input_initial[1]; count++) {
    in_degrees[m_dependencies_final_2nd_indices[count] - 1]++;
  }

  int my_size = input_initial[1];

  int adj_matrix[my_size][my_size];
  for(int i = 0; i < my_size; i++) {
    for(int j = 0; j < my_size; j++) {
      adj_matrix[i][j] = 0;
    }
  }

  bool visited[my_size];
  int round_size[my_size];

  for(int i = 0; i < my_size; i++) {
    adj_matrix[m_dependencies_final_1st_indices[i] - 1][m_dependencies_final_2nd_indices[i] - 1] = 1;
    visited[i] = false;
    round_size[i] = 0;
  }

  int index_count = 0;
  while(1) {
    int current_round[my_size];
    int current_round_length = 0;
    for(int index = 0; index < my_size; index++) {
      if((in_degrees[index] == 0) && (visited[index] == false)) {
        current_round[current_round_length++] = index + 1;
        visited[index] = true;
      }
    }

    if(current_round_length == 0) {
      break;
    }

    for(int outer_count = 0; outer_count < (current_round_length - 1); outer_count++) {
      for(int inner_count = 0; inner_count < (current_round_length - outer_count - 1); outer_count++) {
        if(current_round[inner_count] > current_round[inner_count + 1]) {
          int holder = current_round[inner_count + 1];
          current_round[inner_count + 1] = current_round[inner_count];
          current_round[inner_count] = holder;
        }
      }
    }

    round_size[index_count] = current_round_length;

    for(int how_many_loops_omg = 0; how_many_loops_omg < current_round_length; how_many_loops_omg++) {
      arr_after_kahn_algo_to_print[index_count][how_many_loops_omg] = current_round[how_many_loops_omg];
    }

    index_count++;
    for(int count_check = 0; count_check < current_round_length; count_check++) {
      int placeholder = current_round[count_check] - 1;
      for(int check_inner = 0; check_inner < my_size; check_inner++) {
        if(adj_matrix[placeholder][check_inner] == 1) {
          in_degrees[check_inner]--;
        }
      }
    }
  }

  FILE *file_ptr_2;
  file_ptr_2 = fopen("b.txt", "w");

  fprintf(file_ptr_2, "%d\n", index_count);

  for (int outer_index = 0; outer_index < index_count; outer_index++) {
    for (int inner_index = 0; inner_index < round_size[outer_index]; inner_index++) {
      if (arr_after_kahn_algo_to_print[outer_index][inner_index] != impossible_step) {
        fprintf(file_ptr_2, "%i ", arr_after_kahn_algo_to_print[outer_index][inner_index]);
      }
    }
    fprintf(file_ptr_2, " \n");
  }

  fclose(file_ptr_2);
}
