#include "knight2.h"

/* FUNCTION */
bool isPrime(int maxhp) {
    if (maxhp <= 1) {
        return false;
    }
    else {
        for (int i = 2; i <= sqrt(maxhp); i++) {
            if (maxhp % i == 0) {
                return false;
            }
        }
        return true;
    }
}
bool isPytago(int maxhp) {
    if (maxhp < 100) {
        return false;
    }
    else {
        int a = maxhp % 10, b = (maxhp / 10) % 10, c = (maxhp / 100) % 10;
        bool condition1 = a * a + b * b == c * c;
        bool condition2 = a * a + c * c == b * b;
        bool condition3 = b * b + c * c == a * a;
        if (condition1 || condition2 || condition3) {
            return true;
        }
        return false;

    }
}
KnightType knightTypeIs(int maxhp) {
    if (isPrime(maxhp)) {
        return PALADIN;
    }
    else if (maxhp == 888) {
        return LANCELOT;
    }
    else if (isPytago(maxhp)) {
        return DRAGON;
    }
    else {
        return NORMAL;
    }
}
int countItem(Node* head) {
    int count = 0; 
    while (head != nullptr) {
        count++;
        head = head->nextItem;
    }
    return count;
}
/* FUNCTION */
/*-----------------------------------------------------------------------------------------------------------*/
/* * * BEGIN implementation of class BaseBag * * */
//BaseBag
BaseBag::BaseBag() {
    this->knight = nullptr;
    this->head = nullptr;
}
BaseItem* BaseBag::get(ItemType itemType) {
    bool haveItem = false;
    if (itemType == PHOENIXDOWN) {
        for (Node* temp = head; temp != nullptr; temp = temp->nextItem) {
            bool condition1 = temp->item->itemType() == PHOENIXDOWNI;
            bool condition2 = temp->item->itemType() == PHOENIXDOWNII;
            bool condition3 = temp->item->itemType() == PHOENIXDOWNIII;
            bool condition4 = temp->item->itemType() == PHOENIXDOWNIV;
            if (condition1 || condition2 || condition3 || condition4) {
                if (temp->item->canUse(knight)) {
                    haveItem = true;
                    BaseItem* tmp = head->item;
                    head->item = temp->item;
                    temp->item = tmp;
                    break;
                }
            }
        }
    }
    else {
        for (Node* temp = head; temp != nullptr; temp = temp->nextItem) {
            if (temp->item->itemType() == itemType) {
                if (temp->item->canUse(knight)) {
                    BaseItem* tmp = head->item;
                    head->item = temp->item;
                    temp->item = tmp;
                    haveItem = true;
                    break;
                }
            }
        }
    }
    if (haveItem) {
        return head->item;
    }
    else {
        return nullptr;
    }

}
string BaseBag::toString() const {
    string type[5] = { "Antidote", "PhoenixI", "PhoenixII", "PhoenixIII", "PhoenixIV" };
    string s("");
    s += "Bag[count=" + to_string(countItem(head)) + ";";
    for (Node* temp = head; temp != nullptr; temp = temp->nextItem) {
        if (temp->nextItem == nullptr) {
            s += type[temp->item->itemType()];
        }
        else {
            s += type[temp->item->itemType()] + ",";
        }
    }
    s += "]";
    return s;
}
int BaseBag::numItem() {
    return countItem(this->head);
}
void BaseBag::useItem() {
    Node* temp = head;
    head = head->nextItem;
    delete temp;
}
void BaseBag::clearBag() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->nextItem;
        delete temp;
    }
}
//Paladin
PaladinBag::PaladinBag(BaseKnight* knight, int phoenixdownI, int antidote) {
    this->knight = knight;
    //this->head = nullptr;
    for (int i = 0; i < phoenixdownI; i++) {
        BaseItem* item = new PhoenixDownI;
        insertFirst(item);
    }
    for (int i = 0; i < antidote; i++) {
        BaseItem* item = new Antidote;
        insertFirst(item);
    }
}
bool PaladinBag::insertFirst(BaseItem* item) {
    Node* temp = new Node;
    temp->item = item;
    temp->nextItem = nullptr;
    if (head == nullptr) {
        head = temp;
    }
    else {
        temp->nextItem = head;
        head = temp;
    }
    return true;
}
//Lancelot
LancelotBag::LancelotBag(BaseKnight* knight, int phoenixdownI, int antidote) {
    this->knight = knight;
    //this->head = nullptr;
    for (int i = 0; i < phoenixdownI; i++) {
        BaseItem* item = new PhoenixDownI;
        insertFirst(item);
    }
    for (int i = 0; i < antidote; i++) {
        BaseItem* item = new Antidote;
        insertFirst(item);
    }
}
bool LancelotBag::insertFirst(BaseItem* item) {
    if (countItem(head) < 16) {
        Node* temp = new Node;
        temp->item = item;
        temp->nextItem = nullptr;
        if (head == nullptr) {
            head = temp;
        }
        else {
            temp->nextItem = head;
            head = temp;
        }
        return true;
    }
    else {
        return false;
    }
}
//Dragon
DragonBag::DragonBag(BaseKnight* knight, int phoenixdownI, int antidote) {
    this->knight = knight;
    //this->head = nullptr;
    for (int i = 0; i < phoenixdownI; i++) {
        BaseItem* item = new PhoenixDownI;
        insertFirst(item);
    }
}
bool DragonBag::insertFirst(BaseItem* item) {
    if (countItem(head) < 14 && item->itemType() != ANTIDOTE) {
        Node* temp = new Node;
        temp->item = item;
        temp->nextItem = nullptr;
        if (head == nullptr) {
            head = temp;
        }
        else {
            temp->nextItem = head;
            head = temp;
        }
        return true;
    }
    else {
        return false;
    }
}
//Normal
NormalBag::NormalBag(BaseKnight* knight, int phoenixdownI, int antidote) {
    this->knight = knight;
    //this->head = nullptr;
    for (int i = 0; i < phoenixdownI; i++) {
        BaseItem* item = new PhoenixDownI;
        insertFirst(item);
    }
    for (int i = 0; i < antidote; i++) {
        BaseItem* item = new Antidote;
        insertFirst(item);
    }
}
bool NormalBag::insertFirst(BaseItem* item) {
    if (countItem(head) < 19) {
        Node* temp = new Node;
        temp->item = item;
        temp->nextItem = nullptr;
        if (head == nullptr) {
            head = temp;
        }
        else {
            temp->nextItem = head;
            head = temp;
        }
        return true;
    }
    else {
        return false;
    }
}
/* * * END implementation of class BaseBag * * */
/*-----------------------------------------------------------------------------------------------------------*/
/* * * BEGIN implementation of class BaseOpponent * * */
//BaseOpponent
BaseOpponent::BaseOpponent() {
    this->levelO = 0;
    this->baseDamage = 0;
    this->numGil = 0;
}
int BaseOpponent::getLevelO() {
    return levelO;
}
int BaseOpponent::damage(int level) {
    return (baseDamage * (levelO - level));
}
int BaseOpponent::getNumGil() {
    return numGil;
}
//MadBear
MadBear::MadBear(int i, int eventI) {
    this->levelO = (i + eventI) % 10 + 1;
    this->baseDamage = 10;
    this->numGil = 100;
}
Opponent MadBear::typeOpponent() {
    return MADBEAR;
}
//Bandit
Bandit::Bandit(int i, int eventI) {
    this->levelO = (i + eventI) % 10 + 1;
    this->baseDamage = 15;
    this->numGil = 150;
}
Opponent Bandit::typeOpponent() {
    return BANDIT;
}
//LordLupin
LordLupin::LordLupin(int i, int eventI) {
    this->levelO = (i + eventI) % 10 + 1;
    this->baseDamage = 45;
    this->numGil = 450;
}
Opponent LordLupin::typeOpponent() {
    return LORDLUPIN;
}
//Elf
Elf::Elf(int i, int eventI) {
    this->levelO = (i + eventI) % 10 + 1;
    this->baseDamage = 75;
    this->numGil = 750;
}
Opponent Elf::typeOpponent() {
    return ELF;
}
//Troll
Troll::Troll(int i, int eventI) {
    this->levelO = (i + eventI) % 10 + 1;
    this->baseDamage = 95;
    this->numGil = 800;
}
Opponent Troll::typeOpponent() {
    return TROLL;
}
//Tornbery
Tornbery::Tornbery(int i, int eventI) {
    this->levelO = (i + eventI) % 10 + 1;
    //this->baseDamage = 0;
    //this->numGil = 0;
}
Opponent Tornbery::typeOpponent() {
    return TORNBERY;
}
//Queen Of Cards
QueenOfCards::QueenOfCards(int i, int eventI) {
    this->levelO = (i + eventI) % 10 + 1;
    //this->baseDamage = 0;
    //this->numGil = 0;
}
Opponent QueenOfCards::typeOpponent() {
    return QUEENOFCARDS;
}
//Nina De Rings
/*NinaDeRings::NinaDeRings() {
    this->levelO = 0;
    this->baseDamage = 0;
    this->numGil = 0;
}*/
Opponent NinaDeRings::typeOpponent() {
    return NINADERINGS;
}
//Durian Garden
/*DurianGarden::DurianGarden() {
    this->levelO = 0;
    this->baseDamage = 0;
    this->numGil = 0;
}*/
Opponent DurianGarden::typeOpponent() {
    return DURIANGARDEN;
}
//Omega Weapon
/*OmegaWeapon::OmegaWeapon() {
    this->levelO = 0;
    this->baseDamage = 0;
    this->numGil = 0;
}*/
Opponent OmegaWeapon::typeOpponent() {
    return OMEGAWEAPON;
}
//Hades
/*Hades::Hades() {
    this->levelO = 0;
    this->baseDamage = 0;
    this->numGil = 0;
}*/
Opponent Hades::typeOpponent() {
    return HADES;
}
/* * * END implementation of class BaseOpponent * * */
/*-----------------------------------------------------------------------------------------------------------*/
/* * * BEGIN implementation of class BaseKnight * * */
//BaseKnight
BaseKnight::BaseKnight(int id, int maxhp, int level, int gil, KnightType knightType) {
    this->id = id;
    this->hp = maxhp;
    this->maxhp = maxhp;
    this->level = level;
    this->gil = gil;
    this->knightType = knightType;
    this->poison = 0;
    this->bag = nullptr;

}
string BaseKnight::toString() const {
    string typeString[4] = {"PALADIN", "LANCELOT", "DRAGON", "NORMAL"};
    // inefficient version, students can change these code
    //      but the format output must be the same
    string s("");
    s += "[Knight:id:" + to_string(id) 
        + ",hp:" + to_string(hp) 
        + ",maxhp:" + to_string(maxhp)
        + ",level:" + to_string(level)
        + ",gil:" + to_string(gil)
        + "," + bag->toString()
        + ",knight_type:" + typeString[knightType]
        + "]";
    return s;
}
void BaseKnight::increaseHP(int increase) {
    hp += increase;
    if (hp > maxhp) {
        hp = maxhp;
    }
}
void BaseKnight::decreaseHP(int decrease) {
    hp -= decrease;
}
void BaseKnight::setHP(int hp) {
    this->hp = hp;
}
int BaseKnight::getHP() {
    return hp;
}
int BaseKnight::getMaxHP() {
    return maxhp;
}
void BaseKnight::levelUp() {
    level++;
    if (level > 10) {
        level = 10;
    }
}
void BaseKnight::setLevel(int level) {
    this->level = level;
}
int BaseKnight::getLevel() {
    return level;
}
void BaseKnight::increaseGil(int increase) {
    gil += increase;
}
void BaseKnight::decreaseGil(int decrease) {
    gil -= decrease;
}
void BaseKnight::doubleGil() {
    gil *= 2;
}
void BaseKnight::divideGil() {
    gil /= 2;
}
void BaseKnight::setGil(int gil) {
    this->gil = gil;
}
int BaseKnight::getGil() {
    return gil;
}
void BaseKnight::setPoison(int poison) {
    this->poison = poison;
}
int BaseKnight::getPoison() {
    return poison;
}
void BaseKnight::setBag(BaseBag* bag) {
    this->bag = bag;
}
BaseBag* BaseKnight::getBag() {
    return bag;
}
KnightType BaseKnight::getKnightType() {
    return knightType;
}
BaseKnight* BaseKnight::create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI) {
    BaseKnight* knight = nullptr;
    BaseBag* bag = nullptr;
    switch (knightTypeIs(maxhp)) {
        case PALADIN: {
            knight = new PaladinKnight(id, maxhp, level, gil);
            bag = new PaladinBag(knight, phoenixdownI, antidote);
            knight->setBag(bag);
            break;
        }
        case LANCELOT: {
            knight = new LancelotKnight(id, maxhp, level, gil);
            bag = new LancelotBag(knight, phoenixdownI, antidote);
            knight->setBag(bag);
            break;
        }
        case DRAGON: {
            knight = new DragonKnight(id, maxhp, level, gil);
            bag = new DragonBag(knight, phoenixdownI, antidote);
            knight->setBag(bag);
            break;
        }
        case NORMAL: {
            knight = new NormalKnight(id, maxhp, level, gil);
            bag = new NormalBag(knight, phoenixdownI, antidote);
            knight->setBag(bag);
            break;
        }
    }
    return knight;
}
/* * * END implementation of class BaseKnight * * */
/*-----------------------------------------------------------------------------------------------------------*/
/* * * BEGIN implementation of class ArmyKnights * * */
void ArmyKnights::printInfo() const {
    cout << "No. knights: " << this->count();
    if (this->count() > 0) {
        BaseKnight * lknight = lastKnight(); // last knight
        cout << ";" << lknight->toString();
    }
    cout << ";PaladinShield:" << this->hasPaladinShield()
        << ";LancelotSpear:" << this->hasLancelotSpear()
        << ";GuinevereHair:" << this->hasGuinevereHair()
        << ";ExcaliburSword:" << this->hasExcaliburSword()
        << endl
        << string(50, '-') << endl;
}
void ArmyKnights::printResult(bool win) const {
    cout << (win ? "WIN" : "LOSE") << endl;
}
ArmyKnights::ArmyKnights(const string& file_armyknights) {
    PaladinShield = 0;
    LancelotSpear = 0;
    GuinevereHair = 0;
    ExcaliburSword = 0;
    gilAdd = 0;
    winOmegaWeapon = 0;
    winHades = 0;
    ifstream f;
    f.open(file_armyknights);
    f >> numknights;
    listknights = new BaseKnight * [numknights];
    for (int i = 0; i < numknights; i++) {
        int id = i + 1;
        int maxhp;
        int level;
        int gil;
        int antidote;
        int phoenixdownI;
        f >> maxhp >> level >> phoenixdownI >> gil >> antidote;
        listknights[i] = BaseKnight::create(id, maxhp, level, gil, antidote, phoenixdownI);
    }
    f.close();
}
ArmyKnights::~ArmyKnights() {
    delete[] listknights;
}
bool ArmyKnights::fight(BaseOpponent* opponent) {
    BaseKnight* knight = this->lastKnight();
    bool alive = true;
    switch (opponent->typeOpponent()) {
        case MADBEAR: {
            if (knight->getLevel() >= opponent->getLevelO() || knight->getKnightType() == PALADIN || knight->getKnightType() == LANCELOT) {
                knight->increaseGil(opponent->getNumGil());
                if (knight->getGil() > 999) {
                    gilAdd = knight->getGil() - 999;
                    knight->setGil(999);
                }
                alive = true;
            }
            else {
                knight->decreaseHP(opponent->damage(knight->getLevel()));
                if (knight->getBag()->get(PHOENIXDOWN) != nullptr) {
                    knight->getBag()->get(PHOENIXDOWN)->use(knight);
                    knight->getBag()->useItem();
                    alive = true;
                }
                if (knight->getHP() <= 0) {
                    if (knight->getGil() >= 100) {
                        knight->decreaseGil(100);
                        knight->setHP(knight->getMaxHP() / 2);
                        alive = true;
                    }
                    else {
                        alive = false;
                    }
                }
                else {
                    alive = true;
                }
                if (knight->getHP() <= 0) {
                    alive = false;
                }
            }
            break;
        }
        case BANDIT: {
            if (knight->getLevel() >= opponent->getLevelO() || knight->getKnightType() == PALADIN || knight->getKnightType() == LANCELOT) {
                knight->increaseGil(opponent->getNumGil());
                if (knight->getGil() > 999) {
                    gilAdd = knight->getGil() - 999;
                    knight->setGil(999);
                }
                alive = true;
            }
            else {
                knight->decreaseHP(opponent->damage(knight->getLevel()));
                if (knight->getBag()->get(PHOENIXDOWN) != nullptr) {
                    knight->getBag()->get(PHOENIXDOWN)->use(knight);
                    knight->getBag()->useItem();
                    alive = true;
                }
                if (knight->getHP() <= 0) {
                    if (knight->getGil() >= 100) {
                        knight->decreaseGil(100);
                        knight->setHP(knight->getMaxHP() / 2);
                        alive = true;
                    }
                    else {
                        alive = false;
                    }
                }
                else {
                    alive = true;
                }
                if (knight->getHP() <= 0) {
                    alive = false;
                }
            }
            break;
        }
        case LORDLUPIN: {
            if (knight->getLevel() >= opponent->getLevelO() || knight->getKnightType() == PALADIN || knight->getKnightType() == LANCELOT) {
                knight->increaseGil(opponent->getNumGil());
                if (knight->getGil() > 999) {
                    gilAdd = knight->getGil() - 999;
                    knight->setGil(999);
                }
                alive = true;
            }
            else {
                knight->decreaseHP(opponent->damage(knight->getLevel()));
                if (knight->getBag()->get(PHOENIXDOWN) != nullptr) {
                    knight->getBag()->get(PHOENIXDOWN)->use(knight);
                    knight->getBag()->useItem();
                    alive = true;
                }
                if (knight->getHP() <= 0) {
                    if (knight->getGil() >= 100) {
                        knight->decreaseGil(100);
                        knight->setHP(knight->getMaxHP() / 2);
                        alive = true;
                    }
                    else {
                        alive = false;
                    }
                }
                else {
                    alive = true;
                }
                if (knight->getHP() <= 0) {
                    alive = false;
                }
            }
            break;
        }
        case ELF: {
            if (knight->getLevel() >= opponent->getLevelO() || knight->getKnightType() == PALADIN || knight->getKnightType() == LANCELOT) {
                knight->increaseGil(opponent->getNumGil());
                if (knight->getGil() > 999) {
                    gilAdd = knight->getGil() - 999;
                    knight->setGil(999);
                }
                alive = true;
            }
            else {
                knight->decreaseHP(opponent->damage(knight->getLevel()));
                if (knight->getBag()->get(PHOENIXDOWN) != nullptr) {
                    knight->getBag()->get(PHOENIXDOWN)->use(knight);
                    knight->getBag()->useItem();
                    alive = true;
                }
                if (knight->getHP() <= 0) {
                    if (knight->getGil() >= 100) {
                        knight->decreaseGil(100);
                        knight->setHP(knight->getMaxHP() / 2);
                        alive = true;
                    }
                    else {
                        alive = false;
                    }
                }
                else {
                    alive = true;
                }
                if (knight->getHP() <= 0) {
                    alive = false;
                }
            }
            break;
        }
        case TROLL: {
            if (knight->getLevel() >= opponent->getLevelO() || knight->getKnightType() == PALADIN || knight->getKnightType() == LANCELOT) {
                knight->increaseGil(opponent->getNumGil());
                if (knight->getGil() > 999) {
                    gilAdd = knight->getGil() - 999;
                    knight->setGil(999);
                }
                alive = true;
            }
            else {
                knight->decreaseHP(opponent->damage(knight->getLevel()));
                if (knight->getBag()->get(PHOENIXDOWN) != nullptr) {
                    knight->getBag()->get(PHOENIXDOWN)->use(knight);
                    knight->getBag()->useItem();
                    alive = true;
                }
                if (knight->getHP() <= 0) {
                    if (knight->getGil() >= 100) {
                        knight->decreaseGil(100);
                        knight->setHP(knight->getMaxHP() / 2);
                        alive = true;
                    }
                    else {
                        alive = false;
                    }
                }
                else {
                    alive = true;
                }
                if (knight->getHP() <= 0) {
                    alive = false;
                }
            }
            break;
        }
        case TORNBERY: {
            if (knight->getLevel() >= opponent->getLevelO()) {
                knight->levelUp();
                alive = true;
            }
            else {
                if (knight->getKnightType() == DRAGON) {
                    alive = true;
                }
                else {
                    knight->setPoison(1);
                    if (knight->getBag()->get(ANTIDOTE) != nullptr) {
                        knight->getBag()->get(ANTIDOTE)->use(knight);
                        knight->getBag()->useItem();
                        alive = true;
                    }
                    else {
                        if (knight->getBag()->numItem() > 3) {
                            for (int i = 0; i < 3; i++) {
                                knight->getBag()->useItem();
                            }
                        }
                        else {
                            knight->getBag()->clearBag();
                        }
                        knight->decreaseHP(10);
                        if (knight->getBag()->get(PHOENIXDOWN) != nullptr) {
                            knight->getBag()->get(PHOENIXDOWN)->use(knight);
                            knight->getBag()->useItem();
                            alive = true;
                        }
                        if (knight->getHP() <= 0) {
                            if (knight->getGil() >= 100) {
                                knight->decreaseGil(100);
                                knight->setHP(knight->getMaxHP() / 2);
                                alive = true;
                            }
                            else {
                                alive = false;
                            }
                        }
                        else {
                            alive = true;
                        }
                        if (knight->getHP() <= 0) {
                            alive = false;
                        }
                    }
                }
            }
            break;
        }
        case QUEENOFCARDS: {
            if (knight->getLevel() >= opponent->getLevelO()) {
                knight->doubleGil();
                if (knight->getGil() > 999) {
                    gilAdd = knight->getGil() - 999;
                    knight->setGil(999);
                }
                alive = true;
            }
            else {
                if (knight->getKnightType() == PALADIN) {
                    alive = true;
                }
                else {
                    knight->divideGil();
                    alive = true;
                }
            }
            break;
        }
        case NINADERINGS: {
            if (knight->getKnightType() == PALADIN) {
                if (knight->getHP() < (knight->getMaxHP() / 3)) {
                    knight->increaseHP(knight->getMaxHP() / 5);
                    alive = true;
                }
            }
            else {
                if (knight->getGil() >= 50) {
                    if (knight->getHP() < (knight->getMaxHP() / 3)) {
                        knight->increaseHP(knight->getMaxHP() / 5);
                        knight->decreaseGil(50);
                        alive = true;
                    }
                }
            }
            break;
        }
        case DURIANGARDEN: {
            knight->setHP(knight->getMaxHP());
            alive = true;
            break;
        }
        case OMEGAWEAPON: {
            if ((knight->getLevel() == 10 && knight->getHP() == knight->getMaxHP()) || knight->getKnightType() == DRAGON) {
                winOmegaWeapon = 1;
                knight->setLevel(10);
                knight->setGil(999);
                alive = true;
            }
            else {
                knight->setHP(0);
                if (knight->getBag()->get(PHOENIXDOWN) != nullptr) {
                    knight->getBag()->get(PHOENIXDOWN)->use(knight);
                    knight->getBag()->useItem();
                    alive = true;
                }
                if (knight->getHP() <= 0) {
                    if (knight->getGil() >= 100) {
                        knight->decreaseGil(100);
                        knight->setHP(knight->getMaxHP() / 2);
                        alive = true;
                    }
                    else {
                        alive = false;
                    }
                }
                else {
                    alive = true;
                }
                if (knight->getHP() <= 0) {
                    alive = false;
                }
            }
            break;
        }
        case HADES: {
            if (knight->getLevel() == 10 || (knight->getLevel() >= 8 && knight->getKnightType() == PALADIN)) {
                winHades = 1;
                PaladinShield = 1;
                alive = true;
            }
            else {
                knight->setHP(0);
                if (knight->getBag()->get(PHOENIXDOWN) != nullptr) {
                    knight->getBag()->get(PHOENIXDOWN)->use(knight);
                    knight->getBag()->useItem();
                    alive = true;
                }
                if (knight->getHP() <= 0) {
                    if (knight->getGil() >= 100) {
                        knight->decreaseGil(100);
                        knight->setHP(knight->getMaxHP() / 2);
                        alive = true;
                    }
                    else {
                        alive = false;
                    }
                }
                else {
                    alive = true;
                }
                if (knight->getHP() <= 0) {
                    alive = false;
                }
            }
            break;
        }
    }
    return alive;
}
bool ArmyKnights::die() {
    numknights--;
    if (numknights == 0) {
        return false;
    }
    else {
        BaseKnight** temp = listknights;
        BaseKnight** newListknights = new BaseKnight * [numknights];
        for (int i = 0; i < numknights; i++) {
            newListknights[i] = listknights[i];
        }
        listknights = newListknights;
        delete[] temp;
        return true;
    }
}
bool ArmyKnights::die(int position) {
    if (position == 0) {
        numknights = 0;
        return false;
    }
    else {
        numknights--;
        BaseKnight** temp = listknights;
        BaseKnight** newListknights = new BaseKnight * [numknights];
        for (int i = 0; i < position; i++) {
            newListknights[i] = listknights[i];
        }
        for (int i = (position + 1); i < (numknights + 1); i++) {
            newListknights[i - 1] = listknights[i];
        }
        listknights = newListknights;
        delete[] temp;
        return true;
    }
}
bool ArmyKnights::adventure(Events* events) {
    BaseOpponent* opponent = nullptr;
    bool win = true;
    for (int i = 0; i < events->count(); i++) {
        gilAdd = 0;
        switch (events->get(i)) {
            case 1: {
                opponent = new MadBear(i, events->get(i));
                /*while (this->lastKnight() != nullptr) {
                    if (this->fight(opponent)) {
                        break;
                    }
                    else {
                        if (!(this->die())) { 
                            win = false;
                        }
                    }
                }*/
                if (!(this->fight(opponent))) {
                    if (!(this->die())) {
                        win = false;
                    }
                }
                break;
            }
            case 2: {
                opponent = new Bandit(i, events->get(i));
                /*while (this->lastKnight() != nullptr) {
                    if (this->fight(opponent)) {
                        break;
                    }
                    else {
                        if (!(this->die())) {
                            win = false;
                        }
                    }
                }*/
                if (!(this->fight(opponent))) {
                    if (!(this->die())) {
                        win = false;
                    }
                }
                break;
            }
            case 3: {
                opponent = new LordLupin(i, events->get(i));
                /*while (this->lastKnight() != nullptr) {
                    if (this->fight(opponent)) {
                        break;
                    }
                    else {
                        if (!(this->die())) {
                            win = false;
                        }
                    }
                }*/
                if (!(this->fight(opponent))) {
                    if (!(this->die())) {
                        win = false;
                    }
                }
                break;
            }
            case 4: {
                opponent = new Elf(i, events->get(i));
                /*while (this->lastKnight() != nullptr) {
                    if (this->fight(opponent)) {
                        break;
                    }
                    else {
                        if (!(this->die())) {
                            win = false;
                        }
                    }
                }*/
                if (!(this->fight(opponent))) {
                    if (!(this->die())) {
                        win = false;
                    }
                }
                break;
            }
            case 5: {
                opponent = new Troll(i, events->get(i));
                /*while (this->lastKnight() != nullptr) {
                    if (this->fight(opponent)) {
                        break;
                    }
                    else {
                        if (!(this->die())) {
                            win = false;
                        }
                    }
                }*/
                if (!(this->fight(opponent))) {
                    if (!(this->die())) {
                        win = false;
                    }
                }
                break;
            }
            case 6: {
                opponent = new Tornbery(i, events->get(i));
                /*while (this->lastKnight() != nullptr) {
                    if (this->fight(opponent)) {
                        break;
                    }
                    else {
                        if (!(this->die())) {
                            win = false;
                        }
                    }
                }*/
                if (!(this->fight(opponent))) {
                    if (!(this->die())) {
                        win = false;
                    }
                }
                break;
            }
            case 7: {
                opponent = new QueenOfCards(i, events->get(i));
                this->fight(opponent);
                break;
            }
            case 8: {
                opponent = new NinaDeRings;
                this->fight(opponent);
                break;
            }
            case 9: {
                opponent = new DurianGarden;
                this->fight(opponent);
                break;
            }
            case 10: {
                if (winOmegaWeapon == 0) {
                    opponent = new OmegaWeapon;
                    /*while (this->lastKnight() != nullptr) {
                        if (this->fight(opponent)) {
                            break;
                        }
                        else {
                            if (!(this->die())) {
                                win = false;
                            }
                        }
                    }*/
                    if (!(this->fight(opponent))) {
                        if (!(this->die())) {
                            win = false;
                        }
                    }
                }
                break;
            }
            case 11: {
                if (winHades == 0) {
                    opponent = new Hades;
                    /*while (this->lastKnight() != nullptr) {
                        if (this->fight(opponent)) {
                            break;
                        }
                        else {
                            if (!(this->die())) {
                                win = false;
                            }
                        }
                    }*/
                    if (!(this->fight(opponent))) {
                        if (!(this->die())) {
                            win = false;
                        }
                    }
                }
                break;
            }
            case 112: {
                BaseItem* item = new PhoenixDownII;
                for (int i = numknights - 1; i >= 0; i--) {
                    if (listknights[i]->getBag()->insertFirst(item)) {
                        break;
                    }
                    else {
                        continue;
                    }
                }
                break;
            }
            case 113: {
                BaseItem* item = new PhoenixDownIII;
                for (int i = numknights - 1; i >= 0; i--) {
                    if (listknights[i]->getBag()->insertFirst(item)) {
                        break;
                    }
                    else {
                        continue;
                    }
                }
                break;
            }
            case 114: {
                BaseItem* item = new PhoenixDownIV;
                for (int i = numknights - 1; i >= 0; i--) {
                    if (listknights[i]->getBag()->insertFirst(item)) {
                        break;
                    }
                    else {
                        continue;
                    }
                }
                break;
            }
            case 95: {
                PaladinShield = 1;
                break;
            }
            case 96: {
                LancelotSpear = 1;
                break;
            }
            case 97: {
                GuinevereHair = 1;
                break;
            }
            case 98: {
                if (this->hasPaladinShield() && this->hasLancelotSpear() && this->hasGuinevereHair()) {
                    ExcaliburSword = 1;
                }
                break;
            }
            case 99: {
                if (this->hasExcaliburSword()) {
                    win = true;
                }
                else if (this->hasPaladinShield() && this->hasLancelotSpear() && this->hasGuinevereHair()) {
                    int UltimeciaHP = 5000;
                    for (int i = numknights - 1; i >= 0; i--) {
                        if (listknights[i]->getKnightType() == NORMAL) {
                            if (i == 0) {
                                if (UltimeciaHP > 0) {
                                    this->die(i);
                                    win = false;
                                }
                            }
                            else {
                                continue;
                            }
                        }
                        else {
                            switch (listknights[i]->getKnightType()) {
                                case PALADIN: {
                                    UltimeciaHP -= listknights[i]->getHP() * listknights[i]->getLevel() * 6 / 100;
                                    break;
                                }
                                case LANCELOT: {
                                    UltimeciaHP -= listknights[i]->getHP() * listknights[i]->getLevel() * 5 / 100;                         
                                    break;
                                }
                                case DRAGON: {
                                    UltimeciaHP -= listknights[i]->getHP() * listknights[i]->getLevel() * 75 / 1000;
                                    break;
                                }
                            }
                            if (UltimeciaHP > 0) {
                                if (!(this->die(i))) {
                                    win = false;
                                }
                            }
                            else {
                                win = true;
                                break;
                            }
                        }
                    }
                }
                else {
                    numknights = 0;
                    win = false;
                }
                break;
            }
        }
        this->printInfo();
        if (!win) {
            break;
        }
        if (gilAdd > 0) {
            for (int i = numknights - 2; i >= 0; i--) {
                listknights[i]->increaseGil(gilAdd);
                if (listknights[i]->getGil() > 999) {
                    gilAdd = listknights[i]->getGil() - 999;
                    listknights[i]->setGil(999);
                }
                else {
                    gilAdd = 0;
                    break;
                }
            }
        }
    }
    return win;
}
int ArmyKnights::count() const {
    return numknights;
}
BaseKnight* ArmyKnights::lastKnight() const {
    if (this->count() > 0) {
        return listknights[this->count() - 1];
    }
    else {
        return nullptr;
    }
}
bool ArmyKnights::hasPaladinShield() const {
    return PaladinShield == 1;
}
bool ArmyKnights::hasLancelotSpear() const {
    return LancelotSpear == 1;
}
bool ArmyKnights::hasGuinevereHair() const {
    return GuinevereHair == 1;
}
bool ArmyKnights::hasExcaliburSword() const {
    return ExcaliburSword == 1;
}
/* * * END implementation of class ArmyKnights * * */
/*-----------------------------------------------------------------------------------------------------------*/
/* * * BEGIN implementation of class BaseItem * * */
//Antidote
ItemType Antidote::itemType() {
    return ANTIDOTE;
}
bool Antidote::canUse(BaseKnight* knight) {
    if (knight->getPoison() == 1) {
        return true;
    }
    else {
        return false;
    }
}
void Antidote::use(BaseKnight* knight) {
    knight->setPoison(0);
}
//PhoenixDownI
ItemType PhoenixDownI::itemType() {
    return PHOENIXDOWNI;
}
bool PhoenixDownI::canUse(BaseKnight* knight) {
    if (knight->getHP() <= 0) {
        return true;
    }
    else {
        return false;
    }
}
void PhoenixDownI::use(BaseKnight* knight) {
    knight->setHP(knight->getMaxHP());
}
//PhoenixDownII
ItemType PhoenixDownII::itemType() {
    return PHOENIXDOWNII;
}
bool PhoenixDownII::canUse(BaseKnight* knight) {
    if (knight->getHP() < (knight->getMaxHP() / 4)) {
        return true;
    }
    else {
        return false;
    }
}
void PhoenixDownII::use(BaseKnight* knight) {
    knight->setHP(knight->getMaxHP());
}
//PhoenixDownIII
ItemType PhoenixDownIII::itemType() {
    return PHOENIXDOWNIII;
}
bool PhoenixDownIII::canUse(BaseKnight* knight) {
    if (knight->getHP() < (knight->getMaxHP() / 3)) {
        return true;
    }
    else {
        return false;
    }
}
void PhoenixDownIII::use(BaseKnight* knight) {
    if (knight->getHP() <= 0) {
        knight->setHP(knight->getMaxHP() / 3);
    }
    else {
        knight->increaseHP(knight->getMaxHP() / 4);
    }
}
//PhoenixDownIV
ItemType PhoenixDownIV::itemType() {
    return PHOENIXDOWNIV;
}
bool PhoenixDownIV::canUse(BaseKnight* knight) {
    if (knight->getHP() < (knight->getMaxHP() / 2)) {
        return true;
    }
    else {
        return false;
    }
}
void PhoenixDownIV::use(BaseKnight* knight) {
    if (knight->getHP() <= 0) {
        knight->setHP(knight->getMaxHP() / 2);
    }
    else {
        knight->increaseHP(knight->getMaxHP() / 5);
    }
}
/* * * END implementation of class BaseItem * * */
/*-----------------------------------------------------------------------------------------------------------*/
/* * * BEGIN implementation of class Events * * */
Events::Events(const string& file_events) {
    ifstream f;
    f.open(file_events);
    f >> numevents;
    listevents = new int[numevents];
    for (int i = 0; i < numevents; i++) {
        f >> listevents[i];
    }
    f.close();
}
Events::~Events() {
    delete[] listevents;
}
int Events::count() const {
    return numevents;
}
int Events::get(int i) const {
    return listevents[i];
}
/* * * END implementation of class Events * * */
/*-----------------------------------------------------------------------------------------------------------*/
/* * * BEGIN implementation of class KnightAdventure * * */
KnightAdventure::KnightAdventure() {
    armyKnights = nullptr;
    events = nullptr;
}
KnightAdventure::~KnightAdventure() {
    delete armyKnights;
    delete events;
}
void KnightAdventure::loadArmyKnights(const string& file_armyknights) {
    armyKnights = new ArmyKnights(file_armyknights);
}
void KnightAdventure::loadEvents(const string& file_events) {
    events = new Events(file_events);
}
void KnightAdventure::run() {
    armyKnights->printResult(armyKnights->adventure(events));
}
/* * * END implementation of class KnightAdventure * * */