#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <string>

template <typename T>
std::vector<T> bucket_sort(std::vector<T> array, int max_elem) {

  // initialiseren we een lijst met vectoren er in waar integers in zitten.

  for(int index = max_elem; index >= 0; index--) {

    std::vector<std::vector<T>> buckets = {{}, {}, {}, {}, {}, {}, {}, {}, {}, {}};
    std::cout << "ronde: " << index << std::endl;
    // we itereren door de lijst met getallen die gesorteerd moeten worden.
    for(int elementen = 0; elementen < array.size(); elementen++) {

      // we maken een ostringstream aan voor een string buffer waar een sequence aan chars opgeslagen worden.
      std::ostringstream ss;
      // we zetten de datatype in de string buffer
      ss << std::abs(array[elementen]);
      // we verranderen uiteindelijk de datatype naar een string
      std::string string_integer = ss.str();

      int last_char = string_integer[index];
      int integer = std::stoi(string_integer);
      int last = integer / 1 * std::pow(10, index - 2);

      buckets[last % 10].push_back(array[elementen]);
    }

    array.clear();

    for(int i = 0; i < buckets.size(); i++) {
      // we itereren voor elke bucket in buckets om de getallen te krijgen.
      for(int idx = 0; idx < buckets[i].size(); idx++) {
        // we pushen uiteindelijk alle nummers die we steeds tegen komen in de buckets naar de originele array.

        array.push_back(buckets[i][idx]);
      }
    }
  }
  return array;
}

int main() {

  char c;
  int min;
  int max;
  int amount_of_integers;

  std::vector<float> unsorted;
  std::vector<float> negative_numbers;
  std::vector<float> positive_numbers;

  std::cout << "desired amount of integers: ";
  std::cin >> amount_of_integers;

  std::cout << "desired range of random generated numbers (min/max) ";
  std::cin >> min >> c >> max;

  for(int i = 0; i < amount_of_integers; i++) {
    int random_generated_integer = rand() % (max - min) + min;

    unsorted.push_back(random_generated_integer);

    if(random_generated_integer < 0) {
      negative_numbers.push_back(random_generated_integer);
    } else {
      positive_numbers.push_back(random_generated_integer);
    }
  }

  int max_negative = *min_element(negative_numbers.begin(), negative_numbers.end());
  int max_positive = *max_element(positive_numbers.begin(), positive_numbers.end());

  std::ostringstream ss_neg;
  ss_neg << abs(max_negative);
  std::string string_integer_neg = ss_neg.str();
  int max_elem_neg = string_integer_neg.length();

  std::ostringstream ss_pos;
  ss_pos << max_positive;
  std::string string_integer_pos = ss_pos.str();
  int max_elem_pos = string_integer_pos.length();

  std::vector<float> sorted_array_neg = bucket_sort(negative_numbers, max_elem_neg - 1);
  std::reverse(sorted_array_neg.begin(), sorted_array_neg.end());

  std::vector<float> sorted_array_pos = bucket_sort(positive_numbers, max_elem_pos - 1);

  sorted_array_neg.insert(sorted_array_neg.end(),std::make_move_iterator(sorted_array_pos.begin()),std::make_move_iterator(sorted_array_pos.end()));

  std::cout << "given array - ";

  for(const auto elem : unsorted) { std::cout << elem << " | "; }
  std::cout << std::endl;

  std::cout << "sorted array - ";

  for(const auto elem : sorted_array_neg) { std::cout << elem << " | "; }
  std::cout << std::endl;

  return 0;
}
