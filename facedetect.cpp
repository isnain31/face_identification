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
 Ptr<FaceRecognizer> model = createLBPHFaceRecognizer(6,8,8,8,123.0);
 RNG rng(12345);

 static void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels, char separator = ';') {
    std::ifstream file(filename.c_str(), ifstream::in);
    if (!file) {
        string error_message = "No valid input file was given, please check the given filename.";
        CV_Error(CV_StsBadArg, error_message);
    }
    string line, path, classlabel;
    while (getline(file, line)) {
        stringstream liness(line);
        getline(liness, path, separator);
        getline(liness, classlabel);
        if(!path.empty() && !classlabel.empty()) {
            images.push_back(imread(path, CV_LOAD_IMAGE_GRAYSCALE));
	     if(! imread(path, 0).data )                              // Check for invalid input
    {
        cout <<  "Could not open or find the image" << std::endl ;
        
    }
            labels.push_back(atoi(classlabel.c_str()));
        }
    }
}

  
 /** @function main */
 int main( int argc, const char** argv )
 {
    if (argc != 2) {
        cout << "usage: " << argv[0] << " <csv.ext>" << endl;
        exit(1);
    }
    
    string fn_csv = string(argv[1]);
    // These vectors hold the images and corresponding labels.
    vector<Mat> images;
    vector<int> labels;
    CvCapture* capture;
    Mat frame;	
    try {
        read_csv(fn_csv, images, labels);
    } catch (cv::Exception& e) {
        cerr << "Error opening file \"" << fn_csv << "\". Reason: " << e.msg << endl;
        exit(1);
    }

    // Quit if there are not enough images for this demo.
    if(images.size() <= 1) {
        string error_message = "This demo needs at least 2 images to work. Please add more images to your data set!";
        CV_Error(CV_StsError, error_message);
    }

    if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading\n"); return -1; };	
    

    //int height = images[0].rows;
    //Mat testSample = images[images.size() - 1];
    //int testLabel = labels[labels.size() - 1];
    //images.pop_back();
    //labels.pop_back();
    
    model->train(images, labels);
    

    //-- 2. Read the video stream
    capture = cvCaptureFromCAM( -1 );
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


    
    //string result_message = format("Predicted class = %d / Actual class = %d. / confidence= %f", predictedLabel, testLabel, confidence);
    //string result_message = format("Predicted class = %d /  confidence= %f", predictedLabel, confidence);
    //cout << result_message << endl;
    // model->set("threshold", 0.0);
    //predictedLabel = model->predict(testSample);
    //cout << "Predicted class = " << predictedLabel << endl;
    


    /* 
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
	waitKey(0);     
    */	

    return 0;


 }






/** @function detectAndDisplay */
void detectAndDisplay( Mat frame )
{
  std::vector<Rect> faces;
  Mat frame_gray;

  cvtColor( frame, frame_gray, CV_BGR2GRAY );
  equalizeHist( frame_gray, frame_gray );

  //-- Detect faces
  face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );

  for( size_t i = 0; i < faces.size(); i++ )
  {
    int predictedLabel = -1;
    double confidence = 0.0;
    model->predict(frame_gray( faces[i] ), predictedLabel, confidence);	
    Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
    Point pp( faces[i].x,faces[i].y-10 );
    Point p( faces[i].x,faces[i].y );
    Point q( faces[i].x+ faces[i].width, faces[i].y + faces[i].height);
    string result_message=format("%d", predictedLabel);	
    putText(frame, result_message, pp, FONT_HERSHEY_SCRIPT_SIMPLEX, 1,Scalar::all(255), 2, 8);

    rectangle(frame,p,q,Scalar( 0, 255, 0 ), 4, 8, 0 );	
  }
  return ;
 }
