#include <iostream>
#include <fstream>
#include <cstring>
#include <time.h>
#include <stdlib.h>
#include <typeinfo>
#include <vector>
using namespace std;
enum
{
    Ace=1,
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack=12,
    Queen,
    King
};
class card
{

    friend class deck;
    friend class player;
protected:

    string value;
    char symbol;
    int point;
public:
    card(string val="0",char c='0')
    {
        value = val;
        symbol=c;
        point=0;
    }
    int get_point()
    {
        return point;
    }
    string get_value()
    {
        return value;
    }
    void set(string v,char c)
    {
        value=v;
        symbol=c;
    }
    card& operator=(card& aux);
    friend ostream& operator<<(ostream& os,const card& q);
    virtual void play_card(card ob,int ord,int& winner,int& sum)
    {
        if(ob.get_value()==this->value)
            winner=ord;
    }
};
card& card::operator=(card& aux)
{
    value=aux.value;
    symbol=aux.symbol;
    point=aux.point;
    return aux;
}
ostream& operator<<(ostream& os,const card& q)
{
    os<<"|"<<q.value<<q.symbol<<"| ";
    return os;
}
class point_card:public card
{
public:
    point_card(string val="0",char sym='0'):card(val,sym)
    {
        point=1;
    }
    void play_card(card ob,int ord,int& winner,int& sum)
    {
        sum++;
        if(ob.get_value()==this->value)
            winner=ord;

    }
};
class cut_card:public card
{
public:
    cut_card(string val="0",char sym='0'):card(val,sym) {}
    void play_card(card ob,int ord,int& winner,int& sum)
    {
        if(ob.get_value()!="0")
            winner=ord;

    }
};
class deck
{
    friend class player;
    card**cards;
    int size;
    int *used;
public:

