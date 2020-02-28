#include "Functions.h"
#include <iostream>


void NPuzzle::menu(int argc, char*argv[])
{	
	bool is_solved=false, quit=false;
	int mv=1 ,wrong_input=0, move_counter=0, loop[2]={-1,-1},zero_counter[9][2],select=1;
	char ch=' ';
	cout<<"\n--------> Welcome to N-Puzzle problem <-------\n"<<endl;
	NPuzzle :: Board board;
	board.fill_with_minus1();

	if (argc > 1)
		board.readFromFile(argv,argc);						//for command line

	else						//if board doesnt loaded from file in command line
	{
		cout<<"Input MENU\n1->from keyboard\n2->from file"<<endl;
		cin>>select;
		if (select==2)
			board.readFromFile(argv,argc);

		else
		{
			board.setsize();
			board.fill_with_ordered();
		}

		while(board.isSolved()==true)
			shuffle(board);						
	}

	board.print();
	
		board.finds_zeros_in_board(zero_counter);	//finds zeros in the board

	while(quit!=true)
	{
		
		cout<<"Your move: ";
		cin>>ch;

		switch(ch)
		{	
			case 's':
			case 'S':
				shuffle(board);
				move_counter=0;
				break;
			case 't':
			case 'T':
				cout<<"You are now "<<move_counter<<". movement "<<endl;
				break;
							
			case 'e':
			case 'E':
					writeToFile(board);
				break;
			
			case 'o':
			case 'O':
				board.fill_with_minus1();
				board.readFromFile(argv);
				move_counter=0;
				break;
				
			case 'l':
			case 'L':
				++move_counter;
				board.move(Left);
				break;
			case 'r':
			case 'R':
				++move_counter;
				board.move(Right);
				break;
			case 'u':
			case 'U':
				++move_counter;
				board.move(Up);
				break;
			case 'd':
			case 'D':
				++move_counter;
				board.move(Down);
				break;
			
			case 'i':
			case 'I':
				++move_counter;
				moveIntelligent(board,zero_counter,loop);
				break;
				
			case 'v':
			case 'V':
				solvePuzzle(board,zero_counter,loop,move_counter);
				break;
			case 'q':
			case 'Q':
				quit=true;
				break;

			default:
				cout<<"Wrong input try again\n";
			break;
		}

		board.print();
		is_solved=board.isSolved();
		if (is_solved==true)
			{
				cout<<"Congratulations!!!"<<endl
				<<"You solved this puzzle "<<move_counter<<". move"<<endl;
				quit=true;
			}
						
	}
}
void NPuzzle::solvePuzzle(Board& board,int zero_counter[9][2],int loop[2], int& move_counter)
{
	clock_t start, end;
	start = clock();
	double cpu_time_used;
	
	while(board.isSolved()!=true)
	{
		board.print();
		moveIntelligent(board,zero_counter,loop);
		move_counter++;
		cout<<"--------------------"<<endl;
	}

	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;					//execution time added
	cout<<"Execution time: "<<cpu_time_used<<" seconds (in more intellegent algorithm) \nThanks for waiting!"<<endl;
}

void NPuzzle::moveIntelligent(Board& board, int zero_counter[9][2],int loop[2])
{
	board.intellegent(loop,zero_counter);
}

void NPuzzle::Board::intellegent(int loop[2],int zero_counter[9][2])
{
	Directions move_direction;
	bool is_loop;
	int locations[2], i,j,value_of_empty_card, difference_up,
	difference_down, difference_right, difference_left, temp_value;
	int total_zero,axis_x;		//this contains how many zero in the board 

	if (size_x==-1)
		axis_x=size_y;
	else
		axis_x=size_x;
	
	find_location(locations);
	i=locations[0];				//i
	j=locations[1];				//j

	total_zero=total_zeros(locations[0],zero_counter);			//e kadar olan toplam 0

	value_of_empty_card=i*axis_x+j-total_zero+1;

	if (i!=0 && board[i-1][j]!=0)
	{
		temp_value=board[i-1][j];
		if (temp_value+axis_x==value_of_empty_card)
			difference_up=98;
		else	
			difference_up=value_of_empty_card-temp_value;
				if (difference_up<0)
					difference_up*=-1;
	}
	else
		difference_up=99;
	
	if (j<axis_x-1 && board[i][j+1]!=0)
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

	if (j!=0 && board[i][j-1]!=0)
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

	if (i<size_y-1 && board[i+1][j]!=0)
	{

		temp_value=board[i+1][j];
		if (temp_value-size_y==value_of_empty_card)
			difference_down=98;
		else
			difference_down=value_of_empty_card-temp_value;
			if (difference_down<0)
				difference_down*=-1;
	}
	else
		difference_down=99;

	move_direction=find_direction(difference_up,difference_down,difference_right,difference_left);	//finds intellegent direction according to difference

	is_loop=Is_loop(move_direction,loop);
	if (is_loop==true)
	{
		moveRandom();
		loop[0]=-1;
		loop[1]=-1;
	}

		move(move_direction);
}

