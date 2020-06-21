#include<iostream>
#include<vector>
#include<math.h>
#include<ctime>
#include<fstream>

using namespace std;

enum nutrType{PREDATOR, SCAVANGER, MINERAL_EATER, HERBIVOROUS};
enum breedingType{DIVISION, BUDDING, PAIRING};
enum priority{NUTRITION, BREEDING, NOTHING};

const int WORLD_WIDTH = 40;
const int WORLD_HEIGHT = 40;
const int MUTATION_POWER = 20;
const int WORLD_RICH_LEVEL = 10;
const int RESOURCES_STABILIY_RATE = 1000;

struct Pos{
    int x;
    int y;
};

void writePos(Pos curPos);
ofstream d1;

class Bot;
struct WorldPos{
    int x;
    int y;
    int rottenQuant = 0;
    int plantQuant;
    int mineralsQuant;
    Bot* botOnThisPlace = nullptr;
};

struct botParam{
    int curEnergy;
    priority curPriority;
    int curAge;
    int maxEnergy;
    int breedEnergy;
    int breedAge;
    int nutritionNeedEnergy;
    nutrType nutr;
    int moveEnergySpend;
    breedingType breed;
    int viewingRange;
    int partnerSimilarityLevel;
    int power;
};

struct botForm{
    botParam curParameters;
    vector<Pos> allPositions;
};

WorldPos world1[WORLD_HEIGHT][WORLD_WIDTH];
Bot* allBots[WORLD_HEIGHT*WORLD_WIDTH] = {nullptr};
botForm form;


void fillWorld(int richSeed, bool refill){
    for(int i = 0; i < WORLD_HEIGHT; i++){
        for(int j = 0; j < WORLD_WIDTH; j++){
            if(!refill == true){
                world1[i][j].x = j;
                world1[i][j].y = i;
                world1[i][j].plantQuant = trunc(rand()%richSeed);
                world1[i][j].mineralsQuant = trunc(rand()%richSeed);
                world1[i][j].rottenQuant = 0;
            }
            else {
                world1[i][j].plantQuant = trunc(rand()%richSeed);
                world1[i][j].mineralsQuant = trunc(rand()%richSeed);
            }
        }
    }
}


class Base{
public:

    Pos curPos;
    botParam curParameters;
};

