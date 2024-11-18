#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main () {
  FILE *file_ptr;
  file_ptr = fopen("a.txt", "r");

  int inp_ini[2];
  fscanf(file_ptr, "%i %i\n", &inp_ini[0], &inp_ini[1]);

  int m_dependencies_final_1st_indices[inp_ini[1]];
  int m_dependencies_final_2nd_indices[inp_ini[1]];

  for (int index = 0; index < inp_ini[1]; index++) {
    fscanf(file_ptr, "%i %i\n", &m_dependencies_final_1st_indices[index], &m_dependencies_final_2nd_indices[index]);
  }

  int arr_after_kahn_algo_to_print[inp_ini[0]][inp_ini[0]]; // square matrix of N rows and N columns

  int impossible_step = -1;

  for (int outer_index = 0; outer_index < inp_ini[0]; outer_index++) {
    for (int inner_index = 0; inner_index < inp_ini[0]; inner_index++) {
      arr_after_kahn_algo_to_print[outer_index][inner_index] = impossible_step;
    }
  }

  int in_degrees[inp_ini[0]];
  for(int initializer = 0; initializer < inp_ini[0]; initializer++){
    in_degrees[initializer] = 0;
  }

  for(int count = 0; count < inp_ini[1]; count++) {
    in_degrees[m_dependencies_final_2nd_indices[count] - 1]++;
  }

  // printf("** \n");

  // for (int index_for_in_degrees = 0; index_for_in_degrees < inp_ini[0]; index_for_in_degrees++) {
  //   printf("%i ", in_degrees[index_for_in_degrees]);
  // }

  // printf("\n** \n \n");

  int mySize = inp_ini[1];

  int adj_matrix[mySize][mySize];
  for(int i = 0; i < mySize; i++) {
    for(int j = 0; j < mySize; j++) {
      adj_matrix[i][j] = 0;
    }
  }

  bool visited[mySize];
  int roundSize[mySize];

  for(int i = 0; i < mySize; i++) {
    adj_matrix[m_dependencies_final_1st_indices[i] - 1][m_dependencies_final_2nd_indices[i] - 1] = 1;
    visited[i] = false;
    roundSize[i] = 0;
  }

  int indexCount = 0;
  while(1) {
    int currentRound[mySize];
    int currentRoundLength = 0;
    for(int index = 0; index < mySize; index++) {
      if((in_degrees[index] == 0) && (visited[index] == false)) {
        currentRound[currentRoundLength++] = index + 1;
        visited[index] = true;
      }
    }

    if(currentRoundLength == 0) {
      break;
    }

    for(int outer_count = 0; outer_count < (currentRoundLength - 1); outer_count++) {
      for(int inner_count = 0; inner_count < (currentRoundLength - outer_count - 1); outer_count++) {
        if(currentRound[inner_count] > currentRound[inner_count + 1]) {
          int holder = currentRound[inner_count + 1];
          currentRound[inner_count + 1] = currentRound[inner_count];
          currentRound[inner_count] = holder;
        }
      }
    }

    roundSize[indexCount] = currentRoundLength;

    for(int index = 0; index < currentRoundLength; index++) {
      arr_after_kahn_algo_to_print[indexCount][index] = currentRound[index];
    }

    indexCount++;
    for(int count_check = 0; count_check < currentRoundLength; count_check++) {
      int placeholder = currentRound[count_check] - 1;
      for(int check_inner = 0; check_inner < mySize; check_inner++) {
        if(adj_matrix[placeholder][check_inner] == 1) {
          in_degrees[check_inner]--;
        }
      }
    }
  }

  printf("%d\n", indexCount);
  for (int outer_index = 0; outer_index < indexCount; outer_index++) {
    for (int inner_index = 0; inner_index < roundSize[outer_index]; inner_index++) {
      if (arr_after_kahn_algo_to_print[outer_index][inner_index] != impossible_step) {
        printf("%i ", arr_after_kahn_algo_to_print[outer_index][inner_index]);
      }
    }
    printf("\n");
  }

  fclose(file_ptr);
}
