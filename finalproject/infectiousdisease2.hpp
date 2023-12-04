// Name: Rhea Samuel
// UTEID:rss3488
// TACC Username: rheasamuel12 
//Final Project: Infectious Disease Simulation

#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include<cstdlib>
using namespace std;
using std::vector;
#ifndef INFECTIOUSDISEASE2_HPP
#define INFECTIOUSDISEASE2_HPP



class Disease{
    private:
    double transmission_probability;
    int duration;
    public:
    static int variant_type;
    static int transmissionCounterForMutation;
    int activeVariant;

    Disease(int daysSick): duration(daysSick){}    
    //exercise 49.2
    Disease(int daysSick, double transmissionChance) 
        :duration(daysSick) , transmission_probability(transmissionChance){
            activeVariant = variant_type;
            //srand (time(NULL));
        }

    Disease(){} //empty constructor

    //exercise 49.3
    void setDuration(int days)
    {
        duration = days;
    }
    void setTransmissionChance(double prob)
    {
        transmission_probability = prob;
    }

    int getDuration() const
    {
        return duration;
    }
    double getTransmissionChance() const
    {
        return transmission_probability;
    }
};

//exercise 49.1
class Person{
    private:
    string status; //status of person (susceptible, infected, recovered, vaccinated)
    int infectiousDays;
    vector<Disease> variants; //variants person already has
    Disease *activeDisease = NULL; 

    public:
    Person() : status("Susceptible"), infectiousDays(1) {}
    Person(string s, int iD) : status(s), infectiousDays(iD){
    }

    void infect(const Disease& disease) {
        if (status == "Susceptible") {
            status = "Infected";
            infectiousDays = disease.getDuration();
        }
        
     }

    string get_status(){ //returns whether person is S,I,R
        return status;
    }
    void set_status(string s){
        if(status!=s){
            status = s;
        }
    }
    void one_more_day(){ //updates the status of the person to the next day
       if(status == "Infected" && infectiousDays>0)
       {
            infectiousDays--;
            isRecovered();
       }
       else if(infectiousDays != -5){ //not vaccinated
            isRecovered();
        }
       
    }
    bool isRecovered(){
        if(infectiousDays<=0)
        {
            status = "Recovered";
            return true;
        }
        return false;
    }

    int get_infectiousDays(){
        return infectiousDays;
    }
    void set_vaccinated(){
        status = "Vaccinated";
        infectiousDays = -5;
    }

    void touch(Person& infected, Disease& disease){
        if (status == "Susceptible" && infected.get_status() == "Infected") {
            double randomValue = static_cast<double>(rand()) / (RAND_MAX + 1.0); // Random value between 0 and 1
            if (randomValue < disease.getTransmissionChance()) { //probability of getting infected
                infect(disease);
            }
        }
    }

//49.3.5 Mutation
    void infectVariant(Disease& disease){ //infects with new variant
        bool checkVector = false;
        for(int x = 0; x<variants.size(); x++){
            if(variants[x].variant_type == disease.variant_type) //checks if person already has variant
            {
                checkVector = true;
            }
        }
        if(disease.transmissionCounterForMutation == 0){  //if its time for new variant
                disease.variant_type+=1; //variant type
                disease.transmissionCounterForMutation = 150; //time until new variant
        }
        if ((status == "Susceptible" || (status == "Recovered" && !checkVector))) {
            activeDisease = new Disease(disease.getDuration(), disease.getTransmissionChance()); //creates new disease object
            status = "Infected";
            infectiousDays = disease.getDuration();
            disease.transmissionCounterForMutation--;
        }
     }

     void recoveredVariants(){
        if(infectiousDays<=0){
            status = "Recovered";
            variants.push_back(*activeDisease);
            activeDisease = NULL; //disease is now null
        }
    }
     
     void touchVariant(Person& infected, Disease& disease){ //touch method but with mutation
        bool checkVector = false;
        for(int x = 0; x<variants.size(); x++){
            if(variants[x].variant_type == disease.variant_type)
            {
                checkVector = true;
            }
        }
        if ((status == "Susceptible"  || (status == "Recovered" && !checkVector)) && infected.get_status() == "Infected") {
            double randomValue = static_cast<double>(rand()) / (RAND_MAX + 1.0); // Random value between 0 and 1
            if (randomValue < disease.getTransmissionChance()) {
                infectVariant(disease);
            }
        }
    }

    void one_more_dayVariant(){ //updates the status of the person to the next day
       if(status == "Infected" && infectiousDays>0)
       {
            infectiousDays--;
            recoveredVariants();
       }
       
    }

     
};

