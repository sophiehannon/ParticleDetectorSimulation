/*PROJECT DETECTOR SIMULATION - Sophie Hannon 11/05/24
Tracker class header file, inherits from derived class of ChargedParticleDetector which inherits from the base  of Detector.
Data members: no extra members but parameterized constructor adds another layer to the vector of bools acting as the layers of the detector
Functions: is_detected - detects particles using particle charge
           print_data - prints information about the detector */

#ifndef TRACKER_H
#define TRACKER_H

#include<iostream>
#include<string>
#include<cmath>
#include<vector>
#include<list>
#include<memory>
#include "Detector.h"
#include "Particle.h"
#include "ChargedParticleDetector.h"


class Tracker : public ChargedParticleDetector
{
public:
  // Constructors
  // Default constructor
  Tracker() {} 
  Tracker(bool layer_1_in, bool layer_2_in, bool layer_3_in) :
  ChargedParticleDetector{layer_1_in, layer_2_in}
  {
    charged_particle_detector_layers.push_back(layer_3_in);
  }
  // Destructor
  ~Tracker(){} 
  // Copy constructor
  Tracker(const Tracker&); // Deep copies an already existing tracker
  // Assignment operator
  Tracker& operator=(const Tracker&); // Assigns a right hand value to a left hand variable using = operator
  // Move constructor
  Tracker(Tracker&&); // Moves a tracker to a new tracker and empties the original
  // Move assignment operator
  Tracker& operator=(Tracker&&); // Moves a tracker to a new one by assignment
  
  // Getter functions (accessors) to layer 3 of tracker
  bool get_layer_3()const{return charged_particle_detector_layers[0];};
  //int get_number_detected_tracker()const{return number_detected_tracker;};

  // Setter functions, to change value of layer 3
  void set_layer_3(const bool layer_3_new){charged_particle_detector_layers[2] = layer_3_new;};

  void is_detected(std::shared_ptr<Particle> test_particle) override;  //  Function detects particles based on their charge, overridden from Detector abse class
  
  void print_data() override; // Function to print info about a the tracker
};

#endif