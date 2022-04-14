#include <iostream>
#include <string>
#include <exception>
#include <vector>
#include <memory>
using namespace std;

class InvalidCVV : public exception{
public:
    InvalidCVV() = default;
    const char *what() const noexcept override{
        return "Invalid CVV!\n";
    }
};
class InvalidDate : public exception{
public:
    InvalidDate() = default;
    const char *what() const noexcept override{
        return "Invalid Date!\n";
    }
};
class InvalidCredit : public exception{
public:
    InvalidCredit() = default;
    const char *what() const noexcept override{
        return "Invalid Credit!\n";
    }
};
class InsuficientFunds : public exception{
public:
    InsuficientFunds() = default;
    const char *what() const noexcept override{
        return "Insuficient Funds!\n";
    }
};
class MaximumCreditReached : public exception{
public:
    MaximumCreditReached() = default;
    const char *what() const noexcept override{
        return "Maximum Credit Reached!\n";
    }
};
enum class Card_creditType{
    Card_standard,
    Card_premium
};

class Card_credit
{
    string nr_card;
    string nume_detinator;
    string data_expirare;

    int CVV;
    double credit;
public:
    Card_credit() : nr_card(), nume_detinator(), data_expirare(), CVV(0), credit(0)
    {

    }

    Card_credit(string newcard, string newdet, string newexp, const int &newCVV, const double &newCredit) : nr_card(move(newcard)), nume_detinator(move(newdet)), data_expirare(move(newexp)), CVV(newCVV), credit(newCredit)
    {
        if(CVV < 0 || CVV > 999)
            throw InvalidCVV();
        if(data_expirare[2] != '/' || data_expirare[5] != '/' || data_expirare[6] < '0' || data_expirare[6] > '9'|| data_expirare[7] < '0' || data_expirare[7] > '9'|| data_expirare[3] < '0' || data_expirare[3] > '9'|| data_expirare[4] < '0' || data_expirare[4] > '9'|| data_expirare[0] < '0' || data_expirare[0] > '9'|| data_expirare[1] < '0' || data_expirare[1] > '9')
            throw InvalidDate();
        else
        {
            if(data_expirare[3]=='1' && data_expirare[4] > '2')
                throw InvalidDate();
            else
            if(data_expirare[3] != '1' && data_expirare[3] != '0')
                throw InvalidDate();

            if(data_expirare[0] > '3')
                throw InvalidDate();
            else
            if(data_expirare[0] == '3' && data_expirare[1] != '0')
                throw InvalidDate();
            //toate lunile din anul meu au 30 de zile
        if(credit < 0)
            throw InvalidCredit();
        }
    }
    Card_credit(const Card_credit& card): nr_card(card.nr_card), nume_detinator(card.nume_detinator), data_expirare(card.data_expirare), CVV(card.CVV), credit(card.credit)
    {

    }
    virtual ~Card_credit() = default; // intotdeauna destr virtual in clasele din care se mosteneste

    virtual Card_creditType getType() const = 0;

    string getCard() const
    {
        return nr_card;
    }
    void setCard(string newcard)
    {
        nr_card = move(newcard);
    }

    string getDet() const
    {
        return nume_detinator;
    }
    void setDet(string newdet)
    {
        nume_detinator = move(newdet);
    }

    string getExp() const
    {
        return data_expirare;
    }
    void setExp(string newexp)
    {
        data_expirare = move(newexp);
    }

    int getCVV() const
    {
        return CVV;
    }
    void setCVV(const int &newCVV)
    {
        CVV = newCVV;
    }

    double getcredit() const
    {
        return credit;
    }
    void setCredit(const double &newCredit)
    {
        credit = newCredit;
    }

    virtual void Withdraw(const double &creditextras)
    {
        if(getType() == Card_creditType::Card_standard)
        {
            if(credit - creditextras > -10000)
                credit = credit - creditextras;
            else throw InsuficientFunds();
        }
        else
        {
            if(credit - creditextras > -50000)
                credit = credit - creditextras;
            else throw InsuficientFunds();
        }
    }

    void AddMoney(const double &creditadaugat)
    {
        if(getType() == Card_creditType::Card_standard)
        {
            if(credit + creditadaugat < 10000)
                credit = credit + creditadaugat;
            else throw MaximumCreditReached();
        }
        else
        {
            if(credit + creditadaugat < 50000)
                credit = credit + creditadaugat;
            else throw MaximumCreditReached();
        }
    }
    Card_credit &operator=(const Card_credit &rhs) = default;

