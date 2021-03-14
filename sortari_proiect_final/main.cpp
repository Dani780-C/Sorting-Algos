#include <iostream>
#include <random>
#include <string>
#include <cstdlib>
#include <ctime>
#include <stdlib.h>
#include <algorithm>
#include <iterator>
using namespace std;

unsigned short cod_alg, cod_gen;
unsigned int nr_elemente, nr_max;
vector <unsigned int> v;
vector <double> a;

void citire_date_sortare(unsigned int &nr_elemente,unsigned int &nr_max, unsigned short &cod_alg, unsigned short &cod_gen){
    cout<<"Numarul de elemente: ";
    cin>>nr_elemente;
    cout<<"Numerele vor fi mai mici decat: ";
    cin>>nr_max;
    cout<<"Algoritmul de sortare:\n";
    cout<<"* InsertionSort -- cod 1\n";
    cout<<"* CountSort     -- cod 2\n";
    cout<<"* MergeSort     -- cod 3\n";
    cout<<"* QuickSort     -- cod 4\n";
    cout<<"* RadixSort     -- cod 5\n";
    cout<<"Alege codul...";
    cin>>cod_alg;
    cout<<"\nModul de generare al sirului:\n";
    cout<<"* Aproape sortat               --cod 1\n";
    cout<<"* Aproape sortat, descrescator --cod 2\n";
    cout<<"* Random                       --cod 3\n";
    cout<<"* Constant                     --cod 4\n";
    cout<<"* Cu valori reale              --cod 5\n";
    cout<<"Alege codul...";
    cin>>cod_gen;
    cout<<'\n';
}

string metoda(){
    if(cod_alg == 1) return "InsertionSort";
    if(cod_alg == 2) return "CountSort";
    if(cod_alg == 3) return "MergeSort";
    if(cod_alg == 4) return "QuickSort";
    if(cod_alg == 5) return "RadixSort";
}

void mesaj(){
    cout<<"Vectorul de numere reale pozitive nu poate fi sortat cu metoda mea "<<metoda()<<".\n"<<'\n';
    return;
}

void genereaza_test(unsigned short cod){
    if(cod == 3){                           ///vector random de numere naturale
        std::mt19937 gen(time(0));
        uniform_int_distribution<unsigned int> u_int(0,nr_max);
        for (int j = 1; j <= nr_elemente; j++){
            v.push_back(u_int(gen));
        }
    }else if(cod == 4){                     ///vector constant
        std::mt19937 gen(time(0));
        uniform_int_distribution<unsigned int> u_int(0,nr_max);
        unsigned int val = u_int(gen);
        v.assign(nr_elemente,val);
        }
        else if(cod == 5){                  ///vector de numere reale pozitive
            double lower_bound = 0;
            double upper_bound = nr_max;
            std::uniform_real_distribution<double> unif(lower_bound,upper_bound);
            std::default_random_engine re;
            for(int j = 1;j <= nr_elemente; j++){
                    double numar_random = unif(re);
                    a.push_back(numar_random);
                    }
            }else if(cod == 1){             ///vector aproape sortat
                    std::mt19937 gen(time(0));
                    uniform_int_distribution<unsigned int> u_int(0,nr_max);
                    for (int j = 1; j <= nr_elemente/2; j++) v.push_back(u_int(gen));
                    sort(v.begin(),v.end());
                    for (int j = nr_elemente/2 + 1; j <= nr_elemente; j++) v.push_back(u_int(gen));
                    }
                else{                       ///vector aproape sortat, descrescator
                    std::mt19937 gen(time(0));
                    uniform_int_distribution<unsigned int> u_int(0,nr_max);
                    for (int j = 1; j <= nr_elemente/2; j++) v.push_back(u_int(gen));
                    sort(v.begin(),v.end(), greater<int>());
                    for (int j = nr_elemente/2 + 1; j <= nr_elemente; j++) v.push_back(u_int(gen));
                }
}

/*void afisare_v(){
    for(int p = 0; p < v.size(); p++)
        cout<<v[p]<<" ";
    cout<<'\n';
}

void afisare_a(){
    vector<double>::iterator q;
    for(q = a.begin(); q < a.end(); q++)
        cout<<*q<<" ";
    cout<<'\n';
}*/

void aliniat(int t){
    cout<<"--------------------------Test "<<t<<'\n'<<'\n';
}

