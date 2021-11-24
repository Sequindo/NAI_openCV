#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

const int max_value_hue = 360/2;
const int max_value = 255;

int low_hue = 0, low_saturation = 0, low_value = 0;
int high_hue = max_value_hue;
int high_saturation = max_value, high_value = max_value;

static void on_low_hue_trackbar(int, void *)
{   
    low_hue = std::min(high_hue-1, low_hue);
    cv::setTrackbarPos("Low Hue", "HSV_sliders", low_hue);
}

static void on_high_hue_trackbar(int, void *)
{
    high_hue = std::max(high_hue, low_hue+1);
    cv::setTrackbarPos("High Hue", "HSV_sliders", high_hue);
}

static void on_low_saturation_trackbar(int, void *)
{
    low_saturation = std::min(high_saturation-1, low_saturation);
    cv::setTrackbarPos("Low Saturation", "HSV_sliders", low_saturation);
}

static void on_high_saturation_trackbar(int, void *)
{
    high_saturation = std::max(high_saturation, low_saturation+1);
    cv::setTrackbarPos("High Saturation", "HSV_sliders", high_saturation);
}

static void on_low_value_trackbar(int, void *)
{
    low_value = std::min(high_value-1, low_value);
    cv::setTrackbarPos("Low Value", "HSV_sliders", low_value);
}

static void on_high_value_trackbar(int, void *)
{
    high_value = std::max(high_value, low_value+1);
    cv::setTrackbarPos("High Value", "HSV_sliders", high_value);
}

int main( int argc, char** argv ) {
    int width = 320;
    int height = 200;
    if(argc==3)
    {
        width = std::stoi(argv[1]);
        height = std::stoi(argv[2]);
    }
    bool capturing = true;

    cv::VideoCapture cap(0);
    if ( !cap.isOpened() ) {
        std::cerr << "error opening frames source" << std::endl;
        return -1;
    }
    std::cout << "Video size: " << cap.get( cv::CAP_PROP_FRAME_WIDTH ) 
    << "x" << cap.get( cv::CAP_PROP_FRAME_HEIGHT ) << std::endl;
    cv::Mat save_img;

    cv::namedWindow("HSV sliders", cv::WINDOW_AUTOSIZE);
    cv::createTrackbar("Low Hue", "HSV sliders", &low_hue, max_value_hue, on_low_hue_trackbar);
    cv::createTrackbar("High Hue", "HSV sliders", &high_hue, max_value_hue, on_high_hue_trackbar);
    cv::createTrackbar("Low Saturation", "HSV sliders", &low_saturation, max_value, on_low_saturation_trackbar);
    cv::createTrackbar("High Saturation", "HSV sliders", &high_saturation, max_value, on_high_saturation_trackbar);
    cv::createTrackbar("Low Value", "HSV sliders", &low_value, max_value, on_low_value_trackbar);
    cv::createTrackbar("High Value", "HSV sliders", &high_value, max_value, on_high_value_trackbar);

    cv::Mat image_blurred;
    cv::Mat inRange_image;
    cv::Mat croppedImage;
    cv::Rect2d rec_roi;
    do {
        cv::Mat frame;
        if ( cap.read( frame ) ) {
            cv::resize(frame, frame, cv::Size(width, height), cv::INTER_LINEAR);
            cv::flip(frame, frame, 1);
            GaussianBlur(frame, image_blurred, cv::Size(5, 5), 0);
            cv::cvtColor(image_blurred, image_blurred, cv::COLOR_BGR2HSV);
            cv::inRange(image_blurred, cv::Scalar(low_hue, low_saturation, low_value), cv::Scalar(high_hue, high_saturation, high_value), inRange_image);
            cv::imshow("HSV_image", image_blurred);
            cv::imshow("inRange_output", inRange_image);
        } else {
            // stream finished
            capturing = false;
        }
        //czekaj na klawisz, sprawdz czy to jest 'q'
        int key_read = (cv::waitKey( 1000.0/60.0 )&0x0ff);
        switch(key_read)
        {
            case(113):
                capturing = false;
                break;
            case(120):
                rec_roi = cv::selectROI(inRange_image);
	            croppedImage = inRange_image(rec_roi);
                cv::imwrite("../image.jpg", croppedImage);
                break;
            default:
                break;
        }
    } while( capturing );
    return 0;
}
