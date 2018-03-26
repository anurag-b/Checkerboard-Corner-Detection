#include "iostream"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include <fstream>
 
using namespace cv;
using namespace std;

Mat img_cvt, img_blur, ithresh, img2,ithresh2;
int threshold_value = 190;
int threshold_type = 0;
int const max_BINARY_value = 255;
int maxCorners = 150;
double qualityLevel = 0.00676;
double minDistance = 75;
int blockSize = 6; //5.7
bool useHarrisDetector = true ;
double k = 0.04;
vector<Point2f> corners;
vector<vector<Point> > contours;
vector<Vec4i> hierarchy;
int largest_area=0;
int largest_contour_index=0;
int slargest_area=0;
int slargest_contour_index=0;
Rect bounding_rect;

int main()
{ 
	Mat img = imread("/home/dark_knight/UMD/Courses/CMSC498F Selected Topics in Computer Science; Robotics and Perception/Homework/homework_3/Imgs/4.jpg",CV_LOAD_IMAGE_COLOR);
	img2 = img;
	//namedWindow("Original",CV_WINDOW_NORMAL);
	//imshow("Original",img);
	cvtColor( img, img_cvt, CV_BGR2GRAY );//Converts RGB image to Gray
	//namedWindow("2",CV_WINDOW_NORMAL);
	//imshow("2",img_cvt);
	GaussianBlur( img_cvt, img_blur, Size( 5, 5 ), 0, 0, BORDER_DEFAULT );
	addWeighted(img_cvt, 0.5, img_blur, 0.5, 0, img_blur);
	//namedWindow("3",CV_WINDOW_NORMAL);
	//imshow("3",img_blur);
	threshold( img_blur, ithresh, threshold_value, max_BINARY_value,threshold_type );
	erode(ithresh, ithresh, Mat(), Point(), 2);
	//namedWindow("4",CV_WINDOW_NORMAL);
	//imshow("4",ithresh);
	findContours( ithresh, contours, hierarchy, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
	for(int j = 0; j<contours.size();j++)
	{
     		double a=contourArea( contours[j],false);  //  Find the area of contour
       		//cout << " Area: " << contourArea(contours[j]) << endl;
       		if(a>largest_area)
		{
       			largest_area=a;
       			largest_contour_index=j;                //Store the index of largest contour
       			bounding_rect=boundingRect(contours[j]); // Find the bounding rectangle for biggest contour
		}
	}

	for( int i = 0; i< contours.size(); i++ )
     	{
		double a=contourArea( contours[i],false);
		if(a<largest_area && a>slargest_area)
		{
			slargest_area = a;
			slargest_contour_index = i;
		}       
	}
	drawContours( ithresh, contours,slargest_contour_index, Scalar(255,255,255), -10, 8, hierarchy );
	dilate(ithresh, ithresh, Mat(), Point(), 10);
	threshold(ithresh , ithresh, threshold_value, max_BINARY_value,threshold_type );
	//namedWindow("5",CV_WINDOW_NORMAL);
	//imshow("5",ithresh2);
	erode(img_cvt, img_cvt, Mat(), Point(), 3);
	GaussianBlur( img_cvt, ithresh2, Size( 5, 5 ), 0, 0, BORDER_DEFAULT );
	threshold(ithresh2 , ithresh2, threshold_value, max_BINARY_value,threshold_type );
	goodFeaturesToTrack( ithresh2,
                       corners,
                       maxCorners,
                       qualityLevel,
                       minDistance,
                       ithresh,
                       blockSize,
                       useHarrisDetector,
                       k );
	cornerSubPix(ithresh2, corners, Size(11, 11), Size(-1, -1),
    	TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 40, 0.001));
	cout<<"** Number of corners detected: "<<corners.size()<<endl;
  	int r = 10;
  	for( int i = 0; i < corners.size(); i++ )
	{ 
		//cout<<corners[i];
		circle( img, corners[i], r, Scalar(0,0,255), -1, 8, 0 ); 
	}
	namedWindow( "Output", CV_WINDOW_NORMAL );
  	imshow( "Output", img );
	ofstream outputFile("/home/anuragb/Pictures/Corners.csv"); //Enter the location followed by file name
    	outputFile << format(corners, "CSV") << endl;
    	outputFile.close();
	waitKey(0);
	return 0;
}
