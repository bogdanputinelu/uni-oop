#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

using namespace std;
enum class TipMasina{
    Mini,
    Compact,
    Monovolume
};
class InvalidPersoane:public exception{
public:
    InvalidPersoane()=default;
    const char* what() const noexcept override{
        return "Numar de persoane invalid.";
    }
};

class InvalidAutomobil:public exception{
public:
    InvalidAutomobil()=default;
    const char* what() const noexcept override{
        return "Automobil invalid.";
    }
};
class AlreadyCreated:public exception{
public:
    AlreadyCreated()=default;
    const char* what() const noexcept override{
        return "Creat deja";
    }
};

class Automobil{
protected:
    int pret;
public:
    Automobil(const int& pr=0):pret(pr){}
    virtual ~Automobil()=default;
    Automobil(const Automobil& aut):pret(aut.pret){}
    Automobil& operator=(const Automobil& aut);
    friend istream& operator>>(istream& is,Automobil& a);
    virtual void scan(istream& is);
    friend ostream& operator<<(ostream& os,const Automobil& a);
    virtual void print(ostream& os) const;
    virtual TipMasina getType()const=0;

    int getPret() const;
};
Automobil& Automobil::operator=(const Automobil &aut) {
    if(this==&aut)
        return *this;
    pret=aut.pret;
    return *this;
}
istream& operator>>(istream& is,Automobil& a){
    a.scan(is);
    return is;
}
void Automobil::scan(istream &is) {
    cout<<"Pret:";
    is>>pret;
}
ostream& operator<<(ostream& os,const Automobil& a){
    a.print(os);
    return os;
}
void Automobil::print(ostream &os) const{
    os<<"Pret: "<<pret<<'\n';
}

int Automobil::getPret() const {
    return pret;
}

class Mini:public Automobil{
    int litraj,lung;
public:
    Mini(const int& pr=0,const int& lit=0, const int& l=0):Automobil(pr),litraj(lit),lung(l){}
    Mini(const Mini& m): Automobil(m),litraj(m.litraj),lung(m.lung){}
    Mini& operator=(const Mini& mini);
    void scan(istream& is) override;
    void print(ostream& os) const override;
    TipMasina getType()const override{
        return TipMasina::Mini;
    }

    int getLitraj() const;

    int getLung() const;

};
Mini& Mini::operator=(const Mini& mini){
    Automobil::operator=(mini);
    if(this==&mini)
        return *this;
    litraj=mini.litraj;
    lung=mini.lung;
    return *this;
}
void Mini::scan(istream &is) {
    Automobil::scan(is);
    cout<<"Litraj:";
    is>>litraj;
    cout<<"Lungime:";
    is>>lung;
}
void Mini::print(ostream &os) const {
    Automobil::print(os);
    cout<<"Litraj: "<<litraj<<'\n'<<"Lungime: "<<lung<<'\n';
}

int Mini::getLitraj() const {
    return litraj;
}

int Mini::getLung() const {
    return lung;
}

class Compact:public Automobil{
    int dimensiune;
public:
    Compact(const int& pr=0,const int& d=0): Automobil(pr),dimensiune(d){}
    Compact(const Compact& com): Automobil(com),dimensiune(com.dimensiune){}
    Compact& operator=(const Compact& com);
    void scan(istream& is)override;
    void print(ostream& os) const override;
    TipMasina getType()const override{
        return TipMasina::Compact;
    }

    int getDimensiune() const;
};
Compact& Compact::operator=(const Compact& com){
    Automobil::operator=(com);
    if(this==&com)
        return *this;
    dimensiune=com.dimensiune;
    return *this;
}
void Compact::scan(istream &is) {
    Automobil::scan(is);
    cout<<"Dimensiune:";
    is>>dimensiune;
}
void Compact::print(ostream &os) const {
    Automobil::print(os);
    cout<<"Dimensiune: "<<dimensiune<<'\n';
}

int Compact::getDimensiune() const {
    return dimensiune;
}