    virtual string showstatus() const = 0; //metoda virtuala pura

    virtual void afisare(ostream &os) const
    {
        os << showstatus() << " Card user: " << nume_detinator << ". Your card number is " << nr_card <<" and it will expire on " << data_expirare << ". Your CVV is ";
        if(CVV < 10) cout << "00" << CVV;
        else
        if(CVV < 100) cout << "0" << CVV;
        else cout << CVV;
        if(credit < 0)
            os << ". You owe " << -credit << " Dogecoin.";
        else
            os << ". You have " << credit <<" Dogecoin.";
    }

    virtual void citire(istream &is)
    {
        cout << "Insert your name: ";
        getline(is>>ws, nume_detinator);
        cout << "\nInsert a card number: ";
        is >> nr_card;
        cout << "\nInsert your expiration date(Format: dd/mm/yy): ";
        is >> data_expirare;
        if(data_expirare[2] != '/' || data_expirare[5] != '/' || data_expirare[6] < '0' || data_expirare[6] > '9'|| data_expirare[7] < '0' || data_expirare[7] > '9'|| data_expirare[3] < '0' || data_expirare[3] > '9'|| data_expirare[4] < '0' || data_expirare[4] > '9'|| data_expirare[0] < '0' || data_expirare[0] > '9'|| data_expirare[1] < '0' || data_expirare[1] > '9')
            throw InvalidDate();
        else
        {
            if(data_expirare[3]=='1' && data_expirare[4] > '2')
                throw InvalidDate();
            else
            if(data_expirare[3] != '1' && data_expirare[3] != '0')
                throw InvalidDate();

            if(data_expirare[0] > '3')
                throw InvalidDate();
            else
            if(data_expirare[0] == '3' && data_expirare[1] != '0')
                throw InvalidDate();
            //toate lunile din anul meu au 30 de zile
        }
        cout << "\nInsert your CVV: ";
        is >> CVV;
        if(CVV < 0 || CVV > 999)
            throw InvalidCVV();
        cout << "\nInsert your credit: ";
        is >> credit;
        if(credit < 0)
            throw InvalidCredit();
    }
    friend istream &operator>>(istream &is, Card_credit &card)
    {
        card.citire(is);
        return is;
    }
};

ostream& operator<<(ostream &os, const Card_credit *card)
{
    card->afisare(os);
    return os;
}

class Card_standard : public Card_credit
{
    int limitaExtragere;
    double comisionDepasireLimita;
public:
    Card_standard(string newcard, string newdet, string newexp, const int &newCVV, const double &newCredit, const int &newlimitaExtragere, const double &newcomisionDepasireLimita)
            : Card_credit(move(newcard), move(newdet), move(newexp), newCVV, newCredit), limitaExtragere(newlimitaExtragere), comisionDepasireLimita(newcomisionDepasireLimita)
    {

    }
    Card_creditType getType() const override{
        return Card_creditType::Card_standard;
    }

    int getlimitaExtragere() const
    {
        return limitaExtragere;
    }
    void setlimitaExtragere(const int &newlimitaExtragere)
    {
        limitaExtragere = newlimitaExtragere;
    }

    double getcomisionDepasireLimita() const
    {
        return comisionDepasireLimita;
    }
    void setcomisionDepasireLimita(const double &newcomisionDepasireLimita)
    {
        comisionDepasireLimita = newcomisionDepasireLimita;
    }

    string showstatus() const override
    {
        return "Welcome to Floor Street!(Standard Cards)";
    }

    void afisare(ostream &os) const override
    {
        Card_credit::afisare(os);
        cout << " You have a debt limit of " << limitaExtragere <<". Your commission rate is " << comisionDepasireLimita <<".\n";
    }

    friend ostream &operator<<(ostream &os, const Card_standard &card)
    {
        card.afisare(os);
        return os;
    }

    void citire(istream &is) override
    {
        Card_credit::citire(is);
        cout << "\nInsert your withdraw limit: ";
        is >> limitaExtragere;
        cout << "\nInsert withdraw commission: ";
        is >> comisionDepasireLimita;
        cout << "\n";
    }

