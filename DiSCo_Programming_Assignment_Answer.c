#include <stdio.h>
#include <string.h>

int check_for_dependencies(int val_to_check, int length, int m_dependencies_final_2nd_indices[length]) {
  int place = 0;

  // for (int count = 0; count < (sizeof(m_dependencies_final_2nd_indices) / sizeof(m_dependencies_final_2nd_indices[0])); count++) {
  for (int count = 0; count < length; count++) {
    if ((val_to_check == m_dependencies_final_2nd_indices[count]) && (m_dependencies_final_2nd_indices[count] != 0)) {
      place = -1; // returns -1 if dependencies are found on A, which means A cannot be a root
      break;
    } else if (count == length - 1) {
      place = count;
    }
  }

  return place;
}

int main () {
  FILE *file_ptr;
  file_ptr = fopen("Notes.txt", "r");

  // ~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*

  /*
  // String str = fscanf(file_ptr, "%i %i"); // N and M (number of treats & number of dependencies)
  String str;
  fgets(str, 13, file_ptr); // N and M (number of treats & number of dependencies)

  int str_split[2] = Integer(str.split(" "));
  int n_treats = str_split[0];
  String m_dependencies_storage[str_split[1]]; // number of lines after the first line, of format "%i %i"
  int m_dependencies_final[][str_split[1]]; // number of lines after the first line, of format "%i %i"

  // String dummy_var;
  // fgets(dummy_var, 13, file_ptr);

  int storage[2];

  for (int index = 0; index < str_split[1]; index++) {
    fgets(m_dependencies_storage[index], 13, file_ptr); // of format {"%i %i", "%i %i", "%i %i", ...}
  }

  for (int index = 0; index < str_split[1]; index++) {
    int dummy_arr[2] = Integer(m_dependencies_storage[index].split(" "));
    m_dependencies_final[index][0] = dummy_arr[0];
    m_dependencies_final[index][1] = dummy_arr[1]; // of format {{%i, %i}, {%i, %i}, {%i, %i}, ...}
  }
  */

  // ~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*

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

  int arr_after_kahn_algo_to_print[str_split[1]][str_split[1]]; // square matrix of M rows and M columns

  for (int outer_index = 0; outer_index < str_split[1]; outer_index++) {
    for (int inner_index = 0; inner_index < str_split[1]; inner_index++) {
      arr_after_kahn_algo_to_print[outer_index][inner_index] = -1;
      // printf("%i, ", arr_after_kahn_algo_to_print[outer_index][inner_index]);
    }
  // printf(" * \n");
  }

  int length_of_m_dependencies_final_2nd_indices = str_split[1];
  // printf(" !!! %i \n", length_of_m_dependencies_final_2nd_indices);

  for (int outer_index = 0; outer_index < str_split[1]; outer_index++) {
    for (int inner_index = 0; inner_index < str_split[1]; inner_index++) {
      int place = check_for_dependencies(m_dependencies_final_1st_indices[outer_index], length_of_m_dependencies_final_2nd_indices, m_dependencies_final_2nd_indices);
      if (place == -1) {
        continue;
      } else {
        arr_after_kahn_algo_to_print[outer_index][inner_index] = m_dependencies_final_1st_indices[place];
        break;
      }
    }
  }

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
