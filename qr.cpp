//Reference: https://www.learnopencv.com/opencv-qr-code-scanner-c-and-python/

#include <iostream>
#include <zbar.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;
using namespace zbar;

typedef struct{
  string data; 
  vector <Point> location;
} decodedObject;

// Find and decode QR codes
void decode(Mat &im, vector<decodedObject>&decodedObjects){
  
  // Create zbar scanner
  ImageScanner scanner;

  // Configure scanner
  scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 0);  // disable all
  scanner.set_config(ZBAR_QRCODE, ZBAR_CFG_ENABLE, 1);  // enable QR Code only
  
  // Convert image to grayscale
  Mat imGray;
  cvtColor(im, imGray, COLOR_BGR2GRAY);

  // Wrap image data in a zbar image
  Image image(im.cols, im.rows, "Y800", (uchar *)imGray.data, im.cols * im.rows);

  // Scan the image for qr codes
  int n = scanner.scan(image);
  
  // Print results
  for(Image::SymbolIterator symbol = image.symbol_begin(); symbol != image.symbol_end(); ++symbol)
  {
    decodedObject obj;
    
    obj.data = symbol->get_data();
    
    // Print decoded data
    cout << "Decoded Data : " << obj.data << endl << endl;
    
    // Obtain location
    for(int i = 0; i< symbol->get_location_size(); i++)
    {
      obj.location.push_back(Point(symbol->get_location_x(i),symbol->get_location_y(i)));
    }
    
    decodedObjects.push_back(obj);
  }
}

// Main program
int main(int argc, char* argv[]){
  
  // Read image
  Mat im = imread("/home/bluealgae/Desktop/tht/0001.jpg"); // configure this according to your own image directory
  
  // Variable for decoded objects 
  vector<decodedObject> decodedObjects;
  
  // Find and decode barcodes and QR codes
  decode(im, decodedObjects);
  
  return 0;
}