class Monovolume:public Automobil{
    int pers,ani;
    bool sh,vara;
    const int discount=10;
public:
    Monovolume(const int& pr=0,const int&p=0,const bool& s=false, const int& a=0): Automobil(pr),pers(p),sh(s),ani(a),vara(false){}
    Monovolume(const Monovolume& mono): Automobil(mono),pers(mono.pers),sh(mono.sh),ani(mono.ani),vara(mono.vara){}
    Monovolume& operator=(const Monovolume& mono);
    void scan(istream& is) override;
    void print(ostream& os) const override;
    TipMasina getType()const override{
        return TipMasina::Monovolume;
    }

    void setVara(const bool& v){
        vara=v;
    }

    bool getVara() const{
        return vara;
    }

    int getPers() const;

    int getAni() const;

    bool isSh() const;
};
Monovolume& Monovolume::operator=(const Monovolume& mono){
    Automobil::operator=(mono);
    if(this==&mono)
        return *this;
    pers=mono.pers;
    sh=mono.sh;
    ani=mono.ani;
    vara=mono.vara;
    return *this;
}
void Monovolume::scan(istream &is) {
    Automobil::scan(is);
    vara= false;
    cout<<"Persoane:";
    is>>pers;
    if(pers<5 || pers>7)
        throw InvalidPersoane();
    cout<<"Introduceti 1 daca masina este second hand, altfel 0:";
    is>>sh;
    ani=0;
    if(sh) {
        cout << "Ani vechime:";
        is >> ani;
    }
}
void Monovolume::print(ostream &os) const {
    Automobil::print(os);
    cout<<"Persoane: "<<pers<<'\n';
    if(sh) {
        os<<"Este second hand cu " << ani<<" ani vechime"<<'\n';
        os<<"Reducere: "<<ani<<"%\n";
        if(vara){
            os<<" + reducere de vara: "<<discount<<"%\n";
        }
    }
}

int Monovolume::getPers() const {
    return pers;
}

int Monovolume::getAni() const {
    return ani;
}

bool Monovolume::isSh() const {
    return sh;
}


class Factory{
public:
    static shared_ptr<Automobil> makeAutomobil(const string &automobil,const int& pret=0,const int& litraj=0,const int& lung=0,const bool& sh= false);
};
shared_ptr<Automobil> makeAutomobil(const string &automobil,const int& pret=0,const int& litraj=0,const int& lung=0,const bool& sh= false){
    if(automobil=="mini")
        return make_shared<Mini>(pret,litraj,lung);
    if(automobil=="compact")
        return make_shared<Compact>(pret,litraj);
    if(automobil=="monovolum")
        return make_shared<Monovolume>(pret,litraj,sh,lung);
    throw InvalidAutomobil();
}
template<typename T>
class Vanzare{
    static bool creat;
    static int nrStoc,nrVandute;
    static vector<shared_ptr<T>> stoc;
    static vector<shared_ptr<T>> vandute;
public:
    Vanzare() {
        if(creat)
            throw AlreadyCreated();
        creat= true;
    }

    static const vector<shared_ptr<T>> &getStoc();

    static int getNrStoc() {
        return nrStoc;
    }

    static int getNrVandute() {
        return nrVandute;
    }

