/*PROJECT DETECTOR SIMULATION - Sophie Hannon 11/05/24
CalorimeterParticles derived class header file, inherits from particle class includes copy constructor, assignment operator 
for deep copying, move constructor and move by assignment. Function checks the energy of 
particle > sum of calorimeter energy components. */

#ifndef CALORIMETERPARTICLES_H
#define CALORIMETERPARTICLES_H

#include<iostream>
#include<string>
#include<cmath>
#include<vector>
#include<memory>
#include "Particle.h"
#include "CalorimeterEnergy.h"
#include "RandomGenerators.h"

class CalorimeterParticles : public Particle
{
protected: 
std::unique_ptr<CalorimeterEnergy> calorimeter_energy; // Makes a unique pointer for the calorimeter energy

public:
  // Constructors
  // Default constructor
  CalorimeterParticles() {} 
  // Parameterized constructor, uses setters to assign values and push back values into four momentum
  CalorimeterParticles(int particle_identifier_in, int charge_in, double energy_in) :
  Particle{particle_identifier_in, charge_in, energy_in}
  {
    std::vector<double> probability{random_probability_generator(4)};
    CalorimeterEnergy calorimeter_energy_in(energy_in*probability[0], energy_in*probability[1], energy_in*probability[2], energy_in*probability[3]);
    set_calorimeter_energy(calorimeter_energy_in);
  }
  // Destructor
  ~CalorimeterParticles(){}
  // Copy constructor
  CalorimeterParticles(const CalorimeterParticles&); // Deep copies an already existing particle
  // Assignment operator
  CalorimeterParticles& operator=(const CalorimeterParticles&); // Assigns a right hand value to a left hand variable using = operator
  // Move constructor
  CalorimeterParticles(CalorimeterParticles&&); // Moves a particle to a new particle and empties the original
  // Move assignment operator
  CalorimeterParticles& operator=(CalorimeterParticles&&); // Moves a particle to a new one by assignment
  
  // Getter functions (accessors) to individual elements of 4-momentum and other particle properties
  CalorimeterEnergy get_calorimeter_energy()const{return (*calorimeter_energy);}; // Returns Calorimeter Energy object

  // Setter functions, to change value of Calorimeter Energy 
  // Checks physical input so that energy of particle >= sum of calorimeter deposits
  void set_calorimeter_energy(const CalorimeterEnergy calorimeter_energy_new){calorimeter_energy = std::make_unique<CalorimeterEnergy>(check_energy_physical(calorimeter_energy_new));};

  void print_data() override; // Function to print info about a particle
  CalorimeterEnergy check_energy_physical(CalorimeterEnergy calorimeter_energy_check); // Check energy of particle >= calorimeter deposits
};

#endif