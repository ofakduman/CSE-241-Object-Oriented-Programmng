/*
** 					HW 1 
**
** Author: 			Omer Faruk AKDUMAN
** School number:		1801042094
** extra: 			added difficulty option 
*/
#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

typedef enum {no, yes }yesORno;
typedef enum{Up, Down, Right, Left}Directions;			//defined to the movement on the board
typedef enum {easy, normal, hard}Difficulty;

int input_size( );
//gets the size from user
void board_operation(int [][9], int ,Difficulty);
//happens some board operation ,order, shuffle, checks it is solved ornet (before no input)
void fill_with_ordered(int [][9],int);
//filling with orded number for example 3x3 1 2 3\n 4 5 6\n 7 8 9
yesORno Is_solved(int [][9],int );
//cheks this problem is solved or not after solved
void show_board(int [][9],int );
//shows board
void menu(int [][9], int ,Difficulty);
//commands taken here (right, left, up, down)
void get_informate();
//showing inputs and informs user
void movement(int [][9], Directions, int);
//this function provides movement
void find_location(int [][9], int , int []);
//this function find empty cell's location
void Mix(int [][9], int, Difficulty);
//mix the board according to the difficulty
Difficulty select_difficult();
/*added selecting difficulty option-> Its about the mixing alot or not*/
void intellegent(int, int [][9]);
Directions find_direction(int up,int down, int right, int left);
/*compare differences for making intellegent move*/

int main(int argc, char const *argv[])
{
	srand(time(NULL));
	Difficulty difficult;
	int size, board[9][9];
	size=input_size();			//gets the size
	difficult=select_difficult();		//selects difficult
	menu(board,size,difficult);

	return 0;
}
Difficulty select_difficult()
{
	int select;
	cout<<"Please input difficulty! (as an integer)"<<endl
	<<"1-Easy"<<endl
	<<"2-Normal"<<endl
	<<"3-Hard"<<endl
	<<"Select: ";

	cin>>select;
	if (select==1)
		return easy;

	else if (select==2)
		return normal;

	else return hard;
}
void menu(int board[][9], int size, Difficulty difficult)
{	
	yesORno quit=no ,is_solved=no;
	int mv=1 ,wrong_input=0, move_counter=0;
	char ch=' ';
	cout<<"\n--------> Welcome to N-Puzzle problem <-------\n"<<endl;
	get_informate();
	cout<<"Board size is: "<<size<<"x"<<size<<endl<<"Difficulty is:";
	if (difficult==0)
		cout<<" Easy"<<endl;
	else if (difficult==1)
		cout<<" Normal"<<endl;
	else
		cout<<" Hard"<<endl;
	

	board_operation(board, size, difficult);
	show_board(board,size);
	
	cout<<"Your move: ";
	cin>>ch;	
	
	while(quit!=yes)
	{
		switch(ch)
		{	case 'h':			//gets informate
			case 'H':
				get_informate();
				break;
			case 's':
			case 'S':
				difficult=select_difficult();
				board_operation(board,size, difficult);
				move_counter=0;
				break;

			case 'l':
			case 'L':
				wrong_input=0;
				++move_counter;
				movement(board, Left, size);
				break;
			case 'r':
			case 'R':
				++move_counter;
				wrong_input=0;
				movement(board, Right, size);
				break;
			case 'u':
			case 'U':
				++move_counter;
				wrong_input=0;
				movement(board, Up, size);
				break;
			case 'd':
			case 'D':
				wrong_input=0;
				++move_counter;
				movement(board, Down, size);
				break;
			case 'i':
			case 'I':
				++move_counter;
				intellegent(size,board);
				break;
			case 'q':
			case 'Q':
				quit=yes;
				break;

			default:
			{	
				wrong_input++;
				if (wrong_input==3)					//user may forget inputs so after some wrong input remember the inputs 
				{
					cout<<endl<<endl<<"Your last 3 input is wrong!!"<<endl<<"Inputs:"<<endl;
					get_informate();
					wrong_input=0;
				}
				else
					cout<<"Wrong input try again\n";
			}
			break;
		}

		show_board(board,size);
		is_solved=Is_solved(board,size);
		if (is_solved==yes)
			{
				cout<<"Congratulations!!!"<<endl
				<<"You solved this puzzle "<<move_counter<<". move"<<endl;
				quit=yes;
			}
		else
			{
				cout<<"Your move: ";
				cin>>ch;			
			}
	}
}
void intellegent(int size, int board[][9])
{
	Directions move_direction;
	int locations[2], i,j,value_of_empty_card, difference_up, difference_down, difference_right, difference_left, temp_value ;
	find_location(board, size, locations);
	i=locations[0];				//i
	j=locations[1];				//j

	value_of_empty_card=i*size+j+1;

	if (i!=0)
	{
		temp_value=board[i-1][j];
		if (temp_value+size==value_of_empty_card)
			difference_up=98;
		else	
			difference_up=value_of_empty_card-temp_value;
				if (difference_up<0)
					difference_up*=-1;
	}
	else
		difference_up=99;
	
	if (j<size-1)
	{	
		temp_value=board[i][j+1];
		if (temp_value-1==value_of_empty_card)
			difference_right=98;
		else
			difference_right=value_of_empty_card-temp_value;
				if (difference_right<0)
					difference_right*=-1;	
	}
	else 
		difference_right=99;

	if (j!=0)
	{
		temp_value=board[i][j-1];
		if (temp_value+1==value_of_empty_card)
				difference_left=98;
		else
			difference_left=value_of_empty_card-temp_value;
				if (difference_left<0)
					difference_left*=-1;
	}
	else
		difference_left=99;

	if (i<size-1)
	{

		temp_value=board[i+1][j];
		if (temp_value-size==value_of_empty_card)
			difference_down=98;
		else
			difference_down=value_of_empty_card-temp_value;
			if (difference_down<0)
				difference_down*=-1;
	}
	else
		difference_down=99;


	move_direction=find_direction(difference_up,difference_down,difference_right,difference_left);	//finds intellegent direction according to difference

	movement(board, move_direction, size);
}

