#include<iostream>
#include<vector>
#include<math.h>
#include<iomanip>
#include<ctime>

using namespace std;

enum nutrType{PREDATOR, SCAVANGER, MINERAL_EATER, HERBIVOROUS};
enum breedingType{DIVISION, BUDDING, PAIRING};
enum priority{NUTRITION, BREEDING, NOTHING};

const int WORLD_WIDTH = 20;
const int WORLD_HEIGHT = 20;
const int MUTATION_POWER = 20;


struct Pos{
    int x;
    int y;
};
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

WorldPos world1[WORLD_HEIGHT][WORLD_WIDTH];
Bot* allBots[WORLD_HEIGHT*WORLD_WIDTH] = {nullptr};

void fillWorld(int richSeed){

    for(int i = 0; i < WORLD_HEIGHT; i++){
        for(int j = 0; j < WORLD_WIDTH; j++){
            world1[i][j].x = j;
            world1[i][j].y = i;
            world1[i][j].plantQuant = trunc(rand()%richSeed);
            world1[i][j].mineralsQuant = trunc(rand()%richSeed);
        }
    }
}


class Base{
public:

    Pos curPos;
    botParam curParameters;
};

class CreatureAbleToEat : virtual public Base{
    void eatBot(int x, int y, int z);
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
                updPos();
                break;
            }
            else {
                if(tryCounter < 5){
                    this->curParameters.curEnergy += world1[curPos.y][curPos.x].mineralsQuant;
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
                updPos();
                break;
            }
            else {
                if(tryCounter < 5){
                    this->curParameters.curEnergy += world1[curPos.y][curPos.x].plantQuant;
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
                world1[foodPos.y][foodPos.x].rottenQuant=0;
                updPos();
                break;
            }
            else {
                if(tryCounter < 5){
                    this->curParameters.curEnergy += world1[curPos.y][curPos.x].rottenQuant;
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

        }

    public:
        void action(){
            checkPriority();
            if(curParameters.curPriority == NUTRITION){
                nutrition();
                this->curParameters.curAge++;
                return;
            }
            if(curParameters.curPriority == BREEDING){
                breeding();
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
    system("cls");
    for(int i = 0; i < WORLD_HEIGHT; i++){
        for(int j = 0; j < WORLD_WIDTH; j++){
            if(i == 0 || i == WORLD_HEIGHT-1 || j == 0 || j == WORLD_WIDTH-1){
                cout << '#';
            }
            else {
                if(world1[i][j].botOnThisPlace != nullptr) cout << 'O';
                if(world1[i][j].botOnThisPlace == nullptr)cout << ' ';
            }

        }
        cout << endl;
    }
}

void unbindBot(Bot* temp){
    for(int i = 0; i < WORLD_WIDTH*WORLD_HEIGHT; i++){
        if(allBots[i] == temp){
            allBots[i] = nullptr;
            break;
        }
    }
    for(int i = 0; i < WORLD_HEIGHT; i++){
        for(int j = 0; j < WORLD_WIDTH; j++){
            if(world1[i][j].botOnThisPlace == temp){
                world1[i][j].botOnThisPlace = nullptr;
            }
        }
    }
}

void CreatureAbleToEat::eatBot(int x, int y, int z)
{
    if(this->curParameters.curEnergy + world1[y][x].botOnThisPlace->curParameters.curEnergy <= this->curParameters.maxEnergy){
        this->curParameters.curEnergy += world1[world1[y][x].botOnThisPlace->curPos.y][world1[y][x].botOnThisPlace->curPos.x].botOnThisPlace->curParameters.curEnergy;
    }
    else {
        this->curParameters.curEnergy = this->curParameters.maxEnergy;
        world1[y][x].rottenQuant += this->curParameters.curEnergy + world1[y][x].botOnThisPlace->curParameters.curEnergy - this->curParameters.maxEnergy;
    }
}

void CreatureAbleToEat::updPos(){//вынесено за класс чтобы работало приведение указателя на CreatureAbleToEat к указателю на Bot
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

                if(i > 0 && j > 0 && world1[i][j].botOnThisPlace != nullptr && i < WORLD_HEIGHT && j < WORLD_WIDTH && world1[i][j].botOnThisPlace->curParameters.power < world1[target.y][target.x].botOnThisPlace->curParameters.power){
                    target.x = j;
                    target.y = i;
                    targetNotDefault = true;
                }
            }
        }
        if(targetNotDefault){return target;}
        else return {-1, -1};
    }

    void CreatureAbleToEat::predatorNutrition(){ //вынесено за класс чтобы работать с полями класса Bot
        int tryCounter = this->curParameters.viewingRange+5;
        Pos foodPos;
        foodPos = seekPredatorTarget();
        while(tryCounter > 0 && foodPos.x != -1){
            if(this->curPos.x <= foodPos.x-1 && world1[curPos.y][curPos.x+1].botOnThisPlace == nullptr){
                curPos.x++;
                this->curParameters.curEnergy-=this->curParameters.moveEnergySpend;
            }
            if(this->curPos.x >= foodPos.x+1 && world1[curPos.y][curPos.x-1].botOnThisPlace == nullptr){
                curPos.x--;
                this->curParameters.curEnergy-=this->curParameters.moveEnergySpend;
            }
            if(this->curPos.y <= foodPos.y-1 && world1[curPos.y+1][curPos.x].botOnThisPlace == nullptr){
                curPos.y++;
                this->curParameters.curEnergy-=this->curParameters.moveEnergySpend;
            }
            if(this->curPos.y >= foodPos.y+1 && world1[curPos.y-1][curPos.x].botOnThisPlace == nullptr){
                curPos.y--;
                this->curParameters.curEnergy-=this->curParameters.moveEnergySpend;
            }
            if((this->curPos.x == foodPos.x+1 && this->curPos.y == foodPos.y)|| (this->curPos.x == foodPos.x-1 && this->curPos.y == foodPos.y) || (this->curPos.x == foodPos.x && this->curPos.y == foodPos.y+1)  || (this->curPos.x == foodPos.x && this->curPos.y == foodPos.y-1)){
                eatBot(foodPos.x, foodPos.y, 1);
                unbindBot(world1[foodPos.y][foodPos.x].botOnThisPlace);
                updPos();
                break;
            }
            else {
                if(tryCounter < 5){
                    if(world1[curPos.y][curPos.x+1].botOnThisPlace != nullptr && world1[curPos.y][curPos.x+1].botOnThisPlace->curParameters.power < this->curParameters.power){
                        eatBot(foodPos.x, foodPos.y, 2);
                        delete  world1[curPos.y][curPos.x+1].botOnThisPlace;
                        updPos();
                        break;
                    }
                    else {
                        if(world1[curPos.y][curPos.x-1].botOnThisPlace != nullptr && world1[curPos.y][curPos.x-1].botOnThisPlace->curParameters.power < this->curParameters.power){
                            eatBot(foodPos.x, foodPos.y, 3);
                            delete  world1[curPos.y][curPos.x-1].botOnThisPlace;
                            updPos();
                            break;
                        }
                        else {
                            if(world1[curPos.y+1][curPos.x].botOnThisPlace != nullptr && world1[curPos.y+1][curPos.x].botOnThisPlace->curParameters.power < this->curParameters.power){
                                eatBot(foodPos.x, foodPos.y, 4);
                                delete  world1[curPos.y+1][curPos.x].botOnThisPlace;
                                updPos();
                                break;
                            }
                            else {
                                if(world1[curPos.y-1][curPos.x].botOnThisPlace != nullptr && world1[curPos.y-1][curPos.x].botOnThisPlace->curParameters.power < this->curParameters.power){
                                    eatBot(foodPos.x, foodPos.y, 5);
                                    delete  world1[curPos.y-1][curPos.x].botOnThisPlace;
                                    updPos();
                                    break;
                                }
                                else {
                                    updPos();
                                    break;
                                }
                            }
                        }
                    }

                }
            }
            tryCounter--;
        }
    };

    void CreatureAbleToBreed::division(){
        Bot* tempPtr;
        genom1 = this->curParameters;
        genom1.curEnergy = this->curParameters.curEnergy/2;
        genom1.curAge = 0;
        genom1 = mutateGenom(genom1);
        genom2 = this->curParameters;
        genom2.curEnergy = this->curParameters.curEnergy/2;
        genom2.curAge = 0;
        genom2 = mutateGenom(genom2);
        if(world1[curPos.y+1][curPos.x].botOnThisPlace == nullptr && curPos.y+1 != WORLD_HEIGHT){
            tempPtr=new Bot(genom1, curPos.x, curPos.y+1);
            this->curParameters=genom2;
            return;
        }
        if(world1[curPos.y-1][curPos.x].botOnThisPlace == nullptr && curPos.y-1 != 0){
            tempPtr=new Bot(genom1, curPos.x, curPos.y-1);
            this->curParameters=genom2;
            return;
        }
        if(world1[curPos.y][curPos.x+1].botOnThisPlace == nullptr && curPos.x+1 != WORLD_WIDTH){
            tempPtr=new Bot(genom1, curPos.x+1, curPos.y);
            this->curParameters=genom2;
            return;
        }
        if(world1[curPos.y][curPos.x-1].botOnThisPlace == nullptr && curPos.x-1 != 0){
            tempPtr=new Bot(genom1, curPos.x-1, curPos.y);
            this->curParameters=genom2;
            return;
        }
    }

    bool checkDeath(int i){
        if(allBots[i]->curParameters.curEnergy <= 0){
            world1[allBots[i]->curPos.y ][allBots[i]->curPos.x].rottenQuant+=allBots[i]->curParameters.maxEnergy/2;
            unbindBot(world1[allBots[i]->curPos.y ][allBots[i]->curPos.x].botOnThisPlace);
            delete allBots[i];
            return true;
        }
        else {
            return false;
        }
    }

int main(){
    Bot* test1;
    Bot* test2;
    srand(time(NULL));
    fillWorld(50);
    botParam test{100, NUTRITION, 30, 120, 60, 20, 50, HERBIVOROUS, 1, DIVISION, 6, 5, 10};
    allBots[0] = new Bot(test, 1, 1);

    while(true){
        for(int i = 0 ; i < WORLD_WIDTH*WORLD_HEIGHT; i++){
            if( allBots[i] == nullptr){
                continue;
            }
            if(!checkDeath(i)) allBots[i]->action();
        }
    }
}



