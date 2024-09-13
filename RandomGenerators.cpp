/*PROJECT DETECTOR SIMULATION - Sophie Hannon 11/05/24
RandomGenerators code file, includes function returning random variables to randomly allocate energies between events*/

#include "RandomGenerators.h"
#include <vector>

// Random number generator which returns a vector of probabilities which sum to 1, user determines vector size and thus number of probabilities
std::vector<double> random_probability_generator(int number_probabilities_in)
{
  int number_probabilities = number_probabilities_in - 1; // Accounts for vector indices starting at 0
  std::vector<double> probability_vector; // Vector to store probabilities
  double sum{0};
  if(number_probabilities_in == 1)  // If only 1, push back 1 since only one outcome
  {
    probability_vector.push_back(1); 
    return probability_vector;
  }
  for(int i{}; i<number_probabilities; i++) // Iterate through the number of probabilities
  {
    double random_number = (double)std::rand() / RAND_MAX;
    while(random_number < 0 && random_number>1) random_number = (double)std::rand() / RAND_MAX; // Random number generated between 0 and 1
    sum += random_number;
    while(sum > 1)  // If sums to greater than 1, generate a new random number
    {
      sum -= random_number;
      random_number = (double)std::rand() / RAND_MAX;
      sum += random_number; // Ensures the new number adds to less than 1
    }
    if(i==(number_probabilities-1)) probability_vector.push_back(1-sum);  // If the last iteration, makes sure they sum to 1  
    probability_vector.push_back(random_number); // Adds to probability vector
  }
  return probability_vector;
}

// Generates a random boolean value
bool random_bool()
{
  double rand_num = std::rand() / RAND_MAX;
  if(rand_num > 0.5) return 1;
  else return 0;
}

// Generates a random double value under 1
double random_prob()
{
  double rand_num = std::rand() / RAND_MAX;
  return rand_num;
}