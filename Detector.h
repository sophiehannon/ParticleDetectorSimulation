/*PROJECT DETECTOR SIMULATION - Sophie Hannon 11/05/24
Detector abstract base class.
Data members: energy_detected
              true_energy
              total_energy_in
              true_energy_vect
              interacted_particles
              number_event
              number_detected
              number_in
              event_energy;
Functions: is_detected - virtual
           print_data -virtual */


#ifndef DETECTOR_H
#define DETECTOR_H

#include<iostream>
#include<string>
#include<cmath>
#include<vector>
#include<map>
#include<memory>
#include "Particle.h"


class Detector 
{
protected: //  Protected so they can be accessed by derived classes
int number_event{0};
int number_detected{0};  // Counters
int number_in{0};
double energy_detected{0};
double true_energy{0};  //  Energy totals
double total_energy_in{0};
double event_energy{0};
std::vector<double> true_energy_vect;
std::map<int, double> interacted_particles;  //  Map to store particle ID and energy

public:
  // Constructors
  // Default constructor
  Detector() {} 
  // No need for a parameterized constructor since variables will be assigned through derived classes as particles go through detector
  // Destructor
  virtual ~Detector(){}
  // Copy constructor
  Detector(const Detector&); // Deep copies an already existing detector
  // Assignment operator
  Detector& operator=(const Detector&); // Assigns a right hand value to a left hand variable using = operator
  // Move constructor
  Detector(Detector&&); // Moves a detector to a new particle and empties the original
  // Move assignment operator
  Detector& operator=(Detector&&); // Moves a detector to a new one by assignment
  
  // Getter functions (accessors) to energy detected and interacted particles
  double get_energy_detected()const{return energy_detected;};
  std::map<int, double> get_interacted_particles()const{return interacted_particles;};
  int get_number_event()const{return number_event;};
  int get_number_detected()const{return number_detected;};
  double get_event_energy()const{return event_energy;};
  double get_true_energy() const{return true_energy;};
  double get_total_energy_in() const{return total_energy_in;};
  int get_number_in()const{return number_in;};

  // Setter functions, to change value of energy detected and interacted particles
  void set_energy_detected(const double energy_detected_new){energy_detected = energy_detected_new;};
  void set_interacted_particles(const std::map<int, double> interacted_particles_new){interacted_particles = interacted_particles_new;};
  void set_number_event(const int number_event_new){number_event = number_event_new;};
  void set_event_energy(const double event_energy_new){event_energy = event_energy_new;};
  void set_true_energy(const double true_energy_new){true_energy = true_energy_new;};
  void set_total_energy_in(const double total_energy_in_new){total_energy_in = total_energy_in_new;};

  virtual void print_data()=0;  //  Completely virtual print data function used by derived classes
  virtual void is_detected(std::shared_ptr<Particle> test_particle)=0;  //  Completely virtual detection function used by subdetectors
};

#endif