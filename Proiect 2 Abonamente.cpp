#include <iostream>
#include <string>
#include <memory>
#include <vector>
using namespace std;
class InvalidPret: public exception{
public:
    InvalidPret() = default;
    const char* what() const noexcept override{
        return "Pretul este invalid.";
    }
};
class InvalidPerioada: public exception{
public:
    InvalidPerioada() = default;
    const char* what() const noexcept override{
        return "Perioada este invalida.";
    }
};
class InvalidReducere: public exception{
public:
    InvalidReducere() = default;
    const char* what() const noexcept override{
        return "Reducerea este invalida.";
    }
};
enum class TipAbonament {
    Abonament,
    Abonament_Premium
};
class Abonament{
protected:
    string nume_abonament;
    float pret;
    int perioada;
public:
    Abonament(const string &nume_abonament="",const float &pret=0,const int &perioada=0):nume_abonament(nume_abonament), pret(pret),perioada(perioada){}
    Abonament(const Abonament &abon): nume_abonament(abon.nume_abonament), pret(abon.pret), perioada(abon.perioada){}
    virtual ~Abonament() = default;
    Abonament& operator=(const Abonament &rhs){
        if(this==&rhs)
            return *this;
        nume_abonament=rhs.nume_abonament;
        pret=rhs.pret;
        perioada=rhs.perioada;
        return *this;
    }

    const string &getNumeAbonament() const{
        return nume_abonament;
    }

    void setNumeAbonament(const string &numeAbonament) {
        nume_abonament = numeAbonament;
    }

    float getPret() const {
        return pret;
    }

    void setPret(float pret_) {
        pret = pret_;
    }

    int getPerioada() const {
        return perioada;
    }

    void setPerioada(int perioada_) {
        perioada = perioada_;
    }
    virtual TipAbonament getType() const{
        return TipAbonament::Abonament;
    }
    virtual void print(ostream &os) const{
        os<<"Nume abonament: "<<nume_abonament<<'\n';
        os<<"Pret: "<<pret<<'\n';
        os<<"Perioada (nr de luni): "<<perioada<<'\n';
    }
    friend ostream &operator<<(ostream &os, const Abonament &abonament) {
        abonament.print(os);
        return os;
    }
    virtual void scan(istream &is){
        cout<<"Nume abonament:";
        getline(is>>ws,nume_abonament);
        cout<<"Pret:";
        is>>pret;
        if(pret<0)
            throw InvalidPret();
        cout<<"Perioada (nr de luni):";
        is>>perioada;
        if(perioada<0)
            throw InvalidPerioada();
    }
    friend istream &operator>>(istream &is,Abonament &abonament) {
        abonament.scan(is);
        return is;
    }
};
class Abonament_Premium: public Abonament{
    int reducere;
public:
    Abonament_Premium(const string &nume="",const float &pr=0,const int &per=0,const int &red=0): Abonament(nume,pr,per),reducere(red){}
    Abonament_Premium(const Abonament_Premium &prem): Abonament(prem), reducere(prem.reducere){}
    Abonament_Premium& operator=(const Abonament_Premium &rhs){
        if(this==&rhs)
            return *this;
        Abonament::operator=(rhs);
        reducere=rhs.reducere;
        return *this;
    }
    void print(ostream &os) const override{
        Abonament::print(os);
        os<<"Reducere (%): "<<reducere<<'\n';
    }

    friend ostream &operator<<(ostream &os, const Abonament_Premium &premium) {
        premium.print(os);
        return os;
    }
    TipAbonament getType() const override{
        return TipAbonament::Abonament_Premium;
    }
    void scan(istream &is) override{
        Abonament::scan(is);
        cout<<"Reducere (%):";
        is>>reducere;
        if(reducere<0 || reducere>100)
            throw InvalidReducere();
    }
    friend istream &operator>>(istream &is, Abonament_Premium &premium) {
        cout<<"Prem\n";
        premium.scan(is);
        return is;
    }

