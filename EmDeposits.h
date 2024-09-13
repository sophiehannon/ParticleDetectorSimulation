/*PROJECT DETECTOR SIMULATION - Sophie Hannon 11/05/24
EmDeposits derived class header file, inherits from particle class includes copy constructor, assignment operator 
for deep copying, move constructor and move by assignment. Function checks the energy of 
particle > sum of calorimeter energy components. */

#ifndef EmDeposits_H
#define EmDeposits_H

#include<iostream>
#include<string>
#include<cmath>
#include<vector>
#include<memory>
#include "Particle.h"
#include "CalorimeterEnergy.h"
#include "RandomGenerators.h"
#include "CalorimeterParticles.h"

class EmDeposits : public CalorimeterParticles
{
public:
  // Constructors
  // Default constructor
  EmDeposits() {} 
  // Parameterized constructor, uses setters to assign values and push back values into four momentum
  EmDeposits(int particle_identifier_in, int charge_in, double energy_in) :
  CalorimeterParticles{particle_identifier_in, charge_in, energy_in}
  {
    std::vector<double> probability{random_probability_generator(2)};
    CalorimeterEnergy calorimeter_energy_in(energy_in*probability[0], energy_in*probability[1], 0, 0);
    set_calorimeter_energy(calorimeter_energy_in);
  }
  // Destructor
  ~EmDeposits(){} 
  // Copy constructor
  EmDeposits(const EmDeposits&); // Deep copies an already existing particle
  // Assignment operator
  EmDeposits& operator=(const EmDeposits&); // Assigns a right hand value to a left hand variable using = operator
  // Move constructor
  EmDeposits(EmDeposits&&); // Moves a particle to a new particle and empties the original
  // Move assignment operator
  EmDeposits& operator=(EmDeposits&&); // Moves a particle to a new one by assignment
  
  // Getter functions (accessors) to calorimeter energy
  CalorimeterEnergy get_calorimeter_energy()const{return (*calorimeter_energy);}; // Returns Calorimeter Energy object

  // Setter functions, to change value of Calorimeter Energy 
  // Checks physical input so that energy of particle >= sum of calorimeter deposits
  void set_calorimeter_energy(const CalorimeterEnergy calorimeter_energy_new){calorimeter_energy = std::make_unique<CalorimeterEnergy>(check_energy_physical(calorimeter_energy_new));};

  void print_data() override; // Function to print info about a particle
};

#endif