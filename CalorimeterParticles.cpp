/*PROJECT DETECTOR SIMULATION - Sophie Hannon 11/05/24
CalorimeterParticles derived class code file, inherits from particle class includes copy constructor, assignment operator 
for deep copying, move constructor and move by assignment. Function checks the energy of 
particle > sum of calorimeter energy components. */

#include<iostream>
#include<string>
#include "Particle.h"
#include "CalorimeterParticles.h"
#include "CalorimeterEnergy.h"

// Copy constructor for deep copying
CalorimeterParticles::CalorimeterParticles(const CalorimeterParticles &particle_copy) : Particle(particle_copy)
{
  *calorimeter_energy = particle_copy.get_calorimeter_energy();
}

// Assigment operator for deep copying
CalorimeterParticles & CalorimeterParticles::operator=(const CalorimeterParticles &particle_copy)
{
  if(&particle_copy == this) return *this; // Prevents self assigment
  // Reassign values with copy
  Particle::operator=(particle_copy);
  *calorimeter_energy = particle_copy.get_calorimeter_energy();
  return *this;    
}

// Move constructor which moves a particle to a new particle and empties the original
CalorimeterParticles::CalorimeterParticles(CalorimeterParticles&& particle_move) : Particle(particle_move)
{
  *calorimeter_energy = particle_move.get_calorimeter_energy();
  // Empty initial particle
  particle_move.calorimeter_energy = nullptr;
}

// Print data function
void CalorimeterParticles::print_data()
{
  std::cout.precision(3); // 2 significant figures
  if(charge == 1) std::cout<<"\nProton ";
  if(charge == 0) std::cout<<"\nNeutron ";
  particle_properties();
  std::cout<<"  ";
  calorimeter_energy->print_data_calorimeter_energy();
  return;
}

// Function checks if the energy is greater than the input energy, if it is it redistributes it in the same fractions
CalorimeterEnergy CalorimeterParticles::check_energy_physical(CalorimeterEnergy calorimeter_energy_check)
{
  double sum{calorimeter_energy_check.four_vector_sum()};
  if(sum > energy)
  {
    // If the energy deposited is greater than the energy of the particle, it is rescaled in the same proportions
    calorimeter_energy_check.set_em_1(calorimeter_energy_check.get_em_1() * (energy / sum));
    calorimeter_energy_check.set_em_2(calorimeter_energy_check.get_em_2() * (energy / sum));
    calorimeter_energy_check.set_had_1(calorimeter_energy_check.get_had_1() * (energy / sum));
    calorimeter_energy_check.set_had_2(calorimeter_energy_check.get_had_2() * (energy / sum));
  }  
  return calorimeter_energy_check;
}