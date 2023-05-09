#include<iostream>
#include <cmath>
#include<string.h>
#include <ctime>
#include <cstring>
#include <vector>
#include<algorithm>
using namespace std;

    class Planet {
    public:
        string name;
        int x, y, z;
    public:
    Planet()
    {
        cout<<"this is default"<<endl;
    }
        Planet(string name, int x, int y, int z) {
            this->name = name;
            this->x = x;
            this->y = y;
            this->z = z;
        }
        string getName() {
            return name;
        }
        int getX() {
            return x;
        }
        int getY() {
            return y;
        }
        int getZ() {
            return z;
        }
        int getCoordinates()
        {
            return x,y,z;
        }
        double getDistance(Planet& other) {
            int dx = x - other.getX();
            int dy = y - other.getY();
            int dz = z - other.getZ();
            return sqrt(dx*dx + dy*dy + dz*dz);
        }
};
class Moon : public Planet{
    public:
    int atmosphere;
    int waterlevel;
    Moon(int atmosphere,int waterlevel)
    {
        this->atmosphere=atmosphere;
        this->waterlevel=waterlevel;
    }
    int getatmosphere()
    {
        return atmosphere;
    }
    int getwaterlevel()
    {
        return waterlevel;
    }
};
class Mars : public Planet{
    public:
    int inhabitants;
    int waterlevel;
    Mars(int inhabitants,int waterlevel)
    {
        this->inhabitants=inhabitants;
        this->waterlevel=waterlevel;
    }
    int getinhabitants()
    {
        return inhabitants;
    }
    int getwaterlevel()
    {
        return waterlevel;
    }
};
class Earth : public Planet{
    public:
    int landlevel;
    int waterlevel;
    Earth(int landlevel,int waterlevel)
    {
        this->landlevel=landlevel;
        this->waterlevel=waterlevel;
    }
    int getlandlevel()
    {
        return landlevel;
    }
    int getwaterlevel()
    {
        return waterlevel;
    }
};
class Traveller {
private:
    
    int validityYears;
public:
    static int idcount;
    string name;
    int id=++idcount;
    Traveller(string name, int validityYears) :
        name(name),  validityYears(validityYears) {}

    string getName() 
    { 
        return name; 
    }
    int getId() 
    { 
        return id;
    }
    int getValidityYears()
    { 
        return validityYears; 
    }
    void setValidityYears(int years) 
    { 
        validityYears = years; 
    }
    virtual string getType() 
    { 
        return "Traveller"; 
    }
};

// Astronaut class
class Astronaut : public Traveller {
private:
    int experienceYears;
    
public:
    Astronaut(string name, int id, int experienceYears) :
        Traveller(name,  -1), experienceYears(experienceYears) {}
    int getExperienceYears()
    { 
        return experienceYears; 
    }
    
    virtual string getType() 
    { 
        return "Astronaut"; 
    }
};


// Commander class
class Commander : public Traveller {
private:
    string authority;
public:
    vector<Commander*> commanders;
    Commander(string name, int id, string authority) :
        Traveller(name, -1), authority(authority) {}
        
        
    string getAuthority()
    { 
        return authority; 
    }
    virtual string getType() 
    { 
        return "Commander"; 
    }
    void getList()
    {
        for(int i=0;i<=commanders.size();i++)
        {
            cout<<i<<". "<<(commanders[i])->name<<endl;
        }
    }
    // void checkUpcomingTravel(SpaceTravel& travel)
    // {
        
    // }
};
int Traveller::idcount=0;
class Ticket {
private:
    
    double price;
    
public:
    friend class Traveller;
    Traveller* passenger;
    int passenger_id;
    int validity;
    Planet* source;
    Planet* destination;
    time_t travel_date;
    time_t booking_date;
    bool is_return_ticket;
    bool is_valid;
    double distance;
    static int ticketcount;

    Ticket(Traveller* passenger, Planet* source, Planet* destination, time_t travel_date, bool is_return_ticket) {
        this->passenger = passenger;
        
        this->source = source;
        this->destination = destination;
        this->travel_date = travel_date;
        booking_date = time(NULL);
        this->is_return_ticket = is_return_ticket;
        
        passenger_id=++ticketcount;
        
        validity=10;
        is_valid=true;
        // calculate price
        double K = 100; // constant
        time_t now = time(NULL);
        double days_to_travel = abs(difftime(travel_date, now)) / (60 * 60 * 24);
        price = (days_to_travel + 1) * K*distance;
    }
    int setvalidity(int val)
    {
        validity=val;
    }
    void verify()
    {
        if(validity>0 && validity<=10)
            is_valid=true;
        else
            is_valid=false;
    }
    int setis_valid(bool valid)
    {
        is_valid=valid;
    }
    double getprice()
    {
        return price;
    }
    void setdistance(double dist)
    {
        distance=dist;
    }
    void Bookticket()
    {
        if(is_valid)
        cout<<"your ticket is booked, kindly do Viewticket to print your ticket"<<endl;
        else
        cout<<"you are not eligible"<<endl;
    }
    void viewTicket() {
        if(is_valid){
        cout << "Passenger Name: " << passenger->getName() << endl;
        cout << "Passenger ID: " << passenger_id << endl;
        cout << "Source: " << source->getName() << endl;
        cout << "Destination: " << destination->getName() << endl;
        cout << "Travel Date: " << ctime(&travel_date);
        cout << "Booking Date: " << ctime(&booking_date);
        cout << "Price: " << price << endl;
        cout << "Is Return Ticket: " << (is_return_ticket ? "Yes" : "No") << endl;
        cout << "Valid: " << validity <<" years"<< endl;
        }
    }
    ~Ticket(){
        
    }
    void deleteTicket() {
        is_valid = false;
        ticketcount--;
        passenger_id--;
        cout<<"your ticket is deleted"<<endl;
        this->~Ticket();
        
    }

    
    void updateTicket(Traveller* name, Planet* src, Planet* dest, time_t date, bool is_return) {
        passenger = name;
        source = src;
        destination = dest;
        travel_date = date;
        is_return_ticket = is_return;

        // recalculate price
        double K = 100; // constant
        time_t now = time(NULL);
        double days_to_travel = abs(difftime(travel_date, now)) / (60 * 60 * 24);
        price = (days_to_travel + 1) * K*distance;
    }
};
int Ticket::ticketcount=0;


