/*PROJECT DETECTOR SIMULATION - Sophie Hannon 11/05/24
Neutrino derived class code file, inherits from particle class includes copy constructor, assignment operator 
for deep copying, move constructor and move by assignment. */

#include<iostream>
#include<string>
#include "Particle.h"
#include "Neutrino.h"

// Copy constructor for deep copying
Neutrino::Neutrino(const Neutrino &particle_copy) : Particle(particle_copy)
{
  flavour = particle_copy.get_flavour();
  *has_interacted_neutrino = particle_copy.get_has_interacted_neutrino();  // Copy the flavour and interacted vector from the old neutrino
}

// Assigment operator for deep copying
Neutrino & Neutrino::operator=(const Neutrino &particle_copy)
{
  if(&particle_copy == this) return *this; // Prevents self assigment
  Particle::operator=(particle_copy);
  flavour = particle_copy.get_flavour();
  *has_interacted_neutrino = particle_copy.get_has_interacted_neutrino();  // Reassign the flavour and interacted vector from the old neutrino
  return *this;    
}

// Move constructor which moves a particle to a new particle and empties the original
Neutrino::Neutrino(Neutrino&& particle_move) : Particle(particle_move)
{
  flavour = particle_move.get_flavour();
  *has_interacted_neutrino = particle_move.get_has_interacted_neutrino();
  particle_move.has_interacted_neutrino = nullptr;  // Empty initial particle
}

// Print data function
void Neutrino::print_data()
{
  std::cout.precision(3); // 2 significant figures
  std::cout<<"\n Neutrino ("<<flavour<<") ";
  particle_properties();
  return;
}