Directions find_direction(int up,int down, int right, int left)
{
	cout<<"Intelligent move chooses ";
	if (up<=down && up<=right && up<=left)
	{
		cout<<"U"<<endl<<endl;
		return Up;
	}

	else if (down<=right && down<=left && down<=up )
		{	
			cout<<"D"<<endl<<endl;
			return Down;
		}
	else if (right<=down && right<=left && right<=up)
	{
		cout<<"R"<<endl<<endl;
		return Right;
	}

	else
	{
		cout<<"L"<<endl<<endl;
		return Left;
	} 
}
void movement(int board[][9], Directions direction, int size)
{
	int location[2], i,j,temp;			//location of empty cell which  location[0]=i, location[1]=j
	find_location(board,size,location);
	i=location[0];
	j=location[1];
	if (direction==Up)
	{
		if (i>0)
		{
			temp=board[i][j];
			board[i][j]=board[i-1][j];
			board[i-1][j]=temp;
		}
	}
	else if (direction==Down)
	{
		if (i<size-1)
		{
			temp=board[i][j];
			board[i][j]=board[i+1][j];
			board[i+1][j]=temp;
		}
	}
	else if (direction==Right)
	{
		if (j<size-1)
		{
			temp=board[i][j];
			board[i][j]=board[i][j+1];
			board[i][j+1]=temp;
		}
	}
	if (direction==Left)
	{
		if (j>0)
		{
			temp=board[i][j];
			board[i][j]=board[i][j-1];
			board[i][j-1]=temp;
		}
	}
}
void find_location(int board[][9], int size, int location[2])
{
	int i,j;
	for (i = 0; i < 9; ++i)
		for (j = 0; j <9 ; ++j)
			if (size*size==board[i][j])
			{
				location[0]=i;
				location[1]=j;
				break;
			}
}
void get_informate()
{
	cout<<"\nInput\t\t\t\tAction\nL\t\t\t\tmoves the empty cell left if there is room\nR\t\t\t\tmoves the empty cell right if there is room\nU\t\t\t\t"
	<<"moves the empty cell up if there is room\nD\t\t\t\t"
	<<"moves the empty cell down if there is room\nI\t\t\t\t"
	<<"makes an “intelligent” move for you.\nQ\t\t\t\t"
	<<"Quits the program"<<endl<<endl;
}
int input_size(){
	int size;
	cout<<"Please enter the problem size"<<endl;
	cin>>size;
	while (size<2 || size>10)									
	{
		cout<<"Please enter the valid size"<<endl;
		cin>>size;
	}
	return size;}

void board_operation(int board[][9], int size, Difficulty difficult)
{
	yesORno is_all_one_shuffled = no, is_convenient, is_solved=yes;
	int random, mix_time;	//number of movement space
	fill_with_ordered(board,size);						//filling number with ordered
	while(is_solved!=no)
	{
		Mix(board,size,difficult);
		is_solved=Is_solved(board,size);			//Check whether board is solved in random assignment if it solved fill random again
	}
}

void Mix(int board[][9], int size, Difficulty difficult)
{
	int random, i,times;
	if (difficult==easy)
		times=10;
	else if (difficult==normal)
		times = 100;
	else
		times=10000;

	for (int i = 0; i < times; ++i)
	{
		random=rand()%4+1;			//for assignment random direction 1 is up 2 is down 3 is right 4 is left
		if (random==1)
			movement(board,Up,size);
		else if (random==2)
			movement(board,Down,size);
		else if (random==3)
			movement(board,Right,size);
		else if (random==4)
			movement(board,Left,size);
	}	
}

void fill_with_ordered(int board[][9],int size){
	int i,j;
	for (i = 0; i < size; ++i)
		for (j = 0; j <size ; ++j)
			board[i][j]=i*size+j+1;}


yesORno Is_solved(int board[][9],int size)				//cozulup cozulmedigine bakiyo
{
	int i,j;
	for (i = 0; i < size; ++i)
		for (j = 0; j <size ; ++j)
		{
			if (board[i][j]!=size*i+j+1)
				return no;
		}
		return yes;
}

void show_board(int board[][9],int size)
{
	int i, j;

	cout<<"your board is:"<<endl<<endl;
	for (i = 0; i < size; ++i)
		for (j = 0; j <size ; ++j)
		{
			if (size*size==board[i][j])
				if(size<4) cout<<" ";
				else cout<<"  ";
			
			else
			cout<<board[i][j];

			if (board[i][j]>=10)
				cout<<" ";

			else
				cout<<"  ";

			if (j==size-1 )
				cout<<endl;
		}
}
