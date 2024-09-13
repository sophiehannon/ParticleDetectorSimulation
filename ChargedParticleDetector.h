/*PROJECT DETECTOR SIMULATION - Sophie Hannon 11/05/24
ChargedParticleDetector header file, inherits from the detector abstract base class.
data member of a vector of bools to the charged particle layers.
Interface for the tracker and muon detector,*/

#ifndef CHARGEDPARTICLEDETECTOR_H
#define CHARGEDPARTICLEDETECTOR_H

#include<iostream>
#include<string>
#include<cmath>
#include<vector>
#include<list>
#include<memory>
#include "Detector.h"
#include "Particle.h"

class ChargedParticleDetector : public Detector
{
protected: 
std::vector<bool> charged_particle_detector_layers;

public:
  // Constructors
  // Default constructor
  ChargedParticleDetector() {} 
  ChargedParticleDetector(bool layer_1_in, bool layer_2_in) 
  {
    charged_particle_detector_layers.push_back(layer_1_in);
    charged_particle_detector_layers.push_back(layer_2_in);
  }
  // Destructor
  ~ChargedParticleDetector(){} 
  // Copy constructor
  ChargedParticleDetector(const ChargedParticleDetector&); // Deep copies an already existing particle
  // Assignment operator
  ChargedParticleDetector& operator=(const ChargedParticleDetector&); // Assigns a right hand value to a left hand variable using = operator
  // Move constructor
  ChargedParticleDetector(ChargedParticleDetector&&); // Moves a detector to a new detector and empties the original
  // Move assignment operator
  ChargedParticleDetector& operator=(ChargedParticleDetector&&); // Moves a detector to a new one by assignment
  
  // Getter functions (accessors) to idetector layers
  bool get_layer_1()const{return charged_particle_detector_layers[0];};
  bool get_layer_2()const{return charged_particle_detector_layers[1];};

  // Setter functions, to change values of detector layers
  void set_layer_1(const bool layer_1_new){charged_particle_detector_layers[0] = layer_1_new;};
  void set_layer_2(const bool layer_2_new){charged_particle_detector_layers[1] = layer_2_new;};
};

#endif