void afisare_timp(double t){
    a.clear(),v.clear();
    if(cod_gen == 1) {cout<<"Vectorul generat aproape sortat cu "<<nr_elemente<<" de numere(maxim = "<<nr_max<<") a fost sortat cu metoda "<<metoda()<<" in "<<t<<" secunde.\n\n"; return;}
    if(cod_gen == 2) {cout<<"Vectorul generat aproape sortat(descrescator) cu "<<nr_elemente<<" de numere(maxim = "<<nr_max<<") a fost sortat cu metoda "<<metoda()<<" in "<<t<<" secunde.\n\n"; return;}
    if(cod_gen == 3) {cout<<"Vectorul generat random cu "<<nr_elemente<<" de numere(maxim = "<<nr_max<<") a fost sortat cu metoda "<<metoda()<<" in "<<t<<" secunde.\n\n"; return;}
    if(cod_gen == 4) {cout<<"Vectorul generat constant cu "<<nr_elemente<<" de numere(maxim = "<<nr_max<<") a fost sortat cu metoda "<<metoda()<<" in "<<t<<" secunde.\n\n"; return;}
    if(cod_gen == 5) {cout<<"Vectorul generat cu "<<nr_elemente<<" de numere reale(maxim = "<<nr_max<<") a fost sortat cu metoda "<<metoda()<<" in "<<t<<" secunde.\n\n"; return;}
}

///InsertionSort pentru numere naturale
double InsertionSort(){
    clock_t t;
    int i,j;
    unsigned int valoare;
    t = clock();
    for (i = 1; i<v.size(); i++){
        j = i-1;
        valoare = v[i];
        while(j>-1 && v[j] > valoare){
            v[j+1] = v[j];
            j--;
        }
        v[j+1] = valoare;
    }
    t = clock() - t;
    return (double(t))/CLOCKS_PER_SEC;
}

///InsertionSort pentru numere reale
double InsertionSort_double(){
    clock_t t;
    int i,j;
    double valoare;
    t = clock();
    for (i = 1; i<a.size(); i++){
        j = i-1;
        valoare = a[i];
        while(j>-1 && a[j] > valoare){
            a[j+1] = a[j];
            j--;
        }
        a[j+1] = valoare;
    }
    t = clock() - t;
    return (double(t))/CLOCKS_PER_SEC;
}

///CountSort pentru numere naturale
double CountSort(){
    vector <unsigned int> frecv;
    frecv.reserve(nr_max+1);
    frecv.assign(nr_max+1, 0);
    clock_t t,t1;
    t = clock();
    for(int k = 0; k<v.size(); k++){
        frecv[v[k]]++;
    }
    t = clock() - t;
    v.clear();
    t1 = clock();
    for(int k = 0; k<frecv.size(); k++){
        while(frecv[k]) v.push_back(k), frecv[k]--;
    }
    t1 = clock() - t1;
    frecv.clear();
    return (double(t+t1))/CLOCKS_PER_SEC;
}

///MergeSort pentru numere naturale
void interclasare(int st, int mij, int dr){
    vector <unsigned int> aux;
    aux.reserve(dr-st+1);
    int i,j;
    i = st, j = mij+1;
    while(i <= mij and j <= dr)
        if(v[i]>v[j]) aux.push_back(v[j]), j++;
        else aux.push_back(v[i]), i++;
    while(i<=mij) aux.push_back(v[i++]);
    while(j<=dr)  aux.push_back(v[j++]);
    j = 0;
    for(i=st;i<=dr;i++) v[i] = aux[j++];
    aux.clear();
}

void MergeSort(int st, int dr){
    if(st>=dr) return;
    int mij = (st+dr)/2;
    MergeSort(st,mij);
    MergeSort(mij+1,dr);
    interclasare(st,mij,dr);
}

///MergeSort pentru numere reale
void interclasare_double(int st, int mij, int dr){
    vector <double> aux1;
    aux1.reserve(dr-st+1);
    int i,j;
    i = st, j = mij+1;
    while(i <= mij and j <= dr)
        if(a[i]>a[j]) aux1.push_back(a[j]), j++;
        else aux1.push_back(a[i]), i++;
    while(i<=mij) aux1.push_back(a[i++]);
    while(j<=dr)  aux1.push_back(a[j++]);
    j = 0;
    for(i=st;i<=dr;i++) a[i] = aux1[j++];
    aux1.clear();
}

void MergeSort_double(int st, int dr){
    if(st>=dr) return;
    int mij = (st+dr)/2;
    MergeSort_double(st,mij);
    MergeSort_double(mij+1,dr);
    interclasare_double(st,mij,dr);
}

