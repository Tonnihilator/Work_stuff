#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <memory>

using namespace std;
using std::swap;

enum cardValueList { Two = 2, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace };
enum cardSuitList { Hearts = 1, Diamonds, Clubs, Spades };
vector <string> enumeratorList = { "first", "second", "third", "fourth", "fifth", "sixth", "seventh", "eighth", "ninth", "tenth", "eleventh", "twelfth" };

class Card
{
    private:
        string getValue()
        {
            switch (cardValue)
            {
            case Two:
                return "2";
                break;
            case Three:
                return "3";
                break;
            case Four:
                return "4";
                break;
            case Five:
                return "5";
                break;
            case Six:
                return "6";
                break;
            case Seven:
                return "7";
                break;
            case Eight:
                return "8";
                break;
            case Nine:
                return "9";
                break;
            case Ten:
                return "10";
                break;
            case Jack:
                return "J";
                break;
            case Queen:
                return "Q";
                break;
            case King:
                return "K";
                break;
            case Ace:
                return "A";
                break;
            }
        }
        string getSuit()
        {
            switch (cardSuit)
            {
            case Hearts:
                return "H";
                break;
            case Diamonds:
                return "D";
                break;
            case Clubs:
                return "C";
                break;
            case Spades:
                return "S";
                break;
            }
        }

    public:
        cardValueList cardValue;
        cardSuitList cardSuit;
        bool cardState;

        Card(cardValueList _cardValue, cardSuitList _cardSuit, bool _cardState) : cardValue{ _cardValue }, cardSuit{ _cardSuit }, cardState{ _cardState } {}
        void flip()
        {
            cardState = !cardState;
        }
        friend ostream& operator<<(ostream& out, Card& card)
        {
            if (card.cardState)
            {
                if (card.getSuit() == "H")
                {
                    out << "\x1B[31m" << card.getValue() << card.getSuit() << "\033[0m";
                    return out;
                }
                else if (card.getSuit() == "D")
                {
                    out << "\x1B[94m" << card.getValue() << card.getSuit() << "\033[0m";
                    return out;
                }
                else if (card.getSuit() == "C")
                {
                    out << "\x1B[32m" << card.getValue() << card.getSuit() << "\033[0m";
                    return out;
                }
                else if (card.getSuit() == "S")
                {
                    out << "\x1B[36m" << card.getValue() << card.getSuit() << "\033[0m";
                    return out;
                }
            }
            else
            {
                out << "\x1B[90m" << "XX" << "\033[0m";
                return out;
            }
        }
};

int getCardValue(cardValueList cardValue)
{
    if (cardValue >= 2 && cardValue < 10)
        return cardValue;
    if (cardValue < 14)
        return 10;
    else
        return 11;
}

class Hand
{
    public:
        virtual void Add(cardValueList cardValue, cardSuitList cardSuit, bool cardState)
        {
            Card newCard(cardValue, cardSuit, cardState);
            hand.push_back(newCard);
            return;
        }
        void Clear()
        {
            hand.clear();
            return;
        }
        int getValue() const
        {
            int value = 0;
            for (int i = 0; i < hand.size(); i++)
            {
                value += getCardValue(hand[i].cardValue);
            }
            if (value > 21)
            {
                for (int i = 0; i < hand.size(); i++)
                {
                    if (hand[i].cardValue == 14)
                    {
                        value -= 10;
                    };
                }
            }
            return value;
        }

        vector <Card> hand;
    protected:
    };

    class GenericPlayer : virtual public Hand
    {
    public:
        GenericPlayer(string _name) : Hand(), name{ _name } {}
        virtual bool IsHitting() const = 0;
        virtual bool IsBoosted()
        {
            return (getValue() > 21);
        }
        virtual void Bust()
        {
            cout << "\x1B[91m" << name << " is busted!!" << "\033[0m" << endl;
        }
        string name;
    protected:
};