Directions NPuzzle::Board::find_direction(int up,int down, int right, int left)
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



int NPuzzle::Board::total_zeros(int location_y,int zero_counter[9][2])	//total 0's up to the target location
{
	int i, total_zero=0,j;

	for (i = 0; i <= location_y ; ++i)
	{
		for (j = 0; j < 2 ; ++j)
		{
			total_zero= total_zero +zero_counter[i][j];
		}
	}

	total_zero-=zero_counter[i-1][1];
	return total_zero;
}

bool NPuzzle::Board::Is_loop(Directions direction,int loop[2])	//when intellegent moves checks whether looping or not
{
	if (loop[0]==-1)
	{
		loop[0]=int(direction);
		return false;
	}

	else if (loop[1]==-1)
	{
		loop[1]=int(direction);
		if (loop[0] == 0 && loop[1] == 1)
			return true;
	
		else if (loop[0] == 1 && loop[1] == 0)
			return true;

		else if (loop[0] == 2 && loop[1] == 3)
			return true;

		else if (loop[0] == 3 && loop[1] == 2)
			return true;
		
		else 
		{
			loop[0]=loop[1];
			loop[1]=-1;
			return false;
		}
		return false;
	}
}



void NPuzzle::Board::writeToFile()const
{
	ofstream outStream;

	char outFile[15];
	int i,j,axis_x;
	
	if (size_x==-1)
		axis_x=size_y;
	else
		axis_x=size_x;
	
	cout<<"Input the filename: ";
	cin>>outFile;
	outStream.open(outFile);

	for (i = 0; i < size_y; ++i)
	{
		for (j = 0; j < axis_x; ++j)
		{
			if (board[i][j]==0)
				outStream<<"00 ";

			else if (board[i][j]==-5)
					outStream<<"bb ";

			else if (board[i][j]<10)
				outStream<<"0"<<board[i][j]<<" ";

			else 
				outStream<<board[i][j]<<" ";
		}
		outStream<<endl;
	}
		cout<<"File saved succesfully!"<<endl;
}

void NPuzzle::writeToFile(const Board& board )const{board.writeToFile();}
void NPuzzle::Board::finds_zeros_in_board(int zero_counter[9][2])
{
	int i,j,k=0;

	for (i = 0; i < 9 ; ++i)
		for (j = 0; j < 2; ++j)
			zero_counter[i][j]=0;

	if (size_x==-1)
		return;

	else
	{
		for (i = 0; i <size_y ; ++i)
		{	
			for ( j = 0; j < size_x; ++j)
			{
				if (board[i][j]==0)
					++zero_counter[i][k];

				if (k==0 && board[i][j]!=0)				//sayi gorene kadar gider ve sagdaki 0 larinda sayilmalarinin saglar
					k=1;
			}
			k=0;										//yeni satira gectiginde soldaki sifirlari sayar
		}	
	}
	
}	

void NPuzzle::shuffle(NPuzzle::Board& board)
{
	int  i,times;
	times=getsize(board);
	cout<<"----Rondomizing board----"<<endl;
	for (int i = 0; i < times; ++i)
		board.moveRandom();
}

void NPuzzle::Board::moveRandom()
{
	int random,i;
	for (int i = 0; i < size_y; ++i)
	{
		random=rand()%4+1;			//for assignment random direction 1 is up 2 is down 3 is right 4 is left
		if (random==1)
			move(Up);
		else if (random==2)
			move(Down);
		else if (random==3)
			move(Right);
		else if (random==4)
			move(Left);
	}
}

int NPuzzle::Board::getsize()const
{
	return size_y;
}

int NPuzzle::getsize(const Board& board)
{
	return board.getsize();
}

