#include "boardarray1d.h"

BoardArray1D::BoardArray1D():BoardArray1D(9) {}
	
BoardArray1D::BoardArray1D(int size)
				:BoardArray1D(size,size){}


			
BoardArray1D::BoardArray1D(int length_size, int width_size)
				:length(length_size),width(width_size)
{	
	board = new int [length*width];

	fillWithOrdered();
	board[length*width-1]=-5;/*-5 means last lement of array*/
	number_of_boards++;
}

void BoardArray1D::fillWithOrdered()
{
	for (int i = 0; i < length*width; ++i)
		board[i]=i+1;
}


void BoardArray1D::setSize(int size)
{
	delete[] board;
	length = size;
	width = size;
	board = new int [length*width];
	fillWithOrdered();
	board[length*width-1]=-5;/*-5 means last lement of array*/
	number_of_boards++;
	shuffle();
}

ostream& operator <<(ostream& OutputStream,const BoardArray1D& obj)
{
	for (int i = 0; i < obj.length*obj.width; ++i)
	{
		if (obj.board[i]==0)
			OutputStream<<"00 ";

		else if (obj.board[i]==-5)
			OutputStream<<"   ";

		else if (obj.board[i]<10)
			OutputStream<<"0"<<obj.board[i]<<" ";

		else 
			OutputStream<<obj.board[i]<<" ";

		if ((i+1)%obj.width==0 )
			OutputStream<<endl;
	
	//OutputStream<<endl;
	}
	return OutputStream;
}

void BoardArray1D::print()
{
	cout<<*this;
	/*print with overloaded << operator*/
}

void BoardArray1D::readFromFile(char*argv[],int argc)
{
	char chrctr, an_element[2];
	int i=0,j=0,k=0, number,m=0,l=0,n=0;
	ifstream inStream,findStream;
	ofstream outStream;
	char inFile[15];

	if (argc > 1)
	{
		inStream.open(argv[1]);
		findStream.open(argv[1]);
	}

	else
	{
		cout<<"Input the filename: ";
		cin>>inFile;
		inStream.open(inFile);
		findStream.open(inFile);
	}
	
	if (inStream.fail()){
		cout<<"This : "<<inFile<<" file didnt find!"<<endl<<"Make sure is name correct"<<endl;
		exit(1);}

	findStream.get(chrctr);

	while (! findStream.eof( ))		//to find to board`s length and width
	{	
		if (chrctr=='\n')
		{
			m++;
			n=l/2;
			l=0;
		}
		else if (chrctr!=' ')
			l++;		

		findStream.get(chrctr);
	}

	delete[] board;

	width=n;
	length=m;

	board = new int [length*width];		/*Creating new 2d dynamic array*/
		

	inStream.get(chrctr);
	while (! inStream.eof( ))
	{
		if (chrctr=='b')
		{
			inStream.get(chrctr);
			board[i]=-5;
			i++;
		}
		else if (chrctr=='0')
		{
			inStream.get(chrctr);
			
			if (chrctr=='0')
				{
					board[i]=0;
					i++;
				}
			else
			{
					board[i]=int(chrctr)-48;
					i++;
			}
		}
		else if (chrctr=='\n'){j=0;}

		else if (chrctr!=' ')
		{
			number= (int(chrctr)-48)*10;
			inStream.get(chrctr);
			number=number+int(chrctr)-48;
			board[i]=number;
			i++;
			//j++;
		}		
		inStream.get(chrctr);
	}
	inStream.close();
	outStream.close();
}

void BoardArray1D::writeToFile()const
{
	ofstream outStream;

	char outFile[15];
	
	cout<<"Input the filename: ";
	cin>>outFile;
	outStream.open(outFile);

	for (int i = 0; i < length*width; ++i)
	{
			if (board[i]==0)
				outStream<<"00 ";

			else if (board[i]==-5)
					outStream<<"bb ";

			else if (board[i]<10)
				outStream<<"0"<<board[i]<<" ";

			else 
				outStream<<board[i]<<" ";

			if ((i+1)%width==0)
				outStream<<endl;
	}
	cout<<"File saved succesfully!"<<endl;
}


void BoardArray1D::shuffle()
{
	cout<<"----Rondomizing board----"<<endl;
	for (int i = 0; i < width; ++i)
		moveRandom();
}

void BoardArray1D::moveRandom()
{
	int random;

		random=rand()%4+1;			//for assignment random direction 1 is up 2 is down 3 is right 4 is left
		if (random==1)
			move('U');
		else if (random==2)
			move('D');
		else if (random==3)
			move('R');
		else if (random==4)
			move('L');

		moves++;
}


void BoardArray1D::move(char direction)
{
	int i,j,temp;			//location of empty cell which  location[0]=i, location[1]=j
	i=find_location();		//finds empty cell locatio
	moves++;
	if (direction=='U' || direction=='u')
	{
		if (i>=width && board[i-width]!=0)
		{	
			temp=board[i];
			board[i]=board[i-width];
			board[i-width]=temp;
			last_move='U';
		}
	}

	else if (direction=='D' || direction=='d')
	{
		if (board[i+width]!=0 && i<length*(width-1))
		{
			temp=board[i];
			board[i]=board[i+width];
			board[i+width]=temp;
			last_move='D';
		}
	}
	else if (direction=='R' || direction=='r' )
	{
		if ((i+1)%width!=0 && board[i+1]!=0)
		{
			temp=board[i];
			board[i]=board[i+1];
			board[i+1]=temp;
			last_move='R';
		}
	}
	if (direction=='L' || direction=='l')
	{
		if (i>0 && i%width!=0 )
		{
			if (board[i-1]!=0)
			{
				temp=board[i];
				board[i]=board[i-1];
				board[i-1]=temp;
				last_move='L';
			}
		}
	}
}


