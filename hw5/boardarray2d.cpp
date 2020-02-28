#include "boardarray2d.h"


BoardArray2D::BoardArray2D():BoardArray2D(9) {}
	
BoardArray2D::BoardArray2D(int size)
				:BoardArray2D(size,size){}

BoardArray2D::BoardArray2D(int length, int width)
				:length(length),width(width)
{	
	board = new int* [length];
	for (int i=0; i < length; i++)
		board[i] = new int[width];
			
	fillWithOrdered();
	board[length-1][width-1]=-5;/*-5 means last lement of array*/
}

BoardArray2D::BoardArray2D( BoardArray2D& other)						//copy constructor
				:/*length(other.getLength()),width(other.getWidth()),*/BoardArray2D(other.getLength(),other.getWidth()) 
{
	for (int i = 0; i < length; ++i)
	{
		for (int j = 0; j < width; ++j)
			board[i][j] = other(i,j);
	}
}	

BoardArray2D::~BoardArray2D()
{
	for (int i = 0; i < length; i++)
        delete[] board[i];

    delete[] board;
}

void BoardArray2D::fillWithOrdered()
{
	for (int i = 0; i < length; ++i)
	{
		for (int j = 0; j < width ; ++j)
		{
			board[i][j]=i*width+j+1;
		}
	}
}

ostream& operator <<(ostream& OutputStream,const BoardArray2D& obj)
{
	for (int i = 0; i < obj.length; ++i)
	{
		for (int j = 0; j < obj.width; ++j)
		{
			if (obj.board[i][j]==0)
				OutputStream<<"00 ";

			else if (obj.board[i][j]==-5)
				OutputStream<<"   ";

			else if (obj.board[i][j]<10)
				OutputStream<<"0"<<obj.board[i][j]<<" ";

			else 
				OutputStream<<obj.board[i][j]<<" ";
		}
		OutputStream<<endl;
	}

	return OutputStream;
}

void BoardArray2D::setSize(int size/*int lengthValue, int widthValue*/)
{

	for (int i = 0; i < length; i++)
        delete[] board[i];

    delete[] board;

	length = size;
	width = size;

	board = new int* [length];
	for (int i=0; i < length; i++)
		board[i] = new int[width];

	fillWithOrdered();

	board[length-1][width-1]=-5;/*-5 means last lement of array*/

	shuffle();
}
	
void BoardArray2D::print()
{
	cout<<*this;
	/*print with overloaded << operator*/
}

void BoardArray2D::readFromFile(char*argv[],int argc)
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

	deleteArr();			//free

	width=n;
	length=m;

	board = new int* [length];		/*Creating new 2d dynamic array*/
		
		for (int f=0; f < length; f++)
			board[f] = new int[width];

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
	inStream.close();
	outStream.close();

	finds_zeros_in_board();
}

void BoardArray2D::	deleteArr()
{
	
	for (int i = 0; i < length; i++)
        delete[] board[i];

    delete[] board;
}


