/*PROJECT DETECTOR SIMULATION - Sophie Hannon 11/05/24
Tau derived class code file, inherits from particle class includes copy constructor, assignment operator 
for deep copying, move constructor and move by assignment. Functions checks the energy of 
particle > sum of calorimeter energy components and create a vector of shared pointers of decay products. */

#include<iostream>
#include<string>
#include "Particle.h"
#include "Tau.h"
#include "CalorimeterEnergy.h"
#include "Neutrino.h"
#include "CalorimeterParticles.h"
#include "Muon.h"
#include "RandomGenerators.h"
#include "EmDeposits.h"

// Copy constructor for deep copying
Tau::Tau(const Tau &particle_copy) : Particle(particle_copy)
{
  hadronic_decay = particle_copy.get_hadronic_decay();
  leptonic_decay = particle_copy.get_hadronic_decay();
  decay_products = particle_copy.get_decay_products();
}

// Assigment operator for deep copying
Tau & Tau::operator=(const Tau &particle_copy)
{
  if(&particle_copy == this) return *this; // Prevents self assigment
  // Reassign values with copy
  Particle::operator=(particle_copy);
  hadronic_decay = particle_copy.get_hadronic_decay();
  leptonic_decay = particle_copy.get_hadronic_decay();
  decay_products = particle_copy.get_decay_products();
  return *this;    
}

// Move constructor which moves a particle to a new particle and empties the original
Tau::Tau(Tau&& particle_move) : Particle(particle_move)
{
  hadronic_decay = particle_move.get_hadronic_decay();
  leptonic_decay = particle_move.get_hadronic_decay();
  decay_products = particle_move.get_decay_products();
  // Empty initial particle
  particle_move.hadronic_decay = 0;
  particle_move.leptonic_decay = 0;
  particle_move.decay_products[0] = nullptr;
  particle_move.decay_products[1] = nullptr;
  if(decay_products.size() == 2) particle_move.decay_products[2] = nullptr;
  
}

// Print data function
void Tau::print_data()
{
  std::cout.precision(3); // 2 significant figures
  if(charge == -1) std::cout<<"\nTau properties: ";
  if(charge == 1) std::cout<<"\nAntitau properties: ";
  particle_properties();
  std::cout<<"The decay type was";
  if(leptonic_decay == 1) std::cout<<" leptonic ";
  if(hadronic_decay == 1) std::cout<<" hadronic ";
  if(hadronic_decay == 0 && leptonic_decay == 0) std::cout<<"void.\n";
  std::cout<<"and it decayed into the following particles:";
  for(auto particle_it=decay_products.begin(); particle_it<decay_products.end(); ++particle_it) (*particle_it)->print_data(); 
}


std::vector<std::shared_ptr<Particle>> Tau::make_decay_products(bool hadronic_decay_input, bool leptonic_decay_input) const
{
  std::vector<std::shared_ptr<Particle>> decay_product_vector;  // Vector to store decay products
  std::vector<double> energy_proportions_4{random_probability_generator(4)}; // Random splitting 4 ways
  std::vector<double> energy_proportions_3{random_probability_generator(3)}; // Random splitting three ways
  std::vector<double> energy_proportions_2{random_probability_generator(2)}; // Random splitting two ways
  int tau_id{get_particle_identifier()};

  if(leptonic_decay_input == 1)  //  Leptonic decay
  {
    std::shared_ptr<Neutrino> tau_neutrino_product = std::make_shared<Neutrino>(tau_id, 0, (energy*energy_proportions_3[0]), "tau", 0); // Create a tau neutrino with random proportion of tau energy
    if(charge == -1) decay_product_vector.push_back(tau_neutrino_product); // Taus always decay into a tau neutrino to conserve lepton number
    tau_neutrino_product->set_flavour("antitau");
    if(charge == 1) decay_product_vector.push_back(tau_neutrino_product); // Or an anitau neutrino if an antitau

    double lepton_energy{energy_proportions_3[1]*energy}; // Total energy for electron or muon decay product
    std::shared_ptr<CalorimeterParticles> electron_product = std::make_shared<EmDeposits>((tau_id + 1),-1, lepton_energy); // Initialize electron object
    std::shared_ptr<Neutrino> neutrino_product = std::make_shared<Neutrino>((tau_id + 2), 0, energy*energy_proportions_3[2], "electron", 0); // Initialize electron neutrino
    std::shared_ptr<Muon> muon = std::make_shared<Muon>(1, 1, lepton_energy);  //  Initialize Muon decay product
    if(charge == -1 && 0.5 > energy_proportions_2[0]) // Electron type decay chain from a tau, probability found from branching ratio
    {
      decay_product_vector.push_back(electron_product); // Electron decay product
      neutrino_product->set_flavour("antielectron");    // Change an electron neutrino to an antielectron neutrino
      decay_product_vector.push_back(neutrino_product); // Antielectron neutrino decay product
      return decay_product_vector;
    }
    if(charge == 1 && 0.5 > energy_proportions_2[0]) // Electron type decay chain from an antitau
    {
      electron_product->particle_to_antiparticle(); // Change an electron into a positron
      decay_product_vector.push_back(electron_product); // Positron decay product
      neutrino_product->set_flavour("electron"); // Change neutrino to an electron neutrino to conserve lepton number
      decay_product_vector.push_back(neutrino_product); // Electron neutrino decay product
      return decay_product_vector;
    }
    if(charge == -1 && 0.5 > energy_proportions_2[1]) // Muon decay chain from a tau
    {
      decay_product_vector.push_back(muon);  //  Muon decay product
      neutrino_product->set_flavour("antimuon"); // Change a muon neutrino to an antimuon neutrino
      decay_product_vector.push_back(neutrino_product);  //  Antimuon neutrino decay product
      return decay_product_vector;
    }
    if(charge == 1 && 0.5 > energy_proportions_2[1]) // Muon decay chain from an antitau
    {
      muon->particle_to_antiparticle(); // Change a muon into an antimuon
      decay_product_vector.push_back(muon); // Antimuon decay product
      neutrino_product->set_flavour("antimuon"); // Change neutrino to antimuon to conserve lepton number
      decay_product_vector.push_back(neutrino_product); // Antimuon neutrino decay product
      return decay_product_vector;
    }
  }
  
  // Make tau neutrino with the correct energy proportions for hadronic decay
  std::shared_ptr<Neutrino> tau_neutrino_product = std::make_shared<Neutrino>(tau_id, 0, (energy*energy_proportions_2[0]), "tau", 0); // Create a tau neutrino with random proportion of tau energy
  if(charge == -1) decay_product_vector.push_back(tau_neutrino_product); // Taus always decay into a tau neutrino to conserve lepton number
  tau_neutrino_product->set_flavour("antitau");
  if(charge == 1) decay_product_vector.push_back(tau_neutrino_product); // Or an anitau neutrino if an antitau
  double hadron_energy{energy_proportions_2[1]*energy};
  //CalorimeterEnergy hadron_energy_vector(hadron_energy*energy_proportions_4[0], hadron_energy*energy_proportions_4[1],hadron_energy*energy_proportions_4[2],hadron_energy*energy_proportions_4[3]);
  if(hadronic_decay_input == 1 )  // Since decay products act like protons, decay product of proton
  {
    std::shared_ptr<CalorimeterParticles> proton = std::make_shared<CalorimeterParticles>((tau_id + 1), 1, hadron_energy); // Proton decay product
    decay_product_vector.push_back(proton);
  }
  return decay_product_vector;  
}
