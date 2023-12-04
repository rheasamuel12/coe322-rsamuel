#include "infectiousdisease2.hpp"
#include <algorithm>
using namespace std;


//exercise 49.9
    int Disease::variant_type = 1;
    int Disease::transmissionCounterForMutation = 150; //change as desired (to increase/decrease mutation rate)

    void mutation(int popSize, double probability, double vaccRate){
        Disease disease(5, probability);  
        Population population(popSize,disease);
        cout << "Initial Values: \nVariant type: " << Disease::variant_type << "\nTransmission Counter: " <<  Disease::transmissionCounterForMutation << endl;
        population.random_infectiousVariant(0.01, disease); //infect 10% of the population
        population.random_vaccination(vaccRate);
        cout << "Disease transmission probability: " << probability << endl;
        cout << "Vaccination Rate: " << vaccRate << endl;
        int countInfected = 0;
        int countHealthy = 0;
        int countVaccinated = 0;        
        int day = 1;
        int ind = 0;
        vector <int> pop;
        cout << "\n**Infect 1% of population**" << endl;
        do {
            cout << "\nVariant type: " << Disease::variant_type << "\nTransmission Counter: " <<  Disease::transmissionCounterForMutation << endl;
            for(int x = 0; x<population.populationSize; x++){
                if(population.people[x].get_status() == "Infected"){
                    auto it = find(pop.begin(), pop.end(), x);
                    if (it == pop.end()) {
                        pop.push_back(x); //checks if the index is not already in the vector
                    }
                }
            } 
            countInfected = population.count_infected();
            countHealthy = population.count_healthy();
            countVaccinated = population.count_vaccinated();
            cout << "In step " << day++ << " # sick = " << countInfected << "\n# vaccinated = " << countVaccinated << "\n# healthy = " << countHealthy << endl;
            population.one_more_dayVariant();
            while(ind<pop.size()){
                population.random_contact_infectionMutation(disease, 6, pop[ind]); //randomly infects an individual
                ind++;  
            }  
        } while (countInfected > 0);
        cout << "\nThe disease ran through the simulation for " << day-1 << " days" << endl;
        cout << "Ended with variant " <<  Disease::variant_type << endl;
    }

int main(){
    mutation(10000,0.3, 0.25); //exercise 49.9
    return 0;
}