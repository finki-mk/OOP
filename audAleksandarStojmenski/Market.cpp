#include <iostream>
#include <cstring>
using namespace std;

class Order{
private:
    char ime[100];
    float cena;
    int kolicina;
public:
    Order(char * ime="", float cena=0.0, int kolicina = 0)
    {
        strcpy(this->ime,ime);
        this->cena = cena;
        this->kolicina = kolicina;
    }
    void print()
    {
        cout<<ime<<" "<<kolicina<<" x "<<cena<<endl;
        int novaSuma = price();
        cout<<"Price: "<<novaSuma<<endl;

        cout<<"Total price: "<<novaSuma<<endl;
    }
    float price()
    {
        float novaSuma = cena * kolicina;
        if(novaSuma>15000)
        {
            novaSuma = novaSuma * 0.85;
        }
        return novaSuma;

    }
};

class Invoice{
private:
    long broj;
    Order * naracki;
    int n;
public:
    Invoice(long broj = 0)
    {
        this->broj = broj;
        naracki = 0;
        n = 0;
    }
    ~Invoice()
    {
        delete [] naracki;
    }
    Invoice(const Invoice & dr)
    {
        broj = dr.broj;
        n = dr.n;
        naracki = new Order[n];
        for(int i=0;i<n;i++)
        {
            naracki[i] = dr.naracki[i];
        }
    }
    Invoice & operator=(const Invoice & dr)
    {
        if(this!=&dr){
        broj = dr.broj;
        n = dr.n;
        delete [] naracki;
        naracki = new Order[n];
        for(int i=0;i<n;i++)
        {
            naracki[i] = dr.naracki[i];
        }
        }
        return *this;
    }

    void newOrder(Order & nov)
    {
        Order * temp = new Order[n+1];
        for(int i=0;i<n;i++)
        {
            temp[i] = naracki[i];
        }
        temp[n++] = nov;
        delete [] naracki;
        naracki = temp;
    }
    float calculate()
    {
        float suma = 0;
        for(int i=0;i<n;i++)
        {
            suma+=naracki[i].price();
        }
        return suma;
    }

    float calculateDDV()
    {
        return calculate() * 1.18;
    }

    void print()
    {
     cout<<"Invoice Number: "<<broj<<endl;
     for(int i=0;i<n;i++)
     {
         cout<<i+1<<". ";
         naracki[i].print();
         cout<<endl;
     }
     cout<<"Price: "<<calculate()<<endl;
     cout<<"Tax: "<<calculate()* 0.18<<endl;
     cout<<"Total price: "<< calculateDDV()<<endl;

    }

};


int main() {
	// se testira zadacata modularno
    int testCase;
    cin >> testCase;

	int n, kolicina;
	double cena;
	char ime[100];

	if(testCase == 1) {
        cout << "===== Testiranje na klasata Order ======" << endl;
        cin.get();
        cin >> ime;
        cin >> cena;
        cin >> kolicina;
        Order o(ime, cena, kolicina);
		cout << "Order constructor OK" << endl;
    } else if(testCase == 2) {
        cout << "===== Testiranje na klasata Order so dopolnitelni metodi ======" << endl;
        cin.get();
        cin >> ime;
        cin >> cena;
        cin >> kolicina;
        Order o(ime, cena, kolicina);
		o.print();

    }else if(testCase == 3){
        cout << "===== Testiranje na klasata Invoice so metodot print() ======" << endl;
		Invoice in(123456789);
        in.print();
	}
    else if(testCase == 4) {
        cout << "===== Testiranje na klasata Invoice so metodot newOrder() i dopolnitelni metodi ======" << endl;
		Invoice in(123456789);
		cin>>n;
			for (int i=0;i<n;i++){
				cin.get();
        		cin >> ime;
        		cin >> cena;
        		cin >> kolicina;
        		Order o(ime, cena, kolicina);
				in.newOrder(o);
			}
        in.print();
    }
    else if(testCase == 5) {
        cout << "===== Testiranje kompletna funkcionalnost ======" << endl;
		Invoice in(123456789);
		cin>>n;
			for (int i=0;i<n;i++){
				cin.get();
        		cin >> ime;
        		cin >> cena;
        		cin >> kolicina;
        		Order o(ime, cena, kolicina);
				in.newOrder(o);
			}
        Invoice in_new=in;
        in.print();
        in_new.print();

        cin.get();
        cin >> ime;
        cin >> cena;
        cin >> kolicina;
        Order o(ime, cena, kolicina);
		in.newOrder(o);

        in.print();
        in_new.print();
    }
return 0;
}
