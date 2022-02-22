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

    // we creeren 9 lege buckets
    std::vector<std::vector<T>> buckets = {{}, {}, {}, {}, {}, {}, {}, {}, {}, {}};
    // we itereren door de lijst met getallen die gesorteerd moeten worden.
    for(int elements = 0; elements < array.size(); elements++) {
      // creert nullen voor de cijfers zodat wanneer er 3 getallen er zijn maar de index is 0-1 dan kunnen we nogsteeds de getal pakken zonder dat de programma crashed
      int big_int = std::abs(array[elements]) * std::pow(10, index - 3);

      // we pushbacken de laatse integer als bucket en de element
      buckets[big_int % 10].push_back(array[elements]); //
    }

    // we clearen de array zodat wanneer de nieuwe in komen dat de oude run er niet in zit.
    array.clear(); //


    for(int bucket = 0; bucket < buckets.size(); bucket++) {
      // we itereren voor elke bucket in buckets om de getallen te krijgen.
      for(int integers = 0; integers < buckets[bucket].size(); integers++) {
        // we pushen uiteindelijk alle nummers die we steeds tegen komen in de buckets naar de originele array.
        array.push_back(buckets[bucket][integers]);
      }
    }
  }
  return array;
}

int main() {

  // space char
  char c;
  // min waarde van de input
  int min;
  // max waarde van de input
  int max;
  // amount of integers van de input
  int amount_of_integers;

  // unsorted array vector
  std::vector<float> unsorted;
  // alle negatieve nummers van de unsorted vector
  std::vector<float> negative_numbers;
  // alle positieve nummers van de unsorted vector
  std::vector<float> positive_numbers;
  // gesorteerde negatieve nummers vector
  std::vector<float> sorted_array_neg;
  // gesorteerde positieve nummers vector
  std::vector<float> sorted_array_pos;

  std::cout << "desired amount of integers: ";
  std::cin >> amount_of_integers;

  std::cout << "desired range of random generated numbers (min/max) ";
  std::cin >> min >> c >> max;

  // zorgt er voor dat random nummers van een min value en en max value worden gegenereerd
  for(int i = 0; i < amount_of_integers; i++) {
    int random_generated_integer = rand() % (max - min) + min;

    unsorted.push_back(random_generated_integer);

    if(random_generated_integer < 0) {
      negative_numbers.push_back(random_generated_integer);
    } else {
      positive_numbers.push_back(random_generated_integer);
    }
  }

  // word er gekeken of de lijst van de negatieve nummers niet empty is
  if(!negative_numbers.empty()) {
    int max_negative = *min_element(negative_numbers.begin(), negative_numbers.end());

    std::ostringstream ss_neg;
    ss_neg << abs(max_negative);
    std::string string_integer_neg = ss_neg.str();
    int max_elem_neg = string_integer_neg.length();

    sorted_array_neg = bucket_sort(negative_numbers, max_elem_neg - 1);
    std::reverse(sorted_array_neg.begin(), sorted_array_neg.end());

  }

  // word er gekeken of de lijst van de positieve nummers niet empty is
  if(!positive_numbers.empty()) {
    int max_positive = *max_element(positive_numbers.begin(), positive_numbers.end());

    std::ostringstream ss_pos;
    ss_pos << max_positive;
    std::string string_integer_pos = ss_pos.str();
    int max_elem_pos = string_integer_pos.length();

    sorted_array_pos = bucket_sort(positive_numbers, max_elem_pos - 1);
  }

  // gesorteerde nummers worden toegevoegd aan elkaar
  sorted_array_neg.insert(sorted_array_neg.end(), sorted_array_pos.begin(), sorted_array_pos.end());

  std::cout << "given array - ";

  for(const auto elem : unsorted) { std::cout << elem << " | "; }
  std::cout << std::endl;

  std::cout << "sorted array - ";

  for(const auto elem : sorted_array_neg) { std::cout << elem << " | "; }
  std::cout << std::endl;

  return 0;
}
