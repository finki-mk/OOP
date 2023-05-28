/*
Дадена е класа User во која се чуваат информации за корисничко име, име на компанијата во која работи и ниво на позицијата во компанијата (број од 1 - 10). Во класата се дефинирани сите потребни конструктори, оператори, set, get методи, оператор за печатење и вчитување. Оваа класа не треба да се менува.

Да се дефинира класа Group што ќе означува група корисници. Во неа се чуваат информации за:

Членовите на групата (динамички алоцирана низа од објекти од класата User)
Големина на групата (број на елементи во низата)
Име на групата (низа од најмногу 50 знаци)
За класата да се имплементираат:

Потребните конструктори и деструктор
метод void addMember (User & u)- што ќе додава нов член во групата. Ако веќе постои член со исто корисничко име, да се фрли исклучок од тип OperationNotSupported. Треба да се обезбеди справување со овој исклучок во функцијата main. При фаќање на овој исклучок да се испечати порака "Username already exists".
метод double rating() - што ќе го пресмета рејтингот на групата со формулата: (10 - просечно_ниво_на_позициите_на_членовите) * број_на_членови / 100.
Да се имплементира класа PrivateGroup во која покрај основните информации за една група ќе се чува и:

Капацитет на приватната група (цел број). Капацитетот е ист за сите приватни групи и иницијално има вредност 10. Тој може да се менува.
За класата да се имплеметнираат потребните конструктори и деструктор.

Во класата PrivateGroup да се препокријат методите од класата Group на следниот начин:

метод void addMember (User & u) - што ќе додава нов член во групата. Да не се дозволи надминување на капацитетот на групата. Ако се направи обид да се додаде член кога капацитетот е исполнет да се фрли исклучок од тип OperationNotSupported. Треба да се обезбеди справување со овој исклучок во функцијата main. При фаќање на овој исклучок да се испечати порака "The group’s capacity has been exceeded.".
метод double rating() - што ќе го пресмета рејтингот на групата со формулата: (10 - просечно_ниво_на_позициите_на_членовите) * (број_на_членови / капацитет_на_група) * коефициент_за_приватна_група. Коефициентот за приватна група е ист за сите приватни групи и изнесува 0.8. Тој не може да се менува!
За двете класи да се дефинира оператор за печатење <<. Форматот на печатење на двете групи погледнете го во првите два тест примера.

*/

#include<string.h>
#include<iostream>
using namespace std;

class OperationNotSupported{
private:
    char msg[50];
public:
    OperationNotSupported(char * msg = "")
    {
        strcpy(this->msg,msg);
    }
    void print()
    {
        cout<<msg<<endl;
    }

};


class User {
    char *username;
    char *companyName;
    int position;

    void copy(const User &u) {
        this->username = new char[strlen(u.username) + 1];
        strcpy(this->username, u.username);
        this->companyName = new char[strlen(u.companyName) + 1];
        strcpy(this->companyName, u.companyName);
        this->position = u.position;
    }

public:
    User(char *username = "", char *companyName = "", int position = 0) {
        this->username = new char[strlen(username) + 1];
        strcpy(this->username, username);
        this->companyName = new char[strlen(companyName) + 1];
        strcpy(this->companyName, companyName);
        this->position = position;
    }

    User(const User &u) {
        copy(u);
    }

    User &operator=(const User &u) {
        if (this != &u) {
            delete[] username;
            delete[] companyName;
            copy(u);
        }
        return *this;
    }

    ~User() {
        delete[] username;
        delete[] companyName;
    }

    char *getUsername() const {
        return username;
    }

    void setUsername(char *username) {
        this->username = new char[strlen(username) + 1];
        strcpy(this->username, username);
    }

    char *getCompanyName() const {
        return companyName;
    }

    void setCompanyName(char *companyName) {
        this->companyName = new char[strlen(companyName) + 1];
        strcpy(this->companyName, companyName);
    }

    int getPosition() const {
        return position;
    }

    void setPosition(int position) {
        this->position = position;
    }


