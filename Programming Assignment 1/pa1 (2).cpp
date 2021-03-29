#include<iostream>
#include<string>		/*string*/
#include <cstdlib>     /* srand, rand */
#include <ctime>       /* time */
using namespace std;


void generateSecretNumber(int *secretNumber, int digit);
/*Generate secret number*/

void addDigit(int *secretNumber, int& digit, int randomNumber);
/*If is randomNumber is valid adds number which needed digit*/

void seperateDigits(string str, int *inputArr , int digitNumber);
/*In this function there are two error checking 1- checks input not int value 2- check input valid digit* and also seperating nmbers*/
/*Also in this function number seperate digit by digit for example str = '1'2'3'4'5' inputArr[0] = 1 inputArr[1] = 2 ..*/

bool compare(int *secretNumber, int* inputArr, int digitNumber);
/*This function compares two arr to get hint*/

bool isUniqueNumber(int *, int);
/*Checks whether number is unique or not*/

int main(int argc, char const *argv[])
{
	string inputString;
	string s; //to hold the argv
	int turn = 0;//i started turn 0 but it working like the pdf
	bool is_find = false, is_unique = false;
	/*-to specify find the number or not -to checks whether input number is unique or not*/
	int digit;
	/*How many digit will be the secretNumber*/
	int secretNumberArr[10]/*={1,3,0,4,5,6}*/,inputArr[10]={1,3,0,4,5,6};
	/*I will holding secret number as an array because of easy to compare*/

	if (argc == 1)
	/*Missing parameter*/
	{
		cout<<"E0"<<endl;
		exit(1);
	}

	else if (argv[1][0] == '-' && argv[1][1] == 'r')
	{
		s = argv[2];
		if (s.length() != 1)
		/*if ./exe -r number parameter more than 9*/
			{
				cout<<"E0"<<endl;
				exit(1);
			}
			digit = argv[2][0] - 48;//-48 for ascii to int
		
		if (digit>9 || digit<1 )
		/*If digit minus and more than 9*/
		{
			cout<<"E0"<<endl;
			exit(1);
		}
		generateSecretNumber(secretNumberArr,digit);
	}

	else if (argv[1][0] == '-' && argv[1][1] == 'u')
	{
		s = argv[2];
		digit = s.length();

		for (int i = 0; i < digit ; ++i)
			secretNumberArr[i]=s[i]-48;//-48 for ascii to int also filling array 

		if (secretNumberArr[0]<1)
		/*First element of secret number can not be 0*/
		{
			cout<<"E0"<<endl;
			exit(1);
		}

		for (int i = 1; i < digit; ++i)
		/*If the input number is negative or not valid number to correspondig cell*/
		{
			if (secretNumberArr[i]>9 || secretNumberArr[i]<0)
			{
				cout<<"E0"<<endl;
				exit(1);
			}
		}

		is_unique=isUniqueNumber(secretNumberArr, digit);

		if (!(is_unique))
		/*If not unique*/
		{
			cout<<"E0"<<endl;
			exit(1);
		}
	}

	else
	/*Error checks other options -excepts -r and -u option-*/
	{
		cout<<"E0"<<endl;
		exit(1);
	}

	while(turn<100 && is_find==false)
	{
		cin>>inputString;
		seperateDigits(inputString, inputArr, digit);
		
		is_unique=isUniqueNumber(inputArr, digit);
		if (!(is_unique))
		{
			cout<<"E1"<<endl;
			exit(1);
		}

		is_find=compare(secretNumberArr, inputArr, digit);

		turn++;
	}

	if (is_find==true)
		cout<<"FOUND "<<turn<<endl;
	else
		cout<<"FAILED"<<endl;

	return 0;
}

bool isUniqueNumber(int* arr,int digit)
/*Checks whether number is unique or not*/
{
	int i,k,temp;
	for (i = 0; i < digit-1; ++i)
	{
		temp=arr[i];
		for (k=i+1; k <digit ; ++k)
		{
			if (temp==arr[k])
				return false;
		}
	}

	return true;
}


bool compare(int *secretNumber, int* inputArr, int digitNumber)
{
	int i,k, countExact = 0, countMisplaced = 0;
	for (int i = 0; i < digitNumber; ++i)
	/*This loop compares element which in the arrays one by one for example secretNumber={1,3,0,4,5,6}, inputArr={1,2,3,4,5,6} */
	{
		if (inputArr[i] == secretNumber[i] )
			countExact ++;

		else
		{/*If (secretNumber) digit is equal to corresponding (inputArr) digit countMisplaced 
			in the other hand in these loops search the misplaced number*/
			for (k = i+1; k < digitNumber; ++k)
			{
				if (inputArr[i] == secretNumber[k] )
					countMisplaced++;
			}

			for (k = i-1; k >= 0; k--)
			{
				if (inputArr[i] == secretNumber[k] )
					countMisplaced++;
			}
		}
	}
	
	if (countExact == digitNumber) //if user find the unique number
		return true;

	else
	{
		cout<<countExact<<" "<<countMisplaced<<endl;
		return false;
	}
}


void seperateDigits(string inputString, int *inputArr , int digitNumber)
/*In this function there are two error checking 1- checks input not int value 2- check input valid digit* and also seperating nmbers*/
{
	int i,number;

	for (i = 0; i < digitNumber; ++i)
			inputArr[i] = inputString[i]-48;
	
	for (i = 0; i < inputString.length(); ++i)
	/*checks input not int value*/
	{
		if (inputArr[i]>9 || inputArr[i]<0 )
		{
			cout<<"E2"<<endl;
			exit(1);
		}
	}

	if (digitNumber!=inputString.length())
	{/*check input valid digit*/
		cout<<"E1"<<endl;
		exit(1);
	}
}

void generateSecretNumber(int *secretNumber, int digit)
/*Generate secret number*/
{
	srand (time(NULL));

	int i,randomNumber;
	randomNumber = rand() % 9 +1;
	secretNumber[0]=randomNumber;
	/*(leftmost) digit cannot be 0 so firstly added random number first digit*/

	for (i = 1; i < digit; ++i)
	/*adding digit one by one with checking valid statements*/ 
	{
		randomNumber = rand() % 10;
		addDigit(secretNumber, i, randomNumber);
	}
}

void addDigit(int *secretNumber, int& digit, int randomNumber)
/*this funtion part of the generateSecretNumber funtion this function checks if the randoNumber valid to as a digit for secretNumber*/
{
	bool IsDigitValid = true;

	for (int i = 0; i < digit; ++i)
	{
		if (secretNumber[i] == randomNumber )
			IsDigitValid = false; 
	}

	if (IsDigitValid == true)
		secretNumber[digit]=randomNumber;

	else
		digit--;
	/*adding -1 because this random number is not valid so program will try again until finding valid random number for this digit*/
}