#include <iostream>
#include <algorithm>

using namespace std;

// INDEKSIRANJE POCINJE OD JEDINICE //

class ArrayList {
    int brojClanova;
    double *niz;
    void provjeraIspravnosti (int indeks) {
        if (indeks < 0 || indeks > brojClanova)
            throw::range_error("Pogresan indeks elementa!");
    }
    template <typename IterTip>
    friend int brojNeparnih (IterTip p1, IterTip p2); // DA SE NE BI MOGLE POZVATI IZ OSTATKA PROGRAMA //
    template <typename IterTip>
    friend int brojParnih(IterTip p1, IterTip p2);
    template <typename IterTip>
   friend void zamjeniParne (IterTip p1, IterTip p2, int vrijednost);
   template <typename IterTip>
   friend void IzbrojiParne (IterTip p1, IterTip p2, int &brParnih);
   template <typename IterTip, typename IterTip2>
   friend void IzbaciNeParne(IterTip p1, IterTip p2, IterTip2 q1, IterTip2 q2);
public:
   explicit ArrayList (int brClanova);
    ~ArrayList () { delete []niz;}
    ArrayList (const ArrayList &b);
    ArrayList &operator= (const ArrayList &b);
    ArrayList (ArrayList &&b);
    ArrayList (initializer_list<double> lista); // INICIJALIZACIJA PUTEM ZAGRADA //
    ArrayList &pomnoziNiz (int broj);
    ArrayList &prosiriNiz (int novaDimenzija);
    void Ispisi () const;
    ArrayList &dodajClan (int vrijednost);
    ArrayList &dodajIspred (int vrijednost);
    ArrayList &ukloniNeParne ();
    ArrayList &ukloniParne();
    ArrayList &popuniBrojem (int broj);
    ArrayList &sortirajUnazad () {sort(dajPocetak(), dajKraj(), [](int a, int b) {return b < a;}); return *this;};
    ArrayList &sortirajNiz () { sort(this->dajPocetak(), this->dajKraj()); return *this;}; // NUDI FLEKSIBILNOST KLASI, MOZE SE PISATI niz.sortiraj().Ispisi(); //
    void brParnih ();
    void brNeparnih ();
    ArrayList &promjeniNeparne (int vrijednost);
    ArrayList &promjeniParne (int vrijednost);
    ArrayList &postaviDimenziju (int indeks, int vrijednost); // MOGUC LANCANI POZIV METODE //
    double dajElement (int indeks) const; // POZIVA SE SAMO NA KONSTANTNIM OBJEKTIMA //
    double &dajElement (int indeks); // MOGUCE PROMJENITI VRIJEDNOST //
    void ispisiNajveci ();
    void ispisiNajmanji ();
    double *dajPocetak () { return niz; };
    double *dajKraj () { return niz+brojClanova;};
    double dajVelicinu () const { return brojClanova;};
    void velicinaNiza () const { cout << "(" <<brojClanova <<")";};
    void ispisiElement(int element) {provjeraIspravnosti(element); cout << "(" <<niz[element-1] << ")"; cout <<endl;}
};

template <typename Tip>
bool dalJeParan (Tip broj) {
return ((int)broj%2==0);
}

template <typename IterTip>
int brojParnih (IterTip pocetak, IterTip kraj) {
        int brojac(0);
    while (pocetak != kraj) {
        if (dalJeParan(*pocetak))
            brojac++;
    pocetak++;
    }
return brojac;
}

template <typename Tip>
bool dalJeNeparan (Tip broj) {
return ((int) broj % 2 != 0);
}

template <typename IterTip>
int brojNeparnih(IterTip p1, IterTip p2) {
    int brojac(0);
    while (p1 != p2) {
        if (dalJeNeparan(*p1))
         brojac++;
    p1++;
    }
return brojac;
}


template <typename IterTip>
void izbrojiParne(IterTip p1, IterTip p2, int &brojac) {
    brojac = 0;
    while (p1 != p2) {
        if (dalJeParan(*p1))
            brojac++;
    p1++;
    }
}

template <typename IterTip, typename IterTip2>
void izbaciParne(IterTip p1, IterTip p2, IterTip2 q1, IterTip2 q2) {
    while (p1 != p2) {
        if (!dalJeParan(*p1)) {
            *q1 = *p1;
            q1++;
        }
    p1++;
    }
}

template <typename IterTip, typename IterTip2>
void izbaciNeParne (IterTip p1, IterTip p2, IterTip2 q1, IterTip2 q2) {
    while (p1 != p2) {
        if (dalJeParan(*p1)) {
            *q1 = *p1;
            q1++;
        }
    p1++;
    }
}

ArrayList& ArrayList::ukloniNeParne() {
    int noviBroj(brojParnih(dajPocetak(), dajKraj()));
    try {
    double *noviNiz(new double[noviBroj]);
    fill(noviNiz, noviNiz+noviBroj, 0);
    izbaciNeParne(dajPocetak(), dajKraj(), noviNiz, noviNiz+noviBroj);
    delete [] niz; // DAL JE POTREBNA OVA LINIJA KODA, KADA BUDES CITAO ZASTANI PA POGLEDAJ AKO NIJE PROBLEM //
    niz = noviNiz; brojClanova = noviBroj;
    }
    catch(...) {
    cout << "Problem sa alokacijom!";
    }
}

ArrayList& ArrayList::ukloniParne() {
        int noviBroj(brojNeparnih(dajPocetak(), dajKraj()));
        try {
    double *noviNiz(new double[noviBroj]);
    fill(noviNiz, noviNiz+noviBroj, 0);
    izbaciParne(dajPocetak(), dajKraj(), noviNiz, noviNiz+noviBroj);
    delete [] niz; // ISTO PITANJE //
     niz = noviNiz; brojClanova = noviBroj;
    }
    catch(...) {
        cout << "Greska u alokaciji!";
    }
}

