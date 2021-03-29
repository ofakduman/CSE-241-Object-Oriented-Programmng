#include<iostream>
#include<vector>
#include<string>
#include<fstream>
using namespace std;


typedef struct 
/*Each pixels value stored in RGB struct*/
{
	int r;
	int g;
	int b;
}RGB;

class ImageEditor{
public:
	ImageEditor();
	void loadImage(string nameOfImage);
	void grayScala(double c_r, double c_g, double c_b);
	void saveImage(string nameOfImage)const;
	bool FileIsOpened()const{return isFileOpened;}

private:
	void setWidthHeight(string lenghtString);
	bool isRightFormat();
	string format;	//format must be P3 for this Assignment
	int max_val;
	int width;
	int height;
	vector<RGB> pixel;
	bool isFileOpened;  //If any file opened this will be true
};


ImageEditor::ImageEditor(){
	/*for specify not assigned anything*/
	format = "Unasigned";
	max_val = -1;
	width = -1;
	height = -1;
	isFileOpened = false;
}

void ImageEditor::loadImage(string nameOfImageFile){

	ifstream inFile;

	inFile.open(nameOfImageFile);

	int r,b,g;

	string temp;

	if (!inFile) {
    	//Unable to open file 
    	exit(1);}

	getline(inFile, temp);
    while (temp[0] == '#')//if there is a comment before P3 
    	getline(inFile, temp);
	
    format = temp;
    
    if (!isRightFormat()){	/*In this assignment format must be P3*/
   		//"Unable to open file format
    	exit(1);}

    getline(inFile, temp);
    while (temp[0] == '#')
    	getline(inFile, temp);
   
    setWidthHeight(temp);	//set the width and height seperating the temp string

	getline(inFile, temp);
    while (temp[0] == '#')
    	getline(inFile, temp);

    max_val = stoi(temp);

    getline(inFile,temp);	//solution for after the max_value (255-in this assignment) if there is a comment which starting with # 
    if (temp[0]== '#'){
    	while (temp[0] == '#')
    		getline(inFile, temp);
    }
    
   	inFile.seekg(-(temp.size()+1),inFile.cur);	//after that programs inputs as a integer not line by line so cur. must be head of the img data

    for (int i = 0; i < height * width; ++i){
    	inFile>>r>>g>>b;
    	pixel.push_back(RGB());
		pixel[i].r = r;
		pixel[i].g = g;
		pixel[i].b = b;
    }

    inFile.close();

    isFileOpened = true;	//Image file loaded
}

bool ImageEditor::isRightFormat(){

	if (format[0] == 'P' && format[1] == '3')
	{
		format="P3";		//because line continue with # commend character
		return true;
	}
	else
		return false;
}

void ImageEditor::setWidthHeight(string lenghtString){
	int k = 0,m = 0;
	char Lengths[2][10];

	for (int i = 0; i < lenghtString.length(); ++i)
	{
		if (lenghtString[i] == ' ')
		/*to imminue whitespace*/{	
			if (m != 0)/*to immnue to double or more white space (ex: 117  157)*/{
					Lengths[k][m] = '\0';//define end of the char array
					k++;
					m = 0;
				}
			else
				m = 0;
		}
		else			
			Lengths[k][m++]=lenghtString[i];
	}

	Lengths[k][m] = '\0';//also define end of the last char array

	width = atoi(Lengths[0]);
	height = atoi(Lengths[1]);
}


void ImageEditor::saveImage(string nameOfImage)const{
	ofstream imageFile;
	imageFile.open(nameOfImage);
	imageFile<<format<<endl<<width<<" "<<height<<endl<<max_val<<endl;

	for (int i = 0; i < height * width; ++i)
		imageFile<<pixel[i].r<<endl<<pixel[i].g<<endl<<pixel[i].b<<endl;
}

void ImageEditor::grayScala(double c_r, double c_g, double c_b){

	double pixelColour;
	int pixelAvarage;

	for (int i = 0; i < height * width; ++i){    	
    	pixelColour = c_r*pixel[i].r + c_g*pixel[i].g + c_b*pixel[i].b;
    	
    	if (pixelColour>255)
    	   pixelColour = 255;
    	pixelAvarage = static_cast<int> (pixelColour);
		pixel[i].r = pixelAvarage;
		pixel[i].g = pixelAvarage;
		pixel[i].b = pixelAvarage;
    }
}

bool isCoefficientsAreValid(string tempRed, string tempGreen, string tempBlue, double& c_r, double c_g, double c_b)
/*This funtion is not member function because its about menu*/
{
	if (tempRed[0] == '0' && tempGreen[0] == '0' && tempBlue[0] == '0')
	/*starting with zero is says inputs are valid*/
	{
		c_r = stof(tempRed);		
		c_g = stof(tempGreen);
		c_b = stof(tempBlue);

		if (c_r >= 1 || c_g >= 1 || c_b >= 1)
		//this conditions necessery because user can inputs integer which starting with zero like 09, 03 etc
			return false;
		
		else
			return true;
	}
	else	
		return false;
}

int main(int argc, char const *argv[])
{	
	ImageEditor image;
	string nameOfImage;
	string coeffcnts;	//to check input is valid >Maybe user inputs not value<

	double c_r, c_g, c_b;	//coefficients
	char select = ' ';		//for menu

	string tempRed, tempGreen, tempBlue; //using when take coefficients in menu system

	while(select!='0'){
		
		cout<<"MAIN MENU"<<endl
		<<"0 - Exit"<<endl
		<<"1 - Open An Image(D)"<<endl
		<<"2 - Save Image Data(D)"<<endl
		<<"3 - Scripts(D)"<<endl;
		
		cin>>select;

		while (select == '1'){
			cout<<"OPEN AN IMAGE MENU"<<endl
			<<"0 - UP"<<endl
			<<"1 - Enter The Name Of The Image File"<<endl;
			cin>>select;
			if (select == '1'){
				cin>>nameOfImage;
				image.loadImage(nameOfImage);
			}
			else if (select == '0'){
				select = ' ';
			}
			else{
				exit(1);
			}
		}

		while (select == '2')
		{
			if (!image.FileIsOpened()){
				//Error file is not loaded yet
				exit(1);
				}

			else{
					cout<<"SAVE IMAGE DATA MENU"<<endl
					<<"0 - UP"<<endl
					<<"1 - Enter A File Name"<<endl;
					cin>>select;
					if (select == '1'){
						cin>>nameOfImage;
						image.saveImage(nameOfImage);
						select = '2';
					}
					else if (select == '0'){
						select = ' ';
					}
					
					else
						exit(1);
					
				}
		}
		while (select == '3')
		{

			if (!image.FileIsOpened()){
				//Error file is not loaded yet
				exit(1);
			}
			else{
					cout<<"CONVERT TO GRAYSCALE MENU"<<endl
					<<"0 - UP"<<endl
					<<"1 - Enter Coefficients For RED GREEN And BLUE Channels."<<endl;
					cin>>select;
					
					if (select == '1'){
						cin>>tempRed>>tempGreen>>tempBlue;
						if (isCoefficientsAreValid(tempRed,tempGreen,tempBlue,c_r, c_g, c_b))
						{
							image.grayScala(c_r, c_g, c_b);
							select = '3';
						}
						else//if coefficients not valid to grayscale program quits
							exit(1);
					}
					
					else if (select == '0'){
						select = ' ';
					}
					
					else
						exit(1);	
				}
		}
	}

	return 0;
}