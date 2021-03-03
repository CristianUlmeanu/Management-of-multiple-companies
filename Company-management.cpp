#include <iostream>
#include <ctype.h>
#include <cstring>
#include <stdlib.h>
#include <typeinfo>
#include <vector>


using namespace std;


class Angajat
{
protected:
    string nume;
    string data_angajare;
    int salariu;
    static int nr_angajati;
public:
    Angajat(string, string, int);
    Angajat(Angajat&);
    virtual ~Angajat();
    virtual void citire(istream &in);
    virtual void afisare(ostream& out);
    void salariu_set(int x)
    {
        this->salariu=x;
    }
    string nume_get()
    {
        return nume;
    };
    int salariu_get()
    {
        return salariu;
    };
    friend istream& operator>>(istream& in, Angajat& a);
    friend ostream& operator<<(ostream& out,Angajat& a);
    Angajat& operator=(Angajat& a);
    static void afisare_nr_angajati()
    {
        cout<<"Numarul de angajati este: "<<nr_angajati;
    }

};

int Angajat::nr_angajati;

Angajat::Angajat(string nume="", string data="", int salariu=0)
{
    nr_angajati++;
    this->nume=nume;
    this->data_angajare=data;
    this->salariu=salariu;
}

Angajat::Angajat(Angajat& a)
{
    this->nume=a.nume;
    this->data_angajare=a.data_angajare;
    this->salariu=a.salariu;
}

Angajat::~Angajat()
{

}

void Angajat::citire(istream& in)
{
    cout<<"Care este numele persoanei? ";
    in>>nume;
    cout<<"Cand s-a alaturat companiei? ";
    in>>data_angajare;
    cout<<"Cat castiga acesta? ";
    in>>salariu;
}

istream& operator>>(istream& in, Angajat& a)
{
    a.citire(in);
    return in;
}

void Angajat::afisare(ostream& out)
{
    out<<"Nume: "<<nume<<endl;
    out<<"Acesta s-a angajat pe data de: "<<data_angajare<<endl;
    out<<"Salariu: "<<salariu<<endl;
}

ostream& operator<<(ostream& out, Angajat& a)
{
    a.afisare(out);
    return out;
}

Angajat& Angajat::operator=(Angajat& a)
{
    this->nume=a.nume;
    this->data_angajare=a.data_angajare;
    this->salariu=a.salariu;
}

class Manager:public Angajat
{
private:
    Angajat* ang;
    int nr_ang;
    static int nr_manageri;
public:
    Manager();
    Manager(Manager&);
    ~Manager();
    void citire(istream &in);
    void afisare(ostream &out);
    void nr_ang_set(int x)
    {
        this->nr_ang=x;
    }
    Angajat& ang_get(int x)
    {
        return ang[x];
    }
    int nr_ang_get()
    {
        return nr_ang;
    };
    int suma_salariu();
    void adaugare_ang();
    void stergere_ang();
    friend istream& operator>>(istream &in, Manager& a);
    friend ostream& operator<<(ostream &out, Manager& a);
    Manager& operator=(Manager& a);
    static void afisare_nr_manageri()
    {
        cout<<"Numarul de manageri este: "<<nr_manageri;
    }

};

int Manager::nr_manageri;

Manager::Manager():Angajat()
{
    nr_manageri++;
    this->nr_ang=0;
    this->ang=nullptr;
}

Manager::Manager(Manager& a):Angajat(a)
{
    this->nr_ang=a.nr_ang;
    this->ang=a.ang;
    /*new Angajat[a.nr_ang];
    for(int i=0; i<a.nr_ang; i++)
        b.ang[i]=a.ang[i];*/
}

Manager::~Manager()
{

}

void Manager::citire(istream& in)
{
    Angajat::citire(in);
    cout<<"______________________________________________"<<endl;
    cout<<"Cati angajati are managerul sub supraveghere? ";
    in>>nr_ang;
    cout<<"______________________________________________"<<endl;
    cout<<"Detalii angajati: "<<endl;
    ang=new Angajat[nr_ang];
    for(int i=0; i<nr_ang; i++)
    {
        cout<<endl<<"Angajat "<<i+1<<". "<<endl;
        in>>ang[i];
    }
    system("cls");
}

istream& operator>>(istream& in, Manager& a)
{
    a.citire(in);
    return in;
}

void Manager::afisare(ostream& out)
{
    Angajat::afisare(out);
    out<<"______________________________________________"<<endl;
    out<<"Angajatii managerului sunt: "<<endl;
    for (int i=0; i<nr_ang; i++)
    {
        out<<"Angajat "<<i+1<<". "<<endl;
        out<<ang[i];
    }

}

ostream& operator<<(ostream& out, Manager& a)
{
    a.afisare(out);
    return out;
}

Manager& Manager::operator=(Manager& a)
{
    Angajat::operator=(a);
    this->ang=a.ang;
    this->nr_ang=a.nr_ang;
}

int Manager::suma_salariu()
{
    int total_salariu=0;
    for(int i=0; i<nr_ang; i++)
        total_salariu=total_salariu+ang[i].salariu_get();
    total_salariu=total_salariu+salariu_get();
    return total_salariu;
}

void Manager::adaugare_ang()
{
    Angajat* copie;
    int nr_modificari=0;
    cout<<"Cati angajati vrei sa adaugi? ";
    cin>>nr_modificari;
    copie=new Angajat[nr_ang+nr_modificari];
    for (int i=0; i<nr_ang+nr_modificari; i++)
    {
        if(i<nr_ang)
            copie[i]=ang[i];
        else
        {
            cout<<endl<<"Citeste noul angajat."<<endl;
            cin>>copie[i];
        }
    }
    ang=new Angajat[nr_ang+nr_modificari];
    for (int i=0; i<nr_ang+nr_modificari; i++)
        ang[i]=copie[i];
    nr_ang=nr_ang+nr_modificari;

}

void Manager::stergere_ang()
{
    Angajat* copie;
    int nr_modificari=0,sterg_ang;
    cout<<"Cati angajati vrei sa stergi? ";
    cin>>nr_modificari;
    copie=new Angajat[nr_ang];
    for (int i=1; i<=nr_modificari; i++)
    {
        cout<<"Ce angajat vrei sa stergi? ";
        cin>>sterg_ang;
        try
        {
            if((sterg_ang>0)&&(sterg_ang<=nr_ang))
            {
                int k=0;
                for(int j=0; j<nr_ang-1; j++)
                {
                    if(j!=sterg_ang-1)
                    {
                        copie[j]=ang[k];
                        k++;
                    }
                    else
                    {
                        k++;
                        copie[j]=ang[k];
                        k++;
                    }
                }
                ang=new Angajat[nr_ang-1];
                for(int v=0; v<nr_ang-1; v++)
                {
                    ang[v]=copie[v];
                    cout<<"Dupa stergerea "<<v+1<<" lista s-a modificat in urmatorul mod: "<<endl<<ang[v]<<endl;
                }
                nr_ang=nr_ang-1;
            }
            else
                throw 1;
        }
        catch (int x)
        {
            cout<<"Angajatul selectat nu exista!"<<endl;
            cout<<"Te rog selecteaza un angajat dintre 0 si "<<nr_ang+1;
        }
    }

    //nr_ang=nr_ang-nr_modificari;


}

class Departament
{
protected:
    string nume_departament;
    Manager* man;
    int nr_man;
    static int nr_departamente;
public:
    Departament();
    Departament(Departament&);
    ~Departament();
    virtual void citire(istream &in);
    virtual void afisare(ostream &out);
    void nr_man_set(int x)
    {
        nr_man=x;
    }
    void man_set(int x)
    {
        man=new Manager[x];
    };
    Manager* man_get_p() const
    {
        return man;
    };
    Manager& man_get(int x)
    {
        return man[x];
    };
    string nume_departament_get()
    {
        return nume_departament;
    };
    int nr_man_get()
    {
        return nr_man;
    };
    int counter_ang_dep();
    friend istream& operator>>(istream &in, Departament& a);
    friend ostream& operator<<(ostream &out, Departament& a);
    Departament& operator=(Departament& a);
    static void afisare_nr_departamente()
    {
        cout<<"Numarul de departamente este: "<<nr_departamente;
    }

};

