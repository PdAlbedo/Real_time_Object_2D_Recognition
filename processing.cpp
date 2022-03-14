/*
Xichen Liu
CS5330-Project 3

Includes all functions used to process the image in the project
*/

#include <iostream>
#include <dirent.h>
#include <string>
#include <bits/stdc++.h>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;
using namespace cv;

/*
Stores the features of a region
*/
struct region_features {
    double ratio;
    double percent_filled;
};

/**
 * Separate the object from the back ground according to a threshold
 * Update x, y, original rgb, gray, thresholded value
 * 
 * @param src  input image
 * @param dst  output image
 * @param threshold    the threshold used to make the image binary 
 */
int thresholding(Mat src, Mat &dst, int threshold) {
    
    // blur the input image to make the regions more uniform and then convert to HSV space
    Mat blurred;
    GaussianBlur(src, blurred, Size(3, 3), BORDER_DEFAULT);
    dst = src.clone();
    Mat HSV_pic;
    cvtColor(blurred, HSV_pic, COLOR_BGR2HSV);
    Mat gray_pic;
    cvtColor(blurred, gray_pic, COLOR_BGR2GRAY);
    
    // accoring to grayscale to determine whether the pixel is in foreground or background
    for (int i = 0; i < dst.rows; i++) {
        for (int j = 0; j < dst.cols; j++) {
            if (gray_pic.at<uchar>(i, j) > threshold) {
                dst.at<Vec3b>(i, j)[0] = 0;
                dst.at<Vec3b>(i, j)[1] = 0;
                dst.at<Vec3b>(i, j)[2] = 0;
            }
            else {
                dst.at<Vec3b>(i, j)[0] = 255;
                dst.at<Vec3b>(i, j)[1] = 255;
                dst.at<Vec3b>(i, j)[2] = 255;
            }
        }
    }
    return 0;
}

