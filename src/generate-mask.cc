// generate masks of text regions for the OCR process
// Please read README.txt for information and build instructions.
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <iostream>



using namespace cv;
using namespace std;

bool ok=true;
bool destroy=false;
Rect box;
bool drawing_box = false;


void my_mouse_callback( int event, int x, int y, int flags, void* param );

void draw_box(Mat * img, Rect rect){
	rectangle(*img, Point(box.x, box.y), Point(box.x+box.width,box.y+box.height),Scalar(0,0,255) ,2);
	Rect rect2=Rect(box.x,box.y,box.width,box.height);
}

// mouse callback
void my_mouse_callback( int event, int x, int y, int flags, void* param){
	Mat* frame = (Mat*) param;
	switch( event )  {
		case CV_EVENT_MOUSEMOVE: {
			if( drawing_box ) {
				box.width = x-box.x;
				box.height = y-box.y;
			}
		}		
		break;
		case CV_EVENT_LBUTTONDOWN: {   
			drawing_box = true;
			box = Rect( x, y, 0, 0 );
		}
		break;
		case CV_EVENT_LBUTTONUP: {   
			drawing_box = false;
			if( box.width < 0 )  {   
				box.x += box.width;
				box.width *= -1;      
			}
			if( box.height < 0 ){   
				box.y += box.height;
				box.height *= -1; 
			}
			draw_box(frame, box); 
		}        
		break;
		case CV_EVENT_RBUTTONDOWN: {
			ok=false;
			break; 
		}
		break; 	    
		default:
		break;
	}
}

  
    
// Main function: generates image mask for the OCR process
// Input : image and an output filename
// Output: save the mask in the output filename
// This function displays the input image.
// Draw a rectangle using the mouse and use the right click to confirm

int main(int argc,char **argv){
	// print usages
	if(argc != 3){
		std::cerr << "usage: " << argv[0] << " image.png output_mask.png" << std::endl;
		return 1;
	}
	
	String name = "Box masks";
	namedWindow(name);
	
	// Initialize the rectalgle
	box = Rect(0,0,1,1);
	
	// load the input image 
	Mat image = imread(argv[1],CV_LOAD_IMAGE_COLOR);
	
	// Check for invalid input
    if(!image.data ){
		std::cerr <<  "Could not open or find the image" << std::endl ;
        return -1;
    }
    
	
	
	
	Mat temp = image.clone();
	
	//Set mouse handler for the window 
	setMouseCallback(name, my_mouse_callback, &image);
	// display until rectangle confirmation 
	while(ok){
		temp = image.clone();
		if (drawing_box) draw_box(&temp, box);
		imshow(name, temp);
		if (waitKey(15) ==0) break;
	}
	  
	cv::destroyWindow(name);
	
	// create the mask
	Size s = image.size();
	Mat atom_image = Mat::zeros(s.height,s.width, CV_8UC3 );
	
	// add the rectangle
	rectangle(atom_image,  box, Scalar(255,255,255), -1, 8, 0);
	//save mask
	imwrite(argv[2], atom_image);		
	
	return 0;
}