int Departament::nr_departamente;

Departament::Departament()
{
    nr_departamente++;
    this->nume_departament="";
    this->man=nullptr;
    this->nr_man=0;
}

Departament::Departament(Departament& a)
{
    this->nume_departament=a.nume_departament;
    this->nr_man=a.nr_man;
    this->man=a.man;
    /*new Manager[a.nr_man];
    for(int i=0; i<a.nr_man; i++)
        b.man[i]=a.man[i];*/
}

Departament::~Departament()
{

}

void Departament::citire(istream& in)
{
    system("cls");
    cout<<"Care este numele departamentului? ";
    in>>nume_departament;
    cout<<"Cati manageri are departamentul? ";
    in>>nr_man;
    man=new Manager[nr_man];
    for(int i=0; i<nr_man; i++)
    {
        cout<<"______________________________________________"<<endl<<"Detalii manager "<<i+1<<": "<<endl<<"______________________________________________"<<endl;
        in>>man[i];
    }
    cout<<"______________________________________________";
    cout<<endl;

}

void Departament::afisare(ostream& out)
{
    out<<"Departament: "<<nume_departament;
    for(int i=0; i<nr_man; i++)
    {
        out<<endl<<endl<<"Managerul "<<i+1<<" din departament are urmatoarele informatii: "<<endl;
        out<<"______________________________________________"<<endl;
        out<<man[i];
    }

}

istream& operator>> (istream& in, Departament& a)
{
    a.citire(in);
    return in;
}

ostream& operator<< (ostream& out, Departament& a)
{
    a.afisare(out);
    return out;
}

Departament& Departament::operator=(Departament& a)
{
    this->nume_departament=a.nume_departament;
    this->man=a.man;
    this->nr_man=a.nr_man;
}

int Departament::counter_ang_dep()
{
    int nr_ang_dep=0;
    for(int i=0; i<nr_man; i++)
        nr_ang_dep=nr_ang_dep+man[i].nr_ang_get();
    nr_ang_dep=nr_ang_dep+nr_man;
    return nr_ang_dep;
}

class Departament_impozit:public Departament
{
private:
    int impozit;
    static int nr_departamente_impozit;
public:
    Departament_impozit();
    Departament_impozit(Departament_impozit&);
    ~Departament_impozit();
    void citire(istream& in);
    void afisare(ostream& out);
    void ajustare_salarii();
    friend istream& operator>>(istream &in, Departament_impozit& a);
    friend ostream& operator<<(ostream &out, Departament_impozit& a);
    Departament_impozit& operator=(Departament_impozit& a);
    static void afisare_nr_departamente_impozit()
    {
        cout<<"Numarul de departamente este: "<<nr_departamente_impozit;
    }

};

int Departament_impozit::nr_departamente_impozit;

Departament_impozit::Departament_impozit():Departament()
{
    nr_departamente_impozit++;
    this->impozit=16;
}

Departament_impozit::Departament_impozit(Departament_impozit& a):Departament(a)
{
    this->impozit=a.impozit;
}

Departament_impozit::~Departament_impozit()
{

}

void Departament_impozit::citire(istream& in)
{
    cout<<"Care este rata de impozitare a salariilor in departament? ";
    in>>impozit;
    Departament::citire(in);
    ajustare_salarii();
}

void Departament_impozit::afisare(ostream& out)
{
    out<<"Departamentul are o rata de impozitare a salariilor de: "<<impozit<<" %."<<endl;
    Departament::afisare(out);
}

void Departament_impozit::ajustare_salarii()
{
    for (int i=0; i<nr_man; i++)
    {
        man[i].salariu_set(man[i].salariu_get()-man[i].salariu_get()*impozit/100);
        for(int j=0; j<man[i].nr_ang_get(); j++)
            man[i].ang_get(j).salariu_set(man[i].ang_get(j).salariu_get()-man[i].ang_get(j).salariu_get()*impozit/100);
    }

}

istream& operator>> (istream& in, Departament_impozit& a)
{
    a.citire(in);
    return in;
}

ostream& operator<< (ostream& out, Departament_impozit& a)
{
    a.afisare(out);
    return out;
}

Departament_impozit& Departament_impozit::operator=(Departament_impozit& a)
{
    Departament::operator=(a);
    this->impozit=a.impozit;
}


class Companie
{
private:
    string nume_companie;
    Departament* dep;
    int nr_dep;
    static int nr_companii;
public:
    Companie();
    Companie(Companie&);
    ~Companie();
    void nume_companie_set(string);
    string nume_companie_get()
    {
        return nume_companie;
    };
    Departament& dep_get (int x)
    {
        return dep[x];
    };
    Departament lista_manageri(int x)
    {
        cout<<dep[x]<<endl;
    };
    int nr_dep_get()
    {
        return nr_dep;
    };
    int counter_ang_comp();
    int salariu_total_comp();
    void adaugare_dep();
    void stergere_dep();
    void citire(istream &in);
    void afisare(ostream &out);
    friend istream& operator>>(istream &in, Companie& a);
    friend ostream& operator<<(ostream &out, Companie& a);
    Companie& operator=(const Companie& a);
    Companie operator+(Companie& a);
    friend bool operator==(const Companie &a1, const Companie &a2);
    static void afisare_nr_companii()
    {
        cout<<"Numarul de companii este: "<<nr_companii;
    }

};

int Companie::nr_companii;

Companie::Companie()
{
    nr_companii++;
    this->nume_companie="";
    this->dep=nullptr;
    this->nr_dep=0;
}
Companie::Companie(Companie& a)
{
    this->nume_companie=a.nume_companie;
    this->nr_dep=a.nr_dep;
    this->dep=a.dep;
    /*new Departament[a.nr_dep];
    for(int i=0; i<a.nr_dep; i++)
        b.dep[i]=a.dep[i];*/
}
Companie::~Companie()
{

}

void Companie::nume_companie_set(string x)
{
    nume_companie=x;
}

void Companie::citire(istream &in)
{
    system("cls");
    cout<<"Numele companiei este: ";
    in.get();
    getline(in,nume_companie);
    cout<<"Cate departamente contine compania ta? ";
    in>>nr_dep;
    dep=new Departament[nr_dep];
    for(int i=0; i<nr_dep; i++)
    {
        cout<<endl<<"Departament "<<i+1<<": "<<endl;
        in>>dep[i];
    }
}

void Companie::afisare(ostream &out)
{
    out<<"Numele companiei este: "<<nume_companie<<endl;
    out<<"______________________________________________"<<endl;
    for(int i=0; i<nr_dep; i++)
    {
        out<<endl<<endl<<i+1<<" . ";
        out<<dep[i];
    }

}

istream& operator>> (istream& in, Companie& a)
{
    a.citire(in);
    return in;
}

ostream& operator<< (ostream& out, Companie& a)
{
    a.afisare(out);
    return out;
}

Companie& Companie::operator=(const Companie& a)
{
    this->nume_companie=a.nume_companie;
    this->dep=a.dep;
    this->nr_dep=a.nr_dep;
}

