/*
Xichen Liu
CS5330-Project 3

This project is about 2D object recognition. 
The goal is to have the computer identify a 
specified set of objects placed on a white 
surface in a translation, scale, and rotation 
invariant manner from a camera looking straight 
down. The computer should be able to recognize 
single objects placed in the image and identify 
the object an output image. If provided a video 
sequence, it should be able to do this in real time.
*/

#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
// #include "processing.cpp"
#include "processing.h"

using namespace std;
using namespace cv;

int main(int argc, char* argv[]) {

    VideoCapture *capdev;

    int threshold = 110;

    vector<region_features> features;

    bool isTraining = false;
    bool isRecognizing = false;
    bool isKnnRecognizing = false;
    int flag = 1;
    int k = 5;
    string training_option;

    string input_label;
    string input_dir;
    char buffer[256];
    string csv_file = "database.csv";

    vector<char*> label_names;
    vector<vector<float>> db_fatures;

    // open the video device
    capdev = new VideoCapture(0);
    if(!capdev->isOpened()) {
            printf("Unable to open video device\n");
            return(-1);
    }

    // get some properties of the image
    Size refS((int)capdev->get(CAP_PROP_FRAME_WIDTH),
            (int)capdev->get(CAP_PROP_FRAME_HEIGHT));
    printf("Expected size: %d %d\n", refS.width, refS.height);
    
    // identifies a window
    namedWindow("Video", WINDOW_NORMAL);
    Mat frame;
    // Mat frame = imread("Proj03Examples\\img1p3.png");

    cout << "Place the object under camera" << endl
            << "Press n to contribute the database with current object or existing training set" << endl
            << "Press i to classify the current object" << endl
            << "Press k to classify the object according to a given k" << endl << endl;;
    
    while (true) {
        // get a new frame from the camera, treat as a stream
        *capdev >> frame;
        if(frame.empty()) {
            printf("frame is empty\n");
            break;
        }
        
        imshow("Video", frame);

        // change to binary image
        Mat thresholded;
        thresholding(frame, thresholded, threshold);
        imshow("After Thresholding", thresholded);

        // clean up the binary image
        Mat morphological_filtered = thresholded.clone();
        morphological_operation(thresholded, morphological_filtered);
        imshow("After morphological filtering", morphological_filtered);

        // find the regions
        Mat segmented;
        Mat colored_segmented;
        Mat labels, stats, centroids;
        int region_num = segment(morphological_filtered, segmented, colored_segmented, labels, stats, centroids);
        imshow("Segmented image", segmented);
        imshow("Colored Segmented image", colored_segmented);

        // draw out the features
        Mat feature_image;
        features.clear();
        compute_features(colored_segmented, feature_image, features);
        imshow("Boxes and axis", feature_image);

        if (isTraining) {
            string training_option;
            isTraining = false;
            while(training_option.compare("set") != 0 && training_option.compare("current") != 0) {
                cout << "Enter \"set\" to input a training set, or \"current\" to save the current object into database: ";
                cin >> training_option;
                cout << endl;
            }
            if (training_option.compare("set") == 0) {
                cout << "Enter the directory name: ";
                cin >> input_dir;
                cout << endl;

                char* dir_name = &input_dir[0];
                char* csv_name = &csv_file[0];
                append_all(dir_name, csv_name, threshold);
            }
            else if (training_option.compare("current") == 0) {
                cout << "Enter the label for the object: ";
                cin >> input_label;
                cout << endl;
                
                char* label_name = &input_label[0];
                char* csv_name = &csv_file[0];
                strcpy(buffer, label_name);
                append_image_data_csv(csv_name, buffer, features, false);
            }
        }

        if (isRecognizing) {
            isRecognizing = false;

            char* csv_name = &csv_file[0];
            db_fatures.clear();
            read_image_data_csv(csv_name, label_names, db_fatures, 0);
            string label_assigned = classify(features, db_fatures, label_names, flag);
            // cout << db_fatures.size() << endl;
            cout << "Label classified: " << label_assigned << endl;
        }

        if (isKnnRecognizing) {
            isKnnRecognizing = false;
            
            cout << "Enter the k value for knn: ";
            cin >> k;
            cout << endl;

            char* csv_name = &csv_file[0];
            db_fatures.clear();
            read_image_data_csv(csv_name, label_names, db_fatures, 0);
            string label_assigned = knn_classify(features, db_fatures, label_names, flag, k);
            cout << "Label classified: " << label_assigned << endl << endl;
        }


        char k = waitKey(10);
        if (k == 'q') {
            break;
        }
        else if (k == 'n') {
            isTraining = true;
        }
        else if (k == 'i') {
            isRecognizing = true;
        }
        else if (k == 'k') {
            isKnnRecognizing = true;
        }
    }

    return 0;
}