    friend istream  &operator>>(istream &is, Card_standard &card)
    {
        card.citire(is);
        return is;
    }

    void Withdraw(const double &creditextras) override
    {
        Card_credit::Withdraw(creditextras);
        if(getcredit() < limitaExtragere)
        {
            double datorie = getcredit() - creditextras * comisionDepasireLimita;
            double diferenta = getcredit() - limitaExtragere;
            diferenta = diferenta * comisionDepasireLimita + getcredit();
            if(datorie < diferenta)
                setCredit(diferenta);
            else
                setCredit(datorie);
        }
    }

    Card_standard() : Card_credit(), limitaExtragere(0), comisionDepasireLimita(0)
    {

    }
    Card_standard(const Card_standard &card) : Card_credit(card.getCard(), card.getDet(), card.getExp(), card.getCVV(), card.getcredit()), limitaExtragere(card.limitaExtragere), comisionDepasireLimita(card.comisionDepasireLimita){}

    Card_standard &operator=(const Card_standard &rhs)
    {
        if (this != &rhs)
        {
            Card_credit::operator=(rhs);
            limitaExtragere = rhs.limitaExtragere;
            comisionDepasireLimita = rhs.comisionDepasireLimita;
        }
        return *this;
    }
};
class Card_premium : public Card_credit
{
    double cashback;
public:
    Card_premium(string newcard, string newdet, string newexp, const int &newCVV, const double &newCredit, const double &newcashback)
            : Card_credit(move(newcard), move(newdet), move(newexp), newCVV, newCredit), cashback(newcashback)
    {

    }
    Card_creditType getType() const override{
        return Card_creditType::Card_premium;
    }
    double getcashback() const
    {
        return cashback;
    }
    void setcashback(const double &newcashback)
    {
        cashback = newcashback;
    }
    string showstatus() const override
    {
        return "Welcome to Wall Street!(Premium Cards)";
    }
    void afisare(ostream &os) const override
    {
        Card_credit::afisare(os);
        cout << " You get a cashback of " << cashback << " on every purchase.\n";
    }

    friend ostream &operator<<(ostream &os, const Card_premium &card)
    {
        card.afisare(os);
        return os;
    }

    void citire(istream &is) override
    {
        Card_credit::citire(is);
        cout << "\nInsert your cashback: ";
        is >> cashback;
        cout << "\n";
    }

    friend istream  &operator>>(istream &is, Card_premium &card)
    {
        card.citire(is);
        return is;
    }

    void Withdraw(const double &creditextras) override
    {
        Card_credit::Withdraw(creditextras);
        double backinthepocket = getcredit() + creditextras * cashback;
        setCredit(backinthepocket);
    }

    Card_premium() : Card_credit(), cashback(0)
    {

    }
    Card_premium(const Card_premium &card) : Card_credit(card.getCard(), card.getDet(), card.getExp(), card.getCVV(), card.getcredit()), cashback(card.cashback){}

    Card_premium &operator=(const Card_premium &rhs)
    {
        if (this != &rhs)
        {
            Card_credit::operator=(rhs);
            cashback = rhs.cashback;
        }
        return *this;
    }
};

class Bank{
    static vector<shared_ptr<Card_credit>> cards;
    Bank() = delete;
public:
    static const vector<shared_ptr<Card_credit>> &getCards()
    {
        return cards;
    }
    static void addClient(const shared_ptr<Card_credit> &card)
    {
        cards.push_back(card);
    }
    static void printAllClients() {
        for (auto &card: cards)
            cout << card->getDet() << "\n";
    }
    static void printClient(const string& s)
    {
        for (auto &card: cards)
            if(card->getCard() == s)
            {
                cout << card;
                break;
            }
    }
    static void printPremiumClients()
    {
        for (auto &card: cards)
            if(card->getType() == Card_creditType::Card_premium)
            {
                auto cardpm = dynamic_pointer_cast<Card_premium>(card);
                cout <<"Client Name: "<<cardpm->getDet() <<" Client Cashback: "<< cardpm->getcashback() << "\n";
            }
    }
    static void printStandardClients()
    {
        for (auto &card: cards)
            if(card->getType() == Card_creditType::Card_standard)
            {
                auto cardst = dynamic_pointer_cast<Card_standard>(card);
                cout <<"Client Name: "<< cardst->getDet() <<" Client withdraw limit: "<<cardst->getlimitaExtragere() << " Client commission: " << cardst->getcomisionDepasireLimita() << "\n";
            }
    }
    static void withdrawClient(const string& s, const double &sum)
    {
        for (auto &card: cards)
            if(card->getCard() == s)
            {
                card->Withdraw(sum);
                break;
            }
    }
    static void addMoney(const string& s, const double &sum)
    {
        for (auto &card: cards)
            if(card->getCard() == s)
            {
                card->AddMoney(sum);
                break;
            }
    }
};

