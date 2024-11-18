#include <stdio.h>
#include <string.h>

int main () {
  FILE *file_ptr;
  file_ptr = fopen("Notes.txt", "r");

  int str_split[2];
  fscanf(file_ptr, "%i %i\n", &str_split[0], &str_split[1]);

  int m_dependencies_final[str_split[1]][2]; // number of lines after the first line, of format "%i %i"

  for (int index = 0; index < str_split[1]; index++) {
    fscanf(file_ptr, "%i %i\n", &m_dependencies_final[index][0], &m_dependencies_final[index][1]);
  }

  int m_dependencies_final_1st_indices[str_split[1]];
  int m_dependencies_final_2nd_indices[str_split[1]];

  for (int index = 0; index < str_split[1]; index++) {
    m_dependencies_final_1st_indices[index] = m_dependencies_final[index][0];
    // printf("m_dependencies_final_1st_indices: %i \n", m_dependencies_final_1st_indices[index]);
    m_dependencies_final_2nd_indices[index] = m_dependencies_final[index][1];
    // printf("m_dependencies_final_2nd_indices: %i \n", m_dependencies_final_2nd_indices[index]);
  }

  // printf("~~~ \n");

  int arr_after_kahn_algo_to_print[str_split[0]][str_split[0]]; // square matrix of N rows and N columns

  for (int outer_index = 0; outer_index < str_split[1]; outer_index++) {
    for (int inner_index = 0; inner_index < str_split[1]; inner_index++) {
      arr_after_kahn_algo_to_print[outer_index][inner_index] = -1;
      // printf("%i, ", arr_after_kahn_algo_to_print[outer_index][inner_index]);
    }
  // printf(" * \n");
  }

  int in_degrees[str_split[0]];
  for(int num = 0; num < str_split[0]; num++) {
    for (int index_for_2nd_column = 0; index_for_2nd_column < str_split[1]; index_for_2nd_column++) {
      if ((num + 1) == m_dependencies_final_2nd_indices[index_for_2nd_column]) {
        in_degrees[num] = in_degrees[num] + 1;
      }
    }
  }

  printf(" ** \n");

  for (int index_for_in_degrees = 0; index_for_in_degrees < str_split[0]; index_for_in_degrees++) {
    printf("%i ", in_degrees[index_for_in_degrees]);
  }

  printf(" ** \n");

  // for (int outer_index = 0; outer_index < str_split[1]; outer_index++) {
  //   for (int inner_index = 0; inner_index < str_split[1]; inner_index++) {
  //     int place = check_for_dependencies(m_dependencies_final_1st_indices[outer_index], length_of_m_dependencies_final_2nd_indices, m_dependencies_final_2nd_indices);
  //     if (place == -1) {
  //       break;
  //     } else {
  //       arr_after_kahn_algo_to_print[outer_index][inner_index] = m_dependencies_final_1st_indices[place];
  //       break;
  //     }
  //   }
  // }

  printf("%li \n", (sizeof(arr_after_kahn_algo_to_print) / sizeof(arr_after_kahn_algo_to_print[0])));

  for (int outer_index = 0; outer_index < str_split[1]; outer_index++) {
    for (int inner_index = 0; inner_index < str_split[1]; inner_index++) {
      if (arr_after_kahn_algo_to_print[outer_index][inner_index] > 0) {
        printf("%i", arr_after_kahn_algo_to_print[outer_index][inner_index]);
      }

      if (inner_index != (str_split[1] - 1) && (arr_after_kahn_algo_to_print[inner_index + 1] > 0)) {
        printf(", ");
      } else {
        printf("\n");
      }
    }
  }

  fclose(file_ptr);
}