/*
Set to white any dark pixel which is adjacent to a white pixel
*/
int growing(Mat src, Mat &dst) {
    for (int i = 0; i < src.rows; i++) {
        for (int j = 0; j < src.cols; j++) {
            if (i == 0) {
                if (j == 0) {
                    if (src.at<Vec3b>(i, j + 1)[0] == 255 || src.at<Vec3b>(i + 1, j)[0] == 255 || src.at<Vec3b>(i + 1, j + 1)[0] == 255) {
                        dst.at<Vec3b>(i, j)[0] = 255;
                        dst.at<Vec3b>(i, j)[1] = 255;
                        dst.at<Vec3b>(i, j)[2] = 255;
                    }
                }
                else if (j == src.cols - 1) {
                    if (src.at<Vec3b>(i, j - 1)[0] == 255 || src.at<Vec3b>(i + 1, j)[0] == 255 || src.at<Vec3b>(i + 1, j - 1)[0] == 255) {
                        dst.at<Vec3b>(i, j)[0] = 255;
                        dst.at<Vec3b>(i, j)[1] = 255;
                        dst.at<Vec3b>(i, j)[2] = 255;
                    }
                }
                else {
                    if (src.at<Vec3b>(i, j - 1)[0] == 255 || src.at<Vec3b>(i, j + 1)[0] == 255 || src.at<Vec3b>(i + 1, j)[0] == 255
                        || src.at<Vec3b>(i + 1, j - 1)[0] == 255 || src.at<Vec3b>(i + 1, j + 1)[0] == 255) {
                        dst.at<Vec3b>(i, j)[0] = 255;
                        dst.at<Vec3b>(i, j)[1] = 255;
                        dst.at<Vec3b>(i, j)[2] = 255;
                    }
                }
            }
            else if (i == src.rows - 1) {
                if (j == 0) {
                    if (src.at<Vec3b>(i, j + 1)[0] == 255 || src.at<Vec3b>(i - 1, j)[0] == 255 || src.at<Vec3b>(i - 1, j + 1)[0] == 255) {
                        dst.at<Vec3b>(i, j)[0] = 255;
                        dst.at<Vec3b>(i, j)[1] = 255;
                        dst.at<Vec3b>(i, j)[2] = 255;
                    }
                }
                else if (j == src.cols - 1) {
                    if (src.at<Vec3b>(i, j - 1)[0] == 255 || src.at<Vec3b>(i - 1, j)[0] == 255 || src.at<Vec3b>(i - 1, j - 1)[0] == 255) {
                        dst.at<Vec3b>(i, j)[0] = 255;
                        dst.at<Vec3b>(i, j)[1] = 255;
                        dst.at<Vec3b>(i, j)[2] = 255;
                    }
                }
                else {
                    if (src.at<Vec3b>(i, j - 1)[0] == 255 || src.at<Vec3b>(i, j + 1)[0] == 255 || src.at<Vec3b>(i - 1, j)[0] == 255
                        || src.at<Vec3b>(i - 1, j - 1)[0] == 255 || src.at<Vec3b>(i - 1, j + 1)[0] == 255) {
                        dst.at<Vec3b>(i, j)[0] = 255;
                        dst.at<Vec3b>(i, j)[1] = 255;
                        dst.at<Vec3b>(i, j)[2] = 255;
                    }
                }
            }
            else {
                if (j == 0) {
                    if (src.at<Vec3b>(i + 1, j)[0] == 255 || src.at<Vec3b>(i - 1, j)[0] == 255 || src.at<Vec3b>(i - 1, j + 1)[0] == 255
                        || src.at<Vec3b>(i, j + 1)[0] == 255 || src.at<Vec3b>(i + 1, j + 1)[0] == 255) {
                        dst.at<Vec3b>(i, j)[0] = 255;
                        dst.at<Vec3b>(i, j)[1] = 255;
                        dst.at<Vec3b>(i, j)[2] = 255;
                    }
                }
                else if (j == src.cols - 1) {
                    if (src.at<Vec3b>(i + 1, j)[0] == 255 || src.at<Vec3b>(i - 1, j)[0] == 255 || src.at<Vec3b>(i - 1, j - 1)[0] == 255
                        || src.at<Vec3b>(i, j - 1)[0] == 255 || src.at<Vec3b>(i + 1, j - 1)[0] == 255) {
                        dst.at<Vec3b>(i, j)[0] = 255;
                        dst.at<Vec3b>(i, j)[1] = 255;
                        dst.at<Vec3b>(i, j)[2] = 255;
                    }
                }
                else {
                    if (src.at<Vec3b>(i - 1, j - 1)[0] == 255 || src.at<Vec3b>(i - 1, j)[0] == 255 || src.at<Vec3b>(i - 1, j + 1)[0] == 255
                        || src.at<Vec3b>(i, j - 1)[0] == 255 || src.at<Vec3b>(i, j + 1)[0] == 255
                        || src.at<Vec3b>(i + 1, j - 1)[0] == 255 || src.at<Vec3b>(i + 1, j)[0] == 255 || src.at<Vec3b>(i + 1, j + 1)[0] == 255) {
                        dst.at<Vec3b>(i, j)[0] = 255;
                        dst.at<Vec3b>(i, j)[1] = 255;
                        dst.at<Vec3b>(i, j)[2] = 255;
                    }
                }
            }
        }
    }
    return 0;
}