    int getReducere() const {
        return reducere;
    }

    void setReducere(int reducere_) {
        reducere = reducere_;
    }
};
class Persoana{
protected:
    int id;
    string nume,cnp;
public:
    Persoana(const int &Id=0,const string &Nume="",const string &CNP=""):id(Id),nume(Nume),cnp(CNP){}
    Persoana(const Persoana &pers):id(pers.id),nume(pers.nume),cnp(pers.cnp){}
    virtual ~Persoana() = default;
    Persoana& operator=(const Persoana &rhs){
        if(this==&rhs)
            return *this;
        id=rhs.id;
        nume=rhs.nume;
        cnp=rhs.cnp;
        return *this;
    }

    int getId() const {
        return id;
    }

    void setId(int id_) {
        id = id_;
    }

    const string &getNume() const {
        return nume;
    }

    void setNume(const string &nume_) {
        nume = nume_;
    }

    const string &getCnp() const {
        return cnp;
    }

    void setCnp(const string &cnp_) {
        cnp = cnp_;
    }
    virtual void print(ostream &os) const{
        os << "Id: " << id<<'\n';
        os<< "Nume: " << nume<<'\n';
        os<< "CNP: " << cnp<<'\n';
    }
    friend ostream &operator<<(ostream &os, const Persoana &persoana) {
        persoana.print(os);
        return os;
    }
    virtual void scan(istream &is){
        cout << "Id:";
        is>> id;
        cout<< "Nume:";
        getline(is >> ws,nume);
        cout<< "CNP:";
        is>> cnp;
    }
    friend istream &operator>>(istream &is, Persoana &persoana) {
        persoana.scan(is);
        return is;
    }
};
class Abonat: public Persoana{
    string nr_telefon;
    shared_ptr<Abonament> x;
public:
    Abonat(const int &Id=0,const string &Nume="",const string &CNP="",const string &nrtel="",const shared_ptr<Abonament> y = nullptr):Persoana(Id,Nume,CNP), nr_telefon(nrtel),x(y){}
    Abonat(const Abonat &ab): Persoana(ab),nr_telefon(ab.nr_telefon),x(ab.x){}
    Abonat& operator=(const Abonat &rhs){
        if(this==&rhs)
            return *this;
        Persoana::operator=(rhs);
        nr_telefon=rhs.nr_telefon;
        x=rhs.x;
        return *this;
    }

    const string &getNrTelefon() const {
        return nr_telefon;
    }

    void setNrTelefon(const string &nrTelefon) {
        nr_telefon = nrTelefon;
    }
    void print(ostream &os) const override{
        Persoana::print(os);
        cout<<"Nr telefon: "<<nr_telefon<<'\n';
        cout<<*x<<'\n';
    }
    friend ostream &operator<<(ostream &os, const Abonat &abonat) {
        abonat.print(os);
        return os;
    }
    void scan(istream &is) override{
        Persoana::scan(is);
        int ok;
        cout<<"Nr telefon:";
        is>>nr_telefon;
        cout<<"Alegeti abonamentul (0 pentru abonament normal, 1 pentru abonament premium):";
        is>>ok;
        if(ok){
            Abonament_Premium ab;
            cin>>ab;
            x= make_shared<Abonament_Premium>(ab);
        }
        else{
            Abonament abon;
            cin>>abon;
            x= make_shared<Abonament>(abon);
        }
    }
    friend istream &operator>>(istream &is, Abonat &abonat) {
        abonat.scan(is);
        return is;
    }

    const shared_ptr<Abonament> &getX() const {
        return x;
    }

    void setX(const shared_ptr<Abonament> &x) {
        Abonat::x = x;
    }
};
class Clienti{
    static vector<shared_ptr<Abonat>> abonati;
    Clienti() = delete;
public:
    static void addAbonat(const shared_ptr<Abonat> &abonat){
        abonati.push_back(abonat);
    }