Companie Companie::operator+(Companie& a)
{
    Companie rezultat;
    int departamente_identice=0;
    rezultat.nume_companie=this->nume_companie+" "+a.nume_companie;
    for (int i=0; i<this->nr_dep; i++)
    {
        for(int j=0; j<a.nr_dep; j++)
        {
            if (this->dep[i].nume_departament_get()==a.dep[i].nume_departament_get())
                departamente_identice++;
        }
    }
    rezultat.nr_dep=this->nr_dep+a.nr_dep-departamente_identice;
    rezultat.dep=new Departament[rezultat.nr_dep];
    for (int i=0; i<this->nr_dep; i++)
        rezultat.dep[i]=this->dep[i];
    int mor=this->nr_dep;
    for (int i=0; i<a.nr_dep; i++)
    {
        int ok=0;
        for(int j=0; j<this->nr_dep; j++)
        {
            if (rezultat.dep[j].nume_departament_get()==a.dep[i].nume_departament_get())
            {
                Manager* copie;
                copie=new Manager[rezultat.dep[j].nr_man_get()+a.dep[i].nr_man_get()];
                for(int k=0; k<rezultat.dep[j].nr_man_get(); k++)
                {
                    copie[k]=rezultat.dep[j].man_get(k);
                }
                int aux=rezultat.dep[j].nr_man_get();
                for(int k=0; k<a.dep[i].nr_man_get(); k++)
                {
                    copie[aux]=a.dep[i].man_get(k);
                    aux++;
                }
                rezultat.dep[j].man_set(rezultat.dep[j].nr_man_get()+a.dep[i].nr_man_get());
                for (int k=0; k<rezultat.dep[j].nr_man_get()+a.dep[i].nr_man_get(); k++)
                    rezultat.dep[j].man_get(k)=copie[k];
                ok=1;
                rezultat.dep[j].nr_man_set(rezultat.dep[j].nr_man_get()+a.dep[i].nr_man_get());
            }
        }
        if (ok==0)
        {
            rezultat.dep[mor]=a.dep[i];
            mor++;
        }
    }
    return rezultat;
}

bool operator==(const Companie &a1,const Companie &a2)
{
    if ((a1.nume_companie==a2.nume_companie)&&(a1.nr_dep==a2.nr_dep))
        return true;
}


int Companie::counter_ang_comp()
{
    int nr_ang_comp=0;
    for (int i=0; i<nr_dep; i++)
        nr_ang_comp=nr_ang_comp+dep_get(i).counter_ang_dep();
    return nr_ang_comp;
}

int Companie::salariu_total_comp()
{
    int total_salarii=0;
    for (int i=0; i<nr_dep; i++)
    {
        for (int j=0; j<dep_get(i).nr_man_get(); j++)
            total_salarii=total_salarii+dep_get(i).man_get(j).suma_salariu();
    }
    return total_salarii;
}

void Companie::adaugare_dep()
{
    Departament* copie;
    int nr_modificari=0;
    cout<<"Cate departamente vrei sa adaugi? ";
    cin>>nr_modificari;
    copie=new Departament[nr_dep+nr_modificari];
    for (int i=0; i<nr_dep+nr_modificari; i++)
    {
        if(i<nr_dep)
            copie[i]=dep[i];
        else
        {
            cout<<endl<<"Citeste noul departament."<<endl;
            cin>>copie[i];
        }
    }
    dep=new Departament[nr_dep+nr_modificari];
    for (int i=0; i<nr_dep+nr_modificari; i++)
        dep[i]=copie[i];
    nr_dep=nr_dep+nr_modificari;
}

void Companie::stergere_dep()
{
    Departament* copie;
    int nr_modificari=0,sterg_dep;
    cout<<"Cate departamente vrei sa stergi? ";
    cin>>nr_modificari;
    copie=new Departament[nr_dep];
    for (int i=0; i<nr_modificari; i++)
    {
        cout<<"Ce departament vrei sa stergi? ";
        cin>>sterg_dep;
        try
        {
            if((sterg_dep>0)&&(sterg_dep<=nr_dep))
            {
                int k=0;
                for(int j=0; j<nr_dep-1; j++)
                {
                    if(j!=sterg_dep-1)
                    {
                        copie[j]=dep[k];
                        k++;
                    }
                    else
                    {
                        k++;
                        copie[j]=dep[k];
                        k++;
                    }
                }
                dep=new Departament[nr_dep-1];
                for(int v=0; v<nr_dep-1; v++)
                {
                    dep[v]=copie[v];
                    cout<<"Dupa "<<v+1<<" stergere lista s-a modificat in urmatorul mod: "<<endl<<dep[v]<<endl;
                }
                nr_dep=nr_dep-1;
            }
            else
                throw 1;
        }
        catch (int x)
        {
            cout<<"Departamentul selectat nu exista!"<<endl;
            cout<<"Te rog selecteaza un departament dintre 0 si "<<nr_dep+1;
        }
    }


}

class Companie_impozit
{
private:
    string nume_companie_imp;
    Departament_impozit* dep_imp;
    int nr_dep_imp;
    static int nr_companii_impozit;
public:
    Companie_impozit();
    Companie_impozit(Companie_impozit&);
    ~Companie_impozit();
    void nume_companie_imp_set(string);
    string nume_companie_imp_get()
    {
        return nume_companie_imp;
    };
    Departament_impozit& dep_get_imp (int x)
    {
        return dep_imp[x];
    };
    Departament_impozit lista_manageri_imp(int x)
    {
        cout<<dep_imp[x]<<endl;
    };
    int nr_dep_imp_get()
    {
        return nr_dep_imp;
    };
    int counter_ang_comp_imp();
    int salariu_total_comp_imp();
    void adaugare_dep_imp();
    void stergere_dep_imp();
    void citire(istream &in);
    void afisare(ostream &out);
    friend istream& operator>>(istream &in, Companie_impozit& a);
    friend ostream& operator<<(ostream &out, Companie_impozit& a);
    Companie_impozit& operator=(const Companie_impozit& a);
    Companie_impozit operator+(Companie_impozit& a);
    friend bool operator==(const Companie_impozit &a1, const Companie_impozit &a2);
    static void afisare_nr_companii_imp()
    {
        cout<<"Numarul de companii este: "<<nr_companii_impozit;
    }

};

int Companie_impozit::nr_companii_impozit;

Companie_impozit::Companie_impozit()
{
    nr_companii_impozit++;
    this->nume_companie_imp="";
    this->dep_imp=nullptr;
    this->nr_dep_imp=0;
}
Companie_impozit::Companie_impozit(Companie_impozit& a)
{
    this->nume_companie_imp=a.nume_companie_imp;
    this->nr_dep_imp=a.nr_dep_imp;
    this->dep_imp=a.dep_imp;
}
Companie_impozit::~Companie_impozit()
{

}

void Companie_impozit::nume_companie_imp_set(string x)
{
    nume_companie_imp=x;
}

void Companie_impozit::citire(istream &in)
{
    system("cls");
    cout<<"Numele companiei este: ";
    in.get();
    getline(in,nume_companie_imp);
    cout<<"Cate departamente contine compania ta? ";
    in>>nr_dep_imp;
    dep_imp=new Departament_impozit[nr_dep_imp];
    for(int i=0; i<nr_dep_imp; i++)
    {
        cout<<endl<<"Departament "<<i+1<<": "<<endl;
        in>>dep_imp[i];
    }
}

void Companie_impozit::afisare(ostream &out)
{
    out<<"Numele companiei este: "<<nume_companie_imp<<endl;
    out<<"______________________________________________"<<endl;
    for(int i=0; i<nr_dep_imp; i++)
    {
        out<<endl<<endl<<i+1<<" . ";
        out<<dep_imp[i];
    }

}

istream& operator>> (istream& in, Companie_impozit& a)
{
    a.citire(in);
    return in;
}

ostream& operator<< (ostream& out, Companie_impozit& a)
{
    a.afisare(out);
    return out;
}

Companie_impozit& Companie_impozit::operator=(const Companie_impozit& a)
{
    this->nume_companie_imp=a.nume_companie_imp;
    this->dep_imp=a.dep_imp;
    this->nr_dep_imp=a.nr_dep_imp;
}

