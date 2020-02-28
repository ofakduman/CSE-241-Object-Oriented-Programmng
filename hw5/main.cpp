#include<iostream>
#include<fstream>
#include<cstdlib>
#include<ctime>

#include"boardvector.h"
#include"boardvector.cpp"

#include "boardarray1d.h"
#include "boardarray1d.cpp"

#include "boardarray2d.h"
#include "boardarray2d.cpp"


void print(AbstractBoard* board);


int main(int argc, char *argv[])
{
	srand(time(NULL));
	char ch;
	int select=5,index,index2,size,x,y;

	BoardVector bv1,bv2(3),bv3(3,5);
	BoardArray1D ba1_1,ba1_2(5),ba1_3(9,10);
	BoardArray2D ba2_1,ba2_2(7),ba2_3(5,5);
	
	AbstractBoard* boardArr[9];

	boardArr[0]=&bv1;
	boardArr[1]=&bv2;	
	boardArr[2]=&bv3;

	boardArr[3]=&ba1_1;
	boardArr[4]=&ba1_2;
	boardArr[5]=&ba1_3;

	boardArr[6]=&ba2_1;
	boardArr[7]=&ba2_2;
	boardArr[8]=&ba2_3;

	cout<<"boardArr[0], boardArr[1], boardArr[2] are BoardVector clasess objects \nboardArr[3], boardArr[4], boardArr[5] are BoardArray1D clasess objects \nboardArr[6], boardArr[7], boardArr[8] are BoardArray2D clasess objects"<<endl;

	cout<<endl<<"1- print() function"<<endl<<"2- readFromFile() function"<<endl<<"3- writeToFile() function"<<
		endl<<"4- reset() function"<<endl<<"5- setSize() function"<<endl<<"6- move() function"<<"\n7- isSolved() function"<<
		endl<<"8- operator() function"<<endl<<"9- operator== function"<<endl<<"10- NumberOfBoards() function"<<endl<<
		"11- lastMove() function\n12- numberOfMoves() function\n13- solvePuzzle function \n0-Quit";
	cout<<endl<<endl<<"Please select one option = ";
	cin>>select;

	while(select!=0)
	{
		
		
		if (select == 1)
		{
			cout<<"1- Print all"<<endl<<"2- print choosen one"<<endl<<"0- Back"<<endl;
			cout<<endl<<"Select one : ";
			cin>>select;

			while(select==1 || select == 2)
			{
				if (select==1)
				{
					cout<<endl;
					for (int i = 0; i < 9; ++i)
					{	
						cout<<i<<". array: "<<endl;
						boardArr[i]->print();			
					}
				}

				else
				{
					cout<<endl<<"Please choose one of the index between 0-9 (include 0) : ";
					cin>>index;
					cout<<index<<". array: "<<endl;

					boardArr[index]->print();
				}

				cout<<endl<<endl<<"1- Print all"<<endl<<"2- print choosen one"<<endl<<"0- Back"<<endl;
				cout<<endl<<"Select one : ";
				cin>>select;
			}
		}

		else if (select == 2)
		{
			cout<<"Which index do you want to readFromFile between 0-9 (include 0) :";
			cin>>index;
			boardArr[index]->readFromFile(argv,argc);
			cout<<index<<". array: "<<endl;
			boardArr[index]->print();

		}

		else if (select == 3)
		{
			cout<<"Which index do you want to writeToFile between 0-9 (include 0) :";
			cin>>index;
			boardArr[index]->writeToFile();
			cout<<index<<". array: "<<endl;
			boardArr[index]->print();
		}

		else if (select == 4)
		{
			cout<<"Which index do you want to reset between 0-9 (include 0) :";
			cin>>index;
			boardArr[index]->reset();
			cout<<index<<". array: "<<endl;
			boardArr[index]->print();
		}

		else if (select == 5)
		{
			cout<<"Which index do you want to setSize() between 0-9 (include 0) :";
			cin>>index;
			cout<<"Input the size: ";
			cin>>size;
			boardArr[index]->setSize(size);
			cout<<index<<". array: "<<endl;
			boardArr[index]->print();
		}

		else if (select == 6)
		{
			cout<<"Which index do you want to move() between 0-9 (include 0) :";
			cin>>index;
			while(ch!='q')
			{
				cout<<endl<<"to quit press q"<<endl;
				cout<<"Input the direction ('U','R','L','D'): ";
				cin>>ch;
				if (ch=='U' ||ch=='R' ||ch=='L' || ch=='D' || ch=='u' ||ch=='r' ||ch=='l' || ch=='d' )
				{
					boardArr[index]->move(ch);
				}
				else
					ch='q';
				cout<<index<<". array: "<<endl;
				boardArr[index]->print();
			}
		}

		else if (select == 7)
		{
			cout<<"Which index do you want to isSolved() between 0-9 (include 0) :";
			cin>>index;

			if (boardArr[index]->isSolved())
				cout<<"Yes board is solved!"<<endl;
			else
				cout<<"No board is not solved"<<endl;

			cout<<index<<". array: "<<endl;
			boardArr[index]->print();
		}

		else if (select == 8)
		{
			cout<<"Which index do you want to isSolved() between 0-9 (include 0) :";
			cin>>index;

			cout<<"Input the two indexes x and y\nx = ";
			cin>>x;
			cout<<"y = ";
			cin>>y;
			cout<<index<<". array: "<<endl;
			boardArr[index]->print();
			cout<<"Board["<<x<<"]"<<"["<<y<<"] ="<<boardArr[index]->operator()(x,y)<<endl;
		}

		else if (select == 9)
		{
			cout<<"boardArr[0], boardArr[1], boardArr[2] are BoardVector clasess objects \nboardArr[3], boardArr[4], boardArr[5] are BoardArray1D clasess objects \nboardArr[6], boardArr[7], boardArr[8] are BoardArray2D clasess objects"<<endl;
			cout<<"So same classes objects only can compare!"<<endl;
			cout<<"Which index do you want to compare between 0-9 (include 0) \nindex1 =";
			cin>>index;

			if (index == 0 || index == 1 || index == 2)
			{
				cout<<"Which index do you want to compare Input index = 0 or 1 or 2 \nindex2 =";
				cin>>index2;
			}

			else if (index == 3 || index == 4 || index == 5)
			{
				cout<<"Which index do you want to compare Input index = 3 or 4 or 5 \nindex2 =";
				cin>>index2;
			}

			else
			{
				cout<<"Which index do you want to compare Input index = 6 or 7 or 8 \nindex2 =";
				cin>>index2;
			}

			boardArr[index]->print();
			boardArr[index2]->print();

			if (boardArr[index]==boardArr[index2])
				cout<<"Yes theese two one is equal"<<endl;
			else
				cout<<"No theese two one is not equal"<<endl;	
		}

		else if (select == 10)
		{
			cout<<"Which index do you want to get NumberOfBoards between 0-9 (include 0) :";
			cin>>index;
			if (index == 0 || index == 1 || index == 2)
			{
				cout<<"There are "<<BoardVector::NumberOfBoards()<<" board in BoardVector"<< endl;
			}

			else if (index == 3 || index == 4 || index == 5)
			{
				cout<<"There are "<<BoardArray1D::NumberOfBoards()<<" board in BoardArray1D"<< endl;
			}

			else
			{
				cout<<"There are "<<BoardArray2D::NumberOfBoards()<<" board in BoardArray2D"<< endl;
			}
		}

		else if (select == 11)
		{
			cout<<"Which index do you want to lastMove between 0-9 (include 0) :";
			cin>>index;
			cout<<"lastMove is = "<<boardArr[index]->lastMove()<<endl;
			cout<<index<<". array: "<<endl;
			boardArr[index]->print();
		}

		else if (select == 12)
		{
			cout<<"Which index do you want to get numberOfMoves between 0-9 (include 0) :";
			cin>>index;
			cout<<"numberOfMoves is = "<<boardArr[index]->numberOfMoves()<<endl;
			cout<<index<<". array: "<<endl;
			boardArr[index]->print();
		}

		else if (select == 13)
		{
			cout<<"Which index do you want to solve between 0-9 (include 0) :";
			cin>>index;
			boardArr[index]->solvePuzzle();
			cout<<index<<". array: "<<endl;
			boardArr[index]->print();
		}

		cout<<endl<<"1- print() function"<<endl<<"2- readFromFile() function"<<endl<<"3- writeToFile() function"<<
		endl<<"4- reset() function"<<endl<<"5- setSize() function"<<endl<<"6- move() function"<<"\n7- isSolved() function"<<
		endl<<"8- operator() function"<<endl<<"9- operator== function"<<endl<<"10- NumberOfBoards() function"<<endl<<
		"11- lastMove() function\n12- numberOfMoves() function\n13- solvePuzzle function \n0-Quit";

		cout<<endl<<endl<<"Please select one option = ";
		cin>>select;
	}


	return 0;
}

