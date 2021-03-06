
//OpenCV
#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"
#include "opencv2/features2d.hpp"

//std
#include <iostream>
#include <cstdlib>
#include <vector>

// Utilitzem aquestes comandes per estalbiar posar cv:: , std::

using namespace cv;
using namespace std;

//consts
const unsigned int MIN_NUM_FEATURES = 1000; //minimum number of point fetaures

int main(int argc, char *argv[])
{
    cv::VideoCapture camera; //OpenCV video capture object
    cv::Mat image; //OpenCV image object
	  int cam_id; //camera id . Associated to device number in /dev/videoX
    cv::Ptr<cv::ORB> orb_detector = cv::ORB::create(); //ORB point feature detector
    orb_detector->setMaxFeatures(MIN_NUM_FEATURES);
    std::vector<cv::KeyPoint> point_set; //set of point features
    cv::Mat descriptor_set; //set of descriptors, for each feature there is an associated descriptor

    // Declarem les variables Mat que utilitzarem per poder crear Feature points en un rectangle de la imatge

    cv::Mat grayimage;
    cv::Mat Mask;
    cv::Mat roi;

    cv::Mat edge;
    cv::Mat draw;

    // Variables que s'han creat per fer un escanejat dels Feature points amb una Mascara (Estan bloquejats perque no ha funcionat el programa)

/*
    int h_division;
    int v_division;
    int n_cols;
    int n_rows;
    int i;
    int j;
    int k;
    int l;
    int Px;
    int Py;

*/

  //check user args
	switch(argc)
	{
		case 1: //no argument provided, so try /dev/video0
			cam_id = 0;
			break;
		case 2: //an argument is provided. Get it and set cam_id
			cam_id = atoi(argv[1]);
			break;
		default:
			std::cout << "Invalid number of arguments. Call program as: webcam_capture [video_device_id]. " << std::endl;
			std::cout << "EXIT program." << std::endl;
			break;
	}

	//advertising to the user
	std::cout << "Opening video device " << cam_id << std::endl;

    //open the video stream and make sure it's opened
    if( !camera.open(cam_id) )
	{
        std::cout << "Error opening the camera. May be invalid device id. EXIT program." << std::endl;
        return -1;
    }

    //Process loop. Capture and point feature extraction. User can quit pressing a key
    while(1)
	{
		//Read image and check it. Blocking call up to a new image arrives from camera.
        if(!camera.read(image))
		{
            std::cout << "No image" << std::endl;
            cv::waitKey();
        }

    //**************** Find ORB point fetaures and descriptors ****************************

        //Crear imatge gris

        cv::cvtColor( image, grayimage, CV_BGR2GRAY );

        // Assignar una variable Color (D'aquesta manera podem triar el color de les Keypoints)

        Scalar Color = Scalar(0,255,0); //Assignar a la variable Color el color verd "Scalar(0,255,0)-> Green"

        //clear previous points
        point_set.clear();

        // Assignem a la Mascara (Mask, que es una mascara de tota la imatge) a valors 0

        Mat Mask = Mat::zeros(image.size(), CV_8U);

        // Comanda per poder moure una Mascara dins la imatge

        Mat roi(Mask, cv::Rect(250,150,220,300)); // Només visualitzem KeyPoints en aquest Rectangle, Rect(X_position, Y_position, Mask_width, Mask_Height)

        // Hem col·locat el rectangle perque nomes detecti la zona central de la webcam (Cara) valors (250,150,220,300)

        roi = Scalar(255);

        //Aquest es el codi per fer un escanejat dels Feature points amb una Mascara (Es divideix la imatge amb 12 rectangles) -> No funciona

/*
        n_cols = image.cols;
        n_rows = image.rows;
        h_division = 2;
        v_division = 2;

        Mask = Mat::zeros((n_rows/h_division),(n_cols/v_division),CV_32F);

        for (i=0; i<= v_division; i++)
        {
          for (j=0; j<= h_division; j++)
          {
            for (k=0; k<= (n_cols/v_division); k++)
            {
              for (l=0; l<= (n_rows/h_division); l++)
              {
                Px = i*(n_cols/v_division)+ k;
                Py = j*(n_rows/h_division)+ l;
                Mask = Mat(Px,Py,CV_32F);
                Mask = 255;
              }
            }
          }
        }

*/

        //detect and compute(extract) features
        orb_detector->detectAndCompute(grayimage, Mask, point_set, descriptor_set);

        //draw points on the image
        cv::drawKeypoints(grayimage, point_set, grayimage, Color, cv::DrawMatchesFlags::DEFAULT );

        // Programa per crear el contorn de la imatge (Canny)

        Canny(grayimage, edge, 50, 150, 3);

        edge.convertTo(draw, CV_8U);


    //********************************************************************

        //Mostrem imatge amb escala de grisos i amb els Features points en la imatge
        cv::imshow("Output Window", grayimage);

        //Mostrem imatge el contorn de la imatge
        cv::imshow("Output Window1", draw);

		//Waits 30 millisecond to check if 'q' key has been pressed. If so, breaks the loop. Otherwise continues.
    	if( (unsigned char)(cv::waitKey(30) & 0xff) == 'q' ) break;
    }
}
