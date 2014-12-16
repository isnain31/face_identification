
 #include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
 #include <iostream>
#include<dirent.h>
 #include <string>
using namespace cv;
using namespace std;

String face_cascade_name = "haarcascade_frontalface_alt.xml";
CascadeClassifier face_cascade;

int main( int argc, char** argv )
{
 // char* imageName = argv[1];
 // string imageName = string(argv[1]);
 Mat image;
 if( !face_cascade.load( face_cascade_name ) ){ cout << "--(!)Error loading face cascade"; return -1; }; 

  string dirName = "../imagedb/pictures_database";
  DIR *dir;
    dir = opendir(dirName.c_str());
    string imgName;
    struct dirent *ent;
    if (dir != NULL) {
        while ((ent = readdir (dir)) != NULL) {
             imgName= ent->d_name;
	     if(imgName!="." && imgName!=".."){
		
                Mat img = imread(dirName+"/"+imgName);
		Mat frame_gray;

		cvtColor( img, frame_gray, COLOR_BGR2GRAY );
   		equalizeHist( frame_gray, frame_gray );	

		std::vector<Rect> faces;
		face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30) );
		
		 for ( size_t i = 0; i < faces.size(); i++ )
    		{
			cout << imgName << std::endl;			
			Mat faceROI = frame_gray( faces[i] );	
			imwrite( "../imagedb/greyed/"+imgName, faceROI );
		}

	     }
        }
        closedir (dir);
    }

waitKey(0);

 return 0;
}
