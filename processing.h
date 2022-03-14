#ifndef PROCESSING_H
#define PROCESSING_H

#include <cstdio>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <dirent.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

struct region_features {
    double ratio;
    double percent_filled;
};
int thresholding(Mat src, Mat &dst, int threshold);
int growing(Mat src, Mat &dst);
int shrinking(Mat src, Mat &dst);
int morphological_operation(Mat src, Mat &dst);
int segment(Mat src, Mat &dst, Mat &colored_dst, Mat &labels, Mat &stats, Mat &centroids);
int compute_features(Mat src, Mat &dst, vector<region_features> &features);
int getstring(FILE *fp, char os[]);
int getint(FILE *fp, int *v);
int getfloat(FILE *fp, float *v);
int append_image_data_csv(char *filename, char *image_filename, vector<region_features> label_data, int reset_file);
int append_all(char *dir, char *csv_file, int threshold);
int read_image_data_csv(char *filename, vector<char *> &filenames, vector<vector<float>> &data, int echo_file);
double scaled_dis(region_features f1, region_features f2, int flag);
string classify(vector<region_features> target, vector<vector<float>> db_features, vector<char*> label_names, int flag);
bool cmp(pair<int, double> &a, pair<int, double> &b);
void sort(map<int, double> &features, vector<pair<int, double>> &sorted_distance);
string knn_classify(vector<region_features> target, vector<vector<float>> db_features, vector<char*> label_names, int flag, int k);

#endif
