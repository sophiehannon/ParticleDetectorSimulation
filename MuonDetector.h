/*PROJECT DETECTOR SIMULATION - Sophie Hannon 11/05/24
MuonDetector class header file, inherits from derived class of ChargedParticleDetector which inherits from the base  of Detector.
Data members: no new members
Functions: is_detected - detects particles if they are muons
           print_data - prints information about the detector */

#ifndef MUONDETECTOR_H
#define MUONDETECTOR_H

#include<iostream>
#include<string>
#include<cmath>
#include<vector>
#include<list>
#include<memory>
#include "Detector.h"
#include "Particle.h"
#include "Muon.h"
#include "ChargedParticleDetector.h"


class MuonDetector : public ChargedParticleDetector
{
private: 
//static int number_detected_muon_detector;

public:
  // Constructors
  // Default constructor
  MuonDetector() {} 
  MuonDetector(bool layer_1_in, bool layer_2_in) : ChargedParticleDetector{layer_1_in, layer_2_in} {}
  // Destructor
  ~MuonDetector(){}
  // Copy constructor
  MuonDetector(const MuonDetector&); // Deep copies an already existing muon detector
  // Assignment operator
  MuonDetector& operator=(const MuonDetector&); // Assigns a right hand value to a left hand variable using = operator
  // Move constructor
  MuonDetector(MuonDetector&&); // Moves a muon detector to a new muon detector and empties the original
  // Move assignment operator
  MuonDetector& operator=(MuonDetector&&); // Moves a muon detector to a new one by assignment

  void is_detected(std::shared_ptr<Particle> test_particle) override; //  Function that detects particles if muons, overridden from Detector abse class
  void print_data() override; // Function to print info about a the MuonDetector
};

#endif