    static vector<shared_ptr<Abonat>> getAbonati() {
        return abonati;
    }
    static void showAbonati(){
        int i=1;
        for (auto &abon: Clienti::getAbonati()) {
            if (abon->getX()->getType() == TipAbonament::Abonament) {
                cout<<"Clientul "<<i<<") Abonament Normal\n";
            }
            else{
                cout<<"Clientul "<<i<<") Abonament Premium\n";
            }
            cout<<*abon<<'\n';
            i++;
        }
    }
    static void showAbonatiNormali(){
        int i=1;
        for (auto &abon: Clienti::getAbonati()) {
            if (abon->getX()->getType() == TipAbonament::Abonament) {
                cout << "Clientul " << i << ") Abonament Normal\n";
                cout << *abon << '\n';
                i++;
            }
        }
    }
    static void showAbonatiPremium(){
        int i=1;
        for (auto &abon: Clienti::getAbonati()) {
            if (abon->getX()->getType() == TipAbonament::Abonament_Premium) {
                cout << "Clientul " << i << ") Abonament Premium\n";
                cout << *abon << '\n';
                i++;
            }
        }
    }
    static int getNrAbonatiPremium(){
        int total=0;
        for (auto &abon: Clienti::getAbonati()) {
            if (abon->getX()->getType() == TipAbonament::Abonament_Premium) {
                total++;
            }
        }
        return total;
    }
    static int getNrAbonatiNormali(){
        int total=0;
        for (auto &abon: Clienti::getAbonati()) {
            if (abon->getX()->getType() == TipAbonament::Abonament) {
                total++;
            }
        }
        return total;
    }
    static double sumaIncasata(){
        double suma=0;
        for (auto &abon: Clienti::getAbonati()) {
            if (abon->getX()->getType() == TipAbonament::Abonament_Premium) {
                auto prem = dynamic_pointer_cast<Abonament_Premium>(abon->getX());
                suma+=prem->getPerioada()*(prem->getPret()*(double)(100-prem->getReducere())/100);
            }
            else{
                suma+=abon->getX()->getPret()*abon->getX()->getPerioada();
            }
        }
        return suma;
    }
};
vector<shared_ptr<Abonat>> Clienti::abonati;
int main() {
    int meniu;
    char c[100];
    while(true){
        cout<<"\nClasa Clienti : Pentru a alege o optiune introduceti numarul comenzii:\n\n";
        cout<<"1)Adaugati un client - introduceti 1\n";
        cout<<"2)Adaugati n clienti - introduceti 2\n";
        cout<<"3)Afisati toti clientii - introduceti 3\n";
        cout<<"4)Afisati toti clientii cu abonamente normale - introduceti 4\n";
        cout<<"5)Afisati toti clientii cu abonamente premium - introduceti 5\n";
        cout<<"6)Afisati numarul clientilor cu abonamente normale - introduceti 6\n";
        cout<<"7)Afisati numarul clientilor cu abonamente premium - introduceti 7\n";
        cout<<"8)Afisati suma incasata de la clienti - introduceti 8\n";
        cout<<"9)Inchideti programul - introduceti 9\n";
        cout<<"\nIntroduceti comanda:";
        cin>>meniu;
        cout<<'\n';
        if(meniu==1){
            cout<<"Adaugati un client:\n";
            Abonat abonat;
            bool ok=true;
            int cont;
            while(ok) {
                try {
                    cin >> abonat;
                    auto adaug = make_shared<Abonat>(abonat);
                    Clienti::addAbonat(adaug);
                    ok=false;
                    cout << "\nSucces!\n";
                }
                catch (const InvalidPret &e) {
                    cout << e.what()
                         << "\nComanda nu a fost executata...\nPentru a reincerca introduceti 1, iar pentru a abandona introduceti 0:";
                    cin>>cont;
                    if(cont==0)
                        ok= false;
                }
                catch (const InvalidPerioada &e) {
                    cout << e.what()
                         << "\nComanda nu a fost executata...\nPentru a reincerca introduceti 1, iar pentru a abandona introduceti 0:";
                    cin>>cont;
                    if(cont==0)
                        ok= false;
                }
                catch (const InvalidReducere &e) {
                    cout << e.what()
                         << "\nComanda nu a fost executata...\nPentru a reincerca introduceti 1, iar pentru a abandona introduceti 0:";
                    cin>>cont;
                    if(cont==0)
                        ok= false;
                }
            }
            cout<<"Pentru a continua introduceti un caracter si apasati enter:";
            cin>>c;
        }
        else
            if(meniu==2){
                int n,cont;
                Abonat abonat;
                bool ok,stop=true;
                cout<<"Adaugati numarul clientilor ce vor fi introdusi:";
                cin>>n;
                for(int i=0;i<n && stop;++i){
                    ok=true;
                    while(ok) {
                        try {
                            cin >> abonat;
                            auto adaug = make_shared<Abonat>(abonat);
                            Clienti::addAbonat(adaug);
                            ok=false;
                            cout << "\nSucces!\n";
                        }
                        catch (const InvalidPret &e) {
                            cout << e.what()
                                 << "\nComanda nu a fost executata...\nPentru a reincerca introduceti 1, iar pentru a abandona introduceti 0:";
                            cin>>cont;
                            if(cont==0)
                                stop=ok= false;
                        }
                        catch (const InvalidPerioada &e) {
                            cout << e.what()
                                 << "\nComanda nu a fost executata...\nPentru a reincerca introduceti 1, iar pentru a abandona introduceti 0:";
                            cin>>cont;
                            if(cont==0)
                                stop=ok= false;
                        }
                        catch (const InvalidReducere &e) {
                            cout << e.what()
                                 << "\nComanda nu a fost executata...\nPentru a reincerca introduceti 1, iar pentru a abandona introduceti 0:";
                            cin>>cont;
                            if(cont==0)
                                stop=ok= false;
                        }
                    }
                }
            }
            else
                if(meniu==3){
                    cout<<"Clientii introdusi:\n\n";
                    Clienti::showAbonati();
                    cout<<"\nPentru a continua introduceti un caracter si apasati enter:";
                    cin>>c;
                }
                else
                    if(meniu==4){
                        cout<<"Clientii cu abonamente normale introdusi:\n\n";
                        Clienti::showAbonatiNormali();
                        cout<<"\nPentru a continua introduceti un caracter si apasati enter:";
                        cin>>c;
                    }
                    else
                        if(meniu==5){
                            cout<<"Clientii cu abonamente premium introdusi:\n\n";
                            Clienti::showAbonatiPremium();
                            cout<<"\nPentru a continua introduceti un caracter si apasati enter:";
                            cin>>c;
                        }
                        else
                            if(meniu==6){
                                cout<<"Numarul clientilor cu abonamente normale introdusi: "<<Clienti::getNrAbonatiNormali()<<'\n';
                                cout<<"\nPentru a continua introduceti un caracter si apasati enter:";
                                cin>>c;
                            }
                            else
                                if(meniu==7){
                                    cout<<"Numarul clientilor cu abonamente premium introdusi: "<<Clienti::getNrAbonatiPremium()<<'\n';
                                    cout<<"\nPentru a continua introduceti un caracter si apasati enter:";
                                    cin>>c;
                                }
                                else
                                    if(meniu==8){
                                        cout<<"Suma incasata de la clientii introdusi: "<<Clienti::sumaIncasata()<<'\n';
                                        cout<<"\nPentru a continua introduceti un caracter si apasati enter:";
                                        cin>>c;
                                    }
                                    else
                                        if(meniu==9)
                                            break;
    }
    return 0;
}