class Player : virtual public GenericPlayer
{
    public:
        Player(string _name) : GenericPlayer(_name) {}
        virtual bool IsHitting() const
        {
            string hitFlag = "";
            cout << "\x1B[95m" << "Does " << "\x1B[97m" << name << "\x1B[95m" << " want another card? (Y/N)" << "\033[0m" << endl;
            cin >> hitFlag;
            while (hitFlag != "Y" && hitFlag != "y" && hitFlag != "Y" && hitFlag != "n")
            {
                cout << "Incorrect input! Type 'Y' or 'N'!" << endl;
                cin >> hitFlag;
            }
            if (hitFlag == "Y" || hitFlag == "y")
                return true;
            else
                return false;
        }
        virtual void Win()
        {
            cout << "\x1B[92m" << "Player " << name << " Won!" << "\033[0m" << endl;
        }
        virtual void Lose()
        {
            cout << "\x1B[91m" << "Player " << name << " lost!" << "\033[0m" << endl;
        }
        virtual void Push()
        {
            cout << "\x1B[93m" << "Player " << name << " Played in a draw!" << "\033[0m" << endl;
        }
};

class House : virtual public GenericPlayer
{
    public:
        House(string _name = "House") : GenericPlayer(_name) {}
        virtual bool IsHitting() const
        {
            if (getValue() < 17)
                return true;
            else
                return false;
        }
        void FlipFirstCard()
        {
            hand[0].flip();
        }
        Card GetCardValue(int cardNum)
        {
            return hand[cardNum];
        }
};

class Deck : public Hand
{
    public:
        Deck()
        {
            Populate();
            srand(time(0));
            Shuffle();
        }

        template<typename Hand>
        void Deal(Hand& targetHand)
        {
            targetHand.Add(hand[0].cardValue, hand[0].cardSuit, hand[0].cardState);
            hand.erase(hand.begin());
        }

        void AdditionalCards(GenericPlayer& Player)
        {
            while (Player.IsHitting())
            {
                Deal(Player);
            }
        }
    private:
        void Populate()
        {
            for (int k = 0; k < 2; k++)
            {
                for (int i = 2; i < 15; i++)
                {
                    for (int j = 1; j < 5; j++)
                    {
                        Add((cardValueList)i, (cardSuitList)j, 1);
                    }
                }
            }
        }
        void Shuffle()
        {
            for (int i = 0; i < hand.size(); i++)
                swap(hand[i], hand[rand() % 52]);
        }
};

class Game
{
    public:
        Game(vector <string> vectorOfNames)
        {
            for (int i = 0; i < vectorOfNames.size(); i++)
            {
                vectorOfPlayers.push_back(vectorOfNames[i]);
            }

            string hitFlag = "y";
            while (hitFlag == "Y" || hitFlag == "y")
            {
                houseHand.Clear();
                for (int i = 0; i < vectorOfPlayers.size(); i++)
                {
                    vectorOfPlayers[i].hand.clear();
                }
                play();

                cout << "\x1B[95m" << "Do you wish to play another game behind this table? (Y/N)" << "\033[0m" << endl;
                hitFlag = "";
                cin >> hitFlag;
                while (hitFlag != "Y" && hitFlag != "y" && hitFlag != "Y" && hitFlag != "n")
                {
                    cout << "Incorrect input! Type 'Y' or 'N'!" << endl;
                    cin >> hitFlag;
                }
            }
            vectorOfPlayers.clear();
        }

    private:
        Deck deck;
        House houseHand;
        vector <Player> vectorOfPlayers;


        void printAllCards()
        {
            cout << "\x1B[97m" << houseHand.name << ":" << "\033[0m";
            for (int i = 0; i < houseHand.hand.size(); i++)
            {
                cout << "\t" << houseHand.hand[i];
            }

            if (houseHand.hand[0].cardState == 0)
                cout << endl;
            else
                cout << "\x1B[33m" << "\t" << "|" << houseHand.getValue() << "\033[0m" << endl;

            string nameCut = "";
            for (int i = 0; i < vectorOfPlayers.size(); i++)
            {
                for (int k = 0; k < 5; k++)
                {
                    if (vectorOfPlayers[i].name[k] != '\0')
                        nameCut.insert(k, 1, vectorOfPlayers[i].name[k]);
                    else
                        break;
                }
                cout << "\x1B[97m" << nameCut << ":" << "\033[0m";
                for (int j = 0; j < vectorOfPlayers[i].hand.size(); j++)
                {
                    cout << "\t" << vectorOfPlayers[i].hand[j];
                }
                cout << "\x1B[33m" << "\t" << "|" << vectorOfPlayers[i].getValue() << "\033[0m" << endl;
                nameCut = "";
            }
        }

