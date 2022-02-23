#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <string>
#include <chrono>

using namespace std::chrono;

template <typename T>
std::vector<T> bucket_sort(std::vector<T> array, int max_elem) {

  // initialiseren we een lijst met vectoren er in waar integers in zitten.

  for(int index = 0; index <= max_elem; index++) {

    // we creeren 9 lege buckets
    std::vector<std::vector<T>> buckets = {{}, {}, {}, {}, {}, {}, {}, {}, {}, {}};
    // we itereren door de lijst met getallen die gesorteerd moeten worden.
    for(int elements = 0; elements < array.size(); elements++) {

      // creert nullen voor de cijfers zodat wanneer er 3 getallen er zijn maar de index is 0-1 dan kunnen we nogsteeds de getal pakken zonder dat de programma crashed
      int big_int = std::abs(array[elements]) / (int) std::pow(10, index);

      // we pushbacken de laatse integer als bucket en de element
      buckets[big_int % 10].push_back(array[elements]);
    }

    // we clearen de array zodat wanneer de nieuwe in komen dat de oude run er niet in zit.
    array.clear();

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

void test_bucket_sort(std::vector<float> sorted_array, std::vector<float> unsorted_array) {

  // build in functie om te bevestigen dat de algoritme werkt
  std::sort(unsorted_array.begin(), unsorted_array.end());

  // test of mijn uitkomsten de zelfde zijn als die van c++
  if(unsorted_array == sorted_array) {
    std::cout << " " << std::endl;
    std::cout << "-----------Algorithm sorted validation checkt---------" << std::endl;
    std::cout << "de uitkomst van de eigen gemaakte bucket sort tegenover de sorting algoritme van c++: True" << std::endl;
  } else {
    std::cout << " " << std::endl;
    std::cout << "-----------Algorithm sorted validation check---------" << std::endl;
    std::cout << "----------Worst case scenario of the bucket sort---------" << std::endl;
    std::cout << "de uitkomst van de eigen gemaakte bucket sort tegenover de sorting algoritme van c++: False" << std::endl;
  }
}

void test_bucket_sort_worst_case() {

  // de vectoren met de ongesorteerde waardes
  std::vector<float> negative_numbers = {-10, -20, -400, -4000, -15000};
  std::vector<float> positive_numbers = {110000, 20000, 15000, 4000, 400};
  std::vector<float> unsorted = {-10, -20, -400, -4000, -15000, 110000, 20000, 15000, 4000, 400};

  // hier worden de max element en min element gepakt van de vectors
  int max_negative = *min_element(negative_numbers.begin(), negative_numbers.end());
  int max_positive = *max_element(positive_numbers.begin(), positive_numbers.end());

  // de negatieve getallen worden omgebouwt naar een string
  std::ostringstream ss_neg;
  ss_neg << abs(max_negative);
  std::string string_integer_neg = ss_neg.str();
  int max_elem_neg = string_integer_neg.length();

  // de positieve getallen worden omgebouwt naar een string
  std::ostringstream ss_pos;
  ss_pos << max_positive;
  std::string string_integer_pos = ss_pos.str();
  int max_elem_pos = string_integer_pos.length();

  // counter word bijgehouden voor de run time
  auto start = high_resolution_clock::now();

  // negatieve getallen worden gesorteerd
  std::vector<float> sorted_array_neg = bucket_sort(negative_numbers, max_elem_neg - 1);
  // gesorte negatieve getallen worden gereversed zodat het goed komt te staan later bij de merge
  std::reverse(sorted_array_neg.begin(), sorted_array_neg.end());

  // positieve getallen worden gesorteerd
  std::vector<float> sorted_array_pos = bucket_sort(positive_numbers, max_elem_pos - 1);

  // counter stopt met bijgehouden voor de run time
  auto stop = high_resolution_clock::now();

  // positieve gettalen worden bijgevoegd bij de negatieve getallen.
  sorted_array_neg.insert(sorted_array_neg.end(), sorted_array_pos.begin(), sorted_array_pos.end());

  std::cout << " " << std::endl;

  std::cout << "----------Worst case scenario of the bucket sort---------" << std::endl;

  std::cout << " " << std::endl;

  std::cout << "given test array - ";

  for(const auto elem : unsorted) { std::cout << elem << " | "; }
  std::cout << std::endl;

  std::cout << "sorted test array - ";

  for(const auto elem : sorted_array_neg) { std::cout << elem << " | "; }
  std::cout << std::endl;

  // duration word hier gecalculeert.
  auto duration = duration_cast<microseconds>(stop - start);

  std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;

}

void test_bucket_sort_average_case() {

  // de vectoren met de ongesorteerde waardes
  std::vector<float> negative_numbers = {-63211, -72690, -17285, -53096};
  std::vector<float> positive_numbers = {27079, 88632, 10250, 25437, 85871, 13023};
  std::vector<float> unsorted = {-63211, 27079, 88632, -72690, 10250, 25437, -17285, 85871, -53096, 13023};

  // hier worden de max element en min element gepakt van de vectors
  int max_negative = *min_element(negative_numbers.begin(), negative_numbers.end());
  int max_positive = *max_element(positive_numbers.begin(), positive_numbers.end());

  // de negatieve getallen worden omgebouwt naar een string
  std::ostringstream ss_neg;
  ss_neg << abs(max_negative);
  std::string string_integer_neg = ss_neg.str();
  int max_elem_neg = string_integer_neg.length();

  // de positieve getallen worden omgebouwt naar een string
  std::ostringstream ss_pos;
  ss_pos << max_positive;
  std::string string_integer_pos = ss_pos.str();
  int max_elem_pos = string_integer_pos.length();

  // counter word bijgehouden voor de run time
  auto start = high_resolution_clock::now();

  // negatieve getallen worden gesorteerd
  std::vector<float> sorted_array_neg = bucket_sort(negative_numbers, max_elem_neg - 1);
  // gesorte negatieve getallen worden gereversed zodat het goed komt te staan later bij de merge
  std::reverse(sorted_array_neg.begin(), sorted_array_neg.end());

  // positieve getallen worden gesorteerd
  std::vector<float> sorted_array_pos = bucket_sort(positive_numbers, max_elem_pos - 1);

  // counter stopt met bijgehouden voor de run time
  auto stop = high_resolution_clock::now();

  // positieve gettalen worden bijgevoegd bij de negatieve getallen.
  sorted_array_neg.insert(sorted_array_neg.end(), sorted_array_pos.begin(), sorted_array_pos.end());

  std::cout << " " << std::endl;

  std::cout << "----------Average case scenario of the bucket sort---------" << std::endl;

  std::cout << " " << std::endl;

  std::cout << "given test array - ";

  for(const auto elem : unsorted) { std::cout << elem << " | "; }
  std::cout << std::endl;

  std::cout << "sorted test array - ";

  for(const auto elem : sorted_array_neg) { std::cout << elem << " | "; }
  std::cout << std::endl;

  // duration word hier gecalculeert.
  auto duration = duration_cast<microseconds>(stop - start);

  std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;

}

void test_bucket_sort_best_case() {

  // de vectoren met de ongesorteerde waardes
  std::vector<float> negative_numbers = {-91243, -87564, -68757, -2186,};
  std::vector<float> positive_numbers = {14406, 20622, 23253, 31020, 76913, 89908};
  std::vector<float> unsorted = {-91243, -87564, -68757, -2186, 14406, 20622, 23253, 31020, 76913, 89908};

  // hier worden de max element en min element gepakt van de vectors
  int max_negative = *min_element(negative_numbers.begin(), negative_numbers.end());
  int max_positive = *max_element(positive_numbers.begin(), positive_numbers.end());

  // de negatieve getallen worden omgebouwt naar een string
  std::ostringstream ss_neg;
  ss_neg << abs(max_negative);
  std::string string_integer_neg = ss_neg.str();
  int max_elem_neg = string_integer_neg.length();

  // de positieve getallen worden omgebouwt naar een string
  std::ostringstream ss_pos;
  ss_pos << max_positive;
  std::string string_integer_pos = ss_pos.str();
  int max_elem_pos = string_integer_pos.length();

  // counter word bijgehouden voor de run time
  auto start = high_resolution_clock::now();

  // negatieve getallen worden gesorteerd
  std::vector<float> sorted_array_neg = bucket_sort(negative_numbers, max_elem_neg - 1);
  // gesorte negatieve getallen worden gereversed zodat het goed komt te staan later bij de merge
  std::reverse(sorted_array_neg.begin(), sorted_array_neg.end());

  // positieve getallen worden gesorteerd
  std::vector<float> sorted_array_pos = bucket_sort(positive_numbers, max_elem_pos - 1);

  // counter stopt met bijgehouden voor de run time
  auto stop = high_resolution_clock::now();

  // positieve gettalen worden bijgevoegd bij de negatieve getallen.
  sorted_array_neg.insert(sorted_array_neg.end(), sorted_array_pos.begin(), sorted_array_pos.end());

  std::cout << " " << std::endl;

  std::cout << "----------Best case scenario of the bucket sort---------" << std::endl;

  std::cout << " " << std::endl;

  std::cout << "given test array - ";

  for(const auto elem : unsorted) { std::cout << elem << " | "; }
  std::cout << std::endl;

  std::cout << "sorted test array - ";

  for(const auto elem : sorted_array_neg) { std::cout << elem << " | "; }
  std::cout << std::endl;

  // duration word hier gecalculeert.
  auto duration = duration_cast<microseconds>(stop - start);

  std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;

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

  auto start = high_resolution_clock::now();

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

  auto stop = high_resolution_clock::now();

  sorted_array_neg.insert(sorted_array_neg.end(), sorted_array_pos.begin(), sorted_array_pos.end());

  std::cout << " " << std::endl;

  std::cout << "----------------User inputted outcome---------" << std::endl;

  std::cout << "given array - ";

  for(const auto elem : unsorted) { std::cout << elem << " | "; }
  std::cout << std::endl;

  std::cout << "sorted array - ";

  for(const auto elem : sorted_array_neg) { std::cout << elem << " | "; }
  std::cout << std::endl;

  auto duration = duration_cast<microseconds>(stop - start);

  std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;

  test_bucket_sort(sorted_array_neg, unsorted);

  test_bucket_sort_worst_case();

  test_bucket_sort_average_case();

  test_bucket_sort_best_case();

  return 0;
}