Companie_impozit Companie_impozit::operator+(Companie_impozit& a)
{
    Companie_impozit rezultat;
    int departamente_identice=0;
    rezultat.nume_companie_imp=this->nume_companie_imp+" "+a.nume_companie_imp;
    for (int i=0; i<this->nr_dep_imp; i++)
    {
        for(int j=0; j<a.nr_dep_imp; j++)
        {
            if (this->dep_imp[i].nume_departament_get()==a.dep_imp[i].nume_departament_get())
                departamente_identice++;
        }
    }
    rezultat.nr_dep_imp=this->nr_dep_imp+a.nr_dep_imp-departamente_identice;
    rezultat.dep_imp=new Departament_impozit[rezultat.nr_dep_imp];
    for (int i=0; i<this->nr_dep_imp; i++)
        rezultat.dep_imp[i]=this->dep_imp[i];
    int mor_rau=this->nr_dep_imp;
    for (int i=0; i<a.nr_dep_imp; i++)
    {
        int ok=0;
        for(int j=0; j<this->nr_dep_imp; j++)
        {
            if (rezultat.dep_imp[j].nume_departament_get()==a.dep_imp[i].nume_departament_get())
            {
                Manager* copie;
                copie=new Manager[rezultat.dep_imp[j].nr_man_get()+a.dep_imp[i].nr_man_get()];
                for(int k=0; k<rezultat.dep_imp[j].nr_man_get(); k++)
                {
                    copie[k]=rezultat.dep_imp[j].man_get(k);
                }
                int aux=rezultat.dep_imp[j].nr_man_get();
                for(int k=0; k<a.dep_imp[i].nr_man_get(); k++)
                {
                    copie[aux]=a.dep_imp[i].man_get(k);
                    aux++;
                }
                rezultat.dep_imp[j].man_set(rezultat.dep_imp[j].nr_man_get()+a.dep_imp[i].nr_man_get());
                for (int k=0; k<rezultat.dep_imp[j].nr_man_get()+a.dep_imp[i].nr_man_get(); k++)
                    rezultat.dep_imp[j].man_get(k)=copie[k];
                ok=1;
                rezultat.dep_imp[j].nr_man_set(rezultat.dep_imp[j].nr_man_get()+a.dep_imp[i].nr_man_get());
            }
        }
        if (ok==0)
        {
            rezultat.dep_imp[mor_rau]=a.dep_imp[i];
            mor_rau++;
        }
    }
    return rezultat;
}

bool operator==(const Companie_impozit &a1,const Companie_impozit &a2)
{
    if ((a1.nume_companie_imp==a2.nume_companie_imp)&&(a1.nr_dep_imp==a2.nr_dep_imp))
        return true;
}


int Companie_impozit::counter_ang_comp_imp()
{
    int nr_ang_comp=0;
    for (int i=0; i<nr_dep_imp; i++)
        nr_ang_comp=nr_ang_comp+dep_get_imp(i).counter_ang_dep();
    return nr_ang_comp;
}

int Companie_impozit::salariu_total_comp_imp()
{
    int total_salarii=0;
    for (int i=0; i<nr_dep_imp; i++)
    {
        for (int j=0; j<dep_get_imp(i).nr_man_get(); j++)
            total_salarii=total_salarii+dep_get_imp(i).man_get(j).suma_salariu();
    }
    return total_salarii;
}

void Companie_impozit::adaugare_dep_imp()
{
    Departament_impozit* copie;
    int nr_modificari=0;
    cout<<"Cate departamente vrei sa adaugi? ";
    cin>>nr_modificari;
    copie=new Departament_impozit[nr_dep_imp+nr_modificari];
    for (int i=0; i<nr_dep_imp+nr_modificari; i++)
    {
        if(i<nr_dep_imp)
            copie[i]=dep_imp[i];
        else
        {
            cout<<endl<<"Citeste noul departament."<<endl;
            cin>>copie[i];
        }
    }
    dep_imp=new Departament_impozit[nr_dep_imp+nr_modificari];
    for (int i=0; i<nr_dep_imp+nr_modificari; i++)
        dep_imp[i]=copie[i];
    nr_dep_imp=nr_dep_imp+nr_modificari;
}

void Companie_impozit::stergere_dep_imp()
{
    Departament_impozit* copie;
    int nr_modificari=0,sterg_dep;
    cout<<"Cate departamente vrei sa stergi? ";
    cin>>nr_modificari;
    copie=new Departament_impozit[nr_dep_imp];
    for (int i=0; i<nr_modificari; i++)
    {
        cout<<"Ce departament vrei sa stergi? ";
        cin>>sterg_dep;
        try
        {
            if((sterg_dep>0)&&(sterg_dep<=nr_dep_imp))
            {
                int k=0;
                for(int j=0; j<nr_dep_imp-1; j++)
                {
                    if(j!=sterg_dep-1)
                    {
                        copie[j]=dep_imp[k];
                        k++;
                    }
                    else
                    {
                        k++;
                        copie[j]=dep_imp[k];
                        k++;
                    }
                }
                dep_imp=new Departament_impozit[nr_dep_imp-1];
                for(int v=0; v<nr_dep_imp-1; v++)
                {
                    dep_imp[v]
                        =copie[v];
                    cout<<"Dupa "<<v+1<<" stergere lista s-a modificat in urmatorul mod: "<<endl<<dep_imp[v]<<endl;
                }
                nr_dep_imp=nr_dep_imp-1;
            }
            else
                throw 1;
        }
        catch (int x)
        {
            cout<<"Departamentul selectat nu exista!"<<endl;
            cout<<"Te rog selecteaza un departament dintre 0 si "<<nr_dep_imp+1;
        }
    }


}

template <class gestionar> class HRManager
{
private:
    string nume_gestionar;
    gestionar *comp;
    int nr_comp;
    static int nr_gest;
public:
    HRManager()
    {
        this->nume_gestionar="";
        this->comp=nullptr;
    }
    /*HRManager(HRManager& a)
    {
        this->nume_gestionar=a.nume_gestionar;
        this->comp=a.comp;
    }*/
    ~HRManager()
    {

    }
    gestionar& comp_get(int x)
    {
        return comp[x];
    };
    int nr_comp_get()
    {
        return nr_comp;
    };
    void citire(istream &in)
    {
        cout<<"Ce nume va avea gestionarul tau? "<<endl;
        in.get();
        getline(in,nume_gestionar);
        cout<<"Cate companii va contine gestionarul tau? "<<endl;
        in>>nr_comp;
        comp=new gestionar[nr_comp];
        for (int i=0; i<nr_comp; i++)
        {
            in>>comp[i];
            if(i>0)
            {
                for(int j=i-1; j>=0; j--)
                {
                    try
                    {
                        if (comp[i]==comp[j])
                        {
                            throw 1;
                        }
                    }
                    catch (int x)
                    {
                        cout<<"Compania citita se afla deja in gestionar te rugam sa recitesti compania! ";
                        system("pause");
                        i--;
                    }
                }
            }
        }
    }
    void afisare(ostream &out)
    {
        out<<"Gestionarul se numeste: "<<nume_gestionar<<endl;
        out<<"______________________________________________"<<endl;
        for (int i=0; i<nr_comp; i++)
            out<<"Compania "<<i+1<<" este: "<<endl<<comp[i]<<endl<<endl;
    }
    void fuzionare()
    {
        gestionar* copie;
        int nr_comp1,nr_comp2;
        cout<<"Care e prima companie pe care vrei sa o fuzionezi? ";
        cin>>nr_comp1;
        cout<<"Cu ce companie vrei sa fuzioneze? ";
        cin>>nr_comp2;
        copie=new gestionar[nr_comp-1];
        if(nr_comp1<nr_comp2)
        {
            for(int i=0; i<nr_comp1-1; i++)
                copie[i]=comp[i];
            copie[nr_comp1-1]=comp[nr_comp1-1]+comp[nr_comp2-1];
            for(int i=nr_comp1; i<nr_comp2-1; i++)
                copie[i]=comp[i];
            for(int i=nr_comp2-1; i<nr_comp-1; i++)
                copie[i]=comp[i+1];
        }
        else
        {
            for(int i=0; i<nr_comp2-1; i++)
                copie[i]=comp[i];
            copie[nr_comp2-1]=comp[nr_comp2-1]+comp[nr_comp1-1];
            for(int i=nr_comp2; i<nr_comp1-1; i++)
                copie[i]=comp[i];
            for(int i=nr_comp1-1; i<nr_comp-1; i++)
                copie[i]=comp[i+1];
        }
        comp=new gestionar[nr_comp-1];
        for (int i=0; i<nr_comp-1; i++)
            comp[i]=copie[i];
        nr_comp--;
    }
    void adaugare_comp()
    {
        gestionar* copie;
        int nr_modificari=0;
        cout<<"Cate companii vrei sa adaugi? ";
        cin>>nr_modificari;
        copie=new gestionar[nr_comp+nr_modificari];
        for (int i=0; i<nr_comp+nr_modificari; i++)
        {
            if(i<nr_comp)
                copie[i]=comp[i];
            else
            {
                cout<<endl<<"Citeste noua companie."<<endl;
                cin>>copie[i];
            }
        }
        comp=new gestionar[nr_comp+nr_modificari];
        for (int i=0; i<nr_comp+nr_modificari; i++)
            comp[i]=copie[i];
        nr_comp=nr_comp+nr_modificari;
    }
    void stergere_comp()
    {
        gestionar* copie;
        int nr_modificari=0,sterg_comp;
        cout<<"Cate companii vrei sa stergi? ";
        cin>>nr_modificari;
        copie=new gestionar[nr_comp];
        for (int i=0; i<nr_modificari; i++)
        {
            cout<<"Ce companie vrei sa stergi? ";
            cin>>sterg_comp;
            try
            {
                if((sterg_comp>0)&&(sterg_comp<=nr_comp))
                {
                    int k=0;
                    for(int j=0; j<nr_comp-1; j++)
                    {
                        if(j!=sterg_comp-1)
                        {
                            copie[j]=comp[k];
                            k++;
                        }
                        else
                        {
                            k++;
                            copie[j]=comp[k];
                            k++;
                        }
                    }
                    comp=new gestionar[nr_comp-1];
                    for(int v=0; v<nr_comp-1; v++)
                    {
                        comp[v]=copie[v];
                        cout<<"Dupa stergerea "<<v+1<<" lista s-a modificat in urmatorul mod: "<<endl<<comp[v]<<endl;
                    }
                    nr_comp=nr_comp-1;
                }
                else
                    throw 1;
            }
            catch (int x)
            {
                cout<<"Compania selectata nu exista!"<<endl;
                cout<<"Te rog selecteaza o compani dintre 0 si "<<nr_comp+1;
            }
        }

    }
    friend istream& operator>>(istream &in, HRManager <gestionar> &a)
    {
        a.citire(in);
        return in;
    }

    friend ostream& operator<<(ostream &out, HRManager <gestionar>&a)
    {
        a.afisare(out);
        return out;
    }
    HRManager& operator=(HRManager <gestionar> &a)
    {
        this->nume_gestionar=a.nume_gestionar;
        this->c=a.c;
    }
};

