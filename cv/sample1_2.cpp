#include <opencv2/opencv.hpp>
#include <stdio.h>

cv::Mat inpaint_mask;
cv::Mat original_image, whiteLined_image, inpainted, bitwise;

using namespace cv;

void on_mouse(int event, int x , int y , int flags, void *){
  if(whiteLined_image.empty()){
    return;
  }

  static bool isBrushDown = false;
  static cv::Point prevPt;
  static cv::Point rectPt1;
  cv::Point pt(x, y);
  bool isLButtonPressedBeforeEvent = (bool)(flags & CV_EVENT_FLAG_LBUTTON);
  if(isLButtonPressedBeforeEvent && isBrushDown){
	  cv::line(inpaint_mask, prevPt, pt, cv::Scalar(255), 5, 8, 0);
	  cv::line(whiteLined_image, prevPt, pt, cv::Scalar::all(255), 5, 8, 0);
	  cv::imshow("image", whiteLined_image);
  }
  bool isLButtonPressedAfterEvent = isLButtonPressedBeforeEvent
	  ^ ((event == CV_EVENT_LBUTTONDOWN) || (event == CV_EVENT_LBUTTONUP));
  if (isLButtonPressedAfterEvent) {
	  prevPt = pt;
	  isBrushDown = true;
  }
  else {
	  isBrushDown = false;
  }
  if (event == CV_EVENT_RBUTTONDOWN) {
	  rectPt1 = pt;
  }
  if (event == CV_EVENT_RBUTTONUP) {
	  cv::rectangle(inpaint_mask, rectPt1, pt, cv::Scalar(255), CV_FILLED);
	  cv::rectangle(whiteLined_image, rectPt1, pt, cv::Scalar::all(255), CV_FILLED);
	  imshow("image", whiteLined_image);

  }
}

#define MODE_INPAINT 0
#define MODE_BITWISE 1

int main(int argc, char *argv[]){
  int mode = MODE_BITWISE;

  // 1. read image file
  char *filename = (argc >= 2) ? argv[1] : (char *)"fruits.jpg";
  original_image = cv::imread(filename);
  if(original_image.empty()){
    printf("ERROR: image not found!\n");
    return 0;
  }

  //print hot keys
  printf( "Hot keys: \n"
	  "\tESC - quit the program\n"
	  "\ti or ENTER - run inpainting algorithm\n"
	  "\t\t(before running it, paint something on the image)\n");

  // 2. prepare window
  cv::namedWindow("image",1);

  // 3. prepare Mat objects for processing-mask and processed-image
  whiteLined_image = original_image.clone();
  inpainted = original_image.clone();
  inpaint_mask.create(original_image.size(), CV_8UC1);
  bitwise = original_image.clone();

  inpaint_mask  = cv::Scalar(0);
  inpainted = cv::Scalar(0);
  bitwise = cv::Scalar(0);

  // 4. show image to window for generating mask
  cv::imshow("image", whiteLined_image);

  // 5. set callback function for mouse operations
  cv::setMouseCallback("image", on_mouse, 0);

  bool loop_flag = true;
  while(loop_flag){

	// 6. wait for key input
    int c = cv::waitKey(0);

	// 7. process according to input
    switch(c){
      case 27://ESC
      case 'q':
        loop_flag = false;
        break;

      case 'r':
        inpaint_mask = cv::Scalar(0);
        original_image.copyTo(whiteLined_image);
        cv::imshow("image", whiteLined_image);
        break;

      case 'i':
      case 10://ENTER
		if (mode == MODE_INPAINT) {
			cv::namedWindow("inpainted image", 1);
			cv::inpaint(whiteLined_image, inpaint_mask, inpainted, 3.0, cv::INPAINT_TELEA);
			cv::imshow("inpainted image", inpainted);
		}
		if (mode == MODE_BITWISE) {
			namedWindow("bitwisenot image", 1);
			cv::bitwise_not(original_image, bitwise, inpaint_mask);
			original_image.copyTo(bitwise, ~inpaint_mask);
			cv::imshow("bitwisenot image", bitwise);
		}
		break;

    }
  }
  return 0;
}
