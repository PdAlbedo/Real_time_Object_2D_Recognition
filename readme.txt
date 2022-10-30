CS5330 Project 
Xichen Liu


Khoury wiki:
https://wiki.khoury.northeastern.edu/display/~xicliu/CS5330-Project-3-Report

Real_time_Obj_2D_Rec.cpp: main program
database.csv: stores the feature info
processing.cpp/processing.h: includes all functions used in Real_time_Obj_2D_Rec.cpp


Operating system: Windows 11
IDE: vscode
code-runner execute command: cd "d:\NEU\CS5330\Codes\Project-3\" ; if ($?) { g++ Real_time_Obj_2D_Rec.cpp -o Real_time_Obj_2D_Rec -std=c++14 -I D:\CodeAndTools\OpenCV\opencv\build\include -I D:\CodeAndTools\OpenCV\opencv\build\include\opencv2 -L D:\CodeAndTools\OpenCV\opencv\build\x64\MinGW\lib -l opencv_core455 -l opencv_core455 -l opencv_imgproc455 -l opencv_imgcodecs455 -l opencv_video455 -l opencv_ml455 -l opencv_highgui455 -l opencv_objdetect455 -l opencv_flann455 -l opencv_imgcodecs455 -l opencv_photo455 -l opencv_videoio455 } ; if ($?) { .\Real_time_Obj_2D_Rec }


Procedure of running Real_time_Obj_2D_Rec.cpp:

Put the object under camera, then the modified images will be displayed.
Determine whether or not you want to change the database.
Press n to update databse.
Press i to classify the current viewing object by assigning it a label.
Press k to classify the current viewing object by knn classifier that user can determine which k value to use.
