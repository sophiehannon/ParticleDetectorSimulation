/*PROJECT DETECTOR SIMULATION - Sophie Hannon 11/05/24
Calorimeter energy  class header file, includes copy constructor, assignment operator 
for deep copying, move constructor and move by assignment. Function checks the energy of 
particle > sum of calorimeter energy components. */

#ifndef CALORIMETERENERGY_H
#define CALORIMETERENERGY_H

#include<iostream>
#include<string>
#include<cmath>
#include<vector>
#include<memory>

class CalorimeterEnergy
{
private:
  std::vector<double> calorimeter_energy;
public:
  CalorimeterEnergy()=default; // Default constructor
  CalorimeterEnergy(double em_1_in, double em_2_in, double had_1_in, double had_2_in):
  calorimeter_energy(4, 0.0)
  {
    set_em_1(em_1_in);
    set_em_2(em_2_in);
    set_had_1(had_1_in);  // Uses setters to assign values
    set_had_2(had_2_in);
  }
  ~CalorimeterEnergy(){}
  // Copy constructor
  CalorimeterEnergy(const CalorimeterEnergy&); // Deep copies an already existing CalorimeterEnergy
  // Assignment operator
  CalorimeterEnergy& operator=(const CalorimeterEnergy&); // Assigns a right hand value to a left hand variable using = operator
  // Move constructor
  CalorimeterEnergy(CalorimeterEnergy&&); // Moves a CalorimeterEnergy to a new CalorimeterEnergy and empties the original
  // Move assignment operator
  CalorimeterEnergy& operator=(CalorimeterEnergy&&); // Moves a CalorimeterEnergy to a new one by assignment

  // Getter functions (accessors) to get data of objects
  double get_em_1()const{return calorimeter_energy[0];};
  double get_em_2()const{return calorimeter_energy[1];};
  double get_had_1()const{return calorimeter_energy[2];};
  double get_had_2()const{return calorimeter_energy[3];};
  std::vector<double> get_calorimeter_energy_vector()const{return calorimeter_energy;};

  // Setter functions to set object data members
  void set_em_1(const double em_1_new){calorimeter_energy[0] = em_1_new;};
  void set_em_2(const double em_2_new){calorimeter_energy[1] = em_2_new;};
  void set_had_1(const double had_1_new){calorimeter_energy[2] = had_1_new;};
  void set_had_2(const double had_2_new){calorimeter_energy[3] = had_2_new;};

  void print_data_calorimeter_energy();  //  Function to print information about calorimeter layers
  double four_vector_sum();  //  Function that sums the contents of a four vector
};

#endif