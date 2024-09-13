/*PROJECT DETECTOR SIMULATION - Sophie Hannon 11/05/24
Detector base class code file, includes copy constructor, assignment operator for deep copying, move constructor and 
move by assignment. */

#include<iostream>
#include<string>
#include "Detector.h"
#include "Particle.h"

// Copy constructor for deep copying
Detector::Detector(const Detector &detector_copy)
{
  energy_detected = detector_copy.get_energy_detected();
  interacted_particles = detector_copy.get_interacted_particles();  // Copy data members from old detector to new detector
}

// Assigment operator for deep copying
Detector & Detector::operator=(const Detector &detector_copy)
{
  if(&detector_copy == this) return *this; // Prevents self assigment
  // Reassign values with copy
  energy_detected = detector_copy.get_energy_detected();
  interacted_particles = detector_copy.get_interacted_particles(); // Reassign the copied detector data member to new etector
  return *this;    
}

// Move constructor which moves a detector to a new detector and empties the original
Detector::Detector(Detector&& detector_move)
{
  energy_detected = detector_move.energy_detected;
  interacted_particles = detector_move.interacted_particles; // Get detector to be moved data members
  // Empty initial detector
  detector_move.energy_detected = 0;
  interacted_particles.clear(); // Clear out old detector that was moved
}

// Move by assigment swaps the existing detector with the new one
Detector & Detector::operator=(Detector&& detector_move)
{
  // Reassign values with copy
  energy_detected = detector_move.get_energy_detected();
  interacted_particles = detector_move.get_interacted_particles(); // Reassign detector that was moved 
  return *this;
}