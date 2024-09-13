/*PROJECT DETECTOR SIMULATION - Sophie Hannon 11/05/24
EmDeposits derived class code file, inherits from CalorimeterParticles class which inherits from the base particle class 
includes copy constructor, assignment operator for deep copying, move constructor and move by assignment. 
Function checks the energy of particle > sum of calorimeter energy components. */

#include<iostream>
#include<string>
#include "Particle.h"
#include "EmDeposits.h"
#include "EmDeposits.h"
#include "CalorimeterEnergy.h"

// Copy constructor for deep copying
EmDeposits::EmDeposits(const EmDeposits &particle_copy) : CalorimeterParticles(particle_copy) {}

// Assigment operator for deep copying
EmDeposits & EmDeposits::operator=(const EmDeposits &particle_copy)
{
  if(&particle_copy == this) return *this; // Prevents self assigment
  CalorimeterParticles::operator=(particle_copy);
  return *this;    
}

// Move constructor which moves a particle to a new particle and empties the original
EmDeposits::EmDeposits(EmDeposits&& particle_move) : CalorimeterParticles(particle_move){}

// Print data function
void EmDeposits::print_data()
{
  std::cout.precision(3); // 2 significant figures
  if(charge == 0) std::cout<<"\nPhoton ";
  if(charge == -1) std::cout<<"\nElectron ";  //  Prints name base on charge
  if(charge == 1) std::cout<<"\nPositron ";
  particle_properties();
  std::cout<<"  ";
  calorimeter_energy->print_data_calorimeter_energy();
  return;
}
