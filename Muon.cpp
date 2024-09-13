/*PROJECT DETECTOR SIMULATION - Sophie Hannon 11/05/24
Muon derived class code file, inherits from particle class includes copy constructor, assignment operator 
for deep copying, move constructor and move by assignment. */

#include<iostream>
#include<string>
#include "Particle.h"
#include "Muon.h"

// Copy constructor for deep copying
Muon::Muon(const Muon &particle_copy) : Particle(particle_copy)
{
  has_interacted = particle_copy.has_interacted;  // Copy components of interacted vector from old muon
}

// Assigment operator for deep copying
Muon & Muon::operator=(const Muon &particle_copy)
{
  if(&particle_copy == this) return *this; // Prevents self assigment
  // Reassign values with copy
  Particle::operator=(particle_copy);
  has_interacted = particle_copy.has_interacted;  // Reassign components of interacted vector from old muon
  return *this;    
}

// Move constructor which moves a particle to a new particle and empties the original
Muon::Muon(Muon&& particle_move) : Particle(particle_move)
{
  has_interacted = particle_move.has_interacted; // Get components of interacted vector from muon to be moved
  has_interacted.clear();  // Empty initial particle
}

// Print data function
void Muon::print_data()
{
  std::cout.precision(3); // 2 significant figures
  if(charge == -1) std::cout<<"\nMuon properties: ";
  if(charge == 1) std::cout<<"\nAntimuon properties: ";
  particle_properties();
  return;
}






