#include <iostream>
using namespace std;
class Polinom{
    int grad_polinom;
    double *coeficienti;
public:
    Polinom(){}
    Polinom(int grad,double coef[]){
        grad_polinom=grad;
        coeficienti= new double[grad+1];
        for(int i=0;i<=grad;++i)
            coeficienti[i]=coef[i];
    }
    Polinom(const Polinom &p){
        coeficienti=new double[p.grad_polinom+1];
        grad_polinom=p.grad_polinom;
        for(int i=0;i<=grad_polinom;++i)
            coeficienti[i]=p.coeficienti[i];
    }
    ~Polinom(){
        delete[] coeficienti;
    }
    int getGradPolinom() const {
        return grad_polinom;
    }

    void setGradPolinom(int gradPolinom) {
        grad_polinom = gradPolinom;
        if(coeficienti)
            delete[] coeficienti;
        coeficienti=new double[grad_polinom+1];
    }

    void getCoeficienti(double coef[])const{
        for(int i=0;i<=grad_polinom;++i)
            coef[i]=coeficienti[i];
    }
    void setCoeficienti(double coef[]){
        for(int i=0;i<=grad_polinom;++i)
            coeficienti[i]=coef[i];
    }

    friend ostream &operator<<(ostream &os, const Polinom &polinom) {
        os << "Gradul polinomului: " << polinom.grad_polinom << "\nCoeficientii: ";
        for(int i=0;i<=polinom.grad_polinom;++i)
            os<<polinom.coeficienti[i]<<" ";
        cout<<'\n';
        return os;
    }
    friend istream &operator>>(istream &is,Polinom &polinom){
        cout<<"Gradul polinomului:\n";
        is>>polinom.grad_polinom;
        polinom.coeficienti=new double[polinom.grad_polinom+1];
        cout<<"Coeficientii:\n";
        for(int i=0;i<=polinom.grad_polinom;++i)
            is>>polinom.coeficienti[i];
        cout<<'\n';
        return is;
    }
    double valoarePunct(const double &x)const{
        double sum=0;
        double pct=1;
        for(int i=0;i<=grad_polinom;++i) {
            sum += pct * coeficienti[i];
            pct*=x;
        }
        return sum;
    }
    Polinom operator+(const Polinom &polinom)const{
        int gr=grad_polinom>polinom.grad_polinom?grad_polinom:polinom.grad_polinom;
        int gr_min=grad_polinom<polinom.grad_polinom?grad_polinom:polinom.grad_polinom;
        double coef[gr+1];
        int grad;
        for(int i=0;i<=gr;++i) {
            if(i<=gr_min)
                coef[i] = coeficienti[i] + polinom.coeficienti[i];
            else
                if(gr_min==grad_polinom)
                    coef[i] = 0 + polinom.coeficienti[i];
                else
                    coef[i] = coeficienti[i] + 0;
            if(coef[i])
                grad=i;
        }
        return Polinom(grad,coef);
    }
    Polinom operator-(const Polinom &polinom)const{
        int gr=grad_polinom>polinom.grad_polinom?grad_polinom:polinom.grad_polinom;
        int gr_min=grad_polinom<polinom.grad_polinom?grad_polinom:polinom.grad_polinom;
        double coef[gr+1];
        int grad;
        for(int i=0;i<=gr;++i) {
            if(i<=gr_min)
                coef[i] = coeficienti[i] - polinom.coeficienti[i];
            else
                if(gr_min==grad_polinom)
                    coef[i] = 0 - polinom.coeficienti[i];
                else
                    coef[i] = coeficienti[i] - 0;
            if(coef[i])
                grad=i;
        }
        return Polinom(grad,coef);
    }
    Polinom operator*(const Polinom &polinom)const{
        int gr=grad_polinom+polinom.grad_polinom;
        double coef[gr+1]={};
        for(int i=0;i<=grad_polinom;++i) {
            if(coeficienti[i]){
                for(int j=0;j<=polinom.grad_polinom;++j){
                    coef[i+j]+=coeficienti[i]*polinom.coeficienti[j];
                }
            }
        }
        return Polinom(gr,coef);
    }
    Polinom& operator=(const Polinom &rhs){
        this->setGradPolinom(rhs.grad_polinom);
        this->setCoeficienti(rhs.coeficienti);
    }
    double operator()(int index) const{
        return coeficienti[index];
    }
    void citiren(const int &n){
        int ok=0;
        while((*(this+ok)).coeficienti)
            ok++;
        for(int i=ok;i<n+ok;i++){
            cin>> *(this+i);
        }
    }
    void afisaren(const int &n) const{
        for(int i=0;i<n;i++){
            cout<< i << ")" << *(this+i)<<'\n';
        }
    }

};
int main(){
    int comanda,nrpoli=0,n,m;
    char c[100];
    double val;
    Polinom *point= new Polinom[1000];
    while(true){
        cout<<"\nClasa Polinom : Pentru a alege o optiune introduceti numarul comenzii:\n\n";
        cout<<"1)Adaugati un polinom - introduceti 1\n";
        cout<<"2)Adaugati n polinoame - introduceti 2\n";
        cout<<"3)Duplicati un polinom deja adaugat - introduceti 3\n";
        cout<<"4)Calculati valoarea unui polinom intr-un punct dat - introduceti 4\n";
        cout<<"5)Faceti suma a doua polinoame - introduceti 5\n";
        cout<<"6)Faceti diferenta a doua polinoame - introduceti 6\n";
        cout<<"7)Faceti produsul a doua polinoame - introduceti 7\n";
        cout<<"8)Afisati polinoamele introduse - introduceti 8\n";
        cout<<"9)Inchideti programul - introduceti 9\n";
        cout<<"\nIntroduceti comanda:";
        cin>>comanda;
        cout<<'\n';
        if(comanda==1){
            cout<<"Adaugati un polinom:\n";
            cin>>point[nrpoli];
            nrpoli++;
            cout<<"\nSucces!\nPentru a continua introduceti un caracter si apasati enter:";
            cin>>c;
        }
        else
            if(comanda==2){
                cout<<"Adaugati numarul polinoamelor ce vor fi introduse:";
                cin>>n;
                point->citiren(n);
                nrpoli+=n;
                cout<<"\nSucces!\nPentru a continua introduceti un caracter si apasati enter:";
                cin>>c;
            }
            else
                if(comanda==3){
                    cout<<"Adaugati numarul polinomului ce va fi duplicat:";
                    cin>>n;
                    point[nrpoli]=point[n];
                    nrpoli++;
                    cout<<"\nSucces!\nPentru a continua introduceti un caracter si apasati enter:";
                    cin>>c;
                }
                else
                    if(comanda==4){
                        cout<<"Adaugati numarul polinomului al carei valoare va fi calculata:";
                        cin>>n;
                        cout<<"Adaugati punctul in care se va calcula valoarea:";
                        cin>>val;
                        cout<<"\nPolinomul ales este:\n\n";
                        cout<<point[n];
                        cout<<'\n';
                        cout<<"\nValoarea calculata este: "<<point[n].valoarePunct(val);
                        cout<<"\nPentru a continua introduceti un caracter si apasati enter:";
                        cin>>c;
                    }
                    else
                        if(comanda==5){
                            cout<<"Adaugati numarul primului polinom ce va intra in suma:";
                            cin>>n;
                            cout<<"Adaugati numarul celui de-al doilea polinom ce va intra in suma:";
                            cin>>m;
                            cout<<"\nPrimul polinom:\n\n";
                            cout<<point[n];
                            cout<<"\n\nAl doilea polinom:\n\n";
                            cout<<point[m];
                            cout<<"\n\nSuma celor doua polinoame este:\n\n";
                            cout<<point[n]+point[m];
                            cout<<"\n\nPentru a continua introduceti un caracter si apasati enter:";
                            cin>>c;
                        }
                        else
                            if(comanda==6){
                                cout<<"Adaugati numarul primului polinom ce va intra in diferenta:";
                                cin>>n;
                                cout<<"Adaugati numarul celui de-al doilea polinom ce va intra in diferenta:";
                                cin>>m;
                                cout<<"\nPrimul polinom:\n\n";
                                cout<<point[n];
                                cout<<"\n\nAl doilea polinom:\n\n";
                                cout<<point[m];
                                cout<<"\n\nDiferenta celor doua polinoame este:\n\n";
                                cout<<point[n]-point[m];
                                cout<<"\n\nPentru a continua introduceti un caracter si apasati enter:";
                                cin>>c;
                            }
                            else
                                if(comanda==7){
                                    cout<<"Adaugati numarul primului polinom ce va intra in produs:";
                                    cin>>n;
                                    cout<<"Adaugati numarul celui de-al doilea polinom ce va intra in produs:";
                                    cin>>m;
                                    cout<<"\nPrimul polinom:\n\n";
                                    cout<<point[n];
                                    cout<<"\n\nAl doilea polinom:\n\n";
                                    cout<<point[m];
                                    cout<<"\n\nProdusul celor doua polinoame este:\n\n";
                                    cout<<point[n]*point[m];
                                    cout<<"\n\nPentru a continua introduceti un caracter si apasati enter:";
                                    cin>>c;
                                }
                                else
                                    if(comanda==8){
                                        cout<<"Polinoamele introduse:\n\n";
                                        point->afisaren(nrpoli);
                                        cout<<"\nPentru a continua introduceti un caracter si apasati enter:";
                                        cin>>c;
                                    }
                                    else
                                        if(comanda==9)
                                            break;
    }
    return 0;
}

