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
    REQUIRE(person.get_status() == "Infected"); //status must be infected
}

TEST_CASE("Contact with vaccinated/recovered person and disease", "[Person]") {
    Disease disease(7,1.0); 

    Person vaccinatedPerson("Vaccinated", 0); 
    Person recoveredPerson("Recovered", 0);

    vaccinatedPerson.infect(disease);
    recoveredPerson.infect(disease);

    //must be vaccinated and recovered
    REQUIRE(vaccinatedPerson.get_status() == "Vaccinated");
    REQUIRE(recoveredPerson.get_status() == "Recovered");
}

TEST_CASE("Infection Spread Test", "[Infection]") {
    //5 days of sickness, 50% transmission chance
    Disease disease(5,0.5);

    const int populationSize = 10000; 
    vector<Person> people(populationSize); //vector of people 

    for(int i = 0; i<populationSize; i++){
        double randomValue = static_cast<double>(rand()) / (RAND_MAX + 1.0);
        if(randomValue < disease.getTransmissionChance()) //infects based on disease transmission
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
    Disease disease(5,0.5);

    const int populationSize = 10000; 
    vector<Person> people(populationSize);
    Person infected;
    infected.infect(disease);

    for(int x = 0; x<populationSize; x++)
    {
        people[x].touch(infected,disease); //infects based off of touch method, which follows disease transmission
    }

    int numSick = 0;
    for (auto& person : people) {
        if (person.get_status() == "Infected") {
            numSick++; //counts infected
        }
    }

    //get half of population
    double actualPercentage = static_cast<double>(numSick) / populationSize;
    //tolerance
    REQUIRE(actualPercentage >= disease.getTransmissionChance() - 0.1);
    REQUIRE(actualPercentage <= disease.getTransmissionChance() + 0.1);
}

//49.2.3.1 POPULATION TESTS
TEST_CASE("Everyone is vaccinated with 100 vacccination rate", "[vaccination]") {
    Disease disease(5, 0.0); //0% transmission rate

    Population population(10000, disease);
    population.random_vaccination(1.0); //randomly vaccinates

    // Check if everyone is vaccinated
    REQUIRE(population.count_vaccinated() == 10000);
    REQUIRE(population.count_infected() == 0);
}

//4.9.3.1.1 Tests
TEST_CASE("Duration of disease", "[infection][population]") {
        Disease disease(5, 0.5);
        Population population(10000, disease);

        int initialInfected = population.count_infected();
        int initialHealthy = population.populationSize - initialInfected;


        int currentInfected = 0;
        int currentHealthy = 0;
        for (int day = 1; day <= disease.getDuration()-1; ++day) { //runs until disease dies out
            population.one_more_day();
            currentInfected = population.count_infected();
            currentHealthy = population.populationSize - currentInfected; //rest of population

            REQUIRE(currentInfected == initialInfected);
            REQUIRE(currentHealthy + currentInfected == population.populationSize);

    }
}

//49.3.2.1 sanity tests 
TEST_CASE("Test simulation with p = 1", "[simulation]") {
    srand( (unsigned)time( NULL ) );
    //tests if random index is sick, next day 3 are sick
    Disease disease(5, 1);
    Population population(10000, disease);
    int randomNum = rand() % 10000;
    population.people[randomNum].infect(disease);
    int index = 0;
    for(int x = 0; x<population.people.size(); x++){
        if(population.people[x].get_status() == "Infected"){
            index = x; //finds infected indexx
        }
    }
    //one day
    int day = 0;
    bool ret = false;
    if(population.people[0].get_status() == "Infected"|| population.people[population.populationSize-1].get_status() == "Infected"){
        ret = true; //if index 0 or last index is infected
    }
    population.one_more_day();
    population.neighbor(disease, 1, index);
    if(ret)
    {
        REQUIRE(population.count_infected() == 2); //if index 0 or last index is infected
    }
    else
        REQUIRE(population.count_infected() == 3); //if any other index is infected
}
//if index is 0, then the simulation should run for the number of days equal to population size
TEST_CASE("Test simulation with p = 1, Index = 0", "[simulation]") {
    Disease disease(5, 1); 
    Population population(10000, disease);
    population.people[0].infect(disease); //first index is infected
    int days = 1;
    int x = 0;
    while(x < population.populationSize-1){
        population.one_more_day();
        population.neighbor(disease, 1, x); //goes through neighbor function for each index
        days++;
        x++;
    }
    REQUIRE(days == population.populationSize); //days should equal population size
}
TEST_CASE("Test simulation with p = 0.5", "[simulation]") {
    Disease disease(5, 0.5); 
    Population population(10000, disease);
    population.people[0].infect(disease); 
    int days = 1;
    int x = 0;
    while(x < population.populationSize-1){
        population.one_more_day();
        population.neighbor(disease, 0.5, x); //0.5 transmission rate
        days++;
        x++;
    }
    REQUIRE_NOTHROW(days == population.populationSize); // populationSize won't equal the days
}