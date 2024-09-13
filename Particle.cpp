/*PROJECT DETECTOR SIMULATION - Sophie Hannon 11/05/24
Particle base class code file, includes copy constructor, assignment operator for deep copying, move constructor and 
move by assignment. Function checks the energy of particle > 0. */

#include<iostream>
#include<string>
#include "Particle.h"
#include "CalorimeterEnergy.h"

// Copy constructor for deep copying
Particle::Particle(const Particle &particle_copy)
{
  std::cout<<"Calling Particle copy constructor\n"; 
  particle_identifier = particle_copy.get_particle_identifier();
  charge = particle_copy.get_particle_charge();  // Copy data members from old particle to new particle
  energy = particle_copy.get_particle_energy();
}

// Assigment operator for deep copying
Particle & Particle::operator=(const Particle &particle_copy)
{
  if(&particle_copy == this) return *this; // Prevents self assigment
  std::cout<<"Calling Particle assignment operator\n";
  // Reassign values with copy
  particle_identifier = particle_copy.get_particle_identifier();
  charge = particle_copy.get_particle_charge(); // Reassign the copied particle data member to new particle
  energy = particle_copy.get_particle_energy();
  return *this;    
}

// Move constructor which moves a particle to a new particle and empties the original
Particle::Particle(Particle&& particle_move)
{
  std::cout<<"Calling Particle move constructor\n";
  particle_identifier = particle_move.particle_identifier;
  charge = particle_move.charge; // Get particle to be moved data members
  energy = particle_move.energy;
  // Empty initial particle
  particle_move.particle_identifier = 0;
  particle_move.charge = 0;  // Clear out old particle that was moved
  particle_move.energy = 0;
}

// Move by assigment swaps the existing particle with the new one
Particle & Particle::operator=(Particle&& particle_move)
{
  std::cout<<"Calling Particle move by assignment operator\n";
  // Reassign values with copy
  particle_identifier = particle_move.get_particle_identifier();
  charge = particle_move.get_particle_charge(); // Reassign particle that was moved 
  energy = particle_move.get_particle_energy();
  return *this;
}

// Checks physical validity of energy 
double Particle::check_particle_energy_valid(double test_energy)
{      
  if(test_energy > 0) return test_energy; 
  else throw test_energy; // If unphysical, throws the exception to be caught in main
}

void Particle::particle_properties()
{
  std::cout<<": [identifier, q, true energy(GeV)] = [";
  std::cout<<particle_identifier<<", "<<charge<<", "<<energy<<"]";
}