#include <iostream>
#include <list>
#include <cstring>
using namespace std;
class Multime
{
private:
    list<int> lista;
    int nr_el;
public:
    void set_nr(int a)
    {
        nr_el=a;
    }
    int get_nr() const
    {
        return nr_el;
    }
    void set_lst(const list<int> &lista_)
    {
        lista.clear();
        for (auto const &i: lista_)
        {
            lista.push_back(i);
        }
    }
    list<int> get_lst() const
    {
        return lista;
    }
    Multime()
    {
        nr_el=0;
    }
    Multime(int nr_elem, const list<int> &lista_)
    {
        nr_el=nr_elem;
        for (auto const &i: lista_)
        {
            lista.push_back(i);
        }
    }
    Multime(const Multime &mult)
    {
        nr_el=mult.nr_el;
        for (auto const &i: mult.lista)
        {
            lista.push_back(i);
        }
    }
    Multime& operator=(const Multime &rhs)
    {
        set_lst(rhs.lista);
        this->nr_el=rhs.nr_el;

        return *this;
    }
    ~Multime()
    {
        lista.clear();
    }
    friend istream &operator>>(istream &input, Multime &m);
    friend ostream &operator<<(ostream &output,const Multime &m);

    void unicitate()
    {
        lista.sort();
        lista.unique();
        nr_el=lista.size();
    }

    Multime operator+(const Multime &m) const
    {
        Multime c(0,{});
        for (auto const &i: m.lista)
        {
            c.lista.push_back(i);
        }
        for (auto const &j: this->lista)
        {
            c.lista.push_back(j);
        }
        c.unicitate();
        return c;
    }

    Multime operator-(const Multime &m) const
    {
        Multime c(0,{});
        for (auto const &i: this->lista)
        {
            bool avem = false;
            for (auto const &j: m.lista)
            {
                if(i==j)
                    avem = true;
            }
            if(avem == false)
                c.lista.push_back(i);
        }
        c.unicitate();
        return c;
    }
    Multime operator*(const Multime &m) const
    {
        Multime c(0,{});
        for (auto const &i: this->lista)
        {
            for (auto const &j: m.lista)
            {
                if(i==j)
                {
                    c.lista.push_back(i);
                    break;
                }
            }
        }
        c.unicitate();
        return c;
    }
};

istream &operator>>(istream &is, Multime &m)
{
    m.lista.clear();
    int nr_elem,elem;
    is>>nr_elem;
    m.set_nr(nr_elem);
    for(int i=0;i<nr_elem;i++)
    {
        is>>elem;
        m.lista.push_back(elem);
    }
    return is;
}
ostream &operator<<(ostream &os,const Multime &m)
{
    int nr_elem,ok=0;
    nr_elem=m.get_nr();
    os<<"Multimea: {";
    for (auto const &i: m.lista)
    {
        if(ok==0)
            ok=1;
        else
            os<<", ";
        os << i ;
    }
    os<<"} are "<<nr_elem<<" elemente.";
    return os;
}
int main()
{
    bool meniu=true;
    char help[20];
    while(meniu)
    {
        cout<<"Introduceti o comanda:(Pentru a vedea lista de instructiuni, introducenti comanda Help)"<<"\n";
        cin>>help;
        if(strcmp("Help",help)==0)
        {
            cout<<"Postibile comenzi:"<<"\n";
            cout<<"Multimizeaza: Introduceti numarul de elemente al unui vector si elementele acestuia, si se va afisa multimea formata din elementele vectorului"<<"\n";
            cout<<"Reuneste: Introduceti numarul de elemente si elementele a doi vectori, si se va afisa multimea formata din elementele care apar in oricare dintre vectori"<<"\n";
            cout<<"Intersecteaza: Introduceti numarul de elemente si elementele a doi vectori, si se va afisa multimea formata din elementele care apar in ambii vectori"<<"\n";
            cout<<"Scade: Introduceti numarul de elemente si elementele a doi vectori, si se va afisa multimea formata din elementele care apar doar in primul vector"<<"\n";
            cout<<"Exit: Opriti programul"<<"\n";
        }else
        if(strcmp("Multimizeaza",help)==0)
        {
            Multime m(0,{});
            cin>>m;
            m.unicitate();
            cout<<m<<"\n";
        }else
        if(strcmp("Reuneste",help)==0)
        {
            Multime m1(0,{}),m2(0,{});
            cin>>m1>>m2;
            m1=m1+m2;
            cout<<m1<<"\n";
        }else
        if(strcmp("Intersecteaza",help)==0)
        {
            Multime m1(0,{}),m2(0,{});
            cin>>m1>>m2;
            m1=m1*m2;
            cout<<m1<<"\n";
        }else
        if(strcmp("Scade",help)==0)
        {
            Multime m1(0,{}),m2(0,{});
            cin>>m1>>m2;
            m1=m1-m2;
            cout<<m1<<"\n";
        }else
        if(strcmp("Exit",help)==0)
        {
            meniu=false;
            cout<<"Programul a fost oprit";
        }else
        {
            cout<<"Comanda necunoscuta"<<"\n";
        }
    }
    return 0;
}