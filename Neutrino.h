/*PROJECT DETECTOR SIMULATION - Sophie Hannon 11/05/24
Neutrino derived class header file, inherits from particle class includes copy constructor, assignment operator 
for deep copying, move constructor and move by assignment. Function checks the energy of 
particle > sum of calorimeter energy components. */

#ifndef NEUTRINO_H
#define NEUTRINO_H

#include<iostream>
#include<string>
#include<cmath>
#include<vector>
#include<memory>
#include "Particle.h"
#include "RandomGenerators.h"

class Neutrino : public Particle
{
private: 
std::string flavour;
std::unique_ptr<bool> has_interacted_neutrino; // Makes pointer to a bool of Neutrino chamber interactions

public:
  // Constructors
  // Default constructor
  Neutrino() {} 
  // Parameterized constructor, uses setters to assign values and push back values into four momentum
  Neutrino(int particle_identifier_in, int charge_in, double energy_in, std::string flavour_in, bool has_interacted_neutrino_in) :
  Particle{particle_identifier_in, charge_in, energy_in}
  {
    set_flavour(flavour_in);
    set_has_interacted_neutrino(has_interacted_neutrino_in);  // Use setters to assign input values
  }
  // Destructor
  ~Neutrino(){} // Deletes dynamically allocated vector
  // Copy constructor
  Neutrino(const Neutrino&); // Deep copies an already existing particle
  // Assignment operator
  Neutrino& operator=(const Neutrino&); // Assigns a right hand value to a left hand variable using = operator
  // Move constructor
  Neutrino(Neutrino&&); // Moves a particle to a new particle and empties the original
  // Move assignment operator
  Neutrino& operator=(Neutrino&&); // Moves a particle to a new one by assignment
  
  // Getter functions (accessors) to flavour and interacted vector
  std::string get_flavour()const{return flavour;};
  bool get_has_interacted_neutrino()const{return *has_interacted_neutrino;};

  // Setter functions, to change values of flavour and interacted vector 
  void set_flavour(const std::string flavour_new){flavour = flavour_new;};
  void set_has_interacted_neutrino(const bool has_interacted_new){has_interacted_neutrino = std::make_unique<bool>(has_interacted_new);};

  void print_data() override; // Function to print info about a particle

};

#endif