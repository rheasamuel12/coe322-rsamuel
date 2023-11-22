// Name: Rhea Samuel
// UTEID:rss3488
// TACC Username: rheasamuel12 
//Final Project: Infectious Disease Simulation

#include <iostream>
#include <iomanip>
using namespace std;
#include "infectiousdisease.hpp"
#define CATCH_CONFIG_MAIN
#include "catch2/catch_all.hpp"




TEST_CASE("Infection with 100% transmittable disease", "[Person]") {
    Disease covid(1.0, 5); // 100% transmission chance, 5 days of infection
    Person person;
    // After being infected, the person should register as sick
    person.infect(covid);
    REQUIRE(person.get_status() == "Infected");
}

TEST_CASE("Contact with vaccinated/recovered person and disease", "[Person]") {
    Disease covid(0.5, 7); // 50% transmission chance
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

TEST_CASE("Transmission chance test", "[Person]") {
    // Disease with 50% transmission chance
    Disease covid(0.5, 7);

    int numPeople = 1000; // Number of people in contact
    int numInfected = 0;

    // Simulate contact with the disease for each person
    for (int x = 0; x< numPeople; x++) {
        Person person;
        person.infect(covid);

        if (person.get_status() == "Infected") {
            numInfected++;
        }
    }

    // About half of the people should get sick
    double expectedPercentage = 0.5;
    double actualPercentage = static_cast<double>(numInfected) / numPeople;

    // Allow some tolerance due to random nature
    REQUIRE(actualPercentage >= expectedPercentage - 0.1);
    REQUIRE(actualPercentage <= expectedPercentage + 0.1);
}