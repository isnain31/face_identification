
 #include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
 #include <iostream>
#include<dirent.h>
 #include <string>
using namespace cv;
using namespace std;


int main( int argc, char** argv )
{
 // char* imageName = argv[1];
 // string imageName = string(argv[1]);
 Mat image;


  string dirName = "../imagedb/pictures_database";
  DIR *dir;
    dir = opendir(dirName.c_str());
    string imgName;
    struct dirent *ent;
    if (dir != NULL) {
        while ((ent = readdir (dir)) != NULL) {
             imgName= ent->d_name;
	     if(imgName!="." && imgName!=".."){
		cout << imgName << std::endl;
             Mat img = imread(dirName+"/"+imgName);
             Mat gray_image;
	     cvtColor( img, gray_image, CV_BGR2GRAY );

		imwrite( "../imagedb/greyed/"+imgName, gray_image );
		}
        }
        closedir (dir);
    }



 /*namedWindow( imageName, CV_WINDOW_AUTOSIZE );
 namedWindow( "Gray image", CV_WINDOW_AUTOSIZE );

 imshow( imageName, image );
 imshow( "Gray image", gray_image );
 */

 waitKey(0);

 return 0;
}