class CreatureAbleToEat : virtual public Base{
    void eatBot(int x, int y);
    void updPos();
    Pos seekFoodProvByWorld(nutrType nutr){
        Pos target{this->curPos.x, this->curPos.y};
        for(int i = this->curPos.y-this->curParameters.viewingRange; i <= this->curPos.y+this->curParameters.viewingRange; i++){
            for(int j = this->curPos.x-this->curParameters.viewingRange; j <= this->curPos.x+this->curParameters.viewingRange; j++){

                if(i > 0 && j > 0 && i < WORLD_HEIGHT && j < WORLD_WIDTH && nutr == MINERAL_EATER && world1[i][j].mineralsQuant > world1[target.y][target.x].mineralsQuant){
                    target.x = j;
                    target.y = i;
                }
                if(i > 0 && j > 0 && i < WORLD_HEIGHT && j < WORLD_WIDTH && nutr == HERBIVOROUS && world1[i][j].plantQuant > world1[target.y][target.x].plantQuant){
                    target.x = j;
                    target.y = i;
                }
                if(i > 0 && j > 0 && i < WORLD_HEIGHT && j < WORLD_WIDTH && nutr == SCAVANGER && world1[i][j].rottenQuant > world1[target.y][target.x].rottenQuant){
                    target.x = j;
                    target.y = i;
                }
            }
        }
        return target;
    }
    public:
    void mineralEaterNutrition(){
        int tryCounter = this->curParameters.viewingRange+5;
        Pos foodPos;
        foodPos = seekFoodProvByWorld(MINERAL_EATER);
        while(tryCounter > 0){
            if(this->curPos.x < foodPos.x && world1[curPos.y][curPos.x+1].botOnThisPlace == nullptr){
                curPos.x++;
                this->curParameters.curEnergy-=this->curParameters.moveEnergySpend;
                updPos();
            }
            if(this->curPos.x > foodPos.x && world1[curPos.y][curPos.x-1].botOnThisPlace == nullptr){
                curPos.x--;
                this->curParameters.curEnergy-=this->curParameters.moveEnergySpend;
                updPos();
            }
            if(this->curPos.y < foodPos.y && world1[curPos.y+1][curPos.x].botOnThisPlace == nullptr){
                curPos.y++;
                this->curParameters.curEnergy-=this->curParameters.moveEnergySpend;
                updPos();
            }
            if(this->curPos.y > foodPos.y && world1[curPos.y-1][curPos.x].botOnThisPlace == nullptr){
                curPos.y--;
                this->curParameters.curEnergy-=this->curParameters.moveEnergySpend;
                updPos();
            }
            if(this->curPos.x == foodPos.x && this->curPos.y == foodPos.y){
                this->curParameters.curEnergy += world1[foodPos.y][foodPos.x].mineralsQuant;
                this->curParameters.curEnergy--;
                updPos();
                break;
            }
            else {
                if(tryCounter < 5){
                    this->curParameters.curEnergy += world1[curPos.y][curPos.x].mineralsQuant;
                    this->curParameters.curEnergy--;
                    updPos();
                    break;
                }
            }
            tryCounter--;
        }
    }
    void herbivorousNutrition(){
        int tryCounter = this->curParameters.viewingRange+5;
        Pos foodPos;
        foodPos = seekFoodProvByWorld(HERBIVOROUS);
        while(tryCounter > 0){
            if(this->curPos.x < foodPos.x && world1[curPos.y][curPos.x+1].botOnThisPlace == nullptr){
                curPos.x++;
                this->curParameters.curEnergy-=this->curParameters.moveEnergySpend;
                updPos();
            }
            if(this->curPos.x > foodPos.x && world1[curPos.y][curPos.x-1].botOnThisPlace == nullptr){
                curPos.x--;
                this->curParameters.curEnergy-=this->curParameters.moveEnergySpend;
                updPos();
            }
            if(this->curPos.y < foodPos.y && world1[curPos.y+1][curPos.x].botOnThisPlace == nullptr){
                curPos.y++;
                this->curParameters.curEnergy-=this->curParameters.moveEnergySpend;
                updPos();
            }
            if(this->curPos.y > foodPos.y && world1[curPos.y-1][curPos.x].botOnThisPlace == nullptr){
                curPos.y--;
                this->curParameters.curEnergy-=this->curParameters.moveEnergySpend;
                updPos();
            }
            if(this->curPos.x == foodPos.x && this->curPos.y == foodPos.y){
                this->curParameters.curEnergy += world1[foodPos.y][foodPos.x].plantQuant;
                this->curParameters.curEnergy--;
                updPos();
                break;
            }
            else {
                if(tryCounter < 5){
                    this->curParameters.curEnergy += world1[curPos.y][curPos.x].plantQuant;
                    this->curParameters.curEnergy--;
                    updPos();
                    break;
                }
            }
            tryCounter--;
        }
    }
    void scavangerNutrition(){
        int tryCounter = this->curParameters.viewingRange+5;
        Pos foodPos;
        foodPos = seekFoodProvByWorld(SCAVANGER);
        while(tryCounter > 0){
            if(this->curPos.x < foodPos.x && world1[curPos.y][curPos.x+1].botOnThisPlace == nullptr){
                curPos.x++;
                this->curParameters.curEnergy-=this->curParameters.moveEnergySpend;
                updPos();
            }
            if(this->curPos.x > foodPos.x && world1[curPos.y][curPos.x-1].botOnThisPlace == nullptr){
                curPos.x--;
                this->curParameters.curEnergy-=this->curParameters.moveEnergySpend;
                updPos();
            }
            if(this->curPos.y < foodPos.y && world1[curPos.y+1][curPos.x].botOnThisPlace == nullptr){
                curPos.y++;
                this->curParameters.curEnergy-=this->curParameters.moveEnergySpend;
                updPos();
            }
            if(this->curPos.y > foodPos.y && world1[curPos.y-1][curPos.x].botOnThisPlace == nullptr){
                curPos.y--;
                this->curParameters.curEnergy-=this->curParameters.moveEnergySpend;
                updPos();
            }
            if(this->curPos.x == foodPos.x && this->curPos.y == foodPos.y){
                this->curParameters.curEnergy += world1[foodPos.y][foodPos.x].rottenQuant;
                this->curParameters.curEnergy--;
                world1[foodPos.y][foodPos.x].rottenQuant=0;
                updPos();
                break;
            }
            else {
                if(tryCounter < 5){
                    this->curParameters.curEnergy += world1[curPos.y][curPos.x].rottenQuant;
                    this->curParameters.curEnergy--;
                    world1[foodPos.y][foodPos.x].rottenQuant=0;
                    updPos();
                    break;
                }
            }
            tryCounter--;
        }
    }
    Pos seekPredatorTarget();
    void predatorNutrition();
};
class CreatureAbleToBreed : virtual public Base{
    botParam mutateGenom(botParam tempGenom){
        int mutQuant = trunc(rand()%3), mutTarget;
        float mutLevel;
        nutrType prevNutr[MUTATION_POWER]= {tempGenom.nutr};
        for(int i = 0; i < 4; i++){
            if(i != tempGenom.nutr){
                prevNutr[i] = static_cast<nutrType>(i);
            }
        }
        breedingType prevBreed[MUTATION_POWER]= {tempGenom.breed};
        for(int i = 0; i < 3; i++){
            if(i != tempGenom.breed){
                prevBreed[i] = static_cast<breedingType>(i);
            }
        }
        for(int i = 0; i <= mutQuant; i++){
            int test;
            mutTarget = trunc(rand()%10);
            mutLevel = trunc(rand()%MUTATION_POWER)-MUTATION_POWER/2;
            if(mutTarget == 0)tempGenom.maxEnergy=trunc(tempGenom.maxEnergy*(1+mutLevel/10));

            if(mutTarget == 1)tempGenom.breedEnergy=trunc(tempGenom.breedEnergy*(1+mutLevel/10));

            if(mutTarget == 2)tempGenom.breedAge=trunc(tempGenom.breedAge*(1+mutLevel/10));

            if(mutTarget == 3)tempGenom.nutritionNeedEnergy=trunc(tempGenom.nutritionNeedEnergy*(1+mutLevel/10));

            if(mutTarget == 4){
                tempGenom.nutr= prevNutr[static_cast<int>(trunc(rand()%MUTATION_POWER))];
            }

            if(mutTarget == 5)tempGenom.moveEnergySpend=trunc(tempGenom.moveEnergySpend*(1+mutLevel/10));

            if(mutTarget == 6){
                test = static_cast<int>(trunc(rand()%MUTATION_POWER));
                tempGenom.breed= prevBreed[static_cast<int>(trunc(rand()%MUTATION_POWER))];
            }

            if(mutTarget == 7)tempGenom.viewingRange=trunc(tempGenom.viewingRange*(1+mutLevel/10));

            if(mutTarget == 8)tempGenom.partnerSimilarityLevel=trunc(tempGenom.partnerSimilarityLevel*(1+mutLevel/10));

            if(mutTarget == 9)tempGenom.power=trunc(tempGenom.power*(1+mutLevel/10));

        }
        return tempGenom;
    }
    botParam genom1, genom2;
public:
    void division();
};
class Bot : public CreatureAbleToEat,public CreatureAbleToBreed{
    public:
    void Construct(botParam par, int x, int y){
        world1[y][x].botOnThisPlace = this;
        for(int i = 0 ; i < WORLD_HEIGHT*WORLD_WIDTH; i++){
            if(allBots[i] == nullptr){
                allBots[i] = this;
                break;
            }
        }
        world1[y][x].botOnThisPlace->curParameters = par;
        this->curPos.x = x;
        this->curPos.y = y;
    }
    Bot(botParam par, int x, int y){
        Construct(par, x,y);
    };
    ~Bot(){

    }