/*
Set to dark any white pixel which is adjacent to a dark pixel
*/
int shrinking(Mat src, Mat &dst) {
    for (int i = 0; i < src.rows; i++) {
        for (int j = 0; j < src.cols; j++) {
            if (i == 0) {
                if (j == 0) {
                    if (src.at<Vec3b>(i, j + 1)[0] == 0 || src.at<Vec3b>(i + 1, j)[0] == 0 || 
                        src.at<Vec3b>(i + 1, j + 1)[0] == 0) {
                        dst.at<Vec3b>(i, j)[0] = 0;
                        dst.at<Vec3b>(i, j)[1] = 0;
                        dst.at<Vec3b>(i, j)[2] = 0;
                    }
                }
                else if (j == src.cols - 1) {
                    if (src.at<Vec3b>(i, j - 1)[0] == 0 || src.at<Vec3b>(i + 1, j)[0] == 0 || 
                        src.at<Vec3b>(i + 1, j - 1)[0] == 0) {
                        dst.at<Vec3b>(i, j)[0] = 0;
                        dst.at<Vec3b>(i, j)[1] = 0;
                        dst.at<Vec3b>(i, j)[2] = 0;
                    }
                }
                else {
                    if (src.at<Vec3b>(i, j - 1)[0] == 0 || src.at<Vec3b>(i, j + 1)[0] == 0 || 
                        src.at<Vec3b>(i + 1, j)[0] == 0 || src.at<Vec3b>(i + 1, j - 1)[0] == 0 || 
                        src.at<Vec3b>(i + 1, j + 1)[0] == 0) {
                        dst.at<Vec3b>(i, j)[0] = 0;
                        dst.at<Vec3b>(i, j)[1] = 0;
                        dst.at<Vec3b>(i, j)[2] = 0;
                    }
                }
            }
            else if (i == src.rows - 1) {
                if (j == 0) {
                    if (src.at<Vec3b>(i, j + 1)[0] == 0 || src.at<Vec3b>(i - 1, j)[0] == 0 || 
                        src.at<Vec3b>(i - 1, j + 1)[0] == 0) {
                        dst.at<Vec3b>(i, j)[0] = 0;
                        dst.at<Vec3b>(i, j)[1] = 0;
                        dst.at<Vec3b>(i, j)[2] = 0;
                    }
                }
                else if (j == src.cols - 1) {
                    if (src.at<Vec3b>(i, j - 1)[0] == 0 || src.at<Vec3b>(i - 1, j)[0] == 0 || 
                        src.at<Vec3b>(i - 1, j - 1)[0] == 0) {
                        dst.at<Vec3b>(i, j)[0] = 0;
                        dst.at<Vec3b>(i, j)[1] = 0;
                        dst.at<Vec3b>(i, j)[2] = 0;
                    }
                }
                else {
                    if (src.at<Vec3b>(i, j - 1)[0] == 0 || src.at<Vec3b>(i, j + 1)[0] == 0 || 
                        src.at<Vec3b>(i - 1, j)[0] == 0 || src.at<Vec3b>(i - 1, j - 1)[0] == 0 || 
                        src.at<Vec3b>(i - 1, j + 1)[0] == 0) {
                        dst.at<Vec3b>(i, j)[0] = 0;
                        dst.at<Vec3b>(i, j)[1] = 0;
                        dst.at<Vec3b>(i, j)[2] = 0;
                    }
                }
            }
            else {
                if (j == 0) {
                    if (src.at<Vec3b>(i + 1, j)[0] == 0 || src.at<Vec3b>(i - 1, j)[0] == 0 || 
                        src.at<Vec3b>(i - 1, j + 1)[0] == 0 || src.at<Vec3b>(i, j + 1)[0] == 0 || 
                        src.at<Vec3b>(i + 1, j + 1)[0] == 0) {
                        dst.at<Vec3b>(i, j)[0] = 0;
                        dst.at<Vec3b>(i, j)[1] = 0;
                        dst.at<Vec3b>(i, j)[2] = 0;
                    }
                }
                else if (j == src.cols - 1) {
                    if (src.at<Vec3b>(i + 1, j)[0] == 0 || src.at<Vec3b>(i - 1, j)[0] == 0 || 
                        src.at<Vec3b>(i - 1, j - 1)[0] == 0 || src.at<Vec3b>(i, j - 1)[0] == 0 || 
                        src.at<Vec3b>(i + 1, j - 1)[0] == 0) {
                        dst.at<Vec3b>(i, j)[0] = 0;
                        dst.at<Vec3b>(i, j)[1] = 0;
                        dst.at<Vec3b>(i, j)[2] = 0;
                    }
                }
                else {
                    if (src.at<Vec3b>(i - 1, j - 1)[0] == 0 || src.at<Vec3b>(i - 1, j)[0] == 0 || 
                        src.at<Vec3b>(i - 1, j + 1)[0] == 0 || src.at<Vec3b>(i, j - 1)[0] == 0 || 
                        src.at<Vec3b>(i, j + 1)[0] == 0 || src.at<Vec3b>(i + 1, j - 1)[0] == 0 || 
                        src.at<Vec3b>(i + 1, j)[0] == 0 || src.at<Vec3b>(i + 1, j + 1)[0] == 0) {
                        dst.at<Vec3b>(i, j)[0] = 0;
                        dst.at<Vec3b>(i, j)[1] = 0;
                        dst.at<Vec3b>(i, j)[2] = 0;
                    }
                }
            }
        }
    }
    return 0;
}