void BoardArray2D::writeToFile()const
{
	ofstream outStream;

	char outFile[15];
	
	cout<<"Input the filename: ";
	cin>>outFile;
	outStream.open(outFile);

	for (int i = 0; i < length; ++i)
	{
		for (int j = 0; j < width; ++j)
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

void BoardArray2D::shuffle()
{
	cout<<"----Rondomizing board----"<<endl;
	for (int i = 0; i < width; ++i)
		moveRandom();
}

void BoardArray2D::moveRandom()
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


void BoardArray2D::move(char direction)
{
	int location[2], i,j,temp;			//location of empty cell which  location[0]=i, location[1]=j
	find_location(location);		//finds empty cell locatio
	i=location[0];
	j=location[1];
		moves++;
	if (direction=='U' || direction=='u')
	{
		if (i>0 && board[i-1][j]!=0)
		{
			temp=board[i][j];
			board[i][j]=board[i-1][j];
			board[i-1][j]=temp;
			last_move='U';
		}
	}

	else if (direction=='D' || direction=='d')
	{
		if (i<length-1 && board[i+1][j]!=0)
		{
			temp=board[i][j];
			board[i][j]=board[i+1][j];
			board[i+1][j]=temp;
			last_move='D';
		}
	}
	else if (direction=='R' || direction=='r' )
	{
		if (j<width-1 && board[i][j+1]!=0)
		{
			temp=board[i][j];
			board[i][j]=board[i][j+1];
			board[i][j+1]=temp;
			last_move='R';
		}
	}
	if (direction=='L' || direction=='l')
	{
		if (j>0 && board[i][j-1]!=0)
		{
			temp=board[i][j];
			board[i][j]=board[i][j-1];
			board[i][j-1]=temp;
			last_move='L';
		}
	}
}


void BoardArray2D::find_location(int location[2])const
{
	for (int i = 0; i < length; ++i)
		for (int j = 0; j <width ; ++j)
			if (board[i][j]==-5)
			{
				location[0]=i;
				location[1]=j;
				return;
			}
}


void BoardArray2D::reset(){ 
	while(isSolved()){
		for (int i = 0; i < length*width; ++i)
			moveRandom();
	}
}

bool BoardArray2D::isSolved()const
{
	int counter=1;

	/*if (board[length-1][width-1]!=-5)
		return false;
*/
	for (int i = 0; i <length ; ++i)
	{
		for (int j = 0; j < width ; ++j)
		{
			if (board[i][j]!=0 && board[i][j]!=-5)			//-5 empty cell (bb)
			{
				if (board[i][j]==counter)
					counter++;
				
				else 
					return false;
			}
			else if (board[i][j]==-5)
				counter--;
		}
	}
	return true;}

BoardArray2D& BoardArray2D::operator =(BoardArray2D& rightSide)
{
	if (length == rightSide.getLength() && length == rightSide.getWidth())
	{
		for (int i = 0; i < length; ++i)
		{
			for (int j = 0; j < width ; ++j)
				board[i][j] = rightSide(i,j);
		}
	}

	else
	{
		deleteArr();

    	length = rightSide.getLength();
		width = rightSide.getWidth();

		board = new int* [length];		/*Creating new 2d dynamic array*/
		
		for (int i=0; i < length; i++)
			board[i] = new int[width];
			
		fillWithOrdered();

		board[length-1][width-1]=-5;/*-5 means last lement of array*/

		for (int i = 0; i < length; ++i)
		{
			for (int j = 0; j < width; ++j)
				board[i][j] = rightSide(i,j);
		}		
	}

	return *this;
}

int BoardArray2D::operator ()(int i,int j)
{
	if (length<=i || width<=j)
	{
		cout<<"Invalid input!!"<<endl;
		exit(1);
	}
	return board[i][j];
}


void BoardArray2D::intellegent()
{
	Directions move_direction;
	bool is_loop;
	int locations[2], i,j,value_of_empty_card, difference_up,
	difference_down, difference_right, difference_left, temp_value;
	int total_zero;		//this contains how many zero in the board 

	find_location(locations);
	i=locations[0];				//i
	j=locations[1];				//j


	total_zero=total_zeros(i);			//e kadar olan toplam 0

	value_of_empty_card=i*width+j-total_zero+1;


	if (i!=0 && board[i-1][j]!=0)
	{
		temp_value=board[i-1][j];
		if (temp_value+width==value_of_empty_card)
			difference_up=98;
		else	
			difference_up=value_of_empty_card-temp_value;
				if (difference_up<0)
					difference_up*=-1;
	}
	else
		difference_up=99;
	
	if (j<width-1 && board[i][j+1]!=0)
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

	if (i<length-1 && board[i+1][j]!=0)
	{

		temp_value=board[i+1][j];
		if (temp_value-length==value_of_empty_card)
			difference_down=98;
		else
			difference_down=value_of_empty_card-temp_value;
			if (difference_down<0)
				difference_down*=-1;
	}
	else
		difference_down=99;

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
void BoardArray2D::finds_zeros_in_board()		//tahtadaki 0 lari saymak icin turetilen bir fonksiyon
{
	int k=0,i,j;

	for (i = 0; i < 9 ; ++i)
		for (j = 0; j < 2; ++j)
			zeros[i][j]=0;

	for (i = 0; i <length ; ++i)
	{	
		for ( j = 0; j < width; ++j)
		{
			if (board[i][j]==0)
				++zeros[i][k];

			if (k==0 && board[i][j]!=0)				//sayi gorene kadar gider ve sagdaki 0 larinda sayilmalarinin saglar
				k=1;
		}
		k=0;										//yeni satira gectiginde soldaki sifirlari sayar
	}	

	for (i = 0; i < 9 ; ++i)
	{	for (j = 0; j < 2; ++j)
		{
			cout<<zeros[i][j];
		}
		cout<<endl;
	}
}	
int BoardArray2D::total_zeros(int location_y)	//total 0's up to the target location
{
	int total_zero=0,i,j;

	for (i = 0; i <= location_y ; ++i)
	{
		for (j = 0; j < 2 ; ++j)
		{
			total_zero= total_zero +zeros[i][j];
		}
	}

	total_zero-=zeros[i-1][1];
	return total_zero;
}

Directions BoardArray2D::find_direction(int up,int down, int right, int left)
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

bool BoardArray2D::Is_loop(Directions direction)	//when intellegent moves checks whether looping or not
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
void BoardArray2D::solvePuzzle()
{
	int move_counter=0;

	clock_t start, end;
	start = clock();
	double cpu_time_used;
	
	while(!isSolved())
	{
		print();
		intellegent();
		move_counter++;
		cout<<"--------------------"<<endl;
	}

	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;					//execution time added
	cout<<"Execution time: "<<cpu_time_used<<" seconds (in more intellegent algorithm) \nThanks for waiting!"<<endl<<"Moves = "<<move_counter<<endl;
}

bool operator ==(const BoardArray2D& obj1, const BoardArray2D& obj2)
{
	if (obj1.length==obj2.length && obj1.width==obj2.width)
	{
		for (int i = 0; i < obj1.length; ++i)
		{
			for (int j = 0; j < obj1.width; ++j)
			{
				if (obj1.board[i][j]!=obj2.board[i][j])
					return false;
			}
		}

		return true;
	}

	else
		return false;

}

int BoardArray2D::NumberOfBoards(){return number_of_boards;}
