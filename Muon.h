/*PROJECT DETECTOR SIMULATION - Sophie Hannon 11/05/24
Muon derived class header file, inherits from particle class includes copy constructor, assignment operator 
for deep copying, move constructor and move by assignment. Function prints muon info */

#ifndef MUON_H
#define MUON_H

#include<iostream>
#include<string>
#include<cmath>
#include<vector>
#include<memory>
#include "Particle.h"
#include "RandomGenerators.h"

class Muon : public Particle
{
private: 
std::vector<bool> has_interacted; // Makes vector of pointers to bools of muon chamber interactions

public:
  // Constructors
  // Default constructor
  Muon() {} 
  // Parameterized constructor, uses setters to assign values and push back values into four momentum
  Muon(int particle_identifier_in, int charge_in, double energy_in) :
  Particle{particle_identifier_in, charge_in, energy_in}
  {
    has_interacted.push_back(true);
    has_interacted.push_back(true);
  }
  // Destructor
  ~Muon(){} 
  // Copy constructor
  Muon(const Muon&); // Deep copies an already existing muon
  // Assignment operator
  Muon& operator=(const Muon&); // Assigns a right hand value to a left hand variable using = operator
  // Move constructor
  Muon(Muon&&); // Moves a muon to a new muon and empties the original
  // Move assignment operator
  Muon& operator=(Muon&&); // Moves a muon to a new one by assignment
  
  // Getter functions (accessors) to individual layers of muon detected vector
  bool get_inner_layer()const{return has_interacted[0];};
  bool get_outer_layer()const{return has_interacted[1];};

  // Setter functions, to change bool values of intearacted vector 
  void set_inner_layer(const bool inner_layer_new){has_interacted[0] = inner_layer_new;};
  void set_outer_layer(const bool outer_layer_new){has_interacted[1] = outer_layer_new;};

  void print_data() override; // Function to print info about a particle

};

#endif