template<typename IterTip>
void zamjeniParne(IterTip p1, IterTip p2, int vrijednost) {
    while (p1 != p2) {
        if (dalJeParan(*p1))
            *p1 = vrijednost;
    p1++;
    }
}

template <typename IterTip>
void ZamijeniNeParne(IterTip p1, IterTip p2, int vrijednost) {
    while (p1 != p2) {
        if(dalJeNeparan(*p1))
            *p1 = vrijednost;
    p1++;
    }
}

void ArrayList::brParnih() {
cout << "[" << brojParnih(this->dajPocetak(), this->dajKraj()) << "]"; cout<<endl;
}

void ArrayList::brNeparnih() {
cout << "[" << brojNeparnih(this->dajPocetak(), this->dajKraj()) << "]"; cout <<endl;
}

void ArrayList::ispisiNajmanji() {
    double najmanji(niz[0]);
    for (int i=1; i<brojClanova; i++) {
        if (niz[i] < najmanji)
            najmanji = niz[i];
    }
    cout << najmanji;
cout <<endl;
}

void ArrayList::ispisiNajveci() {
    double najveci(niz[0]);
    for (int i=0; i<brojClanova; i++) {
        if (niz[i] > najveci)
            najveci = niz[i];
    }
    cout << najveci;
cout <<endl;
}


ArrayList& ArrayList::promjeniParne(int vr) {
zamjeniParne(this->dajPocetak(), this->dajKraj(), vr);
return *this;
}

ArrayList& ArrayList::promjeniNeparne(int vr) {
ZamijeniNeParne(dajPocetak(), dajKraj(), vr);
return *this;
}

ArrayList& ArrayList::popuniBrojem(int vrijednost) {
    for (int i=0; i<brojClanova; i++)
        niz[i] = vrijednost;
return *this;
}

ArrayList &ArrayList::pomnoziNiz(int vrijednost) {
    for (int i=0; i<this->dajVelicinu(); i++)
        niz[i] *= vrijednost;
return *this;
}

ArrayList& ArrayList::dodajClan(int vrijednost) {
    double *novi(new double[brojClanova+1]);
    fill(novi, novi+brojClanova+1, 0); // DA NE BI DOBILI NEDEFINISANE VRIJEDNOSTI //
    copy(niz, niz+brojClanova, novi);
    niz = novi; brojClanova +=1;
    postaviDimenziju(brojClanova, vrijednost);
return *this;
}

ArrayList &ArrayList::dodajIspred(int vrijednost) {
    double *novi(new double[brojClanova+1]);
    fill(novi, novi+brojClanova+1, 0);
    copy(niz, niz+brojClanova, novi+1);
    niz = novi; brojClanova+=1;
    postaviDimenziju(1, vrijednost);
return *this;
}

ArrayList::ArrayList(const ArrayList &b) : brojClanova(b.brojClanova), niz(new double[b.brojClanova]){
    copy(b.niz, b.niz+b.brojClanova, niz); // MOGUCE I SA PETLJOM, OVO JE SIGURNIJI NACIN //
}

ArrayList &ArrayList::operator=(const ArrayList &b) {
    if (b.brojClanova > brojClanova || b.brojClanova < brojClanova) {
        double *novi(new double[b.brojClanova]);
        delete []niz; niz = novi;
    }
    brojClanova = b.brojClanova;
    copy(b.niz, b.niz+b.brojClanova, niz);
return *this;
}

ArrayList::ArrayList(ArrayList &&b) : brojClanova(b.brojClanova), niz(b.niz) { // MOVE SEMANTIKA, PRIMA SE R-VALUE VR(Privremeni objekt) //
    b.niz = nullptr;
}

ArrayList::ArrayList(int brClanova): brojClanova(brClanova), niz(new double[brClanova]) {
    fill(niz, niz+brClanova, 0);
}

ArrayList::ArrayList(initializer_list<double> lista): brojClanova(lista.size()), niz(new double[lista.size()]) {
    copy(lista.begin(), lista.end(), niz);
}

void ArrayList::Ispisi() const {
        cout << "[";
    for (int i=0; i<brojClanova; i++) {
        cout << niz[i];
    if (i != brojClanova - 1)
        cout << ",";
    }
    cout << "]";
cout <<endl;
}

ArrayList& ArrayList::prosiriNiz(int noviBrojClanova) {
    if (noviBrojClanova <= brojClanova)
        throw::domain_error("Unesena dimenzija je manja ili jednaka prethodnoj!");
    else {
        double *noviNiz(new double[noviBrojClanova]);
        copy(niz, niz+brojClanova, noviNiz);
        fill(noviNiz+brojClanova, noviNiz+noviBrojClanova, 0);
        delete [] niz;
        niz = noviNiz;
        }
    brojClanova = noviBrojClanova;
return *this;
}

ArrayList& ArrayList::postaviDimenziju(int indeks, int vrijednost) {
    try {
    provjeraIspravnosti(indeks);
    }
    catch(...) {
    cout << "Pogresan indeks!" <<endl;
    }
    niz[indeks-1] = vrijednost;
return *this;
}

double ArrayList::dajElement(int indeks) const {
return niz[indeks-1];
}

double& ArrayList::dajElement(int indeks) {
return niz[indeks-1];
}

int main() {
ArrayList niz{3,1,9,4,5};
niz.Ispisi();
niz.dodajClan(3);
niz.dodajIspred(9).Ispisi();
niz.ispisiNajveci();
niz.promjeniParne(0).promjeniNeparne(-1).Ispisi();
    return 0;
}
