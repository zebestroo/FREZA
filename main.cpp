#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
//It's only convert!!!
//Fun taska convert to black color
int main()
{
	Mat myimg = imread("lalka.jpg");
	ofstream out("file.txt");
	if(out.is_open())	
	for(int i = 0; i < myimg.rows; i++) //Sortirovka na 4ernoe i beloe...
        {
		for(int j = 0; j < myimg.cols; j++)
        	//Tyt 4isla 150 variiryesh i menyaesh spectr obrabotki
		{
			if(myimg.at<Vec3b>(i,j)[0] < 150 && myimg.at<Vec3b>(i,j)[1] < 150  && myimg.at<Vec3b>(i,j)[2] < 150)
			{
				out << 0;
				myimg.at<Vec3b>(i,j)[0]= 0;
                       		myimg.at<Vec3b>(i,j)[1]= 0;
                        	myimg.at<Vec3b>(i,j)[2]= 0;
			}
			else
			{
				out << 1;
				myimg.at<Vec3b>(i,j)[0]= 255;
                                myimg.at<Vec3b>(i,j)[1]= 255;
                                myimg.at<Vec3b>(i,j)[2]= 255;
			}
		}
		out << '\n';
		
		for(int j = myimg.cols; j >= 0; j--)
        	//Tyt 4isla 150 variiryesh i menyaesh spectr obrabotki
		{
			if(myimg.at<Vec3b>(i,j)[0] < 150 && myimg.at<Vec3b>(i,j)[1] < 150  && myimg.at<Vec3b>(i,j)[2] < 150)
			{
				out << 0;
				myimg.at<Vec3b>(i,j)[0]= 0;
                       		myimg.at<Vec3b>(i,j)[1]= 0;
                        	myimg.at<Vec3b>(i,j)[2]= 0;
			}
			else
			{
				out << 1;
				myimg.at<Vec3b>(i,j)[0]= 255;
                                myimg.at<Vec3b>(i,j)[1]= 255;
                                myimg.at<Vec3b>(i,j)[2]= 255;
			}
		}
		out << '\n';
	}

	
	out << '\0';

	out.close();
	imwrite("imagess.jpg", myimg);
	return 0;	
}
