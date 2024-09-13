/*PROJECT DETECTOR SIMULATION - Sophie Hannon 11/05/24
The aim of this project was to simulate a Particle Detector using object orientated programming in C++.
Methods of abstraction, inheritance, polymorphism, and encapsulation were implemented successfully using two class hierarchies.
The hierarchies were classified by particle and detector. Subdetectors were contained in a vector to simulate a real-life detector.
Particles were passed through and results such as energy and identification efficiencies were found.
The project could have been improved by a user interface if time had allowed.

Compile line: g++ -std=c++17 -g main.cpp Particle.cpp CalorimeterEnergy.cpp CalorimeterParticles.cpp Muon.cpp Neutrino.cpp Tau.cpp Detector.cpp ChargedParticleDetector.cpp Tracker.cpp Calorimeter.cpp MuonDetector.cpp RandomGenerators.cpp EmDeposits.cpp CompleteDetector.cpp -o main.exe

main.cpp file where code is implemented. Events are constructed in vectors and placed through the complete detector container.*/

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<memory>
#include "Particle.h"
#include "CalorimeterEnergy.h"
#include"Muon.h"
#include "Neutrino.h"
#include "CalorimeterParticles.h"
#include "Tau.h"
#include "Detector.h"
#include "Tracker.h"
#include "Calorimeter.h"
#include "MuonDetector.h"
#include "RandomGenerators.h"
#include "CompleteDetector.h"



// Main program
int main()
{
  double event_1_energy{125};
  double event_2_energy{1500};
  double event_3_energy{1500};
  double event_4_energy{1500};
  std::srand(time(0));
  try
  {
    // Create individual detectors to be used for detection
    CalorimeterEnergy energy_in(1, 1, 1, 1);
    Calorimeter calorimeter_1(energy_in);
    Tracker tracker_1(1,1,1);
    MuonDetector muon_detector_1(1,1);

    //  Put subdetectors inside a complete detector object
    CompleteDetector complete_detector(calorimeter_1, tracker_1, muon_detector_1);

    // EVENT 1
    std::cout<<"// EVENT 1 //\n";
    //  Create vector of shared pointers to particles for the first event: 2 photons with an initial energy of 125 GeV
    std::vector<std::shared_ptr<Particle>> event_1;
    std::vector<double> energy_proportions_1{random_probability_generator(2)}; //  Random split of the total energy between particles
  
    // Create the two shared pointers to photons using parameterized constructors and push back into events vector
    event_1.push_back(std::make_shared<EmDeposits>(1, 0, event_1_energy*energy_proportions_1[0]));
    event_1.push_back(std::make_shared<EmDeposits>(2, 0, event_1_energy*energy_proportions_1[1]));
    
    complete_detector.print_event_results(event_1);

    // EVENT 2
    std::cout<<"\n// EVENT 2 //\n";
    //  Create vector of shared pointers to particles for the second event: a photon, neutron and proton with initial energy of 1500 GeV
    std::vector<std::shared_ptr<Particle>> event_2;
    std::vector<double> energy_proportions_2{random_probability_generator(3)}; //  Random split of the total energy between particles
    
    // Create shared pointers to a photon, neutron and proton using parameterized constructors and push back into events vector
    event_2.push_back(std::make_shared<CalorimeterParticles>(3, 0, event_2_energy*energy_proportions_2[0])); //  Neutron
    event_2.push_back(std::make_shared<EmDeposits>(4, 0, event_2_energy*energy_proportions_2[1]));  //  Photon
    event_2.push_back(std::make_shared<CalorimeterParticles>(5, 1, event_2_energy*energy_proportions_2[2]));  //  Proton

    complete_detector.print_event_results(event_2);

    //  EVENT 3
    std::cout<<"\n// EVENT 3 //\n";
    std::vector<double> energy_proportions_3{random_probability_generator(2)};
    if(energy_proportions_3[0] < 0.1 || energy_proportions_3[1] < 0.1)  energy_proportions_3 = random_probability_generator(2);  //  Random split of the total energy between particles
    
    // Create a tau decaying hadronically and antitau decaying leptonically
    Tau tau(6, -1, event_3_energy*energy_proportions_3[0], 1, 0);
    Tau antitau(8, 1, event_3_energy*energy_proportions_3[1], 0, 1);
    std::vector<std::shared_ptr<Particle>> event_3 = tau.get_decay_products(); // add decay products to vector
    std::vector<std::shared_ptr<Particle>> antitau_decay_products = antitau.get_decay_products();
    event_3.insert(event_3.end(), antitau_decay_products.begin(), antitau_decay_products.end());

    complete_detector.print_event_results(event_3);


    //  EVENT 4
    std::cout<<"\n// EVENT 4 //\n";
    //  Create vector of shared pointers to particles for the fourth event: a proton and two neutrinos with initial energy of 1500 GeV
    std::vector<std::shared_ptr<Particle>> event_4;
    std::vector<double> energy_proportions_4{random_probability_generator(3)}; //  Random split of the total energy between particles
    
    // Create the three shared pointers to a proton and two neutrinos using parameterized constructors and push back into events vector
    event_4.push_back(std::make_shared<CalorimeterParticles>(11, 1, event_4_energy*energy_proportions_4[0]));
    event_4.push_back(std::make_shared<Neutrino>(12, 0, event_4_energy*energy_proportions_4[1], "electron", 1));
    event_4.push_back(std::make_shared<Neutrino>(13, 0, event_4_energy*energy_proportions_4[2], "antielectron", 1));
    complete_detector.print_event_results(event_4);

    complete_detector.print_summary();  // prints a summary of all results
  }
  catch(...)
  {
    std::cout<<"Energy was unphysical, energy cannot be negative.";  //  Catches unphysical energies
  };

  return 0;
}