    private:
        void checkPriority(){
            if(this->curParameters.curEnergy <= this->curParameters.nutritionNeedEnergy){this->curParameters.curPriority = NUTRITION;}
            else{
                if(this->curParameters.curAge >= this->curParameters.breedAge){this->curParameters.curPriority = BREEDING;}
                else {
                    this->curParameters.curPriority = NOTHING;
                }
            }
        };

        void nutrition() {
            switch (curParameters.nutr) {
                case PREDATOR: predatorNutrition();break;
                case SCAVANGER: scavangerNutrition();break;
                case MINERAL_EATER: mineralEaterNutrition(); break;
                case HERBIVOROUS: herbivorousNutrition(); break;
            }
        }
        void breeding() {
            division();
        }
        void waiting() {
            this->curParameters.curEnergy--;
            this->curParameters.curAge++;
        }

    public:
        void action(){

            checkPriority();
            if(curParameters.curPriority == BREEDING){

                breeding();
                this->curParameters.curAge++;
                d1.close();
                return;
            }
            if(curParameters.curPriority == NUTRITION){
                nutrition();
                this->curParameters.curAge++;

                return;
            }

            if(curParameters.curPriority == NOTHING){
                waiting();
                this->curParameters.curAge++;

                return;
            }
        }
    };

void updateScreen(){
//заглушка
}

void removeFromAllBots(Bot* temp){
    for(int i = 0; i < WORLD_WIDTH*WORLD_HEIGHT; i++){
        if(allBots[i] == temp){
            allBots[i] = nullptr;
            break;
        }
    }
}