/**
 * Clean the thresholded image by growing or shrinking
 * Both growing and shrinking are operating on RGB image
 * 
 * @param src  input image
 * @param dst  output image
 */
int morphological_operation(Mat src, Mat &dst) {

    Mat grow_1 = src.clone();
    growing(src, grow_1);
    // Mat grow_2 = grow_1.clone();
    // growing(grow_1, grow_2);
    // Mat grow_3 = grow_2.clone();
    // growing(grow_2, grow_3);
    // Mat grow_4 = grow_3.clone();
    // growing(grow_3, grow_4);
    // Mat grow_5 = grow_4.clone();
    // growing(grow_4, grow_5);
    // Mat grow_6 = grow_5.clone();
    // growing(grow_5, grow_6);
    // Mat grow_7 = grow_6.clone();
    // growing(grow_6, grow_7);
    // Mat grow_8 = grow_7.clone();
    // growing(grow_7, grow_8);
    // Mat grow_9 = grow_8.clone();
    // growing(grow_8, grow_9);
    // Mat grow_10 = grow_9.clone();
    // growing(grow_9, grow_10);

    Mat shrink_1 = grow_1.clone();
    shrinking(grow_1, shrink_1);
    // Mat shrink_2 = shrink_1.clone();
    // shrinking(shrink_1, shrink_2);
    // Mat shrink_3 = shrink_2.clone();
    // shrinking(shrink_2, shrink_3);
    // Mat shrink_4 = shrink_3.clone();
    // shrinking(shrink_3, shrink_4);
    // Mat shrink_5 = shrink_4.clone();
    // shrinking(shrink_4, shrink_5);
    // Mat shrink_6 = shrink_5.clone();
    // shrinking(shrink_5, shrink_6);
    // Mat shrink_7 = shrink_6.clone();
    // shrinking(shrink_6, shrink_7);
    // Mat shrink_8 = shrink_7.clone();
    // shrinking(shrink_7, shrink_8);
    // Mat shrink_9 = shrink_8.clone();
    // shrinking(shrink_8, shrink_9);
    // Mat shrink_10 = shrink_9.clone();
    // shrinking(shrink_9, shrink_10);

    dst = shrink_1.clone();

    return 0;
}

/*
Region finding algorithm
FIXME: unfinished
*/
/*
int region_growing(Mat src, Mat &dst, Mat &colored_dst, Mat &labels, Mat &stats, Mat &centroids) {
    int region_id = 1;
    vector<pair<int, int>> points;
    // points.push_back(pair<int, int>(img[0].x, img[0].y));
    while (!points.empty()) {
        pair<int, int> tmp = points.back();
        points.pop_back();
        int i = tmp.first;
        int j = tmp.second;
        // calculate the positions of the adjacent pixels in the vec<pixel>
    }
    region_id++;

    return region_id - 1;
}
*/

/**
 * Run connected components analysis on the thresholded and cleaned image to get regions.
 * Also clean up the regions which areas are too small
 * Output two images, one is colored one is uncolored
 * 
 * @param src  input image
 * @param dst  output image
 * @param colored_dst  colored output image
 * @param labels   image with labels assigned to each pixel
 * @param stats    stores various info of regions
 * @param controids    centroids of regions
 * 
 * @return number of regions
 */
