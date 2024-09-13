/*PROJECT DETECTOR SIMULATION - Sophie Hannon 11/05/24
MuonDetector class code file, inherits from derived class of ChargedParticleDetector which inherits from the base  of Detector. Includes 
copy constructor, assignment operator for deep copying, move constructor and move by assignment. Contains a function that prints the 
results of detection and a function which detects particles if they are muons. */

#include<iostream>
#include<string>
#include "MuonDetector.h"
#include "Detector.h"
#include "Particle.h"

// Copy constructor for deep copying
MuonDetector::MuonDetector(const MuonDetector &detector_copy) : ChargedParticleDetector{detector_copy} {}

// Assigment operator for deep copying
MuonDetector & MuonDetector::operator=(const MuonDetector &detector_copy)
{
  if(&detector_copy == this) return *this; // Prevents self assigment
  ChargedParticleDetector::operator=(detector_copy);
  return *this;   
}

// Move constructor which moves a MuonDetector to a new MuonDetector and empties the original
MuonDetector::MuonDetector(MuonDetector&& detector_move) : ChargedParticleDetector(detector_move) {}

// Move by assigment swaps the existing MuonDetector with the new one
MuonDetector & MuonDetector::operator=(MuonDetector&& detector_move)
{
  if(&detector_move == this) return *this; // Prevents self assigment
  ChargedParticleDetector::operator=(detector_move);
  return *this;
}

// Function to print information about muon detections, overriden from base class Detector
void MuonDetector::print_data()
{
  std::cout.precision(4); // 3 significant figures
  std::cout<<"\nThe Muon detector has detected "<<number_event<<" particle(s):\n ";
  auto map_it = interacted_particles.begin();
  auto vect_it = true_energy_vect.begin();  //  Iterators to print the information about the map and vector simultaneously
  for (; map_it != interacted_particles.end() && vect_it != true_energy_vect.end(); ++map_it, ++vect_it) 
  {
    std::cout<<"ID: "<<map_it->first<<" Energy: "<<map_it->second<<" GeV\n";
    std::cout<<"True energy = "<<*vect_it;
  }
  std::cout<<"\nTotal true energy = "<<total_energy_in<<" GeV.";
  std::cout<<"\nTotal energy detected = "<<energy_detected<<" GeV.";
  interacted_particles.clear();
  set_event_energy(0);
  set_number_event(0);  // Set counters to zero for next event
  set_true_energy(0);
  return;
}

//  Function to detect muons, is overriden from bas class Detector
void MuonDetector::is_detected(std::shared_ptr<Particle> test_particle)
{
  if(std::dynamic_pointer_cast<Muon>(test_particle) == nullptr)  //  If not a muon, this will cast to a nullptr so no detection
  {
    set_event_energy(0);  //  No energy detected
    return;
  } 
  std::shared_ptr<Muon> muon_ptr = std::dynamic_pointer_cast<Muon>(test_particle);  //  Cast to a muon so we can access layers
  set_layer_1(muon_ptr->get_inner_layer());
  set_layer_2(muon_ptr->get_outer_layer());  //  Use muon's layers to set detector layers
  int has_interacted;
  for(int i{0}; i < 3; i++) has_interacted += charged_particle_detector_layers[i]; // Sum has interacted bools 
  if(has_interacted>=1) // If >1 layers interacted, particle detected
  {
    double particle_energy{muon_ptr->get_particle_energy()};
    energy_detected += particle_energy;  // Add energy to sum of energy detected and event energy
    event_energy += particle_energy;
    true_energy_vect.push_back(particle_energy);  //  Store true energy in a vector
    total_energy_in += particle_energy;
    interacted_particles.insert(std::make_pair(muon_ptr->get_particle_identifier(), muon_ptr->get_particle_energy()));  // Add particle ID and energy to map
    number_detected += 1; // Add one to counter
    number_event += 1;
  }
  return;
}

