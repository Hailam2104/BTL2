#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG

enum ItemType { ANTIDOTE = 0, PHOENIXDOWNI, PHOENIXDOWNII, PHOENIXDOWNIII, PHOENIXDOWNIV, PHOENIXDOWN };

class BaseKnight;
class BaseItem;
class Events;

struct Node {
    BaseItem* item;
    Node* nextItem;
};

class BaseBag {
protected:
    BaseKnight* knight;
    Node* head;
public:
    BaseBag();
    
    virtual bool insertFirst(BaseItem* item) = 0; 
    virtual BaseItem * get(ItemType itemType); 
    virtual string toString() const;
    
    virtual int numItem();
    virtual void useItem();
    virtual void clearBag();
};

class PaladinBag : public BaseBag {
public:
    PaladinBag(BaseKnight* knight, int phoenixdownI, int antidote);
    bool insertFirst(BaseItem* item);
};

class LancelotBag : public BaseBag {
public:
    LancelotBag(BaseKnight* knight, int phoenixdownI, int antidote); 
    bool insertFirst(BaseItem* item); 
};

class DragonBag : public BaseBag {
public:
    DragonBag(BaseKnight* knight, int phoenixdownI, int antidote); 
    bool insertFirst(BaseItem* item); 
};

class NormalBag : public BaseBag {
public:
    NormalBag(BaseKnight* knight, int phoenixdownI, int antidote);
    bool insertFirst(BaseItem* item);
};

enum Opponent {MADBEAR, BANDIT, LORDLUPIN, ELF, TROLL, TORNBERY, QUEENOFCARDS, NINADERINGS, DURIANGARDEN, OMEGAWEAPON, HADES}; 

class BaseOpponent {
protected: 
    int levelO; 
    int baseDamage; 
    int numGil; 
public:
    BaseOpponent();
    virtual int getLevelO();
    virtual int damage(int level);
    virtual int getNumGil();
    virtual Opponent typeOpponent() = 0;
};

class MadBear : public BaseOpponent {
public:
    MadBear(int i, int eventI);
    Opponent typeOpponent();
};

class Bandit : public BaseOpponent {
public:
    Bandit(int i, int eventI);
    Opponent typeOpponent();
};

class LordLupin : public BaseOpponent {
public:
    LordLupin(int i, int eventI);
    Opponent typeOpponent();
};

class Elf : public BaseOpponent {
public:
    Elf(int i, int eventI);
    Opponent typeOpponent();
};

class Troll : public BaseOpponent {
public:
    Troll(int i, int eventI);
    Opponent typeOpponent();
};

class Tornbery : public BaseOpponent {
public:
    Tornbery(int i, int eventI);
    Opponent typeOpponent();
};

class QueenOfCards : public BaseOpponent {
public:
    QueenOfCards(int i, int eventI);
    Opponent typeOpponent();
};

class NinaDeRings : public BaseOpponent {
public:
    //NinaDeRings();
    Opponent typeOpponent();
};

class DurianGarden : public BaseOpponent {
public:
    //DurianGarden();
    Opponent typeOpponent();
};

class OmegaWeapon : public BaseOpponent {
public:
    //OmegaWeapon();
    Opponent typeOpponent();
};

class Hades : public BaseOpponent {
public:
    //Hades();
    Opponent typeOpponent();
};

enum KnightType { PALADIN = 0, LANCELOT, DRAGON, NORMAL };

class BaseKnight {
protected:
    int id;
    int hp;
    int maxhp;
    int level;
    int gil;
    int poison; 
    BaseBag* bag;
    KnightType knightType;
public:
    BaseKnight(int id, int  maxhp, int level, int gil, KnightType knightType);
    void increaseHP(int increase);
    void decreaseHP(int decrease);
    void setHP(int hp);
    int getHP();
    int getMaxHP();

    void levelUp();
    void setLevel(int level);
    int getLevel();

    void increaseGil(int increase);
    void decreaseGil(int decrease);
    void doubleGil();
    void divideGil();
    void setGil(int gil);
    int getGil();

    void setPoison(int poison);
    int getPoison();

    void setBag(BaseBag* bag);
    BaseBag* getBag();

    KnightType getKnightType();
    
    static BaseKnight* create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    string toString() const;
};

class PaladinKnight : public BaseKnight {
public:
    PaladinKnight(int id, int maxhp, int level, int gil)
        :BaseKnight(id, maxhp, level, gil, PALADIN) {};
};

class LancelotKnight : public BaseKnight {
public:
    LancelotKnight(int id, int maxhp, int level, int gil)
        :BaseKnight(id, maxhp, level, gil, LANCELOT) {};
};

class DragonKnight : public BaseKnight {
public:
    DragonKnight(int id, int maxhp, int level, int gil)
        :BaseKnight(id, maxhp, level, gil, DRAGON) {};
};

class NormalKnight : public BaseKnight {
public:
    NormalKnight(int id, int maxhp, int level, int gil)
        : BaseKnight(id, maxhp, level, gil, NORMAL) {};
};

class ArmyKnights {
protected:
    int PaladinShield;
    int LancelotSpear; 
    int GuinevereHair;
    int ExcaliburSword;
    int numknights;
    int gilAdd;
    int winOmegaWeapon;
    int winHades;
    BaseKnight** listknights;
public:
    ArmyKnights(const string& file_armyknights);
    ~ArmyKnights();
    bool fight(BaseOpponent* opponent); 
    
    bool die();
    bool die(int position);
    
    bool adventure(Events* events); 
    int count() const; 
    BaseKnight* lastKnight() const;

    bool hasPaladinShield() const;
    bool hasLancelotSpear() const;
    bool hasGuinevereHair() const;
    bool hasExcaliburSword() const;

    void printInfo() const;
    void printResult(bool win) const;
};

class BaseItem {
public:
    virtual ItemType itemType() = 0;
    virtual bool canUse(BaseKnight* knight) = 0;
    virtual void use(BaseKnight* knight) = 0;
};

class Antidote : public BaseItem {
public:
    ItemType itemType();
    bool canUse(BaseKnight* knight);
    void use(BaseKnight* knight);
};

class PhoenixDownI : public BaseItem {
public:
    ItemType itemType();
    bool canUse(BaseKnight* knight);
    void use(BaseKnight* knight);
};

class PhoenixDownII : public BaseItem {
public:
    ItemType itemType();
    bool canUse(BaseKnight* knight);
    void use(BaseKnight* knight);
};

class PhoenixDownIII : public BaseItem {
public:
    ItemType itemType();
    bool canUse(BaseKnight* knight);
    void use(BaseKnight* knight);
};

class PhoenixDownIV : public BaseItem {
public:
    ItemType itemType();
    bool canUse(BaseKnight* knight);
    void use(BaseKnight* knight);
};

class Events {
protected:
    int numevents; 
    int* listevents; 
public:
    Events(const string& file_events); 
    ~Events();
    int count() const;
    int get(int i) const;
}; 

class KnightAdventure {
private:
    ArmyKnights* armyKnights;
    Events* events;

public:
    KnightAdventure();
    ~KnightAdventure(); 

    void loadArmyKnights(const string &);
    void loadEvents(const string &);
    void run();
};

int countItem(Node* head);

bool isPrime(int maxhp);
bool isPytago(int maxhp);
KnightType knightTypeIs(int maxhp);

#endif // __KNIGHT2_H__