int segment(Mat src, Mat &dst, Mat &colored_dst, Mat &labels, Mat &stats, Mat &centroids){

    Mat gray_pic;
    cvtColor(src, gray_pic, COLOR_BGR2GRAY);
    int num = connectedComponentsWithStats(gray_pic, labels, stats, centroids, 8);

    // number of colors will equal to number of regions
    vector<Vec3b> colors(num);
    vector<Vec3b> intensity(num);
    // set background to black
    colors[0] = Vec3b(0, 0, 0);
    intensity[0] = Vec3b(0, 0, 0);
    int area = 0;
    for(int i = 1; i < num; i++ ) {
        colors[i] = Vec3b(rand()%256, rand()%256, rand()%256);
        intensity[i] = Vec3b(255, 255, 255);
        // keep only the largest region
        if(stats.at<int>(i, CC_STAT_AREA) > area) {
            area = stats.at<int>(i, CC_STAT_AREA);
        }
        else {
            colors[i] = Vec3b(0,0,0);
            intensity[i] = Vec3b(0, 0, 0);
        }
    }
    // assign the colors to regions
    Mat colored_img = Mat::zeros(src.size(), CV_8UC3);
    Mat intensity_img = Mat::zeros(src.size(), CV_8UC3);
    for(int i = 0; i < colored_img.rows; i++) {
        for(int j = 0; j < colored_img.cols; j++)
        {
            int label = labels.at<int>(i, j);
            colored_img.at<Vec3b>(i, j) = colors[label];
            intensity_img.at<Vec3b>(i, j) = intensity[label];
        }
    }
    
    cvtColor(intensity_img, gray_pic, COLOR_BGR2GRAY);
    num = connectedComponentsWithStats(gray_pic, labels, stats, centroids, 8);
    dst = intensity_img.clone();
    colored_dst = colored_img.clone();

    return num;
}

/**
 * Computes a set of features for a specified region given a region map and a region ID.
 * 
 * @param src  input image
 * @param dst  output image
 * @param features vector of features of each region   
 */
int compute_features(Mat src, Mat &dst, vector<region_features> &features) {

    dst = src.clone();

    vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
    Mat gray_pic;
    cvtColor(src, gray_pic, COLOR_BGR2GRAY);
	findContours(gray_pic, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE, Point());

    Moments moment;
    Point2f center;
    Point2f vertex[4];
    for (int i = 0; i < contours.size(); i++) {
        region_features tmp;

        // calculate moment, center, vertices of bounding box
        moment = moments(contours[i]);
        center = Point2f(moment.m10/moment.m00, 
                            moment.m01/moment.m00);
        RotatedRect rect = minAreaRect(contours[i]);
        double angle = 0.5 * atan((2 * moment.m11)/(moment.m20 - moment.m02));
        int len = max(rect.size.height, rect.size.width);
        int x1 = (moment.m10/moment.m00) + len/2 * cos(angle);
        int y1 = (moment.m01/moment.m00) - len/2 * sin(angle);
        int x2 = (moment.m10/moment.m00) - len/2 * cos(angle);
        int y2 = (moment.m01/moment.m00) + len/2 * sin(angle);
        line(dst, Point2f(x1, y1), Point2f(x2, y2), Scalar(0, 0, 255), 2, LINE_8);
        
        vertex[4];
        rect.points(vertex);
        line(dst, vertex[0], vertex[1], Scalar(0, 0, 255), 2, LINE_8);
        line(dst, vertex[1], vertex[2], Scalar(0, 0, 255), 2, LINE_8);
        line(dst, vertex[2], vertex[3], Scalar(0, 0, 255), 2, LINE_8);
        line(dst, vertex[3], vertex[0], Scalar(0, 0, 255), 2, LINE_8);

        tmp.ratio = max(rect.size.height, rect.size.width)/min(rect.size.height, rect.size.width);
        tmp.percent_filled = moment.m00/(rect.size.height*rect.size.width);
        features.push_back(tmp);
    }

    return 0;
}

