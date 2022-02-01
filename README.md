# NAI_openCV

Repository containing two projects made for the purpose of my CS studies (subject: Computer Vision) using openCV library. Written in C++.

## Color detection

A program for detecting objects of the same color. The image is captured from the camera. If the two biggest (in area) objects are placed on the same level (on the frame read, with some offset tolerance), they are connected with a line.
Target color can be set using sliders (specifying the lower/upper bound for each value from the HSV space).
The program displays simultaneously both windows with the original image (frame captured) and output showing detected areas.
'q' - quit the program
'x' - capture a frame, saving to a file (hardcoded path) after a user sets a ROI.

## Cascades

A program demonstrating the usage of Haar cascades. 
The task is to count the total number of objects' unique appearances of a given type (human body) in a given source (video/camera input). Using Haar cascade for human full-body. Tested with camera input and two .mp4 files.
If you wish to run this program with a .mp4 video as a source, it is recommended to choose a video containing footage of pedestrians (such as cyclists' helmet cam).