///RadixSort pentru numere naturale
unsigned int find_maxim(){
    unsigned int M;
    M = v[0];
    for(int j=1;j<nr_elemente;j++)
        if(v[j] > M) M = v[j];
    return M;
}

void help_radix(int p){
    vector<vector<unsigned int>> qw(1024 ,vector<unsigned int>());
    for(int j=0; j<nr_elemente; j++)
        qw[(v[j]/p)%1024].push_back(v[j]);
    unsigned int l=0;
    for(int j = 0; j<1024; j++){
        for(int k = 0; k < qw[j].size(); k++)
        v[l++] = qw[j][k];
        }
}

void RadixSort(){
    unsigned int m = find_maxim();
    for(int p = 1; m / p > 0; p*=1024)
        help_radix(p);
}

///QuickSort pentru numere naturale
int partitie(int st,int dr){
    unsigned int pivot = v[dr];
    int i = st - 1;
    for(int j = st; j <= dr-1; j++)
        if(v[j]<pivot) swap(v[j],v[++i]);
    swap(v[i+1],v[dr]);
    return i+1;
}

void QuickSort(int st, int dr){
    if(st<dr){
        int p = partitie(st,dr);
        QuickSort(st,p-1);
        QuickSort(p+1,dr);
    }
}

///QuickSort pentru numere reale
int partitie_double(int st,int dr){
    double pivot = a[dr];
    int i = st - 1;
    for(int j = st; j <= dr-1; j++)
        if(a[j]<pivot) swap(a[j],a[++i]);
    swap(a[i+1],a[dr]);
    return i+1;
}

void QuickSort_double(int st, int dr){
    if(st<dr){
        int p = partitie_double(st,dr);
        QuickSort_double(st,p-1);
        QuickSort_double(p+1,dr);
    }
}

double sortare_double(unsigned short cod){
        clock_t t;
        if(cod == 1) return InsertionSort_double();
            else if(cod == 3)  {t = clock(); MergeSort_double(0,nr_elemente-1); t = clock() - t; return (double(t))/CLOCKS_PER_SEC;}
                else if(cod == 4)  {t = clock(); QuickSort_double(0,nr_elemente-1); t = clock() - t; return (double(t))/CLOCKS_PER_SEC;}
        return 0;
}

double sortare(unsigned short cod){
        clock_t t;
        if(cod_gen == 5) return sortare_double(cod);
        if(cod == 1) return InsertionSort();
        else if(cod == 2)  return CountSort();
            else if(cod == 3)  {t = clock(); MergeSort(0,nr_elemente-1); t = clock() - t; return (double(t))/CLOCKS_PER_SEC;}
                else if(cod == 4)  { if(cod_gen == 4 and nr_elemente > 1000) {cout<<"Algoritmul de sortare QuickSort va ceda pentru un sir de lungime foarte mare cu numere constante!\n"; return -1;}
                                    t = clock(); QuickSort(0,nr_elemente-1); t = clock() - t; return (double(t))/CLOCKS_PER_SEC;}
                    else if(cod == 5)  {t = clock(); RadixSort(); t = clock() - t; return (double(t))/CLOCKS_PER_SEC;}
        return 0;
}

void verificare(){
    if(cod_gen == 5){
        for(int i=0 ; i<a.size()-1; i++)
            if(a[i]>a[i+1]) {cout<<"Vectorul este sortat gresit!\n"; return;}
        cout<<"Vectorul este sortat corect!\n";
        return;
    }
    for(int i=0 ; i<v.size()-1; i++)
        if(v[i]>v[i+1]) {cout<<"Vectorul este sortat gresit!\n"; return;}
    cout<<"Vectorul este sortat corect!\n";
    return;
}

int main(){
    int nr_teste;
    cout<<"Numarul de teste: ";
    cin>>nr_teste;
    double timp_sortare;
    clock_t t;
    for(int i=1; i <= nr_teste; i++){
        aliniat(i);
        citire_date_sortare(nr_elemente, nr_max, cod_alg, cod_gen);
        if(cod_gen == 5 && (cod_alg == 2 || cod_alg == 5)) mesaj();    ///RadixSort si CountSort nu functioneazza pe vectorul de numere reale
        else{
            genereaza_test(cod_gen);
            timp_sortare = sortare(cod_alg);
            verificare();
            afisare_timp(timp_sortare);
        }
    }
    return 0;
}