void CreatureAbleToEat::eatBot(int x, int y)
{
    if(this->curParameters.curEnergy + world1[y][x].botOnThisPlace->curParameters.curEnergy <= this->curParameters.maxEnergy){
        this->curParameters.curEnergy += world1[world1[y][x].botOnThisPlace->curPos.y][world1[y][x].botOnThisPlace->curPos.x].botOnThisPlace->curParameters.curEnergy;
    }
    else {
        this->curParameters.curEnergy = this->curParameters.maxEnergy;
        world1[y][x].rottenQuant += this->curParameters.curEnergy + world1[y][x].botOnThisPlace->curParameters.curEnergy - this->curParameters.maxEnergy;
    }
}


void sendMap(){
    d1.open("D:/Server/domains/htdocs/test.ru/public_html/test.txt");
    for(int i = 0; i < WORLD_WIDTH*WORLD_HEIGHT; i++){
        if(allBots[i] != nullptr){
            d1 << allBots[i]->curPos.x << ',';
            d1 << allBots[i]->curPos.y << ',';
            d1 << allBots[i]->curParameters.curEnergy << ',';
            d1 << allBots[i]->curParameters.curPriority << ',';
            d1 << allBots[i]->curParameters.curAge << ',';
            d1 << allBots[i]->curParameters.maxEnergy << ',';
            d1 << allBots[i]->curParameters.breedEnergy << ',';
            d1 << allBots[i]->curParameters.breedAge << ',';
            d1 << allBots[i]->curParameters.nutritionNeedEnergy << ',';
            d1 << allBots[i]->curParameters.nutr << ',';
            d1 << allBots[i]->curParameters.moveEnergySpend << ',';
            d1 << allBots[i]->curParameters.viewingRange;
            d1 << endl;
        }
    }
    d1.close();
}