template <> class HRManager<Companie_impozit>
{
private:
    string nume_gestionar;
    Companie_impozit *comp;
    int nr_comp;
    static int nr_gest;
public:
    HRManager()
    {
        this->nume_gestionar="";
        this->comp=nullptr;
    }
    ~HRManager()
    {

    }
    Companie_impozit& comp_get(int x)
    {
        return comp[x];
    };
    int nr_comp_get()
    {
        return nr_comp;
    };
    void citire(istream &in)
    {
        cout<<"Ce nume va avea gestionarul tau? "<<endl;
        in.get();
        getline(in,nume_gestionar);
        cout<<"Cate companii va contine gestionarul tau? "<<endl;
        in>>nr_comp;
        comp=new Companie_impozit[nr_comp];
        for (int i=0; i<nr_comp; i++)
        {
            in>>comp[i];
            if(i>0)
            {
                for(int j=i-1; j>=0; j--)
                {
                    try
                    {
                        if (comp[i]==comp[j])
                        {
                            throw 1;
                        }
                    }
                    catch (int x)
                    {
                        cout<<"Compania citita se afla deja in gestionar te rugam sa recitesti compania! ";
                        system("pause");
                        i--;
                    }
                }
            }
        }
    }
    void afisare(ostream &out)
    {
        out<<"Gestionarul se numeste: "<<nume_gestionar<<endl;
        out<<"______________________________________________"<<endl;
        for (int i=0; i<nr_comp; i++)
            out<<"Compania "<<i+1<<" este: "<<endl<<comp[i]<<endl<<endl;
    }
    void fuzionare()
    {
        Companie_impozit* copie;
        int nr_comp1,nr_comp2;
        cout<<"Care e prima companie pe care vrei sa o fuzionezi? ";
        cin>>nr_comp1;
        cout<<"Cu ce companie vrei sa fuzioneze? ";
        cin>>nr_comp2;
        copie=new Companie_impozit[nr_comp-1];
        if(nr_comp1<nr_comp2)
        {
            for(int i=0; i<nr_comp1-1; i++)
                copie[i]=comp[i];
            copie[nr_comp1-1]=comp[nr_comp1-1]+comp[nr_comp2-1];
            for(int i=nr_comp1; i<nr_comp2-1; i++)
                copie[i]=comp[i];
            for(int i=nr_comp2-1; i<nr_comp-1; i++)
                copie[i]=comp[i+1];
        }
        else
        {
            for(int i=0; i<nr_comp2-1; i++)
                copie[i]=comp[i];
            copie[nr_comp2-1]=comp[nr_comp2-1]+comp[nr_comp1-1];
            for(int i=nr_comp2; i<nr_comp1-1; i++)
                copie[i]=comp[i];
            for(int i=nr_comp1-1; i<nr_comp-1; i++)
                copie[i]=comp[i+1];
        }
        comp=new Companie_impozit[nr_comp-1];
        for (int i=0; i<nr_comp-1; i++)
            comp[i]=copie[i];
        nr_comp--;
    }
    void adaugare_comp()
    {
        Companie_impozit* copie;
        int nr_modificari=0;
        cout<<"Cate companii vrei sa adaugi? ";
        cin>>nr_modificari;
        copie=new Companie_impozit[nr_comp+nr_modificari];
        for (int i=0; i<nr_comp+nr_modificari; i++)
        {
            if(i<nr_comp)
                copie[i]=comp[i];
            else
            {
                cout<<endl<<"Citeste noua companie."<<endl;
                cin>>copie[i];
            }
        }
        comp=new Companie_impozit[nr_comp+nr_modificari];
        for (int i=0; i<nr_comp+nr_modificari; i++)
            comp[i]=copie[i];
        nr_comp=nr_comp+nr_modificari;
    }
    void stergere_comp()
    {
        Companie_impozit* copie;
        int nr_modificari=0,sterg_comp;
        cout<<"Cate companii vrei sa stergi? ";
        cin>>nr_modificari;
        copie=new Companie_impozit[nr_comp];
        for (int i=0; i<nr_modificari; i++)
        {
            cout<<"Ce companie vrei sa stergi? ";
            cin>>sterg_comp;
            try
            {
                if((sterg_comp>0)&&(sterg_comp<=nr_comp))
                {
                    int k=0;
                    for(int j=0; j<nr_comp-1; j++)
                    {
                        if(j!=sterg_comp-1)
                        {
                            copie[j]=comp[k];
                            k++;
                        }
                        else
                        {
                            k++;
                            copie[j]=comp[k];
                            k++;
                        }
                    }
                    comp=new Companie_impozit[nr_comp-1];
                    for(int v=0; v<nr_comp-1; v++)
                    {
                        comp[v]=copie[v];
                        cout<<"Dupa stergerea "<<v+1<<" lista s-a modificat in urmatorul mod: "<<endl<<comp[v]<<endl;
                    }
                    nr_comp=nr_comp-1;
                }
                else
                    throw 1;
            }
            catch (int x)
            {
                cout<<"Compania selectata nu exista!"<<endl;
                cout<<"Te rog selecteaza o compani dintre 0 si "<<nr_comp+1;
            }
        }

    }
    friend istream& operator>>(istream &in, HRManager <Companie_impozit> &a)
    {
        a.citire(in);
        return in;
    }

    friend ostream& operator<<(ostream &out, HRManager <Companie_impozit>&a)
    {
        a.afisare(out);
        return out;
    }
    HRManager& operator=(HRManager <Companie_impozit> &a)
    {
        this->nume_gestionar=a.nume_gestionar;
        this->comp=a.comp;
    }
};