//global vector
vector<Traveller*> travellers;

class SpaceTravel{
    private:
    

public:
    // Member variables
    int id;
    int max_passengers;
    int num_passengers;
    Planet* source_planet;
    Planet* destination_planet;
    
    Astronaut* astronaut;
    Commander* commander;
    time_t departure_date;
    // Constructor
    SpaceTravel(){
            astronaut = nullptr;
            commander = nullptr;
        }
    SpaceTravel(int id, int max_passengers, Planet* source_planet, Planet* destination_planet, time_t departure_date) {
        this->id = id;
        this->max_passengers = max_passengers;
        this->num_passengers = 0;
        this->source_planet = source_planet;
        this->destination_planet = destination_planet;
        this->departure_date = departure_date;
        this->astronaut = nullptr;
        this->commander = nullptr;
    }

    // Member functions
    void addAstronaut(Astronaut* astronaut)
    {
        if(this->astronaut==nullptr)
        {
            this->astronaut=astronaut;
        
            cout << "Astronaut " << astronaut->getName() << " assigned to space travel " << id << endl;
        }
        
    }
    void addCommander(Commander* commander)
    {
        if(this->commander==nullptr)
        {
            this->commander=commander;
            cout << "Commander " << commander->getName() << " assigned to space travel " << id << endl;
        }
    }
    void updateAstronaut(Astronaut* oldastronaut,Astronaut* newastronaut)
    {
        if(this->astronaut==oldastronaut){
        this->astronaut=newastronaut;
        cout << "Now Astronaut " << astronaut->getName() << " assigned to space travel " << id << endl;
        }

    }
    void updateCommander(Commander* oldcommander,Commander* newcommander)
    {
        if(this->commander==oldcommander){
        this->commander=newcommander;
        cout << "Now Commander " << commander->getName() << " assigned to space travel " << id << endl;
        }

    }
    void addTraveller(Traveller* traveller) {
        if (num_passengers >= max_passengers) {
            cout << "Space travel is already full. Cannot add more passengers." << endl;
            return;
        }

        

        // Add traveller
        travellers.push_back(traveller);
        num_passengers++;

        // Assign astronaut and commander
        // if (traveller->getType() == "Astronaut" && astronaut == nullptr) {            
        // }
        //  else if (traveller->getType() == "Commander" && commander == nullptr) {           
        // }
    }

    void removeTraveller(Traveller* traveller) {
        for (int i = 0; i < travellers.size(); i++) {
            if (travellers[i] == traveller) {
                travellers.erase(travellers.begin() + i);
                num_passengers--;

                // Unassign astronaut or commander if necessary
                if (traveller == astronaut) {
                    astronaut = nullptr;
                } else if (traveller == commander) {
                    commander = nullptr;
                }

                cout << "Traveller " << traveller->getName() << " removed from space travel " << id << endl;
                return;
            }
        }

        cout << "Traveller " << traveller->getName() << " not found on space travel " << id << endl;
    }

    void updateTraveller(Traveller* old_traveller, Traveller* new_traveller) {
        for (int i = 0; i < travellers.size(); i++) {
            if (travellers[i] == old_traveller) {
                

                // Update traveller
                travellers[i] = new_traveller;

                // Assign astronaut or commander if necessary
                            if (new_traveller->getType() == "Astronaut") {
                astronaut = dynamic_cast<Astronaut*>(new_traveller);
            } else if (new_traveller->getType() == "Commander") {
                commander = dynamic_cast<Commander*>(new_traveller);
            }

            cout << "Traveller " << old_traveller->getName() << " updated to " << new_traveller->getName() << " on space travel " << id << endl;
            return;
        }
    }

    cout << "Traveller " << old_traveller->getName() << " not found on space travel " << id << endl;
}

// Getters and setters
// int getId() const {
//     return id;
// }

// int getMaxPassengers() const {
//     return max_passengers;
// }

// int getNumPassengers() const {
//     return num_passengers;
// }

// Planet* getSourcePlanet() const {
//     return source_planet;
// }

// Planet* getDestinationPlanet() const {
//     return destination_planet;
// }

// time_t getDepartureDate() const {
//     return departure_date;
// }

// void setMaxPassengers(int max_passengers) {
//     this->max_passengers = max_passengers;
// }

// void setSourcePlanet(Planet* source_planet) {
//     this->source_planet = source_planet;
// }

// void setDestinationPlanet(Planet* destination_planet) {
//     this->destination_planet = destination_planet;
// }

// void setDepartureDate(time_t departure_date) {
//     this->departure_date = departure_date;
// }

};

