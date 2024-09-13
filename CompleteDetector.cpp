/*PROJECT DETECTOR SIMULATION - Sophie Hannon 11/05/24
CompleteDetector class code file. Includes copy constructor, assignment operator for deep copying, move constructor and 
move by assignment. Contains a function that prints the results of all detectors, a function that takes in all subdetector's 
results to identify the particle detecte, a function that finds the invisible enrgy in an event and a function that prints
a summary after all events. */

#include "CompleteDetector.h"
#include <set>
#include <cmath>

// Copy constructor for deep copying
CompleteDetector::CompleteDetector(const CompleteDetector &detector_copy)
{
  std::cout<<"Calling CompleteDetector copy constructor\n"; 
  *complete_detector[0] = detector_copy.get_calorimeter();
  *complete_detector[1] = detector_copy.get_tracker();
  *complete_detector[2] = detector_copy.get_muon_detector();  // Copy data members from old CompleteDetector to new CompleteDetector
}

// Assigment operator for deep copying
CompleteDetector & CompleteDetector::operator=(const CompleteDetector &detector_copy)
{
  if(&detector_copy == this) return *this; // Prevents self assigment
  std::cout<<"Calling CompleteDetector assignment operator\n";
  // Reassign values with copy
  *complete_detector[0] = detector_copy.get_calorimeter();
  *complete_detector[1] = detector_copy.get_tracker();
  *complete_detector[2] = detector_copy.get_muon_detector();  // Reassign the copied CompleteDetector data member to new CompleteDetector
  return *this;    
}

// Move constructor which moves a CompleteDetector to a new CompleteDetector and empties the original
CompleteDetector::CompleteDetector(CompleteDetector&& detector_move)
{
  std::cout<<"Calling CompleteDetector move constructor\n";
  complete_detector[0] = detector_move.complete_detector[0];
  complete_detector[1] = detector_move.complete_detector[1];
  complete_detector[2] = detector_move.complete_detector[2];  // Get CompleteDetector to be moved data members
  // Empty initial CompleteDetector
  detector_move.complete_detector[0] = nullptr;
  detector_move.complete_detector[1] = nullptr;
  detector_move.complete_detector[2] = nullptr;  // Clear out old CompleteDetector that was moved

}

// Move by assigment swaps the existing CompleteDetector with the new one
CompleteDetector & CompleteDetector::operator=(CompleteDetector&& detector_move)
{
  std::cout<<"Calling CompleteDetector move by assignment operator\n";
  // Reassign values with copy
  *complete_detector[0] = detector_move.get_calorimeter();
  *complete_detector[1] = detector_move.get_tracker();
  *complete_detector[2] = detector_move.get_muon_detector(); // Reassign CompleteDetector that was moved 
  return *this;
}


//  Function that idetifies the particle type by seeing where energy has been detected
void CompleteDetector::find_particle_type(std::shared_ptr<Particle> particle)
{
  Calorimeter calorimeter = get_calorimeter();
  CalorimeterEnergy calorimeter_energy_detected = calorimeter.get_calorimeter_energy_detected();  //  Access calorimeter energy detected
  double em_1{calorimeter_energy_detected.get_em_1()};
  double em_2{calorimeter_energy_detected.get_em_2()};
  double had_1{calorimeter_energy_detected.get_had_1()};
  double had_2{calorimeter_energy_detected.get_had_2()};
  double tracker_energy{(complete_detector[1])->get_event_energy()} ;
  double muon_detector_energy{(complete_detector[2])->get_event_energy()};

  if(tracker_energy != 0) //  If not detected in tracker, must be charged
  {
    if(had_1 == 0 && had_2 == 0)
    {
      if(em_1 == 0 && em_2 == 0)  //  If not seen in calorimeter at all, muon
      {
        if(std::dynamic_pointer_cast<Muon>(particle) !=  nullptr) ++correctly_identified;  //  If the object casts to a muon, correctly identified
        std::string muon{"muon"};
        particle_types.push_back(muon);
      }
      else  //  If seen by electronic calorimeterm electron
      {
        if(std::dynamic_pointer_cast<EmDeposits>(particle) !=  nullptr) ++correctly_identified; //  If the object casts to an electron, correctly identified
        std::string electron{"electron"};
        particle_types.push_back(electron);
      }
    }
    else  //  If seen in all calorimeter layers, proton
    {
      if(std::dynamic_pointer_cast<CalorimeterParticles>(particle) !=  nullptr) ++correctly_identified;  //  If the object casts to a proton, correctly identified
      std::string proton{"proton"};
      particle_types.push_back(proton);
    } 
  }
  else  //  If not seen in tracker, neutral charge
  {
    if(had_1 == 0 && had_2 == 0)
    {
      if(em_1 == 0 && em_2 == 0) // if not seen in calorimeter either, neutrino so not deteceted
      {
        std::string not_detected{"not detected"};  
        particle_types.push_back(not_detected);
      }
      else  //  If just seen in the electronic layers of the calorimeter, photon
      {
        if(std::dynamic_pointer_cast<EmDeposits>(particle) !=  nullptr) ++correctly_identified;  //  If the object casts to a photon, correctly identified
        std::string photon{"photon"};
        particle_types.push_back(photon);
      }
    }
    else if (em_1 != 0 && em_2 != 0) //  If in all layers of calorimeter, neutron
    {
      if(std::dynamic_pointer_cast<CalorimeterParticles>(particle) !=  nullptr) ++correctly_identified;  //  If the object casts to a neutron, correctly identified
      std::string neutron{"neutron"};
      particle_types.push_back(neutron);
    }
  }
}

