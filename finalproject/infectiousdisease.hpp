// Name: Rhea Samuel
// UTEID:rss3488
// TACC Username: rheasamuel12 
//Final Project: Infectious Disease Simulation

#include <iostream>
#include <stdio.h>
#include <vector>
#include<cstdlib>
using namespace std;

#ifndef INFECTIOUSDISEASE_HPP
#define INFECTIOUSDISEASE_HPP

class Disease{
    public:
    double transmission_probability;
    int duration;
    

    //exercise 49.2
    Disease(int daysSick, int transmissionChance) 
        :duration(daysSick) , transmission_probability(transmissionChance){

            srand (time(NULL));
        }

    Disease(){srand (time(NULL));} //empty constructor


    //exercise 49.3
    void setDuration(int days)
    {
        duration = days;
    }
    //exercise 49.3
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
    Person(string s, int iD) : status(s), infectiousDays(iD){}
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
       else{
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
        infectiousDays = 0;
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
    //Disease& disease;

     Population(int size, Disease& disease): populationSize(size){
        srand( (unsigned)time( NULL ) );
        people.resize(populationSize);
        //people[rand() % populationSize].infect(disease);
     }

     void initial_infect(){
        people[rand() % populationSize].infect(disease);
     }
    

    //Population(int size): populationSize(size){}
    void random_infectious(double percent, Disease& disease){
        for(int i = 0; i<populationSize; i++){
            double randomValue = static_cast<double>(rand()) / (RAND_MAX + 1.0);
            if(randomValue < percent)
            {
                people[i].infect(disease);
            }
        }
    }
    void random_vaccination(double percent){
        for(int i = 0; i<populationSize; i++){
            double randomValue = static_cast<double>(rand()) / (RAND_MAX + 1.0);
            if(randomValue < percent)
            {
                people[i].set_vaccinated();
            }
        }
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
            if(people[x].get_status() == "Infected")
            {
                infected++;
            }
        }
        return infected;
    }
    void one_more_day(){
        for(int x = 0; x< populationSize;++x){
            people[x].one_more_day();
        }
    }

    string toStringOne(){
        string ret = "";
        for(Person person: people){
            if(person.get_status() == "Infected")
            {
                ret += " +";
            }else if(person.get_status() == "Susceptible")
            {
                ret += " ?";
            }else if(person.get_status() == "Recovered")
            {
                ret+= " -";
            }
            else{
                ret+= " v";
            }
        }
        return ret;
    }
    void neighbor(Disease& disease, double probability){
        double randomValue = static_cast<double>(rand()) / (RAND_MAX + 1.0);
        int firstIndex = -1;
        int lastIndex = -1;
        for (int x = 0; x < populationSize; ++x) { 
            if(people[x].get_status() == "Infected" && firstIndex < 0){
                firstIndex = x;
            }
            else if(people[x].get_status() == "Infected"){
                lastIndex = x;
            }
        }

        
            if(randomValue<probability){
                //first and last index the same index // ? ? ? ? ? + +
                if(firstIndex>0 && firstIndex<populationSize-1){
                    people[firstIndex+1].infect(disease);
                    people[firstIndex-1].infect(disease);
                }
                if(lastIndex<populationSize-1 && lastIndex>0){
                    people[lastIndex+1].infect(disease);
                    people[lastIndex-1].infect(disease);
                }
                else if(firstIndex==populationSize-1){
                    people[firstIndex-1].infect(disease);
                }
                else if(firstIndex==0){
                    while(people[firstIndex+1].get_status() == "Infected"){
                        firstIndex+=1;
                    }
                    people[firstIndex+1].infect(disease);
                }
                if(lastIndex==populationSize-1){
                    while(people[lastIndex-1].get_status() == "Infected"){
                        lastIndex-=1;
                    }
                    people[lastIndex-1].infect(disease);
                }
            }
    }

};


 /*
int main(){

    Disease covid(5, 0.5);  // disease with 50% transmission chance and 5 days of sickness
   // Person Rhea;
    Population population(10,covid);
    population.intial_infect();
/*
    //exercise 49.4
    int countInfected =0;
    int day = 1;
    do{
        countInfected = population.count_infected();
        cout << "In step " << day++ << " # sick = " << countInfected << ":" << population.toStringOne() << endl ;
        population.one_more_day();
    } while(countInfected>0);

    //exercise 49.5
    int countInfected =0;
    int day = 1;
    do {
        countInfected = population.count_infected();
        cout << "In step " << day++ << " # sick = " << countInfected << ":" << population.toStringOne() << endl;
        // Spread the disease to neighbors
        population.one_more_day();
        population.neighbor(covid, 0.5); // You can adjust the contagion probability
        

    } while (countInfected > 0);

/*
    // On each day, simulate Rhea's progression
    for (int x = 1; x <= 10;x++) {
        Rhea.one_more_day();
        if(Rhea.get_status() == "Infected")/
        {
            cout << "On day " << x << ", Rhea is " << Rhea.get_status() << " (" << Rhea.get_infectiousDays() + 1 << " more days to go)" << endl;
        }
        else
            cout << "On day " << x << ", Rhea is " << Rhea.get_status() << endl;
        // Infect Rhea on day 3
        if (x == 3) {
            Rhea.infect(covid);
            //cout << "Rhea got infected!" << endl;
        }
      
    }

    return 0;
}
*/
#endif