/*
reads a string from a CSV file. the 0-terminated string is returned in the char array os.

The function returns false if it is successfully read. It returns true if it reaches the end of the line or the file.
*/
int getstring(FILE *fp, char os[]) {
    int p = 0;
    int eol = 0;
    
    for (;;) {
        char ch = fgetc(fp);
        if (ch == ',') {
            break;
        }
        else if (ch == '\n' || ch == EOF) {
            eol = 1;
            break;
        }
        // printf("%c", ch ); // uncomment for debugging
        os[p] = ch;
        p++;
    }
    
    // printf("\n"); // uncomment for debugging
    os[p] = '\0';

    return eol; // return true if eol
}

int getint(FILE *fp, int *v) {
    char s[256];
    int p = 0;
    int eol = 0;

    for (;;) {
        char ch = fgetc(fp);

        if (ch == ',') {
            break;
        }
        else if (ch == '\n' || ch == EOF) {
            eol = 1;
            break;
        }
        
        s[p] = ch;
        p++;
    }

    s[p] = '\0'; // terminator
    *v = atoi(s);

    return eol; // return true if eol
}

/*
Utility function for reading one float value from a CSV file

The value is stored in the v parameter

The function returns true if it reaches the end of a line or the file
*/
int getfloat(FILE *fp, float *v) {
    char s[256];
    int p = 0;
    int eol = 0;

    for (;;) {
        char ch = fgetc(fp);

        if (ch == ',') {
            break;
        }
        else if (ch == '\n' || ch == EOF) {
            eol = 1;
            break;
        }
        
        s[p] = ch;
        p++;
    }

    s[p] = '\0'; // terminator
    *v = atof(s);

    return eol; // return true if eol
}

/*
Given a filename, and image filename, and the image features, by
default the function will append a line of data to the CSV format
file.  If reset_file is true, then it will open the file in 'write'
mode and clear the existing contents.

The image filename is written to the first position in the row of
data. The values in label_data are all written to the file as
floats.

The function returns a non-zero value in case of an error.
*/
int append_image_data_csv(char *filename, char *image_filename, vector<region_features> label_data, int reset_file) {
    char buffer[256];
    char mode[8];
    FILE *fp;

    strcpy(mode, "a");

    if (reset_file) {
        strcpy(mode, "w");
    }
    fp = fopen(filename, mode);
    if (!fp) {
        printf("Unable to open output file %s\n", filename);
        exit(-1);
    }
    // write the filename and the feature vector to the CSV file
    strcpy(buffer, image_filename);
    fwrite(buffer, sizeof(char), strlen(buffer), fp);

    for (int i=0; i<label_data.size(); i++) {
        char tmp_1[256];
        char tmp_2[256];
        sprintf(tmp_1, ",%.4f", label_data[i].ratio);
        fwrite(tmp_1, sizeof(char), strlen(tmp_1), fp);
        sprintf(tmp_2, ",%.4f", label_data[i].percent_filled);
        fwrite(tmp_2, sizeof(char), strlen(tmp_2), fp);
    }
        
    fwrite("\n", sizeof(char), 1, fp); // EOL

    fclose(fp);
    
    return 0;
}

/**
 * Extract features from the image set and expend them to csv file
 * 
 * @param dir  folder name of training set
 * @param csv_file name of csv file
 * @param threshold    value of threshold used to determine the binary image
 */
