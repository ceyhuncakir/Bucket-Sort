#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <string>

template <typename T>
std::vector<T> bucket_sort(std::vector<T> array, int k, int i) {


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

  for(int idx = 0; idx < array.size(); idx++) {
                                                                                                        //3    2        2    2
    // verwijder als eerst sws de - van de getallen die negatief zijn zodat de waardes gelijk blijven. (-159, 159) -> (159, 159). zodat die niet de minus neemt als idx
    // check of het mogelijk is dat voor een gegeven array[idx] de idx 3 heeft in het string.
    // neem de length van de string characters voorbeeld: 232 = (2) || i = 2 || 2 - 3 = 1 || i - 2 - i

    // we maken een ostringstream aan voor een string buffer waar een sequence aan chars opgeslagen worden.
    std::ostringstream ss;
    // we zetten de datatype in de string buffer
    ss << array[idx];
    // we verranderen uiteindelijk de datatype naar een string
    std::string string_integer = ss.str();

    string_integer.erase(std::remove(string_integer.begin(), string_integer.end(), '-'), string_integer.end());

    // de waarde die van de string lengte er af word getrokken om de juiste positie te krijgen
    // we pakken van de hele string de laatse char.

    char string_integer_last_char = string_integer[i - 1];

    // we verranderen de char terug naar een int door een int declraratie te geven en ook - 48 te gebruiken aangezien ascii chars op nummer 48 starten.
    int last_digit = (int) string_integer_last_char - 48;

    // we voegen de getallen naar de correspondente buckets
    buckets[last_digit].push_back(array[idx]);
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

  int max_itt = *max_element(array.begin(), array.end());

  std::ostringstream ss;
  ss << max_itt;
  std::string string_integer = ss.str();

  std::cout << string_integer.length() << std::endl;

  std::vector<float> sorted_array = bucket_sort(array, k, string_integer.length());

  std::cout << "given array - ";

  for(const auto elem : array) { std::cout << elem << " | "; }
  std::cout << std::endl;

  std::cout << "sorted array 3 - ";

  for(const auto elem : sorted_array) { std::cout << elem << " | "; }
  std::cout << std::endl;


  return 0;
}
