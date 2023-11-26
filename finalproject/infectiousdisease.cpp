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
//49.2.1.1
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
//49.2.2.1
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
