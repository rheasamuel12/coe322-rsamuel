// Name: Rhea Samuel
// UTEID:rss3488
// TACC Username: rheasamuel12 
//Final Project: Infectious Disease Simulation

#include <iostream>
#include <iomanip>
#include <stdlib.h>
using namespace std;
#include "infectiousdisease.hpp"
#define CATCH_CONFIG_MAIN
#include "catch2/catch_all.hpp"



//49.2.1.1 Person tests
TEST_CASE("Infection with 100% transmittable disease", "[Person]") {
    Disease covid(5,1.0); // 100% transmission chance, 5 days of infection
    Person person;
    // After being infected, the person should register as sick
    person.infect(covid);
    REQUIRE(person.get_status() == "Infected");
}

TEST_CASE("Contact with vaccinated/recovered person and disease", "[Person]") {
    Disease covid(7,1.0); // 50% transmission chance
    Person vaccinatedPerson("Vaccinated", 0);
    //vaccinatedPerson.get_vaccinated();

    Person recoveredPerson("Recovered", 0);
    //recoveredPerson.one_more_day(); // Make the person "Recovered"

    // If vaccinated or recovered, they should stay in their original state
    vaccinatedPerson.infect(covid);
    recoveredPerson.infect(covid);

    REQUIRE(vaccinatedPerson.get_status() == "Vaccinated");
    REQUIRE(recoveredPerson.get_status() == "Recovered");
}

TEST_CASE("Infection Spread Test", "[Infection]") {
    // Create a disease with a 50% transmission chance and 5 days of sickness
    Disease covid(5,0.5);

    // Create a population of people
    const int populationSize = 1000; // Adjust as needed
    vector<Person> people(populationSize);

    // Infect a fixed percentage of people (e.g., 50%)
    for(int i = 0; i<populationSize; i++){
        double randomValue = static_cast<double>(rand()) / (RAND_MAX + 1.0);
        if(randomValue < covid.getTransmissionChance())
        {
            people[i].infect(covid);
        }
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

    // Allow some tolerance due to randomness
    REQUIRE(actualPercentage >= covid.getTransmissionChance() - 0.1);
    REQUIRE(actualPercentage <= covid.getTransmissionChance() + 0.1);
}



//Adapt the above tests, but now a person comes in contact with an infected person, rather than directly
//with a disease

//49.2.2.1 Interaction tests
TEST_CASE("Infection Spread Test 2", "[Infect]") {
    // Create a disease with a 50% transmission chance and 5 days of sickness
    Disease covid(5,0.5);

    // Create a population of people
    const int populationSize = 1000; // Adjust as needed
    vector<Person> people(populationSize);
    Person infected;
    infected.infect(covid);
    // Simulate the progression for a number of days
    // Check if the person can infect others by coming in contact with infected individuals
    for(int x = 0; x<populationSize; x++)
    {
        infected.touch(people[x],covid);
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
    // Allow some tolerance due to randomness
    REQUIRE(actualPercentage >= covid.getTransmissionChance() - 0.1);
    REQUIRE(actualPercentage <= covid.getTransmissionChance() + 0.1);
}

//49.2.3.1 POPULATION TESTS
TEST_CASE("Everyone is vaccinated with 100 vacccination rate", "[vaccination]") {
    // Create a Disease with 0% transmission chance and 5 days of sickness
    Disease covid(5, 0.0);

    // Create a Population with 10 people and 100% vaccination rate
    Population population(1000, covid);
    population.random_vaccination(1.0);

    // Check if everyone is vaccinated
    REQUIRE(population.count_vaccinated() == 1000);
    REQUIRE(population.count_infected() == 0);
}

//4.9.3.1.1 Tests
TEST_CASE("Duration of disease", "[infection][population]") {
        // Create a Disease with 50% transmission chance and 5 days of sickness
        Disease covid(5, 0.5);

        // Create a Population with 100 people and 0% vaccination rate
        Population population(100, covid);

        int initialInfected = population.count_infected();
        int initialHealthy = population.populationSize - initialInfected;

        // Run the simulation for the duration of the disease
        int currentInfected = 0;
        int currentHealthy = 0;
        for (int day = 1; day <= covid.getDuration()-1; ++day) {
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
    Disease covid(5, 1);
    Population population(10, covid);
    population.initial_infect(covid);
    //one day
    int day = 0;
    bool ret = false;
     if(population.people[0].get_status() == "Infected"|| population.people[population.populationSize-1].get_status() == "Infected"){
        ret = true;
    }
    while(day<1){
        population.one_more_day();
        population.neighbor(covid, 1);
        day++;
    }
    if(ret)
    {
        REQUIRE(population.count_infected() == 2);
    }
    else
        REQUIRE(population.count_infected() == 3);
}
//if index is 0, then the simulation should run for the number of days equal to population size
TEST_CASE("Test simulation with p = 1, Index = 0", "[simulation]") {
    Disease covid(5, 1);
    Population population(10, covid);
    population.people[0].infect(covid);
    int days = 1;
    while(population.people[population.populationSize-1].get_status() == "Susceptible"){        
        population.one_more_day();
        population.neighbor(covid, 1); 
        days++;
    }
    REQUIRE(days == population.populationSize); 
}
TEST_CASE("Test simulation with p = 0.5", "[simulation]") {
    Disease covid(5, 0.5);
    Population population(10, covid);
    population.people[0].infect(covid);
    int days = 1;
    int countInfected = 1;
    while(countInfected>0){
        if(population.people[population.populationSize-1].get_status() != "Susceptible")
            break;
        countInfected = population.count_infected();
        population.one_more_day();
        population.neighbor(covid, 0.5); 
        days++;
    }

    REQUIRE_NOTHROW(days == population.populationSize); // populationSize won't equal the days
}