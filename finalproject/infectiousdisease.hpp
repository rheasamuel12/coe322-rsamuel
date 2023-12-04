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
#ifndef INFECTIOUSDISEASE_HPP
#define INFECTIOUSDISEASE_HPP



class Disease{
    private:
    double transmission_probability;
    int duration;
    
    public:
    Disease(int daysSick): duration(daysSick){}    
    //exercise 49.2
    Disease(int daysSick, double transmissionChance) 
        :duration(daysSick) , transmission_probability(transmissionChance){
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
            if (randomValue < disease.getTransmissionChance()) {
                infect(disease);
            }
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

     void initial_infect(Disease& disease){
        int randomValue = rand() % populationSize;
        if(people[randomValue].get_status() == "Susceptible")
            people[randomValue].infect(disease);
     }
    void random_infectious(double percent, Disease& disease){
        int infectedPeople = percent*populationSize;
        int x = 0;
        double randomValue = 0.0;
        while(x<infectedPeople){
            randomValue = rand() % populationSize;
            if(people[randomValue].get_status() == "Susceptible"){
                people[randomValue].infect(disease);
                x++;
            }
        }
    }
    void random_vaccination(double percent){
        int vaccinatedPeople = percent*populationSize;
        int x = 0;
        double randomValue = 0.0;
        while(x<vaccinatedPeople){
            randomValue = rand() % populationSize;
            if(people[randomValue].get_status() == "Susceptible" || people[randomValue].get_status() == "Recovered"){
                people[randomValue].set_vaccinated();
                x++;
            }
        }

    }
    
    vector<int> get_random_vaccination_index(){
        vector <int> index;
        for(int x = 0; x<populationSize; x++){
            if(people[x].get_status() == "Vaccinated"){
                index.push_back(x);
            }
        }
        return index;
    }
    int count_vaccinated(){
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
    int count_infected(){
        int infected = 0;
        for(int x = 0; x<populationSize; x++)
        {
            if(people[x].get_status() == "Infected"){
                infected++;
            }
        }
        return infected;
    }

    int count_recovered(){
        int recovered = 0;
        for(int x = 0; x<populationSize; x++)
        {
            if(people[x].get_status() == "Recovered"){
                recovered++;
            }
        }
        return recovered;
    }

    int count_healthy(){
        int healthy = 0;
        for(int x = 0; x<populationSize; x++)
        {
            if(people[x].get_status() == "Susceptible"){
                healthy++;
            }
        }
        return healthy;
    }
    void one_more_day(){
        for(int x = 0; x< populationSize;++x){
            people[x].one_more_day();
        }
    }

    string toStringOne(){
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
    void neighbor(Disease& disease, double probability, int x){
        if(x>0 && x<populationSize-1){
            people[x+1].touch(people[x],disease);
            people[x-1].touch(people[x],disease);
        }
        else if(x==0){
            people[x+1].touch(people[x],disease);
        }
        else if(x==populationSize-1){
            people[x-1].touch(people[x],disease);
        }
    }
//49.3.4  
    void random_contact_infection(Disease& disease, int max_contact, int index){
        int x = 0;
        double randomValue = -1.0;
        while(x<max_contact){
            randomValue = rand() % populationSize;
            if(index != randomValue){
                people[randomValue].touch(people[index],disease);
                x++;
            }
        }
    }
};

#endif
