# NAI_openCV

Repository containing two projects made for the purpose of my CS studies (subject: Computer Vision) using openCV library. Written in C++.

## Color detection

A program for detecting objects of the same colour. Image is captured from the camera. If two biggest (in area) objects are placed on the same level (on the frame read, with some offset tolerance), they are connected with a line.
Target colour can be set using sliders (specifying the lower/upper bound for each values from the HSV space).
Program displays simultanously both windows with original image (frame captured) and output showing detected areas.
'q' - quit program
'x' - capture a frame, saving to a file (hardcoded path) after a user sets a ROI.

## Cascades

A program demonstrating the usage of Haar cascades. 
The task is to count total number of objects' unique appearances of a given type (human body) in given source (video/camera input). Using Haar cascade for human full-body. Tested with camera input and two .mp4 files.
If you wish to run this program with a .mp4 video as a source, it is recommended to choose a video containing footages of pedestrians (such as cyclists' helmet cam).
