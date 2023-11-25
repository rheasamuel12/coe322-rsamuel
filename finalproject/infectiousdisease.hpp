// Name: Rhea Samuel
// UTEID:rss3488
// TACC Username: rheasamuel12 
//Final Project: Infectious Disease Simulation

#include <iostream>
using namespace std;

#ifndef INFECTIOUSDISEASE_HPP
#define INFECTIOUSDISEASE_HPP

class Disease{
    public:
    double transmission_probability;
    int duration;

    //exercise 49.2
    Disease(int daysSick, int transmissionChance) 
        :duration(daysSick) , transmission_probability(transmissionChance){}

    Disease(){} //empty constructor

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
    void one_more_day(){ //updates the status of the person to the next day
       if(status == "Infected" && infectiousDays>0)
       {
            infectiousDays--;
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
    string get_vaccinated(){
        status = "Vaccinated";
        infectiousDays = 0;
    }

    void touch(Person& infected, Disease& disease){
        if (status == "Susceptible" && infected.get_status() == "Infected") {
            double randomValue = static_cast<double>(rand()) / RAND_MAX; // Random value between 0 and 1
            if (randomValue < disease.getTransmissionChance()) {
                infect(disease);
            }
        }
    }


};

class Population{

};

/*
int main(){
    Disease covid(5, 0.5);  // disease with 50% transmission chance and 5 days of sickness
    Person Rhea;

    // On each day, simulate Rhea's progression
    for (int x = 1; x <= 10;x++) {
        Rhea.one_more_day();
        if(Rhea.get_status() == "Infected")
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