    friend ostream &operator<<(ostream &os, const User &user) {
        return os << "Username: " << user.username
                  << " Company name: " << user.companyName
                  << " Position: " << user.position;
    }

    friend istream &operator>>(istream &in, User &user) {
        return in >> user.username >> user.companyName >> user.position;
    }

    bool operator==(User &u) {
        return strcmp(this->username, u.username) == 0;
    }
};


class Group{
protected:
    User * users;
    int n;
    char ime[50];
public:
    Group(char * ime = "")
    {
        strcpy(this->ime,ime);
        users = 0;
        n = 0;
    }
    Group(const Group & g)
    {
        strcpy(this->ime,g.ime);
        users = new User[g.n];
        n = g.n;
        for(int i=0;i<n;i++)
        {
            users[i] = g.users[i];
        }
    }
    Group& operator=(const Group & g)
    {
        if(this!=&g){
            strcpy(this->ime,g.ime);
            delete [] users;
            users = new User[g.n];
            n = g.n;
            for(int i=0;i<n;i++)
            {
                users[i] = g.users[i];
            }
        }
        return *this;
    }
    ~Group()
    {
        delete [] users;
    }
  double getAvgPosition()
    {
        if(n==0)
            return 0;
        int sum = 0;
        for(int i=0;i<n;i++)
        {
            sum+=users[i].getPosition();
        }
        return (double)sum/n;
    }
virtual double rating(){
    return (10-getAvgPosition())*n/100;
    }

 virtual  void addMember(User & u)
    {
        for(int i=0;i<n;i++)
        {
            if(strcmp(users[i].getUsername(),u.getUsername())==0)
            {
                throw OperationNotSupported("Username already exists");
            }
        }

            User * temp = new User[n+1];
            for(int i=0;i<n;i++)
            {
                temp[i]= users[i];
            }
            temp[n++] = u;
            delete [] users;
            users = temp;
    }

    friend ostream& operator<<(ostream & out, Group & g)
    {
        out<<"Group: "<<g.ime<<endl;
        out<<"Members: "<<g.n<<endl;
        out<<"Rating: "<<g.rating()<<endl;
        out<<"Members list:"<<endl;
        for(int i=0;i<g.n;i++)
        {
          out<<i+1<<". ";
          out<<g.users[i]<<endl;
        }
        return out;
    }

};
class PrivateGroup:public Group{
private:
    static int capacity;
    const static float koeficient;
public:
    PrivateGroup(char * ime = "")
    :Group(ime){}
    static int getCapacity(){return capacity;}
    static void setCapacity(int newCapacity)
    {
        capacity = newCapacity;
    }
    void addMember(User & u)
    {
        if(n>=capacity)
        {
            throw OperationNotSupported("The group�s capacity has been exceeded.");
        }
        Group::addMember(u);
    }
    double rating()
    {
        return (10-getAvgPosition())*(n/capacity)*koeficient;
    }
    friend ostream& operator<<(ostream & out,PrivateGroup & g)
    {

        out<<"Private Group: "<<g.ime<<endl;
        out<<"Members: "<<g.n<<endl;
        out<<"Rating: "<<g.rating()<<endl;
        out<<"Members list:"<<endl;
        if(g.n==0)
        {
            out<<"EMPTY"<<endl;
        }
        else
        {
        for(int i=0;i<g.n;i++)
        {
          out<<i+1<<". ";
          out<<g.users[i]<<endl;
        }
        }
        return out;
    }
};
int PrivateGroup::capacity = 10;
const float PrivateGroup::koeficient = 0.8;

