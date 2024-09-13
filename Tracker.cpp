/*PROJECT DETECTOR SIMULATION - Sophie Hannon 11/05/24
Tracker class code file, inherits from derived class of ChargedParticleDetector which inherits from the base  of Detector.
Includes copy constructor, assignment operator for deep copying, move constructor and move by assignment. 
Contains a function that prints the results of detection and a function which detects particles based on 
their charge. */

#include<iostream>
#include<string>
#include "Tracker.h"
#include "Detector.h"
#include "Particle.h"

// Copy constructor for deep copying
Tracker::Tracker(const Tracker &tracker_copy) : ChargedParticleDetector(tracker_copy){}

// Assigment operator for deep copying
Tracker & Tracker::operator=(const Tracker &tracker_copy)
{
  if(&tracker_copy == this) return *this; // Prevents self assigment
  ChargedParticleDetector::operator=(tracker_copy);
  return *this;
}

// Move constructor which moves a tracker to a new tracker and empties the original
Tracker::Tracker(Tracker&& tracker_move) : ChargedParticleDetector(tracker_move) {}

// Move by assigment swaps the existing tracker with the new one
Tracker & Tracker::operator=(Tracker&& tracker_move)
{
  if(&tracker_move == this) return *this; // Prevents self assigment
  ChargedParticleDetector::operator=(tracker_move);
  return *this;
}

//  Function to print information about particle detections
void Tracker::print_data()
{
  std::cout.precision(4); // 3 significant figures
  std::cout<<"\nThe Tracker has detected "<<number_event<<" particle(s):\n ";
  auto map_it = interacted_particles.begin();
  auto vect_it = true_energy_vect.begin();  //  Iterators to print values of map and vector simultaneously
  for (; map_it != interacted_particles.end() && vect_it != true_energy_vect.end(); ++map_it, ++vect_it) 
  {
    std::cout<<"\nID: "<<map_it->first<<" Energy: "<<map_it->second<<" GeV";
    std::cout<<"\nTrue energy = "<<*vect_it;
  }
  std::cout<<"\nTotal true energy = "<<total_energy_in<<" Gev.";
  std::cout<<"\nTotal detected energy = "<<event_energy<<" GeV.\n";
  interacted_particles.clear();
  set_event_energy(0);
  set_number_event(0);  // Reset counters for next detection 
  return;
}

//  Function to detect particles, if neutral, not detected. If they have charge they will be detecetd if they interact with at least 2 layers.
void Tracker::is_detected(std::shared_ptr<Particle> test_particle)
{
  if(test_particle->get_particle_charge() == 0)
  {
    set_layer_1(0);
    set_layer_2(0);  //  If neutral, returns no detection since tracker won't see
    set_layer_3(0);
    set_event_energy(0);
    return;
  }  
  else
  {
    set_layer_1(1);
    set_layer_2(1);  //  If charged particle, detected by tracker so set layer bools to detected
    set_layer_3(1);
    int has_interacted;
    for(int i{0}; i < 3; i++) has_interacted += charged_particle_detector_layers[i];  //  Sum has interacted bools 
    if(has_interacted >= 2)  //  If >2 layers interacted, particle detected
    {
      double particle_energy{test_particle->get_particle_energy()};
      energy_detected += particle_energy;  //  Add energy to sum of energy detected, event energy and the total energy entering tracker
      event_energy += particle_energy;
      total_energy_in += particle_energy;
      true_energy_vect.push_back(particle_energy);
      interacted_particles.insert(std::pair<int, double>(test_particle->get_particle_identifier(), test_particle->get_particle_energy()));  //  Add particle ID and energy to map
      number_detected += 1;  //  Add one to counter
      number_event += 1;
    }
    else return; 
  }
}