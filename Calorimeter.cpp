/* PROJECT DETECTOR SIMULATION - Sophie Hannon 11/05/24
Calorimeter derived class code file, inherits from base Detector. Includes copy constructor, assignment operator for deep copying, move constructor and 
move by assignment. Contains a function that prints the results of detection and a function which detects particles based on 
the CalorimeterEnergy components. */

#include<iostream>
#include<string>
#include "Calorimeter.h"
#include "Detector.h"
#include "Particle.h"

// Copy constructor for deep copying
Calorimeter::Calorimeter(const Calorimeter &calorimeter_copy) : Detector(calorimeter_copy) // Uses copy constructor from base class
{
  calorimeter_energy_detected = std::make_unique<CalorimeterEnergy>(*(calorimeter_copy.calorimeter_energy_detected)); // Copy data members from old Calorimeter to new Calorimeter
}

// Assigment operator for deep copying
Calorimeter & Calorimeter::operator=(const Calorimeter &calorimeter_copy)
{
  if(&calorimeter_copy == this) return *this; // Prevents self assigment
  Detector::operator=(calorimeter_copy);  // Base class assignment operator
  // Reassign values with copy
  *calorimeter_energy_detected = calorimeter_copy.get_calorimeter_energy_detected(); // Reassign the copied Calorimeter data member to new Calorimeter
  return *this;    
}

// Move constructor which moves a Calorimeter to a new Calorimeter and empties the original
Calorimeter::Calorimeter(Calorimeter&& calorimeter_move) : Detector(calorimeter_move)
{
  *calorimeter_energy_detected = calorimeter_move.get_calorimeter_energy_detected(); // Get Calorimeter to be moved data members
  // Empty initial Calorimeter
  calorimeter_energy_detected->set_em_1(0);
  calorimeter_energy_detected->set_em_2(0);
  calorimeter_energy_detected->set_had_1(0);
  calorimeter_energy_detected->set_had_2(0);  // Clear out old Calorimeter that was moved
}

// Move by assigment swaps the existing Calorimeter with the new one
Calorimeter & Calorimeter::operator=(Calorimeter&& calorimeter_move)
{
  if(&calorimeter_move == this) return *this; // Prevents self assigment
  Detector::operator=(calorimeter_move);
  // Reassign values with copy
  *calorimeter_energy_detected = calorimeter_move.get_calorimeter_energy_detected();  // Reassign Calorimeter that was moved 
  return *this;
}

//  Function that prints information about Calorimeter subdetector, overridden from base class
void Calorimeter::print_data()
{
  std::cout.precision(4); // 3 significant figures
  std::cout<<"\n\nThe Calorimeter has detected "<<number_event<<" particle(s). These are:\n ";
  auto map_it = interacted_particles.begin();
  auto vect_it = calorimeter_energy_detected_vector.begin();  //  Iterators to loop through the map and vectors with data calorimeter has detected
  auto true_it = true_calorimeter_energy.begin();
  for (; map_it != interacted_particles.end() && vect_it != calorimeter_energy_detected_vector.end() && true_it != true_calorimeter_energy.end(); ++map_it, ++vect_it, ++true_it) 
  {
    std::cout << "ID: " << map_it->first << " Energy: " << map_it->second << " GeV";
    std::cout<<"\nTrue energy : ";
    true_it->print_data_calorimeter_energy(); // Prints true energy
    std::cout<<"\nDetected: ";
    vect_it->print_data_calorimeter_energy();  // Prints detected energy
    std::cout<<"\n";
  }
  std::cout<<"Total true energy = "<<true_energy<<" GeV.\n";
  std::cout<<"Total energy detected = "<<event_energy<<" GeV.\n";
  calorimeter_energy_detected_vector.clear();
  set_number_event(0);
  set_event_energy(0);
  set_true_energy(0);
  interacted_particles.clear();
  true_calorimeter_energy.clear();
  calorimeter_energy_detected->set_em_1(0);  // Resets counters to zero after information has been printed
  calorimeter_energy_detected->set_em_2(0);
  calorimeter_energy_detected->set_had_1(0);
  calorimeter_energy_detected->set_had_2(0);
  return;
}

//  Function that detects particles. First tries to dynamically cast the pointer to a pointer of type CalorimeterParticles, these particles
//  have the property of calorimeter energy so will be detected by the Calorimter.
void Calorimeter::is_detected(std::shared_ptr<Particle> test_particle) 
{
  ++number_in;  // Adds one to counter for all particles entering the complete detector
  if(std::dynamic_pointer_cast<CalorimeterParticles>(test_particle) == nullptr)  //  If particle does not have Calorimeter type it will return a nullptr 
  {
    calorimeter_energy_detected->set_em_1(0);
    calorimeter_energy_detected->set_em_2(0);  
    calorimeter_energy_detected->set_had_1(0);  //  The Calorimeter energy detected will be zero
    calorimeter_energy_detected->set_had_2(0); 
    return;
  }
  //  Now cast to a particle with a CalorimterEnergy object to be detected
  std::shared_ptr<CalorimeterParticles> calorimeter_particle_ptr = std::dynamic_pointer_cast<CalorimeterParticles>(test_particle);
  CalorimeterEnergy test_calorimeter_energy{calorimeter_particle_ptr->get_calorimeter_energy()};
  true_calorimeter_energy.push_back(test_calorimeter_energy);  //  Energy straight from particle is true energy
  double true_particle_energy{test_particle->get_particle_energy()};
  true_energy += true_particle_energy;
  total_energy_in += true_particle_energy;
  calorimeter_energy_detected->set_em_1(test_calorimeter_energy.get_em_1());
  calorimeter_energy_detected->set_em_2(test_calorimeter_energy.get_em_2());  //  Set layers of calorimeter to energy detected
  calorimeter_energy_detected->set_had_1(test_calorimeter_energy.get_had_1());
  calorimeter_energy_detected->set_had_2(test_calorimeter_energy.get_had_2());
  double particle_energy{calorimeter_energy_detected->four_vector_sum()};  //  Add energy to sum of energy detected, event energy and the total energy entering calorimeter
  energy_detected += particle_energy;
  event_energy += particle_energy;
  interacted_particles.insert(std::make_pair(calorimeter_particle_ptr->get_particle_identifier(), test_particle->get_particle_energy()));  //  Add particle ID and total energy to a map
  calorimeter_energy_detected_vector.push_back(calorimeter_particle_ptr->get_calorimeter_energy());  //  Add calorimter to a vector to be stored
  ++number_detected;
  ++number_event;  //  Add one to counters since we have detecetd a particle
}