int append_all(char *dir, char *csv_file, int threshold) {
    char dirname[256];
    char buffer[256];
    FILE *fp;
    struct dirent *dp;
    DIR *dirp;
    vector<region_features> features;

    // earse all the contents in the csv file
    fp = fopen(csv_file, "w");
    fclose(fp);

    // get the directory path
    strcpy(dirname, dir);
    printf("Processing directory: %s\n\n", dirname);

    // open the directory
    dirp = opendir(dirname);
    if (dirp == NULL) {
        printf("Cannot open directory %s\n", dirname);
        exit(-1);
    }
    

    // loop over all the files in the image file listing
    while ((dp = readdir(dirp)) != NULL) {
        // check if the file is an image
        if (strstr(dp->d_name, ".jpg") ||
            strstr(dp->d_name, ".JPG") ||
            strstr(dp->d_name, ".png") ||
            strstr(dp->d_name, ".ppm") ||
            strstr(dp->d_name, ".tif")) {

            // build the labels
            strcpy(buffer, dirname);
            strcat(buffer, "/");
            strcat(buffer, dp->d_name);

            features.clear();

            Mat curr_img = imread(buffer);
            if(curr_img.empty()) {
                printf("frame is empty\n");
                break;
            }
            Mat thresholded;
            thresholding(curr_img, thresholded, threshold);
            Mat morphological_filtered = thresholded.clone();
            morphological_operation(thresholded, morphological_filtered);
            Mat segmented;
            Mat colored_segmented;
            Mat labels, stats, centroids;
            int region_num = segment(morphological_filtered, segmented, colored_segmented, labels, stats, centroids);
            Mat feature_image;
            compute_features(segmented, feature_image, features);

            // append image name and features into the csv file
            append_image_data_csv(csv_file, buffer, features, false);
        }
    }
    cout << "All labels added" << endl;
    
    return 0;
}