    deck(int aux=53);
    deck(const deck& A);
    deck& operator=(const deck& A);
    deck partition(int& nr);
    card* operator[](int i)
    {
        return cards[i];
    }
    friend ostream& operator<<(ostream& os,const deck& q);
    int get_size()
    {
        return size;
    }
    int get_used()
    {
        int val=0;
        for(int i=0; i<size; i++)
            if(used[i]==0)
                val++;
        return val;
        //cout<<used[i]<<" ";
    }
};
deck::deck(int aux)
{
    cards=new card*[aux];
    size=aux;
    used=new int[aux];
    used[0]=1;
    for(int i=1; i<aux; i++)
        used[i]=0;
    char suit[4]= {6,4,5,3};
    int k=1;
    int nr=Ace;
    string temp;

    while(k<aux)
    {
        if(nr==Ace)
            for(int i=0; i<=3 && k<aux; i++)
                cards[k++]=new point_card("A",suit[i]);
        else if(nr==Ten)
            for(int i=0; i<=3 && k<aux; i++)
                cards[k++]=new point_card("10",suit[i]);
        else if(nr==Jack)
            for(int i=0; i<=3 && k<aux; i++)
                cards[k++]=new card("J",suit[i]);
        else if(nr==Queen)
            for(int i=0; i<=3 && k<aux; i++)
                cards[k++]=new card("Q",suit[i]);
        else if(nr==King)
            for(int i=0; i<=3 && k<aux; i++)
                cards[k++]=new card("K",suit[i]);
        else if(nr==Seven)
            for(int i=0; i<=3 && k<aux; i++)
                cards[k++]=new cut_card("7",suit[i]);
        else
            for(int i=0; i<=3 && k<aux; i++)
            {
                temp=char(nr+48);
                cards[k++]=new card(temp,suit[i]);
            }


        nr++;
        if(nr==11) nr++;
    }
}
deck::deck(const deck& A)
{
    size=A.size;
    for(int i=1; i<A.size; i++)
        cards[i]=(A.cards[i]);
}
deck& deck::operator=(const deck& A)
{
    size=A.size;
    for(int i=1; i<=A.size; i++)
        *cards[i]=*A.cards[i];
    return *this;
}
deck deck::partition(int& nr)
{
    deck res(33);
    int k=1;
    if(nr<2 || nr>4)
        return res;
    if(nr==2 || nr==4)
    {

        for(int i=1; i<size; i++)
        {
            if(cards[i]->value=="A")
                res.cards[k++]=new point_card(cards[i]->value,cards[i]->symbol);
            else
            {
                if(cards[i]->value=="7")
                    res.cards[k++]=new cut_card(cards[i]->value,cards[i]->symbol);
                else
                {
                    if(i>28)
                    {
                        if(cards[i]->value=="10")
                            res.cards[k++]=new point_card(cards[i]->value,cards[i]->symbol);
                        else
                            res.cards[k++]=new card(cards[i]->value,cards[i]->symbol);
                    }
                }
            }
        }


    }
    else
    {
        res.size-=2;
        int prev=0;
        for(int i=1; i<size; i++)
        {
            if(cards[i]->value=="A")
                res.cards[k++]=new point_card(cards[i]->value,cards[i]->symbol);
            else if(cards[i]->value=="7")
                res.cards[k++]=new cut_card(cards[i]->value,cards[i]->symbol);
            else if(cards[i]->value=="8" && prev<2)
            {
                res.cards[k++]=new cut_card(cards[i]->value,cards[i]->symbol);
                prev++;
            }
            if(i>32)
            {
                if(cards[i]->value=="10")
                    res.cards[k++]=new point_card(cards[i]->value,cards[i]->symbol);
                else
                    res.cards[k++]=new card(cards[i]->value,cards[i]->symbol);
            }
        }
    }
    return res;
}
ostream& operator<<(ostream& os,const deck& q)
{

    for(int i=1; i<q.size; i++)
    {
        cout<<(*(q.cards[i]));
        if(i%4==0)
            cout<<endl;
    }


    return os;
}
class player
{
    card**hand;
    int score;
public:
    player()
    {
        hand=new card*[4];
        score=0;
    }
    int get_score()
    {
        return score;
    }
    card** get_hand()
    {
        return hand;
    }
    void increase_score(int val)
    {
        score+=val;
    }
    void create(deck& ob);
    void erase(int i)
    {
        hand[i]=NULL;
    }
    void complete(deck& ob);
    int valide(string a,char b);
    bool can_continue(string ob);
    friend ostream& operator<<(ostream& os,const player& ob);
    int remain()
    {
        int s=0;
        for(int i=0; i<4; i++)
            if(hand[i]!=NULL)
                s++;
        return s;
    }

};
void player::create(deck& ob)
{
    srand(time(NULL));
    int nr=ob.size;
    for(int i=0; i<4; i++)
    {
        int r=rand()%nr+1;
        while(r==33 || ob.used[r]==1)
            r=rand()%nr+1;

        if(ob[r]->value=="7")
            hand[i]=new cut_card(ob[r]->value,ob[r]->symbol);
        else if(ob[r]->value=="A" || ob[r]->value=="10")
            hand[i]=new point_card(ob[r]->value,ob[r]->symbol);
        else
            hand[i]=new card(ob[r]->value,ob[r]->symbol);
        ob.used[r]=1;

    }

}
void player::complete(deck& ob)
{
    srand(time(NULL));
    int nr=ob.size;
    int nr2=ob.get_used();
    int stop=0;
    for(int i=0; i<4 && stop<nr2/2; i++,stop++)
        if(hand[i]==NULL)
        {
            int r=rand()%nr+1;
            while(r==33 || ob.used[r]==1)
                r=rand()%nr+1;

            if(ob[r]->value=="7")
                hand[i]=new cut_card(ob[r]->value,ob[r]->symbol);
            else if(ob[r]->value=="A" || ob[r]->value=="10")
                hand[i]=new point_card(ob[r]->value,ob[r]->symbol);
            else
                hand[i]=new card(ob[r]->value,ob[r]->symbol);
            ob.used[r]=1;

        }
}
int player::valide(string a,char b)
{
    for(int i=0; i<4; i++)
        //if(hand[i]!=0)
        if(hand[i]->value==a && hand[i]->symbol==b)
            return i;
    return -1;

}
bool player::can_continue(string ob)
{

    for(int i=0; i<4; i++)
        if(hand[i]!=NULL &&(hand[i]->value=="7" || hand[i]->value==ob))
            return true;
    return false;
}
ostream& operator<<(ostream& os, const player& ob)
{
    for(int i=0; i<4; i++)
        if(ob.hand[i]!=NULL)
            os<<*ob.hand[i];
    cout<<endl;
    return os;
}
int main()
{

    deck A;
    int number_of_players=2;

    /*
    cout<<"Numbers of players:";
    cin>>number_of_players;
    while(number_of_players>4||number_of_players<2)
    {
        system("cls");
        cout<<"Numbers of players:";
        cin>>number_of_players;
    }
    */
    deck part=A.partition(number_of_players);
    ///cout<<part;

    vector<player> players;
    int aux=number_of_players;
    while(aux--)
    {
        player temp;
        temp.create(part);
        players.push_back(temp);
    }

    card actual; //("0",'0'
    int temporary_score=0;
    int ord=0;
    string str,val;
    char sym;
    int s;
    int winner=0;
    int cnt=0;
    string rasp;//="Yes";//="No";
    int start=1;
    while(part.get_used())
    {
        if(winner==0)
        {
            if(ord==0)
            {

                cout<<"\nPlayer 0:";
                cout<<players[0];

                cout<<"\n Symbols:  \n"
                    " Spades   (Alt+6) \n"
                    " Diamonds (Alt+4) \n"
                    " Clubs    (Alt+5) \n"
                    " Hearts   (Alt+3) \n"
                    "\n Card:";
                    "\n Card:";
                cin>>str;
                sym=str[str.size()-1];
                for(unsigned int i=0; i<str.size()-1; i++)
                    val+=str[i];
                s=players[0].valide(val,sym);
                while(s==-1)
                {
                    val="";
                    cout<<" Card:";
                    cin>>str;
                    sym=str[str.size()-1];
                    for(unsigned int i=0; i<str.size()-1; i++)
                        val+=str[i];
                    s=players[1].valide(val,sym);
                }

                players[0].get_hand()[s]->play_card(actual,ord,winner,temporary_score);
                if(start)
                {
                    actual.set(val,sym);
                    start=0;
                }
                players[0].erase(s);
                ord=1;
                val="";
                system("cls");
                cout<<"Down card : "<<actual;
            }
            if(ord==1)
            {
                cout<<"\nPlayer 1:";
                cout<<players[1];
                cout<<"\n Symbols:  \n"
                    " Spades   (Alt+6) \n"
                    " Diamonds (Alt+4) \n"
                    " Clubs    (Alt+5) \n"
                    " Hearts   (Alt+3) \n"
                    "\n Card:";
                cin>>str;
                sym=str[str.size()-1];
                for(unsigned int i=0; i<str.size()-1; i++)
                    val+=str[i];
                s=players[1].valide(val,sym);
                while(s==-1)
                {
                    val="";
                    cout<<" Card:";
                    cin>>str;
                    sym=str[str.size()-1];
                    for(unsigned int i=0; i<str.size()-1; i++)
                        val+=str[i];
                    s=players[1].valide(val,sym);
                }

                players[1].get_hand()[s]->play_card(actual,ord,winner,temporary_score);
                if(start)
                {
                    actual.set(val,sym);
                    start=0;
                }
                players[1].erase(s);
                ord=0;
                val="";
                system("cls");
                cout<<"Down card : "<<actual;
            }
            system("cls");
            cnt++;
            ord=winner;
        }
        else if(winner==1)
        {
            if(ord==1)
            {
                cout<<"\nPlayer 1:";
                cout<<players[1];
                cout<<"\n Symbols:  \n"
                    " Spades   (Alt+6) \n"
                    " Diamonds (Alt+4) \n"
                    " Clubs    (Alt+5) \n"
                    " Hearts   (Alt+3) \n"
                    "\n Card:";
                cin>>str;
                sym=str[str.size()-1];
                for(unsigned int i=0; i<str.size()-1; i++)
                    val+=str[i];
                s=players[1].valide(val,sym);
                while(s==-1)
                {
                    val="";
                    cout<<" Card:";
                    cin>>str;
                    sym=str[str.size()-1];
                    for(unsigned int i=0; i<str.size()-1; i++)
                        val+=str[i];
                    s=players[1].valide(val,sym);
                }

                players[1].get_hand()[s]->play_card(actual,ord,winner,temporary_score);
                if(start)
                {
                    actual.set(val,sym);
                    start=0;
                }
                players[1].erase(s);
                ord=0;
                val="";
                system("cls");
                cout<<"Down card : "<<actual;
            }
            if(ord==0)
            {

                cout<<"\nPlayer 0:";
                cout<<players[0];

                cout<<"\n Symbols:  \n"
                    " Spades   (Alt+6) \n"
                    " Diamonds (Alt+4) \n"
                    " Clubs    (Alt+5) \n"
                    " Hearts   (Alt+3) \n"
                    "\n Card:";
                    "\n Card:";
                cin>>str;
                sym=str[str.size()-1];
                for(unsigned int i=0; i<str.size()-1; i++)
                    val+=str[i];
                s=players[0].valide(val,sym);
                while(s==-1)
                {
                    val="";
                    cout<<" Card:";
                    cin>>str;
                    sym=str[str.size()-1];
                    for(unsigned int i=0; i<str.size()-1; i++)
                        val+=str[i];
                    s=players[1].valide(val,sym);
                }

                players[0].get_hand()[s]->play_card(actual,ord,winner,temporary_score);
                if(start)
                {
                    actual.set(val,sym);
                    start=0;
                }
                players[0].erase(s);
                ord=1;
                val="";
                system("cls");
                cout<<"Down card : "<<actual;
            }

            system("cls");
            cnt++;
            ord=winner;
        }
        system("cls");
        cnt++;
        ord=winner;


        if(players[1-winner].can_continue(actual.get_value()))
        {
            cout<<"Player "<<1-winner <<"'s cards: "<<players[1-winner];
            cout<<"\n\n Player "<<1-winner<<", do you continue? <Yes/No> ";
            cin>>rasp;
        }

        else
            rasp="No";
        if(rasp=="Yes")
        {
            winner=1-winner;
            ord=winner;
        }
        else
        {
            players[winner].increase_score(temporary_score);
            players[0].complete(part);
            players[1].complete(part);
            temporary_score=0;
            actual.set("0",'0');
            start=1;
            //system("cls");
        }

    }

    while(players[0].remain()!=0 && players[0].remain()!=0)
    {
        if(winner==0)
        {
            if(ord==0)
            {

                cout<<"\nPlayer 1:";
                cout<<players[0];

                cout<<"\n Symbols:  \n"
                    " Spades (Alt+6) \n Diamonds (Alt+4) \n Clubs (Alt+5) \n Hearts (Alt+3) \n"
                    "\n Card:";
                cin>>str;
                sym=str[str.size()-1];
                for(unsigned int i=0; i<str.size()-1; i++)
                    val+=str[i];
                s=players[0].valide(val,sym);
                while(s==-1)
                {
                    val="";
                    cout<<" Card:";
                    cin>>str;
                    sym=str[str.size()-1];
                    for(unsigned int i=0; i<str.size()-1; i++)
                        val+=str[i];
                    s=players[1].valide(val,sym);
                }

                players[0].get_hand()[s]->play_card(actual,ord,winner,temporary_score);
                if(start)
                {
                    actual.set(val,sym);
                    start=0;
                }
                players[0].erase(s);
                ord=1;
                val="";
                system("cls");
                cout<<"Down card : "<<actual;
            }
            if(ord==1)
            {
                cout<<"\nPlayer 2:";
                cout<<players[1];
                cout<<"\n Symbols:  \n"
                    " Spades   (Alt+6) \n"
                    " Diamonds (Alt+4) \n"
                    " Clubs    (Alt+5) \n"
                    " Hearts   (Alt+3) \n"
                    "\n Card:";
                cin>>str;
                sym=str[str.size()-1];
                for(unsigned int i=0; i<str.size()-1; i++)
                    val+=str[i];
                s=players[1].valide(val,sym);
                while(s==-1)
                {
                    val="";
                    cout<<" Card:";
                    cin>>str;
                    sym=str[str.size()-1];
                    for(unsigned int i=0; i<str.size()-1; i++)
                        val+=str[i];
                    s=players[1].valide(val,sym);
                }

                players[1].get_hand()[s]->play_card(actual,ord,winner,temporary_score);
                if(start)
                {
                    actual.set(val,sym);
                    start=0;
                }
                players[1].erase(s);
                ord=0;
                val="";//system("cls");
                cout<<"Down card : "<<actual;
            }
            system("cls");
            cnt++;
            ord=winner;
        }
        if(winner==1)
        {
            if(ord==1)
            {
                cout<<"\nPlayer 2:";
                cout<<players[1];
                cout<<"\n Symbols:  \n"
                    " Spades   (Alt+6) \n"
                    " Diamonds (Alt+4) \n"
                    " Clubs    (Alt+5) \n"
                    " Hearts   (Alt+3) \n"
                    "\n Card:";
                cin>>str;
                sym=str[str.size()-1];
                for(unsigned int i=0; i<str.size()-1; i++)
                    val+=str[i];
                s=players[1].valide(val,sym);
                while(s==-1)
                {
                    val="";
                    cout<<" Card:";
                    cin>>str;
                    sym=str[str.size()-1];
                    for(unsigned int i=0; i<str.size()-1; i++)
                        val+=str[i];
                    s=players[1].valide(val,sym);
                }

                players[1].get_hand()[s]->play_card(actual,ord,winner,temporary_score);
                if(start)
                {
                    actual.set(val,sym);
                    start=0;
                }
                players[1].erase(s);
                ord=0;
                val="";//system("cls");
                cout<<"Down card : "<<actual;
            }
            if(ord==0)
            {

                cout<<"\nPlayer 1:";
                cout<<players[0];

                cout<<"\n Symbols:  \n"
                    " Spades (Alt+6) \n Diamonds (Alt+4) \n Clubs (Alt+5) \n Hearts (Alt+3) \n"
                    "\n Card:";
                cin>>str;
                sym=str[str.size()-1];
                for(unsigned int i=0; i<str.size()-1; i++)
                    val+=str[i];
                s=players[0].valide(val,sym);
                while(s==-1)
                {
                    val="";
                    cout<<" Card:";
                    cin>>str;
                    sym=str[str.size()-1];
                    for(unsigned int i=0; i<str.size()-1; i++)
                        val+=str[i];
                    s=players[1].valide(val,sym);
                }

                players[0].get_hand()[s]->play_card(actual,ord,winner,temporary_score);
                if(start)
                {
                    actual.set(val,sym);
                    start=0;
                }
                players[0].erase(s);
                ord=1;
                val="";
                system("cls");
                cout<<"Down card : "<<actual;
            }

            system("cls");
            cnt++;
            ord=winner;
        }

        if(players[1-winner].can_continue(actual.get_value()))
        {

            cout<<"\n\n Player "<<1+winner<<", do you continue? <Yes/No>";
            cin>>rasp;
        }

        else
            rasp="No";
        if(rasp=="Yes")
            ord=1-ord;
        else
        {
            players[winner].increase_score(temporary_score);
            temporary_score=0;
            actual.set("0",'0');
            start=1;
            //system("cls");
        }

    }

    if(players[0].get_score()>players[1].get_score())
        cout<<"Player 1 won!";
    else if(players[0].get_score()<players[1].get_score())
        cout<<"Player 2 won!";
    else
        cout<<"Draw!";

    return 0;
}