vector <shared_ptr<Card_credit>> Bank::cards;

int main()
{
    string s;
    bool ok = true, ok2 = true, ok3 = true;
    double money;
    string comanda;
    cout << "Welcome to the Bank! What would you like to do? If you need help, please type HELP. \n";
    while(ok && ok2)
    {
        getline(cin>>ws, comanda);
        if(comanda == "HELP")
        {
            ok3 = true;
            cout << "The following actions are possible:\n";
            cout << "ADD A CARD. The previous command will make a new card!\n";
            cout << "WITHDRAW. The previous command will withdraw money from a certain card!\n";
            cout << "ADD MONEY. The previous command will add money to a certain card!\n";
            cout << "CARD INFO. The previous command will show all the card details!\n";
            cout << "CLIENTS. The previous command will show all clients!\n";
            cout << "PCLIENTS. The previous command will show all premium clients and their cashbacks!\n";
            cout << "SCLIENTS. The previous command will show all standard clients and their withdraw limits and commissions!\n";
            cout << "EXIT. The previous command will close the menu!\n";
        }else
        if(comanda == "ADD A CARD")
        {
            ok3 = true;
            cout << "Select a card type: PREMIUM/ STANDARD\n";
            cin >> comanda;
            if(comanda == "PREMIUM")
            {
                ok3 = true;
                Card_premium card;
                try
                {
                    cin >> card;
                    auto add = make_shared<Card_premium>(card);
                    Bank::addClient(add);
                }
                catch (const InvalidCVV &e)
                {
                    cout<< e.what();
                }
                catch (const InvalidDate &e)
                {
                    cout << e.what();
                }
                catch (const InvalidCredit &e)
                {
                    cout << e.what();
                }
            }
            else
            if(comanda == "STANDARD")
            {
                ok3 = true;
                Card_standard card;
                try
                {
                    cin >> card;
                    auto add = make_shared<Card_standard>(card);
                    Bank::addClient(add);
                }
                catch (const InvalidCVV &e)
                {
                    cout << e.what();
                }
                catch (const InvalidDate &e)
                {
                    cout << e.what();
                }
            }
        }
        else
        if (comanda == "CARD INFO")
        {
            ok3 = true;
            cout << "Insert your card number: ";
            cin >> s;
            Bank::printClient(s);
        }
        else
        if (comanda == "WITHDRAW")
        {
            ok3 = true;
            cout << "\nInsert your card number: ";
            cin >> s;
            cout << "\nInsert the amount you want to extract: ";
            cin >> money;
            try
            {
                Bank::withdrawClient(s,money);
            }
            catch (const InsuficientFunds &e)
            {
                cout << e.what();
            }
        }
        else
            if(comanda == "ADD MONEY")
            {
                ok3 = true;
                cout << "\nInsert your card number: ";
                cin >> s;
                cout << "\nInsert the amount you want to add: ";
                cin >> money;
                try
                {
                    Bank::addMoney(s,money);
                }
                catch (const MaximumCreditReached &e)
                {
                    cout << e.what();
                }
            }
            else
        if(comanda == "CLIENTS")
        {
            ok3 = true;
            Bank::printAllClients();
        }
        else
        if(comanda == "PCLIENTS")
        {
            ok3 = true;
            Bank::printPremiumClients();
        }
        else
        if(comanda == "SCLIENTS")
        {
            ok3 = true;
            Bank::printStandardClients();
        }
        else
        if(comanda == "EXIT")
            ok = false;
        else
        {
            if(ok3)
            {
                cout<<"Unknown command. One more Unknown command will result in loggin out!\n";
                ok3 = false;
            }
            else
                ok2 = false;
        }

        if(comanda == "EXIT")
            ok = false;
        else
        if(ok3||ok2)
            cout << "What else can we do for you?\n";
    }
    cout << "Have a nice day!\n";
    return 0;
}