int BoardArray1D::find_location()const
{
	for (int i = 0; i < length*width; ++i)
			if (board[i]==-5){return i;}
}


void BoardArray1D::reset(){ 
	while(isSolved()){
		for (int i = 0; i < length*width; ++i)
			moveRandom();
	}
}

bool BoardArray1D::isSolved()const
{
	int counter=1;
	for (int i = 0; i <length*width ; ++i)
	{
		if (board[i]!=0 && board[i]!=-5)			//-5 empty cell (bb)
		{
			if (board[i]==counter)
				counter++;
			
			else 
				return false;
		}
		else if (board[i]==-5)
			counter--;
	}
	return true;}


int BoardArray1D::operator ()(int i,int j)
{
	if (length<i || width<j)
	{
		cout<<"Invalid input!!"<<endl;
		exit(1);
	}
	return board[(i*width)+j];
}

void BoardArray1D::intellegent()
{
	Directions move_direction;
	bool is_loop;
	int locationIndex, i,j,value_of_empty_card, difference_up,
	difference_down, difference_right, difference_left, temp_value;
	int total_zero;		//this contains how many zero in the board 

	i=find_location();

	total_zero=total_zeros(i);			//e kadar olan toplam 0

	value_of_empty_card=i-total_zero+1;


	if (i>=width && board[i-width]!=0)			//yukarisi ile olan fark
	{
		temp_value=board[i-width];
		if (temp_value+width==value_of_empty_card)
			difference_up=98;
		else	
			difference_up=value_of_empty_card-temp_value;
				if (difference_up<0)
					difference_up*=-1;
	}
	else
		difference_up=99;
	
	if ((i+1)%width!=0 && board[i+1]!=0)
	{	
		temp_value=board[i+1];
		if (temp_value-1==value_of_empty_card)
			difference_right=98;
		else
			difference_right=value_of_empty_card-temp_value;
				if (difference_right<0)
					difference_right*=-1;	
	}
	else 
		difference_right=99;

	if (i%width!=0 && board[i-1]!=0)
	{
		temp_value=board[i-1];
		if (temp_value+1==value_of_empty_card)
				difference_left=98;
		else
			difference_left=value_of_empty_card-temp_value;
				if (difference_left<0)
					difference_left*=-1;
	}
	else
		difference_left=99;

	if (i<=length*(width-1) && board[i+width]!=0)
	{

		temp_value=board[i+width];
		if (temp_value-length==value_of_empty_card)
			difference_down=98;
		else
			difference_down=value_of_empty_card-temp_value;
			if (difference_down<0)
				difference_down*=-1;
	}
	else
		difference_down=99;

	
	cout<<"down = "<<difference_down<<"	up = "<<difference_up<<"	right = "<<difference_right<<"	left = "<<difference_left<<endl;


	move_direction=find_direction(difference_up,difference_down,difference_right,difference_left);	//finds intellegent direction according to difference

	is_loop=Is_loop(move_direction);
	if (is_loop==true)
	{
		cout<<"------------Rondomizing----------"<<endl;
		for (int i = 0; i < length-(length/4); ++i)
			moveRandom();
		loop[0]=-1;
		loop[1]=-1;
	}
		if (move_direction==Up)
			move('U');

		else if (move_direction==Down)
			move('D');
			
		else if (move_direction==Right)
			move('R');

		else if (move_direction==Left)
			move('L');
}

bool BoardArray1D::Is_loop(Directions direction)	//when intellegent moves checks whether looping or not
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

Directions BoardArray1D::find_direction(int up,int down, int right, int left)
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

int BoardArray1D::total_zeros(int location)	//total 0's up to the target location
{
	int total_zero=0,i,j;

	for (i = 0; i <= location ; ++i)
	{
		if (board[i]==0)
		{
			total_zero++;
		}
	}
	return total_zero;
}

void BoardArray1D::solvePuzzle()
{

	clock_t start, end;
	start = clock();
	double cpu_time_used;
	
	while(!isSolved())
	{
		print();
		intellegent();
		cout<<"--------------------"<<endl;
	}

	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;					//execution time added
	cout<<"Execution time: "<<cpu_time_used<<" seconds (in more intellegent algorithm) \nThanks for waiting!"<<endl<<"Moves = "<<moves<<endl;
}

bool operator ==(const BoardArray1D& obj1, const BoardArray1D& obj2)
{
	if (obj1.length==obj2.length && obj1.width==obj2.width)
	{
		for (int i = 0; i < obj1.length*obj2.width; ++i)
		{
			if (obj1.board[i]!=obj2.board[i])
				return false;
		}

		return true;
	}

	else
		return false;

}

BoardArray1D::~BoardArray1D()
{
    delete[] board;
    number_of_boards--;
}

int BoardArray1D::NumberOfBoards(){return number_of_boards;}