void NPuzzle::Board::move(Directions direction)
{
	int location[2], i,j,temp,axis_x;			//location of empty cell which  location[0]=i, location[1]=j
	find_location(location);		//finds empty cell locatio
	i=location[0];
	j=location[1];

	if (size_x==-1)
		axis_x=size_y;
	else
		axis_x=size_x;
		
	if (direction==Up)
	{
		if (i>0 && board[i-1][j]!=0)
		{
			temp=board[i][j];
			board[i][j]=board[i-1][j];
			board[i-1][j]=temp;
		}
	}

	else if (direction==Down)
	{
		if (i<size_y-1 && board[i+1][j]!=0)
		{
			temp=board[i][j];
			board[i][j]=board[i+1][j];
			board[i+1][j]=temp;
		}
	}
	else if (direction==Right )
	{
		if (j<axis_x-1 && board[i][j+1]!=0)
		{
			temp=board[i][j];
			board[i][j]=board[i][j+1];
			board[i][j+1]=temp;
		}
	}
	if (direction==Left)
	{
		if (j>0 && board[i][j-1]!=0)
		{
			temp=board[i][j];
			board[i][j]=board[i][j-1];
			board[i][j-1]=temp;
		}
	}
}

void NPuzzle::Board::find_location(int location[2])
{
	int i,j,axis_x;
	if (size_x==-1)
		axis_x=size_y;
	else
		axis_x=size_x;

	for (i = 0; i < size_y; ++i)
		for (j = 0; j <axis_x ; ++j)
			if (board[i][j]==-5)
			{
				location[0]=i;
				location[1]=j;
				return;
			}
}

bool NPuzzle::Board::isSolved()const
{
	int counter=1,i,j,axis_x;
	if (size_x==-1)
		axis_x=size_y;
	else
		axis_x=size_x;

	if (board[size_y-1][axis_x-1]!=-5)
		return false;

	for (i = 0; i <size_y ; ++i)
	{
		for (j = 0; j < axis_x ; ++j)
		{
			if (board[i][j]!=0 && board[i][j]!=-5)			//-5 empty cell (bb)
			{
				if (board[i][j]==counter)
					counter++;
				
				else 
					return false;
			}
		}
	}
	return true;}



void NPuzzle::Board::fill_with_ordered(){
	int i,j;
	for (i = 0; i < size_y; ++i)
		for (j = 0; j <size_y ; ++j)
			board[i][j]=i*size_y+j+1;
		board[size_y-1][size_y-1]=-5;
	}
void NPuzzle::Board::readFromFile(char*argv[],int argc){


	char chrctr, an_element[2];
	int i=0,j=0,k=0, number;
	ifstream inStream;
	ofstream outStream;
	char inFile[15];

	if (argc > 1)
		inStream.open(argv[1]);

	else
	{
		cout<<"Input the filename: ";
		cin>>inFile;
		inStream.open(inFile);
	}
	
	if (inStream.fail()){
		cout<<"This : "<<inFile<<" file didnt find!"<<endl<<"Make sure is name correct"<<endl;
		exit(1);}
	
	inStream.get(chrctr);
	while (! inStream.eof( ))
	{
		if (chrctr=='b')
		{
			inStream.get(chrctr);
			board[i][j]=-5;
			j++;
		}
		else if (chrctr=='0')
		{
			inStream.get(chrctr);
			
			if (chrctr=='0')
				{
					board[i][j]=0;
					j++;
				}
			else
			{
					board[i][j]=int(chrctr)-48;
					j++;
			}
		}
		else if (chrctr=='\n')
		{
			i++;
			size_x=j;
			j=0;
		}
		else if (chrctr!=' ')
		{
			number= (int(chrctr)-48)*10;
			inStream.get(chrctr);
			number=number+int(chrctr)-48;
			board[i][j]=number;
			j++;
		}		
		inStream.get(chrctr);
	}

	size_y=i;		//gets size (for ex (9*6))
	inStream.close();
	outStream.close();}

void NPuzzle::Board::print()const{
	int i,j,other_axis;

	if (size_x==-1)
		other_axis=size_y;
	else
		other_axis=size_x;


	for (i = 0; i < size_y; ++i)
	{
		for (j = 0; j < other_axis; ++j)
		{
			if (board[i][j]==0)
				cout<<"00 ";

			else if (board[i][j]==-5)
				cout<<"   ";

			else if (board[i][j]<10)
				cout<<"0"<<board[i][j]<<" ";

			else 
				cout<<board[i][j]<<" ";
		}
		cout<<endl;
	}}
bool NPuzzle::Board::is_board_not_square()const{
	if (size_y==-1)
		return true;
	else
		return false;}

void NPuzzle::Board::setsize(){	
	Board board;

	int board_size;
	cout<<"Please enter the problem size"<<endl;
	cin>>board_size;
	while (board_size<2 || board_size>10)									
	{
		cout<<"Please enter the valid size"<<endl;
		cin>>board_size;
	}
	size_y=board_size;
	size_x=-1;}

void NPuzzle::Board::fill_with_minus1(){
	int i,j;
	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 9; ++j)
		{
			board[i][j]=-1;
		}
	}}


