#include<iostream>
using namespace std;

const int numOfColumns = 20;
const int numOfRows = 20;
const int mutationProbability = 1; //10000 de 1

#include "headers.h"/*headers include Ant.h Ant.cpp 
Organism.h Organism.cpp Doodlebug.h Doodlebug.cpp
PoisonousAnt.h Poisonous.cpp*/

void setInitialWorld(Organism* gameSpace[][numOfColumns] ,Ant ant[], Doodlebug doodlebugs[]);
void calculateNumberOfCritiers(Ant ants[ ], Doodlebug doodlebugs[], PoisonousAnt PAnts[]);

int main(int argc, char const *argv[])
{
	char ch;
    int counter = 0;

    Organism* gameSpace[numOfRows][numOfColumns];

    Organism organism[numOfRows][numOfColumns];

    Ant ant[numOfRows*numOfColumns];

    PoisonousAnt PAnt[numOfRows*numOfColumns];

    Ant* pPAnt[numOfRows*numOfColumns];

    Doodlebug doodlebugs[numOfRows*numOfColumns];

    srand(time(NULL));

	for (int i = 0; i < numOfColumns*numOfRows; ++i)
    	pPAnt[i] = nullptr;

    for (int i = 0; i < numOfColumns*numOfRows; ++i)
    	pPAnt[i] = &PAnt[i];


    for(int c = 0; c < numOfRows; c++){
        for (int i = 0; i < numOfColumns; i++){
            gameSpace[c][i] = nullptr;
        }
    }

    for (int i = 0; i < numOfRows; ++i)
        for (int j = 0; j < numOfColumns; ++j)
        {
            gameSpace[i][j] = &organism[i][j];
            gameSpace[i][j]->setRow(i);
            gameSpace[i][j]->setColoumn(j);
        }


    setInitialWorld(gameSpace,ant,doodlebugs);
	cout<<"Step--->"<<counter<<endl;    
    calculateNumberOfCritiers(ant, doodlebugs, PAnt);



 for (int i = 0; i < numOfRows; ++i)
    {
        for (int j = 0; j < numOfColumns; j++)
            cout<<gameSpace[i][j]->getSymbol()<<" ";

        cout<<endl;
    }  

char test;
bool seenEnd = false;
    while(seenEnd == false){
        cout<<"Press enter to initiate time step: ";
        test = fgetc(stdin);
        if(test == '\n'){
                       
            for (int i = 0; i < numOfRows*numOfColumns; ++i)
            {
                doodlebugs[i].move(gameSpace,organism,doodlebugs);
                ant[i].move(gameSpace,organism,ant,pPAnt);
                PAnt[i].move(gameSpace,organism,ant,pPAnt,PAnt);
            }

            for (int i = 0; i < numOfRows; ++i)
            {
                for (int j = 0; j < numOfColumns; j++)
                    cout<<gameSpace[i][j]->getSymbol()<<" ";

                cout<<endl;
            }
            counter++;
            cout<<"Step--->"<<counter<<endl;  
            calculateNumberOfCritiers(ant, doodlebugs, PAnt);

        }
        else
            seenEnd = true;
    }

	return 0;
}

void setInitialWorld(Organism* gameSpace[][numOfColumns] ,Ant ant[], Doodlebug doodlebugs[]){//Initialize the world with 5 doodlebugs 100 ants

    //100 ant = totalcoloumn*5
    int id;
    int randomRow;//0 down, 1 up, 2 right, 3 left
    int randomColumn;
    for (int i = 0; i < numOfColumns*5 ; ++i)//coulumns = 20 so 20*5=100 ants
    {            
        randomRow = rand() % numOfRows;
        randomColumn = rand() % numOfColumns;
        if (gameSpace[randomRow][randomColumn]->getSymbol()=='-')// - represents empty area
        {
            id = findValidIdForAnt(ant);
            setAntToGrid(gameSpace, ant, randomRow, randomColumn, id);
        }
        else
            i--;// if there is no assignment for any ant
    }

    for (int i = 0; i < numOfColumns/4	 ; ++i)//coulumns = 20 so 20/5=4 Doodlebugs
    {            
        randomRow = rand() % numOfRows;
        randomColumn = rand() % numOfColumns;
        if (gameSpace[randomRow][randomColumn]->getSymbol()=='-')// - represents empty area
        {
            id = findValidIdForDoodlebug(doodlebugs);
            setDoodlebugsToGrid(gameSpace, doodlebugs, randomRow, randomColumn, id);
        }
        else
            i--;// if there is no assignment for any ant
    }
}

void calculateNumberOfCritiers(Ant ants[ ], Doodlebug doodlebugs[], PoisonousAnt PAnts[]){
    int counter = 0;
    for (int i = 0; i < numOfRows*numOfColumns; ++i)
    {
        if (ants[i].getIsAlive() == true)
        {
            counter++;
        }
    }

    cout<<"There are "<<counter<<" ants, ";

    counter = 0;

    for (int i = 0; i < numOfRows*numOfColumns; ++i)
    {
        if (doodlebugs[i].getIsAlive() == true)
        {
            counter++;
        }
    }

    cout<<counter<<" doodlebugs, ";

    counter = 0;

    for (int i = 0; i < numOfRows*numOfColumns; ++i)
    {
        if (PAnts[i].getIsAlive() == true)
        {
            counter++;
        }
    }

    cout<<counter<<" PoisonousAnt "<<endl;

}