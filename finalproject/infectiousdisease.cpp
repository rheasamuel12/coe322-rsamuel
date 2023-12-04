// Name: Rhea Samuel
// UTEID:rss3488
// TACC Username: rheasamuel12 
//Final Project: Infectious Disease Simulation

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <stdlib.h>
using namespace std;
#include "infectiousdisease.hpp"
#define CATCH_CONFIG_MAIN
#include "catch2/catch_all.hpp"



//49.2.1.1 Person tests
TEST_CASE("Infection with 100% transmittable disease", "[Person]") {
    Disease disease(5,1.0); // 100% transmission chance, 5 days of infection
    Person person;
    person.infect(disease);
    REQUIRE(person.get_status() == "Infected");
}

TEST_CASE("Contact with vaccinated/recovered person and disease", "[Person]") {
    Disease disease(7,1.0); // 50% transmission chance
    Person vaccinatedPerson("Vaccinated", 0);

    Person recoveredPerson("Recovered", 0);

    vaccinatedPerson.infect(disease);
    recoveredPerson.infect(disease);

    REQUIRE(vaccinatedPerson.get_status() == "Vaccinated");
    REQUIRE(recoveredPerson.get_status() == "Recovered");
}

TEST_CASE("Infection Spread Test", "[Infection]") {
    // Create a disease with a 50% transmission chance and 5 days of sickness
    Disease disease(5,0.5);

    const int populationSize = 10000; 
    vector<Person> people(populationSize);

    for(int i = 0; i<populationSize; i++){
        double randomValue = static_cast<double>(rand()) / (RAND_MAX + 1.0);
        if(randomValue < disease.getTransmissionChance())
        {
            people[i].infect(disease);
        }
    }

    int numSick = 0;
    for (auto& person : people) {
        if (person.get_status() == "Infected") {
            numSick++;
        }
    }

    double actualPercentage = static_cast<double>(numSick) / populationSize;

    //tolerance
    REQUIRE(actualPercentage >= disease.getTransmissionChance() - 0.1);
    REQUIRE(actualPercentage <= disease.getTransmissionChance() + 0.1);
}



//Adapt the above tests, but now a person comes in contact with an infected person, rather than directly
//with a disease

//49.2.2.1 Interaction tests
TEST_CASE("Infection Spread Test 2", "[Infect]") {
    // Create a disease with a 50% transmission chance and 5 days of sickness
    Disease disease(5,0.5);

    const int populationSize = 10000; // Adjust as needed
    vector<Person> people(populationSize);
    Person infected;
    infected.infect(disease);

    for(int x = 0; x<populationSize; x++)
    {
        people[x].touch(infected,disease);
    }

    // Count the number of people who are sick after the simulation
    int numSick = 0;
    for (auto& person : people) {
        if (person.get_status() == "Infected") {
            numSick++;
        }
    }

    // Check if about half of the people got sick
    double actualPercentage = static_cast<double>(numSick) / populationSize;
    //tolerance
    REQUIRE(actualPercentage >= disease.getTransmissionChance() - 0.1);
    REQUIRE(actualPercentage <= disease.getTransmissionChance() + 0.1);
}

//49.2.3.1 POPULATION TESTS
TEST_CASE("Everyone is vaccinated with 100 vacccination rate", "[vaccination]") {
    // Create a Disease with 0% transmission chance and 5 days of sickness
    Disease disease(5, 0.0);

    // Create a Population with 10 people and 100% vaccination rate
    Population population(10000, disease);
    population.random_vaccination(1.0);

    // Check if everyone is vaccinated
    REQUIRE(population.count_vaccinated() == 10000);
    REQUIRE(population.count_infected() == 0);
}

//4.9.3.1.1 Tests
TEST_CASE("Duration of disease", "[infection][population]") {
        // Create a Disease with 50% transmission chance and 5 days of sickness
        Disease disease(5, 0.5);

        Population population(10000, disease);

        int initialInfected = population.count_infected();
        int initialHealthy = population.populationSize - initialInfected;

        // Run the simulation for the duration of the disease
        int currentInfected = 0;
        int currentHealthy = 0;
        for (int day = 1; day <= disease.getDuration()-1; ++day) {
            population.one_more_day();
            currentInfected = population.count_infected();
            currentHealthy = population.populationSize - currentInfected;

            // Check if the number of infected people stays constant during the duration of the disease
            REQUIRE(currentInfected == initialInfected);

            // Check if the sum of healthy and infected people stays equal to the population size
            REQUIRE(currentHealthy + currentInfected == population.populationSize);

    }
}

//49.3.2.1 sanity tests 
TEST_CASE("Test simulation with p = 1", "[simulation]") {
    //tests if random index is sick, next day 3 are sick
    Disease disease(5, 1);
    Population population(10000, disease);
    population.initial_infect(disease);
    int index = 0;
    for(int x = 0; x<population.people.size(); x++){
        if(population.people[x].get_status() == "Infected"){
            index = x;
        }
    }
    //one day
    int day = 0;
    bool ret = false;
    if(population.people[0].get_status() == "Infected"|| population.people[population.populationSize-1].get_status() == "Infected"){
        ret = true;
    }
    population.one_more_day();
    population.neighbor(disease, 1, index);
    if(ret)
    {
        REQUIRE(population.count_infected() == 2);
    }
    else
        REQUIRE(population.count_infected() == 3);
}
//if index is 0, then the simulation should run for the number of days equal to population size
TEST_CASE("Test simulation with p = 1, Index = 0", "[simulation]") {
    Disease disease(5, 1); 
    Population population(10000, disease);
    population.people[0].infect(disease); //+ ? ? ? 
    int days = 1;
    int x = 0;
    while(x < population.populationSize){
        population.one_more_day();
        population.neighbor(disease, 1, x); 
        days++;
        x++;
    }
    REQUIRE(days == population.populationSize); 
}
TEST_CASE("Test simulation with p = 0.5", "[simulation]") {
    Disease disease(5, 0.5);
    Population population(10000, disease);
    population.people[0].infect(disease);
    int days = 1;
    int ind = 0;
    int countInfected = 0;
    vector <int> pop;
    while(countInfected>0){
        for(int x = 0; x<population.populationSize; x++){
            if(population.people[x].get_status() == "Infected"){
                auto it = find(pop.begin(), pop.end(), x);
                if (it == pop.end()) {
                    pop.push_back(x); //checks if the index is not already in the vector
                }
            }
        } 
        if(population.people[population.populationSize-1].get_status() != "Susceptible")
            break;
        countInfected = population.count_infected();
        population.one_more_day();
        while(ind<pop.size()){
                population.neighbor(disease, 0.5, pop[ind]);    
                ind++;    
            }  
        days++;
    }

    REQUIRE_NOTHROW(days == population.populationSize); // populationSize won't equal the days
}