void CreatureAbleToEat::updPos(){//вынесено за класс чтобы работало приведение указателя на CreatureAbleToEat к указателю на Bot
        sendMap();
        for(int i = 0; i < WORLD_HEIGHT; i++){
            for(int j = 0; j < WORLD_WIDTH; j++){
                if(world1[i][j].botOnThisPlace == this) world1[i][j].botOnThisPlace = nullptr;
            }
        }
        world1[curPos.y][curPos.x].botOnThisPlace = static_cast<Bot*>(this);
        updateScreen();
    }

    Pos CreatureAbleToEat::seekPredatorTarget(){//вынесено за класс чтобы работать с полями класса Bot
        Pos target{this->curPos.x, this->curPos.y};
        bool targetNotDefault = false;
        for(int i = this->curPos.y-this->curParameters.viewingRange; i <= this->curPos.y+this->curParameters.viewingRange; i++){
            for(int j = this->curPos.x-this->curParameters.viewingRange; j <= this->curPos.x+this->curParameters.viewingRange; j++){

                if(i > 0 && j > 0  && i < WORLD_HEIGHT && j < WORLD_WIDTH && world1[i][j].botOnThisPlace != nullptr){
                    if(world1[i][j].botOnThisPlace->curParameters.power < world1[target.y][target.x].botOnThisPlace->curParameters.power){
                        target.x = j;
                        target.y = i;
                        targetNotDefault = true;
                    }
                }

            }
        }
        if(targetNotDefault){return target;}
        else return {-1, -1};
    }
    Pos checkNear(int x, int y){
        if(x+1 > 0 && y > 0 && x+1 < WORLD_WIDTH && y < WORLD_HEIGHT && world1[y][x+1].botOnThisPlace != nullptr && world1[y][x+1].botOnThisPlace->curParameters.power < world1[y][x].botOnThisPlace->curParameters.power){
            return {x+1,y};
        }
        else{
            if(x-1 > 0 && y > 0 && x-1 < WORLD_WIDTH && y < WORLD_HEIGHT && world1[y][x-1].botOnThisPlace != nullptr && world1[y][x-1].botOnThisPlace->curParameters.power < world1[y][x].botOnThisPlace->curParameters.power){
                return {x-1,y};
            }
            else{
                if(x > 0 && y+1 > 0 && x < WORLD_WIDTH && y+1 < WORLD_HEIGHT && world1[y+1][x].botOnThisPlace != nullptr && world1[y+1][x].botOnThisPlace->curParameters.power < world1[y][x].botOnThisPlace->curParameters.power){
                    return {x, y+1};
                }
                else{
                    if(x > 0 && y-1 > 0 && x < WORLD_WIDTH && y-1 < WORLD_HEIGHT && world1[y-1][x].botOnThisPlace != nullptr && world1[y-1][x].botOnThisPlace->curParameters.power < world1[y][x].botOnThisPlace->curParameters.power){
                        return {x,y-1};
                    }
                    else {
                        return {-1, -1};
                    }
                }
            }
        }
    }
    void CreatureAbleToEat::predatorNutrition(){ //вынесено за класс чтобы работать с полями класса Bot
        Pos foodPos = seekPredatorTarget();
        int tryCounter = this->curParameters.viewingRange+5;
        while(tryCounter > 0 && foodPos.x !=-1){
            if(this->curPos.x < foodPos.x && world1[this->curPos.y][this->curPos.x+1].botOnThisPlace == nullptr){
                this->curPos.x++;
                updPos();
            }
            if(this->curPos.y < foodPos.y && world1[this->curPos.y+1][this->curPos.x].botOnThisPlace == nullptr){
                this->curPos.y++;
                updPos();
            }
            if(this->curPos.x > foodPos.x && world1[this->curPos.y][this->curPos.x-1].botOnThisPlace == nullptr){
                this->curPos.x--;
                updPos();
            }
            if(this->curPos.y > foodPos.y && world1[this->curPos.y-1][this->curPos.x].botOnThisPlace == nullptr){
                this->curPos.y--;
                updPos();
            }
            tryCounter--;
        }

        if(this->curPos.x == foodPos.x+1 || this->curPos.x == foodPos.x-1 || this->curPos.y == foodPos.y+1 || this->curPos.y == foodPos.y-1){
            eatBot(foodPos.x, foodPos.y);
            removeFromAllBots(world1[foodPos.y][foodPos.x].botOnThisPlace);
            world1[foodPos.y][foodPos.x].botOnThisPlace = nullptr;
        }
        else {

            foodPos = checkNear(this->curPos.x, this->curPos.y);
            if(foodPos.x != -1){
                eatBot(foodPos.x, foodPos.y);
                removeFromAllBots(world1[foodPos.y][foodPos.x].botOnThisPlace);
                world1[foodPos.y][foodPos.x].botOnThisPlace = nullptr;
            }
        }
    };

    void CreatureAbleToBreed::division(){

        genom1 = this->curParameters;
        genom1.curEnergy = this->curParameters.curEnergy/2;
        genom1.curAge = 0;
        genom1 = mutateGenom(genom1);
        genom2 = this->curParameters;
        genom2.curEnergy = this->curParameters.curEnergy/2;
        genom2.curAge = 0;
        genom2 = mutateGenom(genom2);
        if(world1[curPos.y+1][curPos.x].botOnThisPlace == nullptr && curPos.y+1 != WORLD_HEIGHT){
            new Bot(genom1, curPos.x, curPos.y+1);
            this->curParameters=genom2;
            return;
        }
        if(world1[curPos.y-1][curPos.x].botOnThisPlace == nullptr && curPos.y-1 != 0){
            new Bot(genom1, curPos.x, curPos.y-1);
            this->curParameters=genom2;
            return;
        }
        if(world1[curPos.y][curPos.x+1].botOnThisPlace == nullptr && curPos.x+1 != WORLD_WIDTH){
            new Bot(genom1, curPos.x+1, curPos.y);
            this->curParameters=genom2;
            return;
        }
        if(world1[curPos.y][curPos.x-1].botOnThisPlace == nullptr && curPos.x-1 != 0){
            new Bot(genom1, curPos.x-1, curPos.y);
            this->curParameters=genom2;
            return;
        }
    }

    bool checkDeath(int i){
        if(allBots[i]->curParameters.curEnergy <= 0){
            world1[allBots[i]->curPos.y ][allBots[i]->curPos.x].rottenQuant+=allBots[i]->curParameters.maxEnergy/2;
            removeFromAllBots(world1[allBots[i]->curPos.y ][allBots[i]->curPos.x].botOnThisPlace);
            delete allBots[i];
            return true;
        }
        else {
            return false;
        }
    }

int main(){
    int counter;

    srand(time(NULL));
    fillWorld(WORLD_RICH_LEVEL, false);
    for(int i = 0; i < 400; i++){
        allBots[i] = nullptr;

    }
    botParam test{200, NUTRITION, 30, 120, 20, 20, 50, HERBIVOROUS, 1, DIVISION, 10, 5, 10};
    allBots[0] = new Bot(test, 10, 10);
    updateScreen();
    while(true){
        for(int i = 0; i < 400; i++){
            if(allBots[i] != nullptr && !checkDeath(i)){
                allBots[i]->action();
                updateScreen();
                counter++;
                if(counter == RESOURCES_STABILIY_RATE){
                    counter = 0;
                    fillWorld(WORLD_RICH_LEVEL, true);
                }
            }
        }
    }

}