        void gameResults()
        {
            cout << "\x1B[95m" << "Results of the game:" << "\033[0m" << endl;
            {
                if (houseHand.IsBoosted())
                {
                    for (int i = 0; i < vectorOfPlayers.size(); i++)
                    {
                        if (vectorOfPlayers[i].IsBoosted())
                        {
                            vectorOfPlayers[i].Lose();
                        }
                        else
                        {
                            vectorOfPlayers[i].Win();
                        }
                    }
                }
                else if (houseHand.getValue() == 21)
                {
                    for (int i = 0; i < vectorOfPlayers.size(); i++)
                    {
                        if (vectorOfPlayers[i].getValue() == 21)
                        {
                            vectorOfPlayers[i].Push();
                        }
                        else
                        {
                            vectorOfPlayers[i].Lose();
                        }
                    }
                }
                else
                {
                    for (int i = 0; i < vectorOfPlayers.size(); i++)
                    {
                        if (vectorOfPlayers[i].getValue() == houseHand.getValue())
                        {
                            vectorOfPlayers[i].Push();
                        }
                        else if (vectorOfPlayers[i].getValue() < houseHand.getValue())
                        {
                            vectorOfPlayers[i].Lose();
                        }
                        else if (((vectorOfPlayers[i].getValue() > houseHand.getValue()) && !vectorOfPlayers[i].IsBoosted()))
                        {
                            vectorOfPlayers[i].Win();
                        }
                        else
                        {
                            vectorOfPlayers[i].Lose();
                        }
                    }
                }
            }
        }

        void play()
        {
            deck.Deal(houseHand);
            deck.Deal(houseHand);
            houseHand.FlipFirstCard();
            for (int i = 0; i < vectorOfPlayers.size(); i++)
            {
                deck.Deal(vectorOfPlayers[i]);
                deck.Deal(vectorOfPlayers[i]);
            }
            cout << "\x1B[95m" << "Initial hands of cards are dealt! Current state of the table: " << "\033[0m" << endl;
            printAllCards();
            cout << "\x1B[95m" << "Draw stage: " << "\033[0m" << endl;
            for (int i = 0; i < vectorOfPlayers.size(); i++)
            {
                while (vectorOfPlayers[i].IsHitting())
                {
                    deck.Deal(vectorOfPlayers[i]);
                    string nameCut = "";
                    for (int k = 0; k < 5; k++)
                    {
                        if (vectorOfPlayers[i].name[k] != '\0')
                            nameCut.insert(k, 1, vectorOfPlayers[i].name[k]);
                        else
                            break;
                    }
                    cout << "\x1B[97m" << nameCut << ":" << "\033[0m";
                    for (int j = 0; j < vectorOfPlayers[i].hand.size(); j++)
                    {
                        cout << "\t" << vectorOfPlayers[i].hand[j];
                    }
                    cout << "\x1B[33m" << "\t" << "|" << vectorOfPlayers[i].getValue() << "\033[0m" << endl;
                    if (vectorOfPlayers[i].IsBoosted())
                    {
                        vectorOfPlayers[i].Bust();
                        break;
                    }
                }
            }
            cout << "\x1B[95m" << "Now house is hitting!" << "\033[0m" << endl;
            while (houseHand.IsHitting())
            {
                deck.Deal(houseHand);
            }
            houseHand.FlipFirstCard();
            printAllCards();

            gameResults();
        }
};

class Date
{
    public:
        Date() {};
        Date(short _day, short _month, short _year) : day{ _day }, month{ _month }, year{ _year } {};
        ~Date() {};

        void setDay(short newDay)
        {
            day = newDay;
        }
        void setMonth(short newMonth)
        {
            month = newMonth;
        }
        void setYear(short newYear)
        {
            year = newYear;
        }

        short getDay()
        {
            return day;
        }
        short getMonth()
        {
            return month;
        }
        short getYear()
        {
            return year;
        }


        friend ostream& operator<<(ostream& out, Date date)
        {
            out << date.day << " " << date.month << " " << date.year << " ";
            return out;
        }

    private:
        short day;
        short month;
        short year;
};