//  Function that prints results of events
void CompleteDetector::print_event_results(std::vector<std::shared_ptr<Particle>> event_vector)
{
  std::cout<<"\nThis event consists of the following particles:";
  for(auto event_it=event_vector.begin(); event_it<event_vector.end(); ++event_it)
  {
    for(auto detector_it=complete_detector.begin(); detector_it<complete_detector.end(); ++detector_it)
    {
      (*detector_it)->is_detected(*event_it);  //  acts detectors on each particle one at a time
    }
    find_particle_type(*event_it);  //  Once a particle has been through all subdetectors, it can be identified
    (*event_it)->print_data();  //  Prints inputs into event
  }
  find_invisible_energy(event_vector);  //  Once all particles in an event have gone through the detector, the invisible enrgy can be found
  for(auto detector_it=complete_detector.begin(); detector_it<complete_detector.end(); ++detector_it)
  {
    (*detector_it)->print_data();  //  Print information found in detections
  }
  std::cout<<"\n\nThe following particles have been detected:\n ";
  for(int i{0}; i < particle_types.size(); i++) std::cout<<particle_types[i]<<"\n";  //  Print types found
  particle_types.clear();  //  Clear vector of types for next event
  std::cout<<"\nThe invisible energy was "<<invisible_energy<<" GeV.\n";  //  Prints invisible energy

}

//  Finds invisible energy for an event, based on detector results
void CompleteDetector::find_invisible_energy(std::vector<std::shared_ptr<Particle>> event_vector)
{
  double initial_energy{0};
  std::set<int> detected_identifiers;  // Create a set of the particle ID's that have been detected
  for(auto event_it=event_vector.begin(); event_it<event_vector.end(); ++event_it) initial_energy += (*event_it)->get_particle_energy();    
  invisible_energy = initial_energy;
  for(auto detector_it=complete_detector.begin(); detector_it<complete_detector.end(); ++detector_it)  //  Iterate through subdetectors
  {
    std::map<int, double> detected_map = (*detector_it)->get_interacted_particles();  //  Get detected information
    for(const auto pair : detected_map)
    {
      if(!detected_identifiers.count(pair.first)) invisible_energy -= pair.second;  //  If the ID is not found in the set, energy subtracted from invisible energy
      detected_identifiers.insert(pair.first); // Add already subtracted energy to set to avpid double counting
    } 
    if(invisible_energy < 0.001) set_invisible_energy(0); //  To prevent rounding errors
  }
}

//  Function to print a summary of the results of the detections
void CompleteDetector::print_summary()
{
  std::vector<double> energy_efficiency;
  int total_particles_in{0};
  for(auto detector_it=complete_detector.begin(); detector_it<complete_detector.end(); ++detector_it)  //  Iterate through the 3 subbdetectors
  {
    total_particles_in += (*detector_it)->get_number_in();  //  Sum number of particles in
    double energy_detected{(*detector_it)->get_energy_detected()};
    double total_energy_in{(*detector_it)->get_total_energy_in()};
    energy_efficiency.push_back(energy_detected/total_energy_in);  //  Create a vector of the efficiencies of the subdetectors
  }
  std::cout<<"\n\n\n//      SUMMARY OF DETECTIONS     //\n\n";
  std::cout<<"\nThe calorimeter has detected "<<complete_detector[0]->get_number_detected()<<" particle(s).";
  std::cout<<"\nThe calorimeter's energy efficiency is: "<<energy_efficiency[0];
  std::cout<<"\n\nThe tracker has detected "<<complete_detector[1]->get_number_detected()<<" particle(s).";
  std::cout<<"\nThe tracker's energy efficiency is: "<<energy_efficiency[1];
  std::cout<<"\n\nThe muon detector has detected "<<complete_detector[2]->get_number_detected()<<" particle(s).";
  if(complete_detector[2]->get_number_detected() == 0) std::cout<<"\nThe muon detector's energy efficiency is: "<<"n/a"<<".";
  else std::cout<<"\nThe muon detector's energy efficiency is: "<<energy_efficiency[2]<<".";
  double identification_efficiency;
  identification_efficiency = (double)correctly_identified / (double)total_particles_in;  //  Calculate the identification efficiency
  std::cout<<"\nThe total identification efficiency is "<<identification_efficiency<<".";
}