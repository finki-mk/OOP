#include <iostream>
#include <cstring>
using namespace std;

class Flight{
private:
    char gradPoletuvanje[100];
    char gradSletuvanje[100];
    float cena;
    float vremetraenje;
public:
    Flight(char * gradPoletuvanje = "",
           char * gradSletuvanje = "",
           float vremetraenje = 0.0,
           float cena = 0.0)
           {
               strcpy(this->gradPoletuvanje, gradPoletuvanje);
               strcpy(this->gradSletuvanje, gradSletuvanje);
               this->vremetraenje = vremetraenje;
               this->cena = cena;
           }

    void printDuration(){
        int cas = (int) vremetraenje;
        float ostatok = vremetraenje - cas;
        int minuti = ostatok *60;
        cout<<cas<<"h:"<<minuti<<"min";
    }
    void printFlight()
    {
        cout<<gradPoletuvanje<<" -> ";
        printDuration();
        cout<<" -> "<<gradSletuvanje<<": "<<cena<<"EUR"<<endl;
    }
    friend class Airline;
    char * getDepartureCity()
    {
        return gradPoletuvanje;
    }
    char * getArrivalCity()
    {
        return gradSletuvanje;
    }
};

class Airline{
private:
    char ime[100];
    Flight * letovi;
    int n;
public:
    Airline(char * ime = "")
    {
        strcpy(this->ime,ime);
        letovi = 0;
        n = 0;
    }
    ~Airline()
    {
        delete [] letovi;
    }
    Flight * getFlights()
    {
        return letovi;
    }
    Airline(const Airline & dr)
    {
        strcpy(this->ime, dr.ime);
        n = dr.n;
        letovi = new Flight[n];
        for(int i=0;i<n;i++)
        {
            letovi[i] = dr.letovi[i];
        }
    }
    int getN()
    {
        return n;
    }
    Airline & operator=(const Airline & dr)
    {
        if(this!=&dr){
        strcpy(this->ime, dr.ime);
        n = dr.n;
        delete [] letovi;
        letovi = new Flight[n];
        for(int i=0;i<n;i++)
        {
            letovi[i] = dr.letovi[i];
        }
        }
        return *this;
    }
    void addFlight(Flight & nov)
    {
        int flag =0;
        for(int i=0;i<n;i++){
           if(strcmp(letovi[i].gradPoletuvanje,nov.gradPoletuvanje)==0
              &&strcmp(letovi[i].gradSletuvanje,nov.gradSletuvanje)==0)
           {
              flag = 1;
           }
        }
        if(flag ==0)
        {
            Flight * temp = new Flight[n+1];
            for(int i=0;i<n;i++)
            {
                temp[i] = letovi[i];
            }
            temp[n++] = nov;
            delete [] letovi;
            letovi = temp;
        }

    }
    friend void searchFlights(Airline a, char departureCity[], char arrivalCity[]);

};


void searchFlights(Airline a, char departureCity[], char arrivalCity[])
{
    int flag = 0;
    for(int i=0;i<a.n;i++)
    {
        if(strcmp(a.letovi[i].getDepartureCity(),departureCity)==0
           &&strcmp(a.letovi[i].getArrivalCity(),arrivalCity)==0)
        {
            flag = 1;
            a.letovi[i].printFlight();
            return;
        }
    }

    for(int i=0;i<a.n;i++)
    {
         if(strcmp(a.letovi[i].getDepartureCity(), departureCity) == 0){
            for(int j = 0; j < a.n; j++){
                if(strcmp(a.letovi[j].getDepartureCity(), a.letovi[i].getArrivalCity()) == 0
                   && strcmp(a.letovi[j].getArrivalCity(), arrivalCity) == 0){
                    flag = true;
                    a.letovi[i].printFlight();
                    cout << " 1 stop ";
                    a.letovi[j].printFlight();
                    cout << endl;
                }
            }
        }
    }
    if(flag==0)
    {
        cout<<"Ne se pronajdeni letovi"<<endl;
    }
}


int main(){

    int testCase;
    cin >> testCase;

    if(testCase == 1){
        cout << "====Testing class Flight constructors and additional methods====" << endl;
        Flight f1;
        char dep[50], arr[50];
        double dur, pr;
        cin >> dep >> arr >> dur >> pr;
        Flight f2(dep, arr, dur, pr);
        cout << f2.getDepartureCity() << " " << f2.getArrivalCity() << endl;
        cout << "Testing OK" << endl;
    }
    else if(testCase == 2){
        cout << "====Testing class Flight methods printDuration() and printFlight()====" << endl;
        char dep[50], arr[50];
        double dur, pr;
        cin >> dep >> arr >> dur >> pr;
        Flight f2(dep, arr, dur, pr);
        f2.printFlight();
        cout << endl;
    }
    else if(testCase == 3){
        cout << "====Testing class Airplane constructors and methods====" << endl;
        Airline a("Wizzair");
        char dep[50], arr[50];
        double dur, pr;
        cin >> dep >> arr >> dur >> pr;
        Flight f1(dep, arr, dur, pr);
        a.addFlight(f1);
        Flight f3 = f1;
        a.addFlight(f3);
        a.getFlights()[0].printFlight();
        cout << endl;
        cout << a.getN() << endl;
        Airline b = a;
        b.getFlights()[0].printFlight();
        cout << endl;
        cin >> dep >> arr >> dur >> pr;
        Flight f2(dep, arr, dur, pr);
        b.addFlight(f2);
        b.getFlights()[1].printFlight();
        cout << endl;
        cout << "Testing OK" << endl;
    }
    else if(testCase == 4){
        cout << "====Testing global function====" << endl;
        Airline a("Wizzair");
        char dep[50], arr[50];
        double dur, pr;
        int n;
        cin >> n;
        for(int i = 0; i < n; i++){
            cin >> dep >> arr >> dur >> pr;
            Flight f(dep, arr, dur, pr);
            a.addFlight(f);
        }
        cin >> dep >> arr;
        searchFlights(a, dep, arr);
        cout << endl << "Testing OK" << endl;
    }

    return 0;
}
