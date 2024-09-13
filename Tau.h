/*PROJECT DETECTOR SIMULATION - Sophie Hannon 11/05/24
Tau derived class header file, inherits from particle class includes copy constructor, assignment operator 
for deep copying, move constructor and move by assignment. Function checks the energy of 
particle > sum of calorimeter energy components. */

#ifndef Tau_H
#define Tau_H

#include<iostream>
#include<string>
#include<cmath>
#include<vector>
#include<memory>
#include "Particle.h"
#include "CalorimeterEnergy.h"


class Tau : public Particle
{
private:
bool hadronic_decay;
bool leptonic_decay;
std::vector<std::shared_ptr<Particle>> decay_products;


public:
  // Constructors
  // Default constructor
  Tau() {} 
  // Parameterized constructor, uses setters to assign values and push back values into four momentum
  Tau(int particle_identifier_in, int charge_in, double energy_in, bool hadronic_decay_in, bool leptonic_decay_in) :
  Particle{particle_identifier_in, charge_in, energy_in}
  {
    set_hadronic_decay(hadronic_decay_in);
    set_leptonic_decay(leptonic_decay_in);  // Use setters to assign initial values to data members
    set_decay_products(make_decay_products(hadronic_decay_in, leptonic_decay_in));
  }
  // Destructor
  ~Tau(){} // Deletes dynamically allocated four-momenta
  // Copy constructor
  Tau(const Tau&); // Deep copies an already existing particle
  // Assignment operator
  Tau& operator=(const Tau&); // Assigns a right hand value to a left hand variable using = operator
  // Move constructor
  Tau(Tau&&); // Moves a particle to a new particle and empties the original
  // Move assignment operator
  Tau& operator=(Tau&&); // Moves a particle to a new one by assignment
  
  // Getter functions (accessors) to decay bools, decay type and decay products
  bool get_hadronic_decay()const{return hadronic_decay;};
  bool get_leptonic_decay()const{return leptonic_decay;};
  std::vector<std::shared_ptr<Particle>> get_decay_products()const{return decay_products;};

  // Setter functions, to change values of decay bools, decay type and decay product vector
  void set_hadronic_decay(const bool hadronic_decay_new){hadronic_decay = hadronic_decay_new;};
  void set_leptonic_decay(const bool leptonic_decay_new){leptonic_decay = leptonic_decay_new;};
  void set_decay_products(const std::vector<std::shared_ptr<Particle>> decay_products_new){decay_products = decay_products_new;};

  void print_data() override; // Function to print info about a particle
  std::vector<std::shared_ptr<Particle>> make_decay_products(bool hadronic_decay_input ,bool leptonic_decay_input) const;


};

#endif