void meniu_principal()
{

    cout<<endl<<" 1. Citire"<<endl;
    cout<<" 2. Afisare completa"<<endl;
    cout<<" 3. Afisare numar angajati"<<endl;
    cout<<" 4. Costurile salariilor pe care le are o companie"<<endl;
    cout<<" 5. Afisare lista manageri companie si subalternii acestuia"<<endl;
    cout<<" 6. Afisare lista departamente bazat pe numarul de angajati"<<endl;
    cout<<" 7. Modificarea datelor"<<endl;
    cout<<" 8. Fuzionare companii"<<endl;
    cout<<" 9. Testare concepte de Dynamic cast, Upcasting si Downcasting"<<endl;
    cout<<" 10. Iesire"<<endl;
}

int meniu()
{
    cout<<"Ulmeanu Cristian, Grupa 253, Proiect 3, Implementare Clasa 'Companii' "<<endl;
    cout<<endl<<"|||-------------------------MENIU-------------------------------|||"<<endl;
    cout<<endl<<" In acest meniu sunt prezente toate actiunile cerute de proiect";
    cout<<endl<<"_____________________________________________________________________"<<endl<<endl;
    int opt=1, nr_gest, tip_gestionar;
    cout<<"Pe ce tip de gestionar doresti sa lucrezi dintre: "<<endl<<"1. Gestionar pentru toate companiile"<<endl;
    cout<<"2. Gestionar specializat pentru companiile ce au impozit"<<endl<<"Alege varianta 1 sau varianta 2 (1 /2)."<<endl;
    cin>>tip_gestionar;
    if(tip_gestionar==1)
    {
        system("cls");
        vector <HRManager <Companie>> gest;
        while (opt!=100)
        {
            meniu_principal();
            cout<<endl<<"Ce actiune doriti sa incercati (actiunea aleasa trebuie sa fie unul din numerele de ordine reprezentative de la 1 la 10)? "<<endl;
            cin>>opt;
            if(opt==1)
            {
                system("cls");
                cout<<"Cate gestionare doriti sa aveti? ";
                cin>>nr_gest;
                try
                {
                    if (nr_gest<1)
                        throw 'c';
                    else
                    {
                        gest.resize(nr_gest);
                        for(int i=0; i<nr_gest; i++)
                            cin>>gest[i];
                    }
                }
                catch (char c)
                {
                    cout<<"Numarul de gestionare nu poate fi mai mic de 1";
                    exit(EXIT_FAILURE);
                }
            }
            if (opt==2)
            {
                system("cls");
                if(nr_gest!=0)
                {
                    for(int i=0; i<nr_gest; i++)
                        cout<<gest[i];
                }
                else
                    cout<<"Gestionarul nu a fost creat.";
            }

            if (opt==3)
            {
                system("cls");
                int nr_departament,nr_companie, nr_gestionar;
                string varianta;
                cout<<"In ce gestionar doresti sa lucrezi? ";
                cin>>nr_gestionar;
                try
                {
                    if((nr_gestionar>0)&&(nr_gestionar<=nr_gest))
                    {
                        cout<<"Doresti sa aflii angajatii intregii companiei sau a unui departament din companie(Companie/Departament)? ";
                        cin>>varianta;
                        if(varianta=="Departament")
                        {
                            cout<<"Din ce companie face parte departamentul tau? ";
                            cin>>nr_companie;
                            cout<<"Al carei departament doresti sa ii aflii numarul de angajati? ";
                            cin>>nr_departament;
                            cout<<"Numarul de angajati ai departamentului "<<nr_departament<<" este: ";
                            cout<<gest[nr_gestionar-1].comp_get(nr_companie-1).dep_get(nr_departament-1).counter_ang_dep();
                        }
                        else if(varianta=="Companie")
                        {
                            cout<<"A carei companii vrei sa aflii numarul total de angajati? ";
                            cin>>nr_companie;
                            cout<<"Numarul de angajati ai companiei "<<nr_companie<<" din gestionarul "<<nr_gestionar<<" este: ";
                            cout<<gest[nr_gestionar-1].comp_get(nr_companie-1).counter_ang_comp();
                        }
                        else
                            throw 1;
                    }
                    else
                        throw 'c';
                }
                catch (char c)
                {
                    cout<<"Gestionarul ales nu exista!"<<endl;
                    cout<<"Te rog alege un nr intre 0 si "<<nr_gest+1<<" ."<<endl;
                }
                catch (int nr)
                {
                    cout<<"Varianta aleasa nu este valida";
                    exit(EXIT_FAILURE);
                }

            }

            if (opt==4)
            {
                system("cls");
                int nr_companie,nr_gestionar;
                cout<<"In ce gestionar doresti sa lucrezi? ";
                cin>>nr_gestionar;
                try
                {
                    if((nr_gestionar>0)&&(nr_gestionar<=nr_gest))
                    {
                        cout<<"A carei companii vrei sa aflii suma totala pe care o are alocata pentru salarii? ";
                        cin>>nr_companie;
                        cout<<"Suma totala alocata pentru salarii de compania "<<gest[nr_gestionar-1].comp_get(nr_companie-1).nume_companie_get()<<" este: "<<gest[nr_gestionar-1].comp_get(nr_companie-1).salariu_total_comp();
                    }
                    else
                        throw 1;
                }
                catch (int nr)
                {
                    cout<<"Gestionarul ales nu exista!"<<endl;
                    cout<<"Te rog alege un nr intre 0 si "<<nr_gest+1<<" ."<<endl;
                }
            }
            if (opt==5)
            {
                system("cls");
                int nr_companie,nr_gestionar;
                cout<<"In ce gestionar doresti sa lucrezi? ";
                cin>>nr_gestionar;
                try
                {
                    if((nr_gestionar>0)&&(nr_gestionar<=nr_gest))
                    {
                        cout<<"Al carei companii doresti sa ii aflii Managerii si subalternii acestuia? ";
                        cin>>nr_companie;
                        for(int i=0; i<gest[nr_gestionar-1].comp_get(nr_companie-1).nr_dep_get(); i++)
                            gest[nr_gestionar-1].comp_get(nr_companie-1).lista_manageri(i);
                    }
                    else
                        throw 1;
                }
                catch (int x)
                {
                    cout<<"Gestionarul ales nu exista!"<<endl;
                    cout<<"Te rog alege un nr intre 0 si "<<nr_gest+1<<" ."<<endl;
                }
            }

            if (opt==6)
            {
                system("cls");
                int nr_angajat,nr_gestionar;
                cout<<"In ce gestionar doresti sa lucrezi? ";
                cin>>nr_gestionar;
                try
                {
                    if((nr_gestionar>0)&&(nr_gestionar<=nr_gest))
                    {
                        cout<<"De cati angajati are nevoie departamentul pentru a fi valid? ";
                        cin>>nr_angajat;
                        for(int i=0; i<gest[nr_gestionar-1].nr_comp_get(); i++)
                        {
                            for(int j=0; j<gest[nr_gestionar-1].comp_get(i).nr_dep_get(); j++)
                            {
                                if (gest[nr_gestionar-1].comp_get(i).dep_get(j).counter_ang_dep()>nr_angajat)
                                {
                                    cout<<"Compania "<<gest[nr_gestionar-1].comp_get(i).nume_companie_get()<<" are departamentul: "<<gest[nr_gestionar-1].comp_get(i).dep_get(j).nume_departament_get()<<" care contine mai multi angajati de "<<nr_angajat<<" ."<<endl;
                                }
                            }
                            cout<<"______________________________________________"<<endl;
                        }
                    }
                    else
                        throw 1;
                }
                catch (int x)
                {
                    cout<<"Gestionarul ales nu exista!"<<endl;
                    cout<<"Te rog alege un nr intre 0 si "<<nr_gest+1<<" ."<<endl;
                }
            }

            if (opt==7)
            {
                system("cls");
                string optiune, alegere;
                int nr_companie, nr_departament, nr_manager, nr_gestionar;
                cout<<"In ce gestionar doresti sa lucrezi? ";
                cin>>nr_gestionar;
                try
                {
                    if((nr_gestionar>0)&&(nr_gestionar<=nr_gest))
                    {
                        cout<<"Ce doresti sa modifici dintre Companie, Departament, Angajat? ";
                        cin>>optiune;
                        cout<<endl<<"______________________________________________"<<endl;
                        if(optiune=="Companie")
                        {
                            cout<<"Cum modifici lista de companii? (Adaugare / Stergere)? ";
                            cin>>alegere;
                            if (alegere=="Adaugare")
                            {
                                system("cls");
                                gest[nr_gestionar-1].adaugare_comp();
                            }
                            else if(alegere=="Stergere")
                            {
                                system("cls");
                                gest[nr_gestionar-1].stergere_comp();
                            }
                        }
                        else if (optiune=="Departament")
                        {
                            cout<<"Din ce companie doresti sa modifici setul de departamente? ";
                            cin>>nr_companie;
                            cout<<"Cum modifici lista de departamente? (Adaugare / Stergere)? ";
                            cin>>alegere;
                            if (alegere=="Adaugare")
                            {
                                system("cls");
                                gest[nr_gestionar-1].comp_get(nr_companie-1).adaugare_dep();
                            }
                            else if(alegere=="Stergere")
                            {
                                system("cls");
                                gest[nr_gestionar-1].comp_get(nr_companie-1).stergere_dep();
                            }
                        }
                        else if (optiune=="Angajat")
                        {
                            cout<<"Din ce companie doresti sa modifici lista de angajatii? ";
                            cin>>nr_companie;
                            cout<<"Din ce departament doresti sa modifici setul angajatii? ";
                            cin>>nr_departament;
                            cout<<"Modificarile aduse vor viza angajatii ai carui manager? ";
                            cin>>nr_manager;
                            cout<<"Ce modificare doresti (Adaugare / Stergere)? ";
                            cin>>alegere;
                            if (alegere=="Adaugare")
                            {
                                system("cls");
                                gest[nr_gestionar-1].comp_get(nr_companie-1).dep_get(nr_departament-1).man_get(nr_manager-1).adaugare_ang();
                            }
                            else if(alegere=="Stergere")
                            {
                                system("cls");
                                gest[nr_gestionar-1].comp_get(nr_companie-1).dep_get(nr_departament-1).man_get(nr_manager-1).stergere_ang();
                            }
                        }
                    }
                    else
                        throw 1;
                }
                catch (int x)
                {
                    cout<<"Gestionarul ales nu exista!"<<endl;
                    cout<<"Te rog alege un nr intre 0 si "<<nr_gest+1<<" ."<<endl;
                }
            }
            if (opt==8)
            {
                int nr_gestionar;
                cout<<"In ce gestionar doresti sa lucrezi? ";
                cin>>nr_gestionar;
                try
                {
                    if((nr_gestionar>0)&&(nr_gestionar<=nr_gest))
                        gest[nr_gestionar-1].fuzionare();
                    else
                        throw 1;
                }
                catch (int exceptie)
                {
                    cout<<"Gestionarul ales nu exista!"<<endl;
                    cout<<"Te rog alege un nr intre 0 si "<<nr_gest+1<<" ."<<endl;
                }
            }

            if (opt==9)
            {
                system("cls");
                cout<<"Optiunea de Downcasting nu este posibila in cazul ierarhiei prezente."<<endl<<"______________________________________________"<<endl;
                string optiune;
                cout<<"Ce doresti sa incerci intre Dynamic cast sau Downcast? ";
                cin.get();
                getline(cin,optiune);
                try
                {
                    if(optiune=="Dynamic cast")
                    {
                        Angajat* a=new Manager;
                        Manager* b;
                        b=dynamic_cast<Manager*>(a);
                        cout<<"Tipul primului obiect Angajat* a este: "<<typeid(*a).name()<<endl<<"Tipul primului obiect dupa etichetare este: "<<typeid(a).name();
                        cout<<endl<<"Tipul celui de al doilea obiect Manager* b este: "<<typeid(*b).name()<<endl<<"Tipul obiectului 2 dupa dynamic cast este: "<<typeid(b).name()<<endl;

                    }
                    else if(optiune=="Downcast")
                    {
                        Angajat *a=new Manager;
                        cout<<"Tipul obiectului Angajat *a este: "<<typeid(*a).name()<<endl<<"Dupa etichetarea de downcast acesta se modifica in: "<<typeid(a).name()<<endl;
                    }
                    else
                        throw 1;
                }
                catch (int exceptie)
                {
                    cout<<"Varianta aleasa este invalida!"<<endl;
                }

            }
            if (opt==10)
            {
                system("cls");
                cout<<"O zi buna!";
                return 0;
            }
            if ((opt<1)||(opt>10))
            {
                system("cls");
                cout<<"Optiunea nu este valida, te rog alege un numar intre 1 si 10";
            }
            cout<<endl;
            system("pause");
            system("cls");
        }
    }
    else
    {
        system("cls");

        vector <HRManager <Companie_impozit>> gest;
        while (opt!=100)
        {
            meniu_principal();
            cout<<endl<<"Ce actiune doriti sa incercati (actiunea aleasa trebuie sa fie unul din numerele de ordine reprezentative de la 1 la 10)? "<<endl;
            cin>>opt;
            if(opt==1)
            {
                system("cls");
                cout<<"Cate gestionare doriti sa aveti? ";
                cin>>nr_gest;
                try
                {
                    if (nr_gest<1)
                        throw 'c';
                    else
                    {
                        gest.resize(nr_gest);
                        for(int i=0; i<nr_gest; i++)
                            cin>>gest[i];
                    }
                }
                catch (char c)
                {
                    cout<<"Numarul de gestionare nu poate fi mai mic de 1";
                    exit(EXIT_FAILURE);
                }
            }
            if (opt==2)
            {
                system("cls");
                if (nr_gest==0)
                    cout<<"Gestionarul tau nu a fost creat";
                else
                {
                    for(int i=0; i<nr_gest; i++)
                        cout<<gest[i];
                }
            }

            if (opt==3)
            {
                system("cls");
                int nr_departament,nr_companie, nr_gestionar;
                string varianta;
                cout<<"In ce gestionar doresti sa lucrezi? ";
                cin>>nr_gestionar;
                try
                {
                    if((nr_gestionar>0)&&(nr_gestionar<=nr_gest))
                    {
                        cout<<"Doresti sa aflii angajatii intregii companiei sau a unui departament din companie(Companie/Departament)? ";
                        cin>>varianta;
                        if(varianta=="Departament")
                        {
                            cout<<"Din ce companie face parte departamentul tau? ";
                            cin>>nr_companie;
                            cout<<"Al carei departament doresti sa ii aflii numarul de angajati? ";
                            cin>>nr_departament;
                            cout<<"Numarul de angajati ai departamentului "<<nr_departament<<" este: ";
                            cout<<gest[nr_gestionar-1].comp_get(nr_companie-1).dep_get_imp(nr_departament-1).counter_ang_dep();
                        }
                        else if(varianta=="Companie")
                        {
                            cout<<"A carei companii vrei sa aflii numarul total de angajati? ";
                            cin>>nr_companie;
                            cout<<"Numarul de angajati ai companiei "<<nr_companie<<" din gestionarul "<<nr_gestionar<<" este: ";
                            cout<<gest[nr_gestionar-1].comp_get(nr_companie-1).counter_ang_comp_imp();
                        }
                        else
                            throw 1;
                    }
                    else
                        throw 'c';
                }
                catch (char c)
                {
                    cout<<"Gestionarul ales nu exista!"<<endl;
                    cout<<"Te rog alege un nr intre 0 si "<<nr_gest+1<<" ."<<endl;
                }
                catch (int nr)
                {
                    cout<<"Varianta aleasa nu este valida";
                    exit(EXIT_FAILURE);
                }

            }

            if (opt==4)
            {
                system("cls");
                int nr_companie,nr_gestionar;
                cout<<"In ce gestionar doresti sa lucrezi? ";
                cin>>nr_gestionar;
                try
                {
                    if((nr_gestionar>0)&&(nr_gestionar<=nr_gest))
                    {
                        cout<<"A carei companii vrei sa aflii suma totala pe care o are alocata pentru salarii? ";
                        cin>>nr_companie;
                        cout<<"Suma totala alocata pentru salarii de compania "<<gest[nr_gestionar-1].comp_get(nr_companie-1).nume_companie_imp_get()<<" este: "<<gest[nr_gestionar-1].comp_get(nr_companie-1).salariu_total_comp_imp();
                    }
                    else
                        throw 1;
                }
                catch (int exceptie)
                {
                    cout<<"Gestionarul ales nu exista!"<<endl;
                    cout<<"Te rog alege un nr intre 0 si "<<nr_gest+1<<" ."<<endl;
                }
            }

            if (opt==5)
            {
                system("cls");
                int nr_companie,nr_gestionar;
                cout<<"In ce gestionar doresti sa lucrezi? ";
                cin>>nr_gestionar;
                try
                {
                    if((nr_gestionar>0)&&(nr_gestionar<=nr_gest))
                    {
                        cout<<"Al carei companii doresti sa ii aflii Managerii si subalternii acestuia? ";
                        cin>>nr_companie;
                        for(int i=0; i<gest[nr_gestionar-1].comp_get(nr_companie-1).nr_dep_imp_get(); i++)
                            gest[nr_gestionar-1].comp_get(nr_companie-1).lista_manageri_imp(i);
                    }
                    else
                        throw 1;
                }
                catch (int exceptie)
                {
                    cout<<"Gestionarul ales nu exista!"<<endl;
                    cout<<"Te rog alege un nr intre 0 si "<<nr_gest+1<<" ."<<endl;
                }
            }

            if (opt==6)
            {
                system("cls");
                int nr_angajat,nr_gestionar;
                cout<<"In ce gestionar doresti sa lucrezi? ";
                cin>>nr_gestionar;
                try
                {
                    if((nr_gestionar>0)&&(nr_gestionar<=nr_gest))
                    {
                        cout<<"De cati angajati are nevoie departamentul pentru a fi valid? ";
                        cin>>nr_angajat;
                        for(int i=0; i<gest[nr_gestionar-1].nr_comp_get(); i++)
                        {
                            for(int j=0; j<gest[nr_gestionar-1].comp_get(i).nr_dep_imp_get(); j++)
                            {
                                if (gest[nr_gestionar-1].comp_get(i).dep_get_imp(j).counter_ang_dep()>nr_angajat)
                                {
                                    cout<<"Compania "<<gest[nr_gestionar-1].comp_get(i).nume_companie_imp_get()<<" are departamentul: "<<gest[nr_gestionar-1].comp_get(i).dep_get_imp(j).nume_departament_get()<<" care contine mai multi angajati de "<<nr_angajat<<" ."<<endl;
                                }
                            }
                            cout<<"______________________________________________"<<endl;
                        }
                    }
                    throw 1;
                }
                catch (int exceptie)
                {
                    cout<<"Gestionarul ales nu exista!"<<endl;
                    cout<<"Te rog alege un nr intre 0 si "<<nr_gest+1<<" ."<<endl;
                }
            }

            if (opt==7)
            {
                try
                {
                    system("cls");
                    string optiune, alegere;
                    int nr_companie, nr_departament, nr_manager, nr_gestionar;
                    cout<<"In ce gestionar doresti sa lucrezi? ";
                    cin>>nr_gestionar;
                    cout<<"Ce doresti sa modifici dintre Companie, Departament, Angajat? ";
                    cin>>optiune;
                    cout<<endl<<"______________________________________________"<<endl;
                    if(optiune=="Companie")
                    {
                        cout<<"Cum modifici lista de companii? (Adaugare / Stergere)? ";
                        cin>>alegere;
                        if (alegere=="Adaugare")
                        {
                            system("cls");
                            gest[nr_gestionar-1].adaugare_comp();
                        }
                        else if(alegere=="Stergere")
                        {
                            system("cls");
                            gest[nr_gestionar-1].stergere_comp();
                        }
                    }
                    else if (optiune=="Departament")
                    {
                        cout<<"Din ce companie doresti sa modifici setul de departamente? ";
                        cin>>nr_companie;
                        cout<<"Cum modifici lista de departamente? (Adaugare / Stergere)? ";
                        cin>>alegere;
                        if (alegere=="Adaugare")
                        {
                            system("cls");
                            gest[nr_gestionar-1].comp_get(nr_companie-1).adaugare_dep_imp();
                        }
                        else if(alegere=="Stergere")
                        {
                            system("cls");
                            gest[nr_gestionar-1].comp_get(nr_companie-1).stergere_dep_imp();
                        }
                    }
                    else if (optiune=="Angajat")
                    {
                        cout<<"Din ce companie doresti sa modifici lista de angajatii? ";
                        cin>>nr_companie;
                        cout<<"Din ce departament doresti sa modifici setul angajatii? ";
                        cin>>nr_departament;
                        cout<<"Modificarile aduse vor viza angajatii ai carui manager? ";
                        cin>>nr_manager;
                        cout<<"Ce modificare doresti (Adaugare / Stergere)? ";
                        cin>>alegere;
                        if (alegere=="Adaugare")
                        {
                            system("cls");
                            gest[nr_gestionar-1].comp_get(nr_companie-1).dep_get_imp(nr_departament-1).man_get(nr_manager-1).adaugare_ang();
                        }
                        else if(alegere=="Stergere")
                        {
                            system("cls");
                            gest[nr_gestionar-1].comp_get(nr_companie-1).dep_get_imp(nr_departament-1).man_get(nr_manager-1).stergere_ang();
                        }
                    }
                    else
                        throw 1;
                }
                catch (int exceptie)
                {
                    cout<<"Varianta clasa aleasa nu exista!"<<endl<<"Te rugam alege una din urmatoarele Companie, Departament sau Angajat."<<endl;
                }
            }
            if (opt==8)
            {
                int nr_gestionar;
                cout<<"In ce gestionar doresti sa lucrezi? ";
                cin>>nr_gestionar;
                try
                {
                    if ((nr_gestionar>0)&&(nr_gestionar<=nr_gest))
                        gest[nr_gestionar-1].fuzionare();
                    else
                        throw 1;
                }
                catch (int exceptie)
                {
                    cout<<"Gestionarul ales nu exista!"<<endl;
                    cout<<"Te rog alege un nr intre 0 si "<<nr_gest+1<<" ."<<endl;
                }
            }
            if (opt==9)
            {
                system("cls");
                cout<<"Optiunea de Downcasting nu este posibila in cazul ierarhiei prezente."<<endl<<"______________________________________________"<<endl;
                string optiune;
                cout<<"Ce doresti sa incerci intre Dynamic cast sau Downcast? ";
                cin.get();
                getline(cin,optiune);
                try
                {
                    if(optiune=="Dynamic cast")
                    {
                        Angajat* a=new Manager;
                        Manager* b;
                        b=dynamic_cast<Manager*>(a);
                        cout<<"Tipul primului obiect Angajat* a este: "<<typeid(*a).name()<<endl<<"Tipul primului obiect dupa etichetare este: "<<typeid(a).name();
                        cout<<endl<<"Tipul celui de al doilea obiect Manager* b este: "<<typeid(*b).name()<<endl<<"Tipul obiectului 2 dupa dynamic cast este: "<<typeid(b).name()<<endl;
                    }
                    else if(optiune=="Upcast")
                    {
                        Angajat *a=new Manager;
                        cout<<"Tipul obiectului Angajat *a este: "<<typeid(*a).name()<<endl<<"Dupa etichetarea de upcast acesta se modifica in: "<<typeid(a).name()<<endl;
                    }
                    else
                        throw 1;
                }
                catch (int exceptie)
                {
                    cout<<"Varianta aleasa este invalida!"<<endl;
                }

            }
            if (opt==10)
            {
                system("cls");
                cout<<"O zi buna!";
                return 0;
            }
            if ((opt<1)||(opt>10))
            {
                system("cls");
                cout<<"Optiunea nu este valida, te rog alege un numar intre 1 si 10";
            }
            cout<<endl;
            system("pause");
            system("cls");
        }
    }

}

int main()
{
    meniu();
    return 0;
}