int main() {
    int testCase;
    cin >> testCase;
    if (testCase == 1) {
        cout << "TESTING CLASS GROUP: CONSTRUCTOR AND OPERATOR <<" << endl;
        Group g("test");
        cout << g;
    } else if (testCase == 2) {
        cout << "TESTING CLASS PRIVATE GROUP: CONSTRUCTOR AND OPERATOR <<" << endl;
        PrivateGroup pg("private test");
        cout << pg;
    } else if (testCase == 3) {
        cout << "TESTING CLASS GROUP: CONSTRUCTOR, METHOD ADD_MEMBER AND OPERATOR <<" << endl;
        Group *g = new Group("FINKI students");
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            User u;
            cin >> u;
            g->addMember(u);
        }
        cout << *g;
        delete g;
    } else if (testCase == 4) {
        cout << "TESTING CLASS PRIVATE_GROUP: CONSTRUCTOR, METHOD ADD_MEMBER AND OPERATOR <<" << endl;
        Group *g = new PrivateGroup("FINKI students");
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            User u;
            cin >> u;
            g->addMember(u);
        }
        cout << *g;
        delete g;
    } else if (testCase == 5) {
        cout << "TESTING CLASS GROUP: CONSTRUCTOR, METHOD ADD_MEMBER, EXCEPTION AND OPERATOR <<" << endl;
        Group *g = new Group("FINKI students");
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            User u;
            cin >> u;
            try {
                g->addMember(u);
            } catch (OperationNotSupported &e) {
                e.print();
            }
        }
        cout << *g;
        delete g;
    } else if (testCase == 6) {
        cout << "TESTING CLASS PRIVATE GROUP: CONSTRUCTOR, METHOD ADD_MEMBER, EXCEPTION AND OPERATOR <<" << endl;
        Group *g = new PrivateGroup("FINKI");
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            User u;
            cin >> u;
            try {
                g->addMember(u);
            } catch (OperationNotSupported e) {
                e.print();
            }
        }
        cout << *g;
        delete g;
    } else if (testCase == 7) {
        cout << "TESTING CLASS PRIVATE GROUP: CONSTRUCTOR, METHOD ADD_MEMBER AND CHANGE OF STATIC MEMBER"
             << endl;
        Group *g = new PrivateGroup("FINKI");
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            User u;
            cin >> u;
            g->addMember(u);
        }
        cout << "RATING BEFORE CHANGE" << endl;
        cout << g->rating();
        PrivateGroup::setCapacity(20);
        cout << "RATING AFTER CHANGE" << endl;
        cout << g->rating();
        delete g;
    }
    else if (testCase==8) {
        cout << "TESTING CLASS PRIVATE GROUP: CONSTRUCTOR, METHOD ADD_MEMBER, EXCEPTION AND CHANGE OF STATIC MEMBER"
             << endl;

        Group *g = new PrivateGroup("FINKI");
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            User u;
            cin >> u;
            try {
                g->addMember(u);
            } catch (OperationNotSupported & e) {
                int capacity = PrivateGroup::getCapacity();
                cout<<"Increasing capacity from "<<capacity<<" to "<<capacity+1<<endl;
                PrivateGroup::setCapacity(capacity+1);
                g->addMember(u);
                cout<<g->rating()<<endl;
            }
        }

    }else {
        cout<<"INTEGRATION TEST"<<endl;
        char name [50];
        int nGroups;
        cin>>nGroups;
        Group ** groups = new Group * [nGroups];
        for (int i=0;i<nGroups;i++) {
            int type;
            cin>>type;
            cin>>name;
            if (type==1) { //normal group
                groups[i] = new Group(name);
            } else { //private group
                groups[i] = new PrivateGroup(name);
            }
            int nUsers;
            cin>>nUsers;
            for (int j=0;j<nUsers;j++) {
                User u;
                cin>>u;
                try {
                    groups[i]->addMember(u);
                } catch (OperationNotSupported e) {
                    e.print();
                }
            }
        }

        cout<<"BEFORE CHANGE OF PRIVATE GROUP COEFFICIENT"<<endl;
        for (int i = 0; i < nGroups; ++i) {
            cout<<*groups[i];
        }
        PrivateGroup::setCapacity(15);
        cout<<"AFTER CHANGE OF PRIVATE GROUP COEFFICIENT"<<endl;
        for (int i = 0; i < nGroups; ++i) {
            cout<<*groups[i];
        }
    }
}
