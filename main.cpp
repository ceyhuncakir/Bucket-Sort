#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <sstream>

template <typename T>
std::vector<T> bucket_sort(std::vector<T> array, int k) {


  // initialiseren we een lijst met vectoren er in waar integers in zitten.
  std::vector<std::vector<T>> buckets;

  // we itereren door de aantal wat de gebruiker heeft meegegeven aan deze functie
  for(int i = 0; i < k; i++) {
    // we initaliseren een empty list
    std::vector<T> empty_list;

    // we pushen de empty lists als een buckets binnen de buckets lists.
    buckets.push_back(empty_list);
  }

  // O(n)
  // we itereren door de lijst met getallen die gesorteerd moeten worden.
  for(int i = 0; i < array.size(); i++) {


    // we maken een ostringstream aan voor een string buffer waar een sequence aan chars opgeslagen worden.
    std::ostringstream ss;
    // we zetten de datatype in de string buffer
    ss << array[i];
    // we verranderen uiteindelijk de datatype naar een string
    std::string string_integer = ss.str();

    // we pakken van de hele string de laatse char.
    char string_integer_last_char = string_integer.back();

    // we verranderen de char terug naar een int door een int declraratie te geven en ook - 48 te gebruiken aangezien ascii chars op nummer 48 starten.
    int last_digit = (int) string_integer_last_char - 48;

    // we voegen de getallen naar de correspondente buckets
    buckets[last_digit].push_back(array[i]);
  }

  // we gebruiken de clear functie om de nieuwe gesorteerde waardes er in te zetten.
  array.clear();

  // O(n ^ 2)
  // we itereren door de buckets array heen waar allemaal buckets in zitten.
  for(int i = 0; i < buckets.size(); i++) {
    // we itereren voor elke bucket in buckets om de getallen te krijgen.
    for(int idx = 0; idx < buckets[i].size(); idx++) {
      // we pushen uiteindelijk alle nummers die we steeds tegen komen in de buckets naar de originele array.
      array.push_back(buckets[i][idx]);
    }
  }

  // we returnen de gesorteerde originele array terug.
  return array;
}

int main() {

  char c;
  int min;
  int max;
  int amount_of_integers;

  std::vector<float> array;
  int k = 10;

  std::cout << "desired buckets in array: ";
  std::cin >> k;

  std::cout << "desired amount of integers: ";
  std::cin >> amount_of_integers;

  std::cout << "desired range of random generated numbers (min/max) ";
  std::cin >> min >> c >> max;

  for(int i = 0; i < amount_of_integers; i++) {
    int random_generated_integer = rand() % (max - min) + min;
    array.push_back(random_generated_integer);
  }

  // vraag aan docent hoe je de vector array als een T kan krijgen

  array.push_back(-1.5);
  array.push_back(-0.9);
  array.push_back(1.2);
  array.push_back(0.4);

  std::vector<float> sorted_array = bucket_sort(array, k);

  std::cout << "given array - ";

  for(const auto elem : array) { std::cout << elem << " | "; }
  std::cout << std::endl;

  std::cout << "sorted array - ";

  for(const auto elem : sorted_array) { std::cout << elem << " | "; }
  std::cout << std::endl;

  return 0;
}
