/* PROJECT DETECTOR SIMULATION - Sophie Hannon 11/05/24
Calorimeter derived class header file, inherits from base Detector. 
Data members: unique ptr to CalrorimeterEnergy: calorimeter_energy_detected (for specific detections)
              vector of CalorimeterEnergy to store multiple particle's energies
              vector of true calorimeter energies
Functions: is_detected - detects particles using calorimeter energy properties
           print_data - prints information about the detector */

#ifndef CALORIMETER_H
#define CALORIMETER_H

#include<iostream>
#include<string>
#include<cmath>
#include<vector>
#include<list>
#include<memory>
#include "Detector.h"
#include "CalorimeterParticles.h"
#include "Particle.h"
#include "CalorimeterEnergy.h"
#include "Muon.h"
#include "Neutrino.h"
#include "EmDeposits.h"

class Calorimeter : public Detector
{
private: 
std::unique_ptr<CalorimeterEnergy> calorimeter_energy_detected;
std::vector<CalorimeterEnergy> calorimeter_energy_detected_vector;
std::vector<CalorimeterEnergy> true_calorimeter_energy;

public:
  // Constructors
  // Default constructor
  Calorimeter() {} 
  Calorimeter(CalorimeterEnergy calorimeter_energy_in) 
  {
    set_calorimeter_energy_detected(calorimeter_energy_in);
  }
  // Destructor
  ~Calorimeter(){} 
  // Copy constructor
  Calorimeter(const Calorimeter&); // Deep copies an already existing particle
  // Assignment operator
  Calorimeter& operator=(const Calorimeter&); // Assigns a right hand value to a left hand variable using = operator
  // Move constructor
  Calorimeter(Calorimeter&&); // Moves a particle to a new particle and empties the original
  // Move assignment operator
  Calorimeter& operator=(Calorimeter&&); // Moves a particle to a new one by assignment
  
  // Getter functions (accessors) to calorimeter energy data members
  CalorimeterEnergy get_calorimeter_energy_detected()const{return *calorimeter_energy_detected;};
  std::vector<CalorimeterEnergy> get_calorimeter_energy_detected_vector()const{return calorimeter_energy_detected_vector;};

  // Setter functions, to change values of data members 
  void set_calorimeter_energy_detected(const CalorimeterEnergy calorimeter_energy_detected_new){calorimeter_energy_detected = std::make_unique<CalorimeterEnergy>(calorimeter_energy_detected_new);};
  void set_calorimeter_energy_detected_vector(const std::vector<CalorimeterEnergy> calorimeter_energy_vector_new){calorimeter_energy_detected_vector = calorimeter_energy_vector_new;};

  void is_detected(std::shared_ptr<Particle> test_particle) override;  //  Function to detect particles, overridden from Detector abse class
  void print_data() override; // Function to print info about a the Calorimeter
};

#endif