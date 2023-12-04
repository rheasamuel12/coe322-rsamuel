#include "infectiousdisease.hpp"
#include "infectiousdisease.cpp"
#include <iostream>

using namespace std;

//exercise 49.1
void personSimulation(){
        Person Rhea;
        Disease disease(5);  
        for (int x = 1; x <= 10; x++) {
            Rhea.one_more_day();
            if(Rhea.get_status() == "Infected"){
                cout << "On day " << x << ", Rhea is " << Rhea.get_status() << " (" << Rhea.get_infectiousDays() << " more days to go)" << endl;
            }
            else
                cout << "On day " << x << ", Rhea is " << Rhea.get_status() << endl;
            if (x == 3) {
                Rhea.infect(disease);
                cout << "Rhea got infected" << endl;
                cout << "On day " << x << ", Rhea is " << Rhea.get_status() << " (" << Rhea.get_infectiousDays() << " more days to go)" << endl;
            }
      
        }
    }


    //exercise 49.4
    void populationSimulation(int popSize, double probability){
        Disease disease(5, probability);  
        Population population(popSize,disease);
        //population.initial_infect(disease); //infect only one person initially
        population.random_infectious(0.01, disease); //infect 10% of the population
        int countInfected =0;
        int day = 1;

        do{
            countInfected = population.count_infected();
            cout << "In step " << day++ << " # sick = " << countInfected << ":" << population.toStringOne() << endl ;
            population.one_more_day();
        } while(countInfected>0);
    }
    //exercise 49.5
    void neighborSimulation(int popSize, double probability){
        Disease disease(5, probability);  
        Population population(popSize,disease);
        //population.initial_infect(disease); //infect only one person initially
        population.random_infectious(0.01, disease); //infect 10% of the population
        cout << "Initial values: \nDisease transmission probability: " << probability << endl;
        int countInfected =0;
        int countHealthy = 0;
        int day = 1;
        do {
            countInfected = population.count_infected();
            countHealthy = population.count_healthy();
            cout << "\nIn step " << day++ << " # sick = " << countInfected << "\n# healthy = " << countHealthy << endl;
            population.one_more_day();
            population.neighbor(disease, probability);        

        } while (countInfected > 0);
        cout << "Number of healthy people at the end: " << countHealthy << endl;
    }
//exercise 49.6
    void vaccinationSimulation(int popSize, double probability, double vaccRate){ 
        Disease disease(5, probability);  
        Population population(popSize,disease);
        //population.initial_infect(disease); //infect only one person initially
        population.random_infectious(0.1, disease); //infect 10% of the population
        population.random_vaccination(vaccRate);
        cout << "Initial values: \nDisease transmission probability: " << probability << endl;
        cout << "Vaccination Rate: " << vaccRate << endl;
        int countInfected = 0;
        int countHealthy = 0;
        int countVaccinated = 0;
        int day = 1;
        do {
            countInfected = population.count_infected();
            countHealthy = population.count_healthy();
            countVaccinated = population.count_vaccinated();
            cout << "\nIn step " << day++ << " # sick = " << countInfected << "\n# vaccinated = " << countVaccinated << "\n# healthy = " << countHealthy << endl;
            population.one_more_day();
            population.neighbor(disease, probability);   
            
        } while (countInfected > 0);
    }
//exercise 49.7
    void testRandomContact(int popSize, double probability, double vaccRate){ 
        Disease disease(5, probability);  // disease with 50% transmission chance and 5 days of sickness
        Population population(popSize,disease);
        //population.initial_infect(disease); //infect only one person initially
        population.random_infectious(0.01, disease); //infect 10% of the population
        population.random_vaccination(vaccRate);
        cout << "Initial values: \nDisease transmission probability: " << probability << endl;
        cout << "Vaccination Rate: " << vaccRate << endl;
        int countInfected = 0;
        int countHealthy = 0;
        int countVaccinated = 0;
        int day = 1;
        int ind = 0;
        vector <int> pop;
        do {
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
            cout << "\nIn step " << day++ << " # sick = " << countInfected << "\n# vaccinated = " << countVaccinated << "\n# healthy = " << countHealthy << endl;
            population.one_more_day();
            while(ind<pop.size()){
                population.random_contact_infection(disease, 6, pop[ind]); 
                ind++;  
            }  
            //cout << countInfected << endl;
        } while (countInfected > 0);
        cout << "\nThe disease ran through the simulation for " << day-1 << " days" << endl;
    }
//exercise 49.8
    void herdImmunity(int popSize, double probability, double vaccRate){
        Disease disease(5, probability);  
        Population population(popSize,disease);
        //population.initial_infect(disease); //infect only one person initially
        population.random_infectious(0.01, disease); //infect 1% of the population
        population.random_vaccination(vaccRate);
        cout << "Initial Values: \nDisease transmission probability: " << probability << endl;
        cout << "Vaccination Rate: " << vaccRate << endl;
        int countInfected = 0;
        int countHealthy = 0;
        int countVaccinated = 0;
        int day = 1;
        int ind = 0;
        vector <int> pop;
        do {
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
            day++;
            population.one_more_day();
            while(ind<pop.size()){
                population.random_contact_infection(disease, 6, pop[ind]); 
                ind++;  
            }  
        } while (countInfected > 0);
        cout << "The disease ran through the simulation for " << day-1 << " days" << endl;
        cout << "The amount of healthy and non-vaccinated people after the simulation is " << countHealthy << endl;
    }

    //exercise 49.9
    int Disease::variant_type = 1;
    int Disease::transmissionCounterForMutation = 101; //change as desired (to increase/decrease mutation rate)

    void mutation(int popSize, double probability, double vaccRate){
        Disease disease(5, probability);  
        Population population(popSize,disease);
        //population.initial_infect(disease); //infect only one person initially
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
                population.random_contact_infectionMutation(disease, 6, pop[ind]); 
                ind++;  
            }  
        } while (countInfected > 0);
        cout << "\nThe disease ran through the simulation for " << day-1 << " days" << endl;
        cout << "Ended with variant " <<  Disease::variant_type << endl;
    }
    /*
int main(){
    //personSimulation(); //exercise 49.1
    //populationSimulation(10000,0.30); //exercise 49.4
    neighborSimulation(10000,0.3); //exercise 49.5
    //vaccinationSimulation(100000,0.3,0.75); //exercise 49.6
    //testRandomContact(10000,0.30,0.75); //exercise 49.7
/*
    for(double x = 0.10; x<=1; x+=0.20){ //exercise 49.8
        for(double y = 0.10; y<=0.90; y+=0.10){
            herdImmunity(10000,x, y);
            cout << endl;
        }
    } 

    //mutation(10000,0.3, 0.30); //exercise 49.9

    return 0;
}
*/