    static void addCar(const shared_ptr<T> &car){
        stoc.push_back(car);
        nrStoc++;
    }
    static void printCarsStoc(){
        int i=0;
        for(auto& car: stoc){
            ++i;
            if(car->getType()==TipMasina::Monovolume) {
                cout<<i << ") Monovolum\n";
                cout<<*car;
            }
            if(car->getType()==TipMasina::Mini) {
                cout<<i << ") Mini\n";
                cout<<*car;
            }
            if(car->getType()==TipMasina::Compact) {
                cout<<i << ") Compact\n";
                cout<<*car;
            }
        }
    }
    static void printCarsVandute(){
        int i=0;
        for(auto& car: vandute){
            ++i;
            if(car->getType()==TipMasina::Monovolume) {
                cout<<i << ") Monovolum\n";
                cout<<*car;
            }
            if(car->getType()==TipMasina::Mini) {
                cout<<i << ") Mini\n";
                cout<<*car;
            }
            if(car->getType()==TipMasina::Compact) {
                cout<<i << ") Compact\n";
                cout<<*car;
            }
        }
    }
    Vanzare<T>& operator-=(shared_ptr<T>& car){
        nrStoc--;
        nrVandute++;
        stoc.erase(remove(stoc.begin(),stoc.end(),car),stoc.end());
        if(car->getType()==TipMasina::Monovolume) {
            int i;
            cout << "Este vara? 1 pentru da, 0 pentru nu: ";
            cin >> i;
            if (i) {
                auto mono = dynamic_pointer_cast<Monovolume>(car);
                mono->setVara(true);
            }
        }
        vandute.push_back(car);
        return *this;
    }

};
template<typename T>
vector<shared_ptr<T>> Vanzare<T>::stoc;
template<typename T>
vector<shared_ptr<T>> Vanzare<T>::vandute;
template<typename T>
int Vanzare<T>::nrStoc=0;
template<typename T>
int Vanzare<T>::nrVandute=0;
template<typename T>
bool Vanzare<T>::creat=false;


template<>
class Vanzare<Monovolume>{
    static bool creat;
    static int nrStoc,nrVandute,nrVanduteVara;
    static vector<shared_ptr<Monovolume>> stoc;
    static vector<shared_ptr<Monovolume>> vandute;
public:
    Vanzare() {
        if(creat)
            throw AlreadyCreated();
        creat= true;
    }

    static const vector<shared_ptr<Monovolume>> &getStoc();

    static int getNrStoc() {
        return nrStoc;
    }

    static int getNrVandute() {
        return nrVandute;
    }

    static int getNrVanduteVara() {
        return nrVanduteVara;
    }

    static void addCar(const shared_ptr<Monovolume> &car){
        stoc.push_back(car);
        nrStoc++;
    }
    static void printCarsStoc(){
        int i=0;
        for(auto& car: stoc){
            ++i;
            cout<<i << ") Monovolum\n";
            cout<<*car;
        }
    }
    static void printCarsVandute(){
        int i=0;
        for(auto& car: vandute){
            ++i;
            cout<<i << ") Monovolum\n";
            cout<<*car;
        }
    }
    static void printCarsVanduteVara(){
        int i=0;
        for(auto& car: vandute){
            if(car->getVara()) {
                ++i;
                cout << i << ") Monovolum\n";
                cout << *car;
            }
        }
    }
    Vanzare<Monovolume>& operator-=(shared_ptr<Monovolume>& car){
        int i;
        cout<<"Este vara? 1 pentru da, 0 pentru nu: ";
        cin>>i;
        nrStoc--;
        nrVandute++;
        stoc.erase(remove(stoc.begin(),stoc.end(),car),stoc.end());
        if(i){
            nrVanduteVara++;
            car->setVara(true);
        }
        vandute.push_back(car);
        return *this;
    }

};
vector<shared_ptr<Monovolume>> Vanzare<Monovolume>::stoc;
vector<shared_ptr<Monovolume>> Vanzare<Monovolume>::vandute;
int Vanzare<Monovolume>::nrStoc=0;
int Vanzare<Monovolume>::nrVandute=0;
int Vanzare<Monovolume>::nrVanduteVara=0;
bool Vanzare<Monovolume>::creat=false;

const vector<shared_ptr<Monovolume>> &Vanzare<Monovolume>::getStoc() {
    return stoc;
}

template<typename T>
const vector<shared_ptr<T>> &Vanzare<T>::getStoc() {
    return stoc;
}


class Menu {
    static Menu* instance;

    Vanzare<Automobil> automobile;
    Vanzare<Monovolume> monovolume;

    Menu() = default;

public:
    static Menu* getInstance();

    Menu(const Menu&) = delete;
    Menu& operator=(const Menu&) = delete;

    void run();
};

Menu* Menu::instance = nullptr;

