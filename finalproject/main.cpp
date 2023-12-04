#include "infectiousdisease.hpp"
#include <algorithm>
using namespace std;

//exercise 49.1
    void personSimulation(){
        Person Rhea;
        Disease disease(5);  
        for (int x = 1; x <= 10; x++) { //loops through 10 days 
            Rhea.one_more_day();
            if(Rhea.get_status() == "Infected"){ //Displays my infectious days
                cout << "On day " << x << ", Rhea is " << Rhea.get_status() << " (" << Rhea.get_infectiousDays() << " more days to go)" << endl;
            }
            else //returns my status
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
        population.random_infectious(0.01, disease); //infect 1% of the population
        int countInfected =0;
        int day = 1;

        do{
            countInfected = population.count_infected();
            //cout << "In step " << day++ << " # sick = " << countInfected << ":" << population.toStringOne() << endl ;
            cout << "Infected count on day " << day << ": " << countInfected << endl;
            day++;
            population.one_more_day();
        } while(countInfected>0);
    }
//exercise 49.5
    void neighborSimulation(int popSize, double probability){
        Disease disease(5, probability);  
        Population population(popSize,disease);
        population.random_infectious(0.01, disease); //infect 10% of the population
        cout << "Initial values: \nDisease transmission probability: " << probability << endl;
        int countInfected =0;
        int countHealthy = 0;
        int day = 1;
        vector <int> pop; //stores indexes of infected values
        int ind = 0; //index
        do {
            for(int x = 0; x<population.populationSize; x++){
                if(population.people[x].get_status() == "Infected"){
                    auto it = find(pop.begin(), pop.end(), x); //checks if the index is not already in the vector
                    if (it == pop.end()) {
                        pop.push_back(x); //if not, adds to vector
                    }
                }
            } 
            countInfected = population.count_infected();
            countHealthy = population.count_healthy();
            //uncomment to see the value during EACH step!
            //cout << "\nIn step " << day << " # sick = " << countInfected << "\n# healthy = " << countHealthy << endl;
            day++;
            population.one_more_day();
            while(ind<pop.size()){ //loops through infected indexes
                population.neighbor(disease, probability, pop[ind]);    
                ind++;    
            }
        } while (countInfected > 0);
        cout << "Number of healthy people at the end: " << countHealthy << endl;
    }
//exercise 49.6
   void vaccSimulation(int popSize, double probability, double vaccRate){ 
        Disease disease(5, probability);  
        Population population(popSize,disease);
        population.random_infectious(0.01, disease); //infect 1% of the population
        population.random_vaccination(vaccRate); //randomly vaccinates people based on vaccRate
        cout << "Initial values: \nDisease transmission probability: " << probability << endl;
        cout << "Vaccination Rate: " << vaccRate << endl;
        int countInfected =0;
        int countHealthy = 0;
        int countVaccinated = 0;
        int countTotalInfected = 0;
        int day = 1;
        vector <int> pop; //vector of infected indexes
        int ind = 0;
        do {
            for(int x = 0; x<population.populationSize; x++){
                if(population.people[x].get_status() == "Infected"){
                    auto it = find(pop.begin(), pop.end(), x); //checks if the index is not already in the vector
                    if (it == pop.end()) {
                        pop.push_back(x); //if not, adds to vector
                    }
                }
            } 
            countInfected = population.count_infected();
            countHealthy = population.count_healthy();
            countVaccinated = population.count_vaccinated();
            countTotalInfected += population.count_infected(); 
            //cout << "\nIn step " << day << " # sick = " << countInfected << "\n# vaccinated = " << countVaccinated << "\n# healthy = " << countHealthy << endl;
            day++;
            population.one_more_day();
            while(ind<pop.size()){ //loops through infected indexes
                population.neighbor(disease, probability, pop[ind]);    
                ind++;    
            }
        } while (countInfected > 0);
        cout << "Number of infected people at the end: " << countTotalInfected << endl;
    }
//exercise 49.7
    void testRandomContact(int popSize, double probability, double vaccRate){ 
        Disease disease(5, probability); 
        Population population(popSize,disease);
        population.random_infectious(0.01, disease); //infect 1% of the population
        population.random_vaccination(vaccRate); //randomly vaccinates
        cout << "Initial values: \nDisease transmission probability: " << probability << endl;
        cout << "Vaccination Rate: " << vaccRate << endl;
        int countInfected = 0;
        int countHealthy = 0;
        int countVaccinated = 0;
        int day = 1;
        int ind = 0;
        vector <int> pop; //vector of infected indexes
        do {
            for(int x = 0; x<population.populationSize; x++){
                if(population.people[x].get_status() == "Infected"){
                    auto it = find(pop.begin(), pop.end(), x); //checks if the index is not already in the vector
                    if (it == pop.end()) {
                        pop.push_back(x); 
                    }
                }
            } 
            countInfected = population.count_infected();
            countHealthy = population.count_healthy();
            countVaccinated = population.count_vaccinated();
            //cout << "\nIn step " << day << " # sick = " << countInfected << "\n# vaccinated = " << countVaccinated << "\n# healthy = " << countHealthy << endl;
            day++;
            population.one_more_day();
            while(ind<pop.size()){
                population.random_contact_infection(disease, 6, pop[ind]); //random infection to a max of 6 people
                ind++;  
            }  
        } while (countInfected > 0);
        cout << "\nThe disease ran through the simulation for " << day-1 << " days" << endl;
    }
//exercise 49.8
    void herdImmunity(int popSize, double probability, double vaccRate){
        Disease disease(5, probability);  
        Population population(popSize,disease);
        population.random_infectious(0.01, disease); //infect 1% of the population
        population.random_vaccination(vaccRate); //vaccinates randomly
        cout << "Initial Values: \nDisease transmission probability: " << probability << endl;
        cout << "Vaccination Rate: " << vaccRate << endl;
        int countInfected = 0;
        int countHealthy = 0;
        int countVaccinated = 0;
        int day = 1;
        int ind = 0;
        vector <int> pop; //vector of infected indexes
        do {
            for(int x = 0; x<population.populationSize; x++){
                if(population.people[x].get_status() == "Infected"){
                    auto it = find(pop.begin(), pop.end(), x); //checks if the index is not already in the vector
                    if (it == pop.end()) {
                        pop.push_back(x); 
                    }
                }
            } 
            countInfected = population.count_infected();
            countHealthy = population.count_healthy();
            countVaccinated = population.count_vaccinated();
            day++;
            population.one_more_day();
            while(ind<pop.size()){
                population.random_contact_infection(disease, 6, pop[ind]); //randomly touches max of 6 people
                ind++;  
            }  
        } while (countInfected > 0);
        cout << "The disease ran through the simulation for " << day-1 << " days" << endl;
        cout << "The amount of healthy and non-vaccinated people after the simulation is " << countHealthy << endl;
    }

    


int main(){
    //uncomment based on the excercise you would like to run!
    //for running purposes, I will leave the testRandomContact excercise unccomented!
    cout << "Person Simulation:\n";
    personSimulation(); //exercise 49.1
    cout << "--------------------------\nPopulation Simulation:\n";
    populationSimulation(10000,0.30); //exercise 49.4
    cout << "--------------------------\nNeighbor Simulation:\n";
    neighborSimulation(10000,0.5); //exercise 49.5
    cout << "--------------------------\nVaccination Simulation:\n";
    vaccSimulation(10000,0.3,0.75); //exercise 49.6
    cout << "--------------------------\nRandom Contact Simulation:\n";
    testRandomContact(10000,0.3,0.75); //exercise 49.7
    cout << "--------------------------\nHerd Immunity Simulation:\n";
    herdImmunity(10000,0.3,0.75);
/*
    for(double x = 0.10; x<=1; x+=0.20){ //exercise 49.8
        for(double y = 0.10; y<=0.90; y+=0.10){
            herdImmunity(10000,x, y);
            cout << endl;
        }
    } 
*/
    return 0;
}
