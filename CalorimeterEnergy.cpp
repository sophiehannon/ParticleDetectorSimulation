/*PROJECT DETECTOR SIMULATION - Sophie Hannon 11/05/24
Calorimeter energy class code file includes copy constructor, assignment operator 
for deep copying, move constructor and move by assignment. Function checks the energy of 
particle > sum of calorimeter energy components. */

#include<iostream>
#include<string>
#include "CalorimeterEnergy.h"

// Copy constructor for deep copying
CalorimeterEnergy::CalorimeterEnergy(const CalorimeterEnergy &calorimeter_energy_copy)
{
  calorimeter_energy = calorimeter_energy_copy.get_calorimeter_energy_vector();
}

// Assigment operator for deep copying
CalorimeterEnergy & CalorimeterEnergy::operator=(const CalorimeterEnergy &calorimeter_energy_copy)
{
  if(&calorimeter_energy_copy == this) return *this; // Prevents self assigment
  // Reassign values with copy
  calorimeter_energy = calorimeter_energy_copy.get_calorimeter_energy_vector();
  return *this;    
}

// Move constructor which moves a CalorimeterEnergy to a new CalorimeterEnergy and empties the original
CalorimeterEnergy::CalorimeterEnergy(CalorimeterEnergy&& calorimeter_energy_move)
{
  calorimeter_energy = calorimeter_energy_move.calorimeter_energy;
  // Empty initial CalorimeterEnergy
  calorimeter_energy_move.calorimeter_energy[0] = 0;
  calorimeter_energy_move.calorimeter_energy[1] = 0;
  calorimeter_energy_move.calorimeter_energy[2] = 0;
  calorimeter_energy_move.calorimeter_energy[3] = 0;
}

// Move by assigment swaps the existing CalorimeterEnergy with the new one
CalorimeterEnergy & CalorimeterEnergy::operator=(CalorimeterEnergy&& calorimeter_energy_move)
{
  // Reassign values with copy
  calorimeter_energy = calorimeter_energy_move.get_calorimeter_energy_vector();
  return *this;
}

// Printing function, checking CalorimeterEnergy implemented correctly
void CalorimeterEnergy::print_data_calorimeter_energy()
{
  std::cout<<"\nCalorimeter energy layers, [EM_1, EM_2, HAD_1, HAD_2]: ["<<calorimeter_energy[0]<<", "<<calorimeter_energy[1]<<", "<<calorimeter_energy[2]<<", "<<calorimeter_energy[3]<<"].";
}

// Sums a four vector
double CalorimeterEnergy::four_vector_sum()
{
  double sum;
  for(int i{0}; i<4; i++) sum +=  calorimeter_energy[i]; 
  return sum;
}