Menu* Menu::getInstance() {
    if (!instance)
        instance = new Menu();
    return instance;
}

void Menu::run() {
    int gest;
    cout << "1. Gestionare Mini/Compact/Monovolum\n";
    cout << "2. Gestionare Monovolum\n";
    cin>>gest;
    if(gest==1) {
        while (true) {
            int comanda;
            cout << "1. Adaugare masina in stoc\n";
            cout << "2. Vanzare masina din stoc\n";
            cout << "3. Afisare masini din stoc\n";
            cout << "4. Afisare masini vandute\n";
            cout << "5. Afisare numar masini stoc\n";
            cout << "6. Afisare numar masini vandute\n";
            cout << "7. Iesire\n\n";
            cin >> comanda;
            if (comanda == 1) {
                int masina;
                string tip[4] = {"mini", "compact", "monovolum"};
                cout << "1. Mini\n";
                cout << "2. Compact\n";
                cout << "3. Monovolum\n";
                cin >> masina;

                try {
                    if (masina == 1) {
                        Mini m;
                        cin >> m;

                        auto car = makeAutomobil(tip[masina - 1], m.getPret(), m.getLitraj(), m.getLung());
                        automobile.addCar(car);
                    } else if (masina == 2) {
                        Compact c;
                        cin >> c;

                        auto car = makeAutomobil(tip[masina - 1], c.getPret(), c.getDimensiune());
                        automobile.addCar(car);
                    } else if (masina == 3) {
                        Monovolume mon;
                        cin >> mon;

                        auto car = makeAutomobil(tip[masina - 1], mon.getPret(), mon.getPers(), mon.isSh(),
                                                 mon.getAni());
                        automobile.addCar(car);
                    }

                }
                catch (const InvalidAutomobil &e) {
                    cout << e.what() << '\n';
                }

            } else if (comanda == 2) {
                int vand;
                automobile.printCarsStoc();
                cout << "Numarul masinii ce se vinde:";
                cin >> vand;
                auto masina = automobile.getStoc()[vand - 1];
                automobile -= masina;
            } else if (comanda == 3) {
                automobile.printCarsStoc();
            } else if (comanda == 4) {
                automobile.printCarsVandute();
            } else if (comanda == 5) {
                cout << automobile.getNrStoc() << '\n';
            } else if (comanda == 6) {
                cout << automobile.getNrVandute() << '\n';
            } else
                break;
        }
    }
    else{
        while (true) {
            int comanda;
            cout << "1. Adaugare masina in stoc\n";
            cout << "2. Vanzare masina din stoc\n";
            cout << "3. Afisare masini din stoc\n";
            cout << "4. Afisare masini vandute\n";
            cout << "5. Afisare masini vandute vara\n";
            cout << "6. Afisare numar masini stoc\n";
            cout << "7. Afisare numar masini vandute\n";
            cout << "8. Afisare numar masini vandute vara\n";
            cout << "9. Iesire\n\n";
            cin >> comanda;
            if (comanda == 1) {
                Monovolume mon;
                cin >> mon;

                auto car = make_shared<Monovolume>(mon);

                monovolume.addCar(car);
            } else if (comanda == 2) {
                int vand;
                monovolume.printCarsStoc();
                cout << "Numarul masinii ce se vinde:";
                cin >> vand;
                auto masina = dynamic_pointer_cast<Monovolume>(monovolume.getStoc()[vand - 1]);
                monovolume -= masina;
            } else if (comanda == 3) {
                monovolume.printCarsStoc();
            } else if (comanda == 4) {
                monovolume.printCarsVandute();
            } else if (comanda == 5) {
                monovolume.printCarsVanduteVara();
            } else if (comanda == 6) {
                cout << monovolume.getNrStoc() << '\n';
            } else if (comanda == 7) {
                cout << monovolume.getNrVandute() << '\n';
            } else if (comanda == 8) {
                cout << monovolume.getNrVanduteVara() << '\n';
            } else
                break;
        }
    }

}

int main(){
    Menu::getInstance()->run();
    return 0;
}
