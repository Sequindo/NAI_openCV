#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/objdetect.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>

using namespace cv;
#define MARGIN 150

CascadeClassifier haar_fullbody_cascade;
std::vector<Rect> prev_frame_objects;
uint16_t detected_persons_counter = 0;

void detectAndDisplay(Mat frame) {
    Mat frame_gray;

    cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray);

    std::vector<Rect> bodies;
    haar_fullbody_cascade.detectMultiScale(frame_gray, bodies);
    for(auto &body : bodies)
    {
        if(!prev_frame_objects.empty())
        {
            bool wasAlreadyDetected = false;
            for(auto &cmp: prev_frame_objects)
            {
                if(abs(cmp.x-body.x) <= MARGIN && abs(cmp.y-body.y) <= MARGIN)
                {
                    wasAlreadyDetected = true;
                }
            }
            if(!wasAlreadyDetected) detected_persons_counter++;
        }
        else
        {
            detected_persons_counter++;
        }
        Point center(body.x + body.width/2, body.y + body.height/2 );
        rectangle(frame, Point(body.x, body.y), Point(body.x+body.width, body.y+body.height), Scalar(255, 0, 255), 2);
    }
    std::string msg{"All detected persons: "};
    msg.append(std::to_string(detected_persons_counter));
    cv::putText(frame, msg, cv::Point(10,50), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 255), 2, LINE_AA);

    prev_frame_objects.clear();
    std::copy(bodies.begin(), bodies.end(), back_inserter(prev_frame_objects));
    cv::imshow("pedestrian_detector", frame);
}

int main(int argc, char** argv)
{
    int width = 960;
    int height = 540;
    if(argc==3)
    {
        width = std::stoi(argv[1]);
        height = std::stoi(argv[2]);
    }
    bool capturing = true;
    cv::VideoCapture cap(0);
    //cv::VideoCapture cap("pedestrians.mp4");
    //cv::VideoCapture cap("hamilton.mp4");
    cv::Mat frame;
    std::string haar_fullbody_cascade_name = samples::findFile("haarcascade_fullbody.xml", true);
    if(!haar_fullbody_cascade.load(haar_fullbody_cascade_name)) {
        std::cout << "--(!)Error loading full-body cascade\n";
        return -1;
    };
    if(!cap.isOpened()) {
        std::cerr << "error opening frames source" << std::endl;
        return -1;
    }
    do {    
        if (cap.read(frame)) {
            cv::resize(frame, frame, cv::Size(width, height), cv::INTER_LINEAR);
            cv::flip(frame, frame, 1);
            detectAndDisplay(frame);
        } else {
            capturing = false;
        }
        int key_read = (cv::waitKey( 1000.0/60.0 )&0x0ff);
        switch(key_read)
        {
            case(113):
                capturing = false;
                break;
            default:
                break;
        }
    } while(capturing);
    return 0;
}