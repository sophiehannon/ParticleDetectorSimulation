/*PROJECT DETECTOR SIMULATION - Sophie Hannon 11/05/24
ChargedParticleDetector base class code file, includes copy constructor, assignment operator for deep copying, move constructor and 
move by assignment. */

#include<iostream>
#include<string>
#include "ChargedParticleDetector.h"
#include "Detector.h"
#include "Particle.h"

// Copy constructor for deep copying
ChargedParticleDetector::ChargedParticleDetector(const ChargedParticleDetector &detector_copy)
{
  charged_particle_detector_layers = detector_copy.charged_particle_detector_layers;
}

// Assigment operator for deep copying
ChargedParticleDetector & ChargedParticleDetector::operator=(const ChargedParticleDetector &detector_copy)
{
  if(&detector_copy == this) return *this; // Prevents self assigment
  // Reassign values with copy
  charged_particle_detector_layers[0] = detector_copy.get_layer_1();
  charged_particle_detector_layers[1] = detector_copy.get_layer_2();  // Reassign the copied detector data member to new detector
  return *this;    
}

// Move constructor which moves a detector to a new detector and empties the original
ChargedParticleDetector::ChargedParticleDetector(ChargedParticleDetector&& detector_move)
{
  charged_particle_detector_layers[0] = detector_move.charged_particle_detector_layers[0];
  charged_particle_detector_layers[1] = detector_move.charged_particle_detector_layers[1];  // Get detector to be moved data members
  // Empty initial ChargedParticleDetector
  detector_move.charged_particle_detector_layers[0] = 0;
  detector_move.charged_particle_detector_layers[1] = 0;  // Clear out old detector that was moved

}

// Move by assigment swaps the existing detector with the new one
ChargedParticleDetector & ChargedParticleDetector::operator=(ChargedParticleDetector&& detector_move)
{
  // Reassign values with copy
  charged_particle_detector_layers[0] = detector_move.get_layer_1();
  charged_particle_detector_layers[1] = detector_move.get_layer_2();  // Reassign detector that was moved 
  return *this;
}