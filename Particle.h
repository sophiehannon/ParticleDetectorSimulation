/*PROJECT DETECTOR SIMULATION - Sophie Hannon 11/05/24
Particle base class header file, includes copy constructor, assignment operator 
for deep copying, move constructor and move by assignment. Function checks the energy of 
particle > sum of calorimeter energy components. */

#ifndef PARTICLE_H
#define PARTICLE_H

#include<iostream>
#include<string>
#include<cmath>
#include<vector>
#include<memory>

class Particle
{
protected:
  int particle_identifier; 
  int charge;
  double energy;

public:
  Particle()=default; // Default constructor
  // Parameterised constructor:
  Particle(int particle_identifier_in, int charge_in, double energy_in):
  charge{charge_in} 
  {
    set_particle_identifier(particle_identifier_in);
    set_particle_energy(check_particle_energy_valid(energy_in));
  }
  ~Particle(){} // Destructor

  // Copy constructor
  Particle(const Particle&); // Deep copies an already existing particle
  // Assignment operator
  Particle& operator=(const Particle&); // Assigns a right hand value to a left hand variable using = operator
  // Move constructor
  Particle(Particle&&); // Moves a particle to a new particle and empties the original
  // Move assignment operator
  Particle& operator=(Particle&&); // Moves a particle to a new one by assignment
  

  // Getter functions (accessors) to get data of objects
  int get_particle_identifier()const{return particle_identifier;};
  int get_particle_charge()const{return charge;};
  double get_particle_energy()const{return energy;};

  // Setter functions to set object data members
  // No charge setter since charge is an intrinsic property so cannot be changed
  void set_particle_identifier(const int particle_identifier_new){particle_identifier = particle_identifier_new;};
  void set_particle_energy(const double energy_new){energy = energy_new;};

  virtual void print_data()=0;
  double check_particle_energy_valid(double test_energy); // Checks energy validity, energy must be positive
  void particle_to_antiparticle()const{charge*-1;}; // Function to convert between particles and antiparticles
  void particle_properties();
};

#endif