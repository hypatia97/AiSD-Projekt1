#include <iostream>
#include <fstream>
#include<time.h>
#include<cstdlib>
#include <vector>
#include <iomanip>

using namespace std;

void Wprowadzanie(const char*nazwa) //funkcja do wprowadzania danych
{
    int n;

    ofstream zapis1(nazwa);
    n=rand()% 99 + 2;// losowanie liczb z zakresu od 2 do 100
    int *Z= new int[n];

    for (int i=0; i<n; i++)
    {


        Z[i]=-20+rand()%41; // losowanie liczb z zakresu -20 do 20
        zapis1<<Z[i]<<" ";
    }
    zapis1.close();
    delete [] Z;
}


void Odczyt_txt(const char* nazwa,int &n,vector<int>&tab)
{

    ifstream zrodlo(nazwa);
    int liczba=0;
    while(zrodlo>>liczba) //dopoki w zrodle znajduje sie liczba
        tab.push_back(liczba); //dodaj element do wektora tab

    n=tab.size(); //rozmiar wektora tab

}


void Wypisz_tablice(vector<int> tablica, int rozmiar, const char*nazwa)
{
    //funkcja do wypisywaania tablicy
    int i;
    cout<<nazwa<<":"<<endl<<endl;
    for (i=0; i<rozmiar; i++)
        cout<<tablica[i]<<setw(4);
    cout<<endl;
}

void Max_iloczyn(vector<int> tablica,int & maks,int rozmiar,int& s, vector<int> &para)
{

    int i,j;
    int max0;

    int m,n,k,l;
    int f;
    int mianownik=0; //niefortunna nazwa zmiennej, sluzy do zliczania jak licznik
    int licznik=0;
    bool ok=false;
    m=rozmiar-1;
    n=rozmiar-2;
    vector <int> tablica3;

    maks=tablica[m]*tablica[n]; //przypisanie maksymalnego iloczynu do dwoch ostatnich elementow tablicy
    for(i=0; i<rozmiar; i++)
    {

        if(tablica[i]>=0) //sprawdzanie czy dodatnia
        {
            mianownik++;

            for(j=i+1; j<rozmiar; j++)
            {
                licznik++;
                if(tablica[j]>=0) //sprawdzanie czy dodatnia
                {

                    max0=tablica[i]*tablica[j]; //przypisanie maksa do kolejnych elementow

                    if(max0>maks) //sprawdzenie czy nowy iloczyn jest wiekszy od poprzedniego najwiekszego
                    {
                        maks=max0;
                        m=i;  //przypisanie w celu latwego znalezienia liczb wyznaczajacych najwiekszy iloczyn
                        n=j;
                    }

                    if(tablica[i]<=tablica[j])
                        i=j;                    //przypisanie w celu nie sprawdzania dalszych elementow tablicy
                    // przy pomocy liczby ktora nie da najwiekszego iloczynu



                }
                else if (mianownik==1)       //sprawdzenie warunku zeby nie dodac dwa razy tych samych liczb
                    tablica3.push_back(tablica[j]);

            }


        }


        else if (licznik==0) //sprawdzenie warunku jak wyzej
            tablica3.push_back(tablica[i]);



    }

    f=tablica3.size(); //rozmiar tablicy liczb ujemnych


    k=f-1;


    if (f>=2)
    {
        l=f-2;
        for (int i=0; i<f; i++)
            for(int j=i+1; j<f; j++)
            {
                max0=tablica3[i]*tablica3[j];

                if(max0>=maks) //analogicznie jak poprzedniu ale zamiast"=" mamy ">=" umozliwia znaleznienie
                {
                    maks=max0;      //liczb w przypadku gdy iloczyn liczb dodatnich jest rowny iloczynowi liczb ujemnych
                    k=i;
                    l=j;
                }
                if(tablica3[j]<=tablica3[i])
                    i=j;
            }





    }
    else if (f==1) //gdy rozmiar tablicy liczb ujemnych jest rowny 1, dopisujemy element
    {

        tablica3[k]=tablica[m];
        tablica3.push_back(tablica[n]);
        l=1;
        tablica3[l]=tablica[n];


    }
    else //gdy brak elementow, dopisujemy dwa elementy
    {
        tablica3.push_back(tablica[m]);
        tablica3.push_back(tablica[n]);
        k=0;
        l=1;

    }


    if(maks>0)
    {
        if(tablica[m]*tablica[n]==tablica3[k]*tablica3[l]&&tablica[m]!=tablica3[k]&&tablica[m]!=tablica3[l]) //gdy maks dodatnich jest
            //rowny maksowi ujemnych
        {
            para.push_back(tablica[m]);
            para.push_back(tablica[n]);
            para.push_back(tablica3[k]);
            para.push_back(tablica3[l]);

        }
        else if(tablica[m]*tablica[n]>tablica3[k]*tablica3[l]) //gdy maksymalny iloczyn dodatnich wiekszy od maksymalnego ujemnych
        {
            para.push_back(tablica[m]);
            para.push_back(tablica[n]);
        }
        else //gdy maksymalny iloczyn liczb ujemnych jest wiekszy niz liczb dodatnich
        {
            para.push_back(tablica3[k]);
            para.push_back(tablica3[l]);
        }



    }
    else if(maks==0 && rozmiar>2) //gdy tablica z samymi zereami i ewnetualnie jedna liczba dodania i/lub ujemna
    {
        for(int i=0; i<rozmiar; i++)
            if(tablica[i]!=0)
            {
                para.push_back(0);         //dodanie do wektora wyjsciowego pary 0 oraz niezerowej liczby
                para.push_back(tablica[i]);
                ok=true;
            }
        if(rozmiar>3 || ok==false) // gdy rozmiar tablicy wiekszy od 3, maks iloczyn daje tez para [0,0]
        {
            //gdy mamy same 0 w tablicy 3-elementowej chcemy wypisac pare [0,0] tylko raz
            para.push_back(0);
            para.push_back(0);

        }
    }
    else //gdy mamy dwa elementy z maksymalnym iloczynem mniejszym od 0 (dodatnia i ujemna)
    {
        para.push_back(tablica[0]);
        para.push_back(tablica[1]);
    }

    s=para.size();  //rozmiar wektora



}

void Zapisz(const char*nazwa,int maks, int k, vector<int>A)
{

    ofstream plik(nazwa);
    plik<< "Najwiekszy iloczyn dwoch liczb:"<<endl;
    plik << maks<<endl;
    plik<<"Pary liczb:"<<endl;
    for(int i=0; i<k; i+=2) //wypisanie par liczb z wektora wyznaczonego w funkcji Max_iloczyn
        plik<<"["<<A[i]<<","<<A[i+1]<<"]"<<endl;

}


int main()

{

    int n,k;
    vector <int> v;
    vector<int>A;
    int max1;



    srand ( ( unsigned )time ( NULL ) );

    Wprowadzanie("dane.txt");
    Odczyt_txt("dane.txt",n,v);
    Wypisz_tablice(v,n,"Tablica");
    if(n>=2)
    {

        Max_iloczyn(v,max1,n,k,A);
        Zapisz("wyniki.txt",max1,k,A);
    }
    else
        cout<<"Brak wystarczajacej liczby elementow w tablicy"<<endl;

    return 0;
}