int main()
{   
    vector<Ticket*> tickets_travel;
    int i,j,k,count=0,flag=0;

    Planet p("mars",1,1,1);
    Planet q("moon",2,2,2);
    Planet r("earth",3,3,3);
    double dist=p.getDistance(q);
    
    
    time_t departure_date = 02022003; // 30 days from now
    // SpaceTravel travel(1, 10, &p, &q, departure_date);

// Create travellers
    Astronaut astro1("Goku", 233435, 2);
    Astronaut astro2("Mickey", 243546, 3);

    Commander comm1("yoriichi", 24, "USA");
    Commander comm2("MAdara",12345,"India");
    

    Traveller passenger1("rengoku",10);
    Ticket t1(&passenger1,&p,&q,02022003,true);
    t1.Bookticket();
    tickets_travel.push_back(&t1);

    Traveller passenger2("tanjiro",10);
    Ticket t2(&passenger2,&p,&q,02022003,true);
    t2.Bookticket();
    tickets_travel.push_back(&t2);

    Traveller passenger3("naruto",10);
    Ticket t3(&passenger3,&p,&q,02022003,true);
    t3.Bookticket();
    tickets_travel.push_back(&t3);

    
    SpaceTravel travel;

    
    for (i = 0; i<=tickets_travel.size(); i++){
    for ( j = 0; j<=tickets_travel.size(); j++){
        if(i==j)continue;
        for (k = 0; k<=tickets_travel.size(); k++){
            if(j==k || i==k)continue;
    if((tickets_travel[i]->source)->name == (tickets_travel[j]->source )->name
   && (tickets_travel[i]->source)->name == (tickets_travel[k]->source )->name
   && (tickets_travel[i]->destination)->name == (tickets_travel[j]->destination)->name
   && (tickets_travel[i]->destination )->name== (tickets_travel[k]->destination)->name
   && tickets_travel[i]->booking_date == tickets_travel[j]->booking_date
   && tickets_travel[i]->booking_date == tickets_travel[k]->booking_date){
            
            flag = 1;
            break;

    }
    
}
if(flag)break;
    
}
if(flag)break;
}
cout<<flag<<endl;
if(flag){
    travel.id=1; travel.source_planet= tickets_travel[i]->source; travel.destination_planet= tickets_travel[i]->destination; travel.departure_date = tickets_travel[i]->booking_date ;
    travel.addTraveller(tickets_travel[i]->passenger);
            travel.addTraveller(tickets_travel[j]->passenger);
            travel.addTraveller(tickets_travel[k]->passenger);
            travel.addAstronaut(&astro1);
            travel.addCommander(&comm1);
}
    Traveller passenger4("gojo",10);
    Ticket t4(&passenger4,&p,&q,02022003,true);
    t4.Bookticket();
    tickets_travel.push_back(&t4);


    Traveller passenger5("zenitsu",10);
    Ticket t5(&passenger5,&p,&q,02022003,true);
    t5.Bookticket();
    tickets_travel.push_back(&t4);

    Traveller passenger6("inosuke",10);
    Ticket t6(&passenger6,&p,&q,02022003,true);
    t6.Bookticket();
    tickets_travel.push_back(&t4);

    if(travel.source_planet==t4.source && travel.destination_planet == t4.destination && travel.departure_date == t4.booking_date){
    travel.addTraveller(t4.passenger);
    }
    if(travel.source_planet==t5.source && travel.destination_planet == t5.destination && travel.departure_date == t5.booking_date){
    travel.addTraveller(t5.passenger);
    }
    if(travel.source_planet==t6.source && travel.destination_planet == t6.destination && travel.departure_date == t6.booking_date){
    travel.addTraveller(t6.passenger);
    }
    // delete the fourth traveller
    // if(travel.source_planet==t4.source && travel.destination_planet == t4.destination && travel.departure_date == t4.booking_date){
    // travel.removeTraveller(t4.passenger);
    // }
    


// Update traveller
    // travel.updateAstronaut(&astro1,&astro2);
    // travel.updateCommander(&comm1,&comm2);
    
     for( i=0;i<travellers.size();i++)
     {
         cout<<((travellers[i])->name)<<endl;
     }
     for( i=0;i<travellers.size();i++)
     {
         cout<<((travellers[i])->getType())<<endl;
     }    
         for( i=0;i<travellers.size();i++)
     {
         cout<<((travellers[i])->getId())<<endl;
     }
    
    
    return 0;
}    

