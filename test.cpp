 #include "opencv2/objdetect/objdetect.hpp"
 #include "opencv2/highgui/highgui.hpp"
 #include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/core/core.hpp"

 #include <iostream>
 #include <stdio.h>
 #include <fstream>
 #include <sstream>
 #include <string>
 using namespace std;
 using namespace cv;

 /** Function Headers */
 void detectAndDisplay( Mat frame);

 /** Global variables */
 String face_cascade_name = "haarcascade_frontalface_alt.xml";
 CascadeClassifier face_cascade;
 string window_name = "Capture - Face detection";
// Ptr<FaceRecognizer> model = createLBPHFaceRecognizer(6,8,8,8,123.0);
 Ptr<FaceRecognizer> model = createLBPHFaceRecognizer();
 const string ppl[]={"santosh","nicolas","argen","dev","stepan","isnain","surya"} ;
 RNG rng(12345);

  
 /** @function main */
 int main( int argc, const char** argv )
 {
    
    CvCapture* capture;
    Mat frame;	
    

    if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };	
    
    model->load("face_model.xml");
    

    //-- 2. Read the video stream
    capture = cvCaptureFromCAM( 1 );
    if( capture )
    {
     while( true )
     {
    	frame = cvQueryFrame( capture );
        //-- 3. Apply the classifier to the frame
        if( !frame.empty() )
        { 

		detectAndDisplay( frame ); 
		//-- Show what you got
	        imshow( window_name, frame );

	}
        else
        { printf(" --(!) No captured frame -- Break!"); break; }

         int c = waitKey(10);
         if( (char)c == 'c' ) { break; }
        }
    }


    
     return 0;


 }






/** @function detectAndDisplay */
void detectAndDisplay( Mat frame )
{
  std::vector<Rect> faces;
  Mat frame_gray;

  cvtColor( frame, frame_gray, CV_BGR2GRAY );
  equalizeHist( frame_gray, frame_gray );
	

cout << "Model Information:" << endl;
    string model_info = format("\tLBPH(radius=%i, neighbors=%i, grid_x=%i, grid_y=%i, threshold=%.2f)",
            model->getInt("radius"),
            model->getInt("neighbors"),
            model->getInt("grid_x"),
            model->getInt("grid_y"),
            model->getDouble("threshold"));
    cout << model_info << endl;
    // We could get the histograms for example:
    vector<Mat> histograms = model->getMatVector("histograms");
    // But should I really visualize it? Probably the length is interesting:
    cout << "Size of the histograms: " << histograms[0].total() << endl; 


  //-- Detect faces
  face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );

  for( size_t i = 0; i < faces.size(); i++ )
  {
   // int predictedLabel = -1;
  //  double confidence = 0.0;
  int predictedLabel = model->predict(frame_gray( faces[i]));
  //  model->predict(frame_gray( faces[i] ), predictedLabel, confidence);	

    //imwrite( "test.bmp", frame_gray( faces[i] ) );	


    Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
    Point pp( faces[i].x,faces[i].y-10 );
    Point p( faces[i].x,faces[i].y );
    Point q( faces[i].x+ faces[i].width, faces[i].y + faces[i].height);
    //string result_message=format("%d", ppl[predictedLabel]);	
    putText(frame, ppl[predictedLabel], pp, FONT_HERSHEY_SCRIPT_SIMPLEX, 1,Scalar::all(255), 2, 8);

    rectangle(frame,p,q,Scalar( 0, 255, 0 ), 4, 8, 0 );	
  }
  return ;
 }