/*
Given a file with the format of a string as the first column and
floating point numbers as the remaining columns, this function
returns the filenames as a std::vector of character arrays, and the
remaining data as a 2D std::vector<float>.

filenames will contain all of the image file names.
data will contain the features calculated from each image.

If echo_file is true, it prints out the contents of the file as read
into memory.

The function returns a non-zero value if something goes wrong.
*/
int read_image_data_csv(char *filename, vector<char *> &filenames, vector<vector<float>> &data, int echo_file) {
    FILE *fp;
    float fval;
    char img_file[256];

    fp = fopen(filename, "r");
    if (!fp) {
        printf("Unable to open feature file\n");
        return(-1);
    }

    printf("\nReading %s\n", filename);
    for (;;) {
        vector<float> dvec;
        
        // read the filename
        if (getstring(fp, img_file)) {
            break;
        }
        // printf("Evaluting %s\n", filename);

        // read the whole feature file into memory
        for (;;) {
            // get next feature
            float eol = getfloat(fp, &fval);
            dvec.push_back(fval);
            if (eol) break;
        }
        // printf("read %lu features\n", dvec.size());

        data.push_back(dvec);

        char *fname = new char[strlen(img_file) + 1];
        strcpy(fname, img_file);
        filenames.push_back(fname);
    }
    fclose(fp);
    printf("Finished reading CSV file\n\n");

    if (echo_file) {
        for (int i=0; i<data.size(); i++) {
            for (int j=0; j<data[i].size(); j++) {
                printf("%.4f  ", data[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }

    return 0;
}

/**
 * 
 * Calculate various distance according to flag
 *
 * @param f1   features of a region
 * @param f2   features of a region
 * @param flag used to determin which distance to use
 */
double scaled_dis(region_features f1, region_features f2, int flag) {
    double ratio_mean = f1.ratio + f2.ratio;
    double percentage_mean = f1.percent_filled + f2.percent_filled;
    double ratio_dev = sqrt((f1.ratio - ratio_mean) * (f1.ratio - ratio_mean) + (f2.ratio - ratio_mean) * (f2.ratio - ratio_mean));
    double percentage_dev = sqrt((f1.percent_filled - percentage_mean) * (f1.percent_filled - percentage_mean) + (f2.percent_filled - percentage_mean) * (f2.percent_filled - percentage_mean));

    double scaled_Euc_dis = abs(f1.ratio - f2.ratio)/ratio_dev + abs(f1.percent_filled - f2.percent_filled)/percentage_dev;
    double Euc_dis = sqrt((f1.ratio - f2.ratio) * (f1.ratio - f2.ratio) + 
                        (f1.percent_filled - f2.percent_filled) * (f1.percent_filled - f2.percent_filled));
    double Manhattan_dis = abs(f1.ratio - f2.ratio) + abs(f1.percent_filled - f2.percent_filled);

    // cout << "calculated dis: " << dis << endl;
    if (flag == 1) {
        return scaled_Euc_dis;
    }
    else if (flag == 2) {
        return Euc_dis;
    }
    else if (flag == 3) {
        return Manhattan_dis;
    }
    else {
        return scaled_Euc_dis;
    }
}

/**
 * Classify the object in the input image
 * 
 * @param target        the object in the current camera
 * @param db_features   database features
 * @param label_names   labels in database
 * @param flag          determine which distance to use
 * @return string       classified label
 */
string classify(vector<region_features> target, vector<vector<float>> db_features, vector<char*> label_names, int flag) {

    double total_dis = INFINITY;
    double min = INFINITY;
    string assigned_label;
    
    for (int i = 0; i < target.size(); i++) {
        for (int j = 0; j < db_features.size(); j++) {

            region_features tmp;
            tmp.ratio = db_features[j][0];
            tmp.percent_filled = db_features[j][1];
            
            total_dis = scaled_dis(target[i], tmp, flag);

            // get the label with the shortest distance
            if (total_dis < min) {
                min = total_dis;
                string str(label_names[j]);
                size_t lastslash = str.find_last_of("/"); 
                size_t lastdot = str.find_last_of("."); 
                assigned_label = str.substr(lastslash + 1, lastdot - lastslash - 3);
            }
        }
    }

    return assigned_label;
}

/*
comparator to sort the calculated distances
*/
bool cmp(pair<int, double> &a, pair<int, double> &b) {
    return a.second < b.second;
}

/*
Function to sort the map according to value in a (key-value) pairs
*/
void sort(map<int, double> &features, vector<pair<int, double>> &sorted_distance) { 
    // Copy key-value pair from Map to vector of pairs
    for (auto& it : features) {
        sorted_distance.push_back(it);
    }
  
    // Sort using comparator function
    sort(sorted_distance.begin(), sorted_distance.end(), cmp);

    return;
}

/**
 * Classify the object in the input image with a given k value
 * 
 * @param target        the object in the current camera
 * @param db_features   database features
 * @param label_names   labels in database
 * @param flag          determine which distance to use
 * @param k             k value of knn
 * @return string       classified label
 */
string knn_classify(vector<region_features> target, vector<vector<float>> db_features, vector<char*> label_names, int flag, int k) {

    double total_dis = INFINITY;
    double min = INFINITY;
    map<int, double> distance_map;
    vector<pair<int, double>> sorted_dis;
    vector<string> labels;
    vector<string> knn_labels;
    
    for (int i = 0; i < target.size(); i++) {
        for (int j = 0; j < db_features.size(); j++) {

            region_features tmp;
            tmp.ratio = db_features[j][0];
            tmp.percent_filled = db_features[j][1];
            
            total_dis = scaled_dis(target[i], tmp, flag);
            distance_map.insert(pair<int, double>(j, total_dis));
        }
    }
    sort(distance_map, sorted_dis);

    // get the labels
    for (int i = 0; i < sorted_dis.size(); i++) {
        string tmp(label_names[sorted_dis[i].first]);
        size_t lastslash = tmp.find_last_of("/"); 
        size_t lastdot = tmp.find_last_of("."); 
        labels.push_back(tmp.substr(lastslash + 1, lastdot - lastslash - 3));
    }
    
    cout << "Top " << k << "matches: " << endl;
    for (int i = 0; i < k; i++) {
        knn_labels.push_back(labels[i]);
        cout << labels[i] << endl;
    }
    cout << endl;

    // get the most frequent labels in top k labels
    int max = 0;
    string assigned_label;
    for (int i = 0; i < k; i++) {
        string curr = knn_labels[i];
        int c = count(knn_labels.begin(), knn_labels.end(), knn_labels.at(i));
        if (c > max) {
            max = c;
            assigned_label = knn_labels[i];
        }
    }

    return assigned_label;
}