shared_ptr <Date> LatestDate(shared_ptr<Date> date1, shared_ptr<Date> date2)
{
    if (date1->getYear() > date2->getYear())
        return date2;
    else if (date1->getYear() < date2->getYear())
        return date2;
    else
    {
        if (date1->getMonth() > date2->getMonth())
            return date1;
        else if (date1->getMonth() < date2->getMonth())
            return date2;
        else
        {
            if (date1->getDay() > date2->getDay())
                return date1;
            else if (date1->getDay() < date2->getDay())
                return date2;
        }
    }
}

void switchRes(shared_ptr<Date>& (date1), shared_ptr<Date>& (date2))
{
    shared_ptr<Date> date3(new Date());

    date3->setDay(date2->getDay());
    date3->setMonth(date2->getMonth());
    date3->setYear(date2->getYear());

    date2->setDay(date1->getDay());
    date2->setMonth(date1->getMonth());
    date2->setYear(date1->getYear());

    date1->setDay(date3->getDay());
    date1->setMonth(date3->getMonth());
    date1->setYear(date3->getYear());
}

int main()
{
    system("color 0");

    /*Date todayy(10, 9, 22);
    cout << todayy << endl;

    shared_ptr<Date> ptr(new Date(5, 6, 21));
    cout << *ptr << endl;

    cout << ptr->getDay() << " ";
    cout << ptr->getMonth() << " ";
    cout << ptr->getYear() << " " << endl;

    shared_ptr<Date> ptr2(new Date());
    ptr2->setDay(ptr->getDay());
    ptr2->setMonth(ptr->getMonth());
    ptr2->setYear(ptr->getYear());
    cout << *ptr << endl;
    cout << *ptr2 << endl;

    if (ptr != 0 && ptr2 != 0)
    {
        cout << "Pointers are not null!" << endl; //?????????
    }

    Date date1(11, 5, 23);
    Date date2(12, 12, 23);

    shared_ptr<Date>date1_ptr(&date1);
    shared_ptr<Date>date2_ptr(&date2);

    shared_ptr<Date>latestDate_ptr = LatestDate(date1_ptr, date2_ptr); //????????? Я так и не понял что требуется сделать в этом задании, но это лучшее, что смог из себя выдавить

    switchRes(date1_ptr, date2_ptr);*/

    /////////////////////////////////////////////// Вот тут играем в блекджек //////////////////////////////////////////////////////

    bool gameIsOn = true;

    while (gameIsOn)
    {

        int playerNum = 0;
        string inputLine = "";
        vector <string> vectorOfnames;

        cout << "\x1B[95m" << "Game is starting! How many players will be playing? (less than 12)" << "\033[0m" << endl;
        while (playerNum <= 0)
        {
            getline(cin, inputLine);
            try
            {
                playerNum = stoi(inputLine.c_str());
            }
            catch (std::invalid_argument const& e)
            {
                cerr << "Incorrect input, please reenter the number of players!" << endl;
            }
            if (playerNum > 12)
            {
                cerr << "Incorrect input, please reenter the number of players!" << endl;
                playerNum = 0;
            }
        }
        inputLine = "";
        for (int i = 0; i < playerNum; i++)
        {
            cout << "\x1B[97m" << "Enter the name of " << enumeratorList[i] << " player (less than 15 characters):" << "\033[0m" << endl;
            while (inputLine == "")
            {
                getline(cin, inputLine);
                if (inputLine.size() > 15)
                {
                    cerr << "Incorrect input, please reenter the name!" << endl;
                    inputLine = "";
                }
            }
            vectorOfnames.push_back(inputLine);
            inputLine = "";
        }
        cin.clear();

        Game* startGame = new Game(vectorOfnames);

        cout << "\x1B[95m" << "Do you wish to play another game behind a different table? (Y/N)" << "\033[0m" << endl;
        string gameFlag = "";
        cin >> gameFlag;
        while (gameFlag != "Y" && gameFlag != "y" && gameFlag != "Y" && gameFlag != "n")
        {
            cout << "Incorrect input! Type 'Y' or 'N'!" << endl;
            cin >> gameFlag;
        }
        if (gameFlag == "Y" || gameFlag == "y")
            gameIsOn = true;
        else
            gameIsOn = false;
    }

    std::cout << "\x1B[93m" << "K, cya!" << "\033[0m" << std::endl;
    return 0;
}
