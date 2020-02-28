#include "Functions.h"
#include <iostream>



void fill_with_minus1(int board[9][9]){
	int i,j;
	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 9; ++j)
		{
			board[i][j]=-1;
		}
	}}

void load_board(int board[9][9],int size[2]){
	char chrctr, an_element[2];
	int i=0,j=0,k=0, number;
	ifstream inStream;
	ofstream outStream;
	char inFile[15];

	fill_with_minus1(board);

	cout<<"Input the filename: ";
	cin>>inFile;
	inStream.open(inFile);
	
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
			size[1]=j;
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

	size[0]=i;		//gets size (for ex (9*6))
	inStream.close();
	outStream.close();}

void load_board(int board[9][9],int size[2], char* name){
	char chrctr;
	int i=0,j=0, number;
	ifstream inStream;
	ofstream outStream;
	fill_with_minus1(board);

	inStream.open(name);
	
	if (inStream.fail()){
		cout<<"This : "<<name<<" file didnt find!"<<endl<<"Make sure is name correct"<<endl;
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
			size[1]=j;
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

	size[0]=i;		//gets size (for ex (9*6))
	inStream.close();
	outStream.close();}

void print_board(int board[9][9],int size[2]){
	int i,j,size_y;

	if (size[1]==-1)
		size_y=size[0];
	else
		size_y=size[1];


	for (i = 0; i < size[0]; ++i)
	{
		for (j = 0; j < size_y; ++j)
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

void save_file(int board[9][9], int size[]){
	ofstream outStream;

	char outFile[15];
	int i,j,size_y;
	
	if (size[1]==-1)
		size_y=size[0];
	else
		size_y=size[1];
	
	cout<<"Input the filename: ";
	cin>>outFile;
	outStream.open(outFile);

	for (i = 0; i < size[0]; ++i)
	{
		for (j = 0; j < size_y; ++j)
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

bool is_solved_board(int board[9][9], int size[]){
	int counter=1,i,j,size_y;
	if (size[1]==-1)
		size_y=size[0];
	else
		size_y=size[1];

	if (board[size[0]-1][size_y-1]!=-5)
		return false;

	for (i = 0; i <size[0] ; ++i)
	{
		for (j = 0; j < size_y ; ++j)
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

void board_operation(int board[9][9], int size[],bool loaded)
{
	bool is_solved=true;
	if (size[1]==-1)			//board is square like hw 1 not input in the file
	{
		fill_with_ordered(board,size);
	}
	
	is_solved=is_solved_board(board,size);

		if (is_solved==true || loaded == false)//if it's loaded from file it will not shuffle
		{
			Mix(board,size,size[0]*size[0]+10);
				is_solved=is_solved_board(board,size);			
			while(is_solved==true)
			{
				Mix(board,size,size[0]*size[0]+10);
				is_solved=is_solved_board(board,size);			//Check whether board is solved in random assignment if it solved fill random again
			}
		}
	
}

void Mix(int board[9][9], int size[], int times)
{
	int random, i;
	cout<<"----Rondomizing board----"<<endl;
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

void movement(int board[9][9], Directions direction, int size[])
{
	int location[2], i,j,temp,size_y;			//location of empty cell which  location[0]=i, location[1]=j
	find_location(board,size,location);		//finds empty cell location
	i=location[0];
	j=location[1];

	if (size[1]==-1)
		size_y=size[0];
	else
		size_y=size[1];
		
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
		if (i<size[0]-1 && board[i+1][j]!=0)
		{
			temp=board[i][j];
			board[i][j]=board[i+1][j];
			board[i+1][j]=temp;
		}
	}
	else if (direction==Right )
	{
		if (j<size_y-1 && board[i][j+1]!=0)
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

void find_location(int board[][9], int size[], int location[2])
{
	int i,j,size_y;
	if (size[1]==-1)
		size_y=size[0];
	else
		size_y=size[1];

	for (i = 0; i < size[0]; ++i)
		for (j = 0; j <size_y ; ++j)
			if (board[i][j]==-5)
			{
				location[0]=i;
				location[1]=j;
				break;
			}
}

void menu(int board[][9], int size[2])
{	
	bool is_solved=false, quit=false;
	int mv=1 ,wrong_input=0, move_counter=0, loop[2]={-1,-1},zero_counter[9][2],select=1;
	char ch=' ';
	cout<<"\n--------> Welcome to N-Puzzle problem <-------\n"<<endl;

	if (size[0]==-1)							//if board doesnt loaded from file
	{
		cout<<"Input MENU\n1->from keyboard\n2->from file"<<endl;
		cin>>select;
		if (select==2)
		{
			load_board(board,size);
			board_operation(board, size, true);

		}

		else
		{
			size[0]=input_size( );
			board_operation(board, size);
		}
	}

	get_informate();
	print_board(board,size);
	
	cout<<"Your move: ";
	cin>>ch;	
	
	while(quit!=true)
	{
		finds_zeros_in_board(size,board,zero_counter);	//finds zeros in the board
		switch(ch)
		{	case 'h':			//gets informate
			case 'H':
				get_informate();
				break;
			case 's':
			case 'S':
				board_operation(board,size,false);
				move_counter=0;
				break;
			case 't':
			case 'T':
				cout<<"You are now "<<move_counter<<". movement ";
				break;
			case 'e':
			case 'E':
				save_file(board,size);
				break;

			case 'o':
			case 'O':
			case 'y':
			case 'Y':
				load_board(board,size);
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
					intellegent(size,board,loop,zero_counter);
				break;
			case 'v':
			case 'V':
				clock_t start, end;
				start = clock();
				double cpu_time_used;
				while(is_solved==false)
				{
					print_board(board,size);
					intellegent(size,board,loop,zero_counter);
					move_counter++;
					cout<<"--------------------"<<endl;
					is_solved=is_solved_board(board,size);	
				}
				end = clock();
				cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;					//execution time added
				cout<<"Execution time: "<<cpu_time_used<<" seconds (in more intellegent algorithm) \nThanks for waiting!"<<endl;
				break;
			case 'q':
			case 'Q':
				quit=true;
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

		print_board(board,size);
		is_solved=is_solved_board(board,size);
		if (is_solved==true)
			{
				cout<<"Congratulations!!!"<<endl
				<<"You solved this puzzle "<<move_counter<<". move"<<endl;
				quit=true;
			}
		else
			{
				cout<<"Your move: ";
				cin>>ch;			
			}
	}
}
void get_informate(){
	cout<<"\nInput\t\t\tAction"
	<<"\nU\tUp"
	<<"\nL\tLeft"
	<<"\nR\tRight"
	<<"\nD\tDown"
	<<"\nI\tIntellegent."	
	<<"\nV\tNew intelligent algorithm."
	<<"\nT\tReports"
	<<"\nE\tSave."
	<<"\nY\tLoad."
	<<"\nH\tHelp."
	<<"\nQ\tQuits the program"<<endl<<endl;}

void intellegent(int size[2], int board[][9],int loop[2], int zero_counter[9][2] )
{
	Directions move_direction;
	bool is_loop;
	int locations[2], i,j,value_of_empty_card, difference_up,
	difference_down, difference_right, difference_left, temp_value;
	int total_zero,size_y;		//this contains how many zero in the board 

	if (size[1]==-1)
		size_y=size[0];
	else
		size_y=size[1];
	
	find_location(board, size, locations);
	i=locations[0];				//i
	j=locations[1];				//j

	total_zero=total_zeros(locations[0],zero_counter);			//e kadar olan toplam 0

	value_of_empty_card=i*size_y+j-total_zero+1;

	if (i!=0 && board[i-1][j]!=0)
	{
		temp_value=board[i-1][j];
		if (temp_value+size_y==value_of_empty_card)
			difference_up=98;
		else	
			difference_up=value_of_empty_card-temp_value;
				if (difference_up<0)
					difference_up*=-1;
	}
	else
		difference_up=99;
	
	if (j<size_y-1 && board[i][j+1]!=0)
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

	if (i<size[0]-1 && board[i+1][j]!=0)
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
	//cout<<endl<<"is_loop : "<< is_loop<<endl;
	if (is_loop==true)
	{
		Mix(board,size,size[0]);
		loop[0]=-1;
		loop[1]=-1;
	}

		movement(board, move_direction, size);
}

bool Is_loop(Directions direction,int loop[2])
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
	return false;
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

int total_zeros(int location_y,int zero_counter[9][2])	//location y is ekseni
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

void finds_zeros_in_board(int size[2], int board[][9],int zero_counter[9][2])
{
	int i,j,k=0;

	for (i = 0; i < 9 ; ++i)
		for (j = 0; j < 2; ++j)
			zero_counter[i][j]=0;

	for (i = 0; i <size[0] ; ++i)
	{
		for ( j = 0; j < size[1]; ++j)
		{
			if (board[i][j]==0)
				++zero_counter[i][k];

			if (k==0 && board[i][j]!=0)				//sayi gorene kadar gider ve sagdaki 0 larinda sayilmalarinin saglar
				k=1;
		}
		k=0;										//yeni satira gectiginde soldaki sifirlari sayar
	}
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

	void fill_with_ordered(int board[][9],int size[]){
	int i,j;
	for (i = 0; i < size[0]; ++i)
		for (j = 0; j <size[0] ; ++j)
			board[i][j]=i*size[0]+j+1;
		board[size[0]-1][size[0]-1]=-5;
	}