class Population{
    public:
    vector<Person> people;
    int populationSize;
    public:
     Population(int size, Disease& disease): populationSize(size){
        srand( (unsigned)time( NULL ) );
        people.resize(populationSize);
     }

    void random_infectious(double percent, Disease& disease){ //infects a random percentage of people
        int infectedPeople = percent*populationSize;
        int x = 0;
        double randomValue = 0.0;
        while(x<infectedPeople){
            randomValue = rand() % populationSize;
            if(people[randomValue].get_status() == "Susceptible"){ //checks if they are healthy
                people[randomValue].infect(disease);
                x++;
            }
        }
    }
    void random_vaccination(double percent){ //vaccinates a random percentage of people
        int vaccinatedPeople = percent*populationSize;
        int x = 0;
        double randomValue = 0.0;
        while(x<vaccinatedPeople){
            randomValue = rand() % populationSize;
            //can vaccinate if healthy or recovered
            if(people[randomValue].get_status() == "Susceptible" || people[randomValue].get_status() == "Recovered"){
                people[randomValue].set_vaccinated();
                x++;
            }
        }

    }
    int count_vaccinated(){ //returns amount of vaccinated people in population
        int vacc = 0;
        for(int x = 0; x<populationSize; x++)
        {
            if(people[x].get_status() == "Vaccinated")
            {
                vacc++;
            }
        }
        return vacc;
    }
    int count_infected(){ //returns amount of infected people in population
        int infected = 0;
        for(int x = 0; x<populationSize; x++)
        {
            if(people[x].get_status() == "Infected"){
                infected++;
            }
        }
        return infected;
    }

    int count_recovered(){ //returns amount of recovered people in population
        int recovered = 0;
        for(int x = 0; x<populationSize; x++)
        {
            if(people[x].get_status() == "Recovered"){
                recovered++;
            }
        }
        return recovered;
    }

    int count_healthy(){ //returns amount of healthy people in population
        int healthy = 0;
        for(int x = 0; x<populationSize; x++)
        {
            if(people[x].get_status() == "Susceptible"){
                healthy++;
            }
        }
        return healthy;
    }
    void one_more_day(){ //increases the day for each person
        for(int x = 0; x< populationSize;++x){
            people[x].one_more_day();
        }
    }

    string toStringOne(){ //output for the smaller cases
        string ret = "";
        for(Person person: people){
            if(person.get_status() == "Infected"){
                ret += " +";
            }else if(person.get_status() == "Susceptible"){
                ret += " ?";
            }else if(person.get_status() == "Recovered"){
                ret+= " -";
            }
            else{
                ret+= " v";
            }
        }
        return ret;
    }
    void neighbor(Disease& disease, double probability, int x){ //infects the neigbors
        if(x>0 && x<populationSize-1){
            people[x+1].touch(people[x],disease);
            people[x-1].touch(people[x],disease);
        }
        else if(x == 0){ //if its the first index
            people[x-1].touch(people[x],disease);
        }
        else if(x==populationSize-1){ //if its the last index
            people[x-1].touch(people[x],disease);
        }
    }
//49.3.4  
    void random_contact_infection(Disease& disease, int max_contact, int index){ //infected randomly touches a max amount of people 
        int x = 0;
        double randomValue = -1.0;
        while(x<max_contact){
            randomValue = rand() % populationSize; //random value in population size
            if(index != randomValue){
                people[randomValue].touch(people[index],disease);
                x++;
            }
        }
    }

//49.9 mutation
    void random_infectiousVariant(double percent, Disease& disease){ //infects random amount of people based on percent
        int infectedPeople = percent*populationSize;
        int x = 0;
        double randomValue = 0.0;
        while(x<infectedPeople){
            randomValue = rand() % populationSize;
            if(people[randomValue].get_status() == "Susceptible"){
                people[randomValue].infectVariant(disease);
                x++;
            }
        }
    }
    void one_more_dayVariant(){ //one more day increment
        for(int x = 0; x< populationSize;++x){
            people[x].one_more_dayVariant();
        }
    }

    void random_contact_infectionMutation(Disease& disease, int max_contact, int index){ //infected randomly touches a max amount of people
        int x = 0;
        double randomValue = -1.0;
        while(x<max_contact){
            randomValue = rand() % populationSize;
            if(index != randomValue){
                people[randomValue].touchVariant(people[index],disease);
                x++;
            }
        }
    }
    
};

#endif
