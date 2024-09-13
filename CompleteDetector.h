/*PROJECT DETECTOR SIMULATION - Sophie Hannon 11/05/24
CompleterDetector header file. 
Data members: vector of the subdetectors
              vector of strings to particle types
              double of invisible energy
              int counter for correctly identified
Functions:    find_particle_type - finds the particle type based on detections
              print_event_results - prints information for an event
              find_invisible_energy - finds invisble enrgy in each event
              print_summary - prints a summary of detections */

#ifndef COMPLETEDETECTOR_H
#define COMPLETEDETECTOR_H

#include<iostream>
#include<string>
#include<cmath>
#include<vector>
#include<list>
#include<memory>
#include "Detector.h"
#include "Calorimeter.h"
#include "Tracker.h"
#include "MuonDetector.h"
#include "Particle.h"


class CompleteDetector 
{
private: 
std::vector<std::shared_ptr<Detector>> complete_detector;
std::vector<std::string> particle_types;
double invisible_energy{0};
int correctly_identified{0};

public:
  // Constructors
  // Default constructor
  CompleteDetector() {} 
  CompleteDetector(Calorimeter calorimeter_in, Tracker tracker_in, MuonDetector muon_detector_in) 
  {
    complete_detector.push_back(std::make_shared<Calorimeter>(calorimeter_in));
    complete_detector.push_back(std::make_shared<Tracker>(tracker_in));
    complete_detector.push_back(std::make_shared<MuonDetector>(muon_detector_in));
  }
  // Destructor
  ~CompleteDetector(){} 
  // Copy constructor
  CompleteDetector(const CompleteDetector&); // Deep copies an already existing CompleteDetector
  // Assignment operator
  CompleteDetector& operator=(const CompleteDetector&); // Assigns a right hand value to a left hand variable using = operator
  // Move constructor
  CompleteDetector(CompleteDetector&&); // Moves a CompleteDetector to a new CompleteDetector and empties the original
  // Move assignment operator
  CompleteDetector& operator=(CompleteDetector&&); // Moves a CompleteDetector to a new one by assignment
  
  // Getter functions (accessors) to layer 3 of CompleteDetector
  Calorimeter get_calorimeter()const{return *(std::dynamic_pointer_cast<Calorimeter>(complete_detector[0]));};
  Tracker get_tracker()const{return *(std::dynamic_pointer_cast<Tracker>(complete_detector[1]));};
  MuonDetector get_muon_detector()const{return *(std::dynamic_pointer_cast<MuonDetector>(complete_detector[2]));};
  std::vector<std::shared_ptr<Detector>> get_detector_vector()const{return complete_detector;};
  double get_invisible_energy()const{return invisible_energy;};
  int get_correctly_identified()const{return correctly_identified;};

  // Setter functions, to change detectors
  void set_calorimeter(const Calorimeter calorimeter_new){complete_detector[0] = std::make_shared<Calorimeter>(calorimeter_new);};
  void set_tracker(const Tracker tracker_new){complete_detector[1] = std::make_shared<Tracker>(tracker_new);};
  void set_muon_detector(const MuonDetector muon_detector_new){complete_detector[2] = std::make_shared<MuonDetector>(muon_detector_new);};
  void set_invisible_energy(const double invisible_energy_new){invisible_energy = invisible_energy_new;};

  void find_particle_type(std::shared_ptr<Particle> particle);  //  Finds particle type based on detection results
  void print_event_results(std::vector<std::shared_ptr<Particle>> event_vector);  //  Prints results of detections
  void find_invisible_energy(std::vector<std::shared_ptr<Particle>> event_vector);  //  Finds invisible enrgy from an eevnt
  void print_summary();  //  Prints a summary of all the detections
};

#endif