#include "LBP.hpp"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>


using namespace lbp;

void drawHist(vector<double> hist, int histSize, int hist_w, int hist_h, string title = "calcHist");
cv::Mat drawHist_rect(vector<double> _histMat, int _histSize, int w, int h);
cv::Mat drawHist_2(vector<double> _histMat, int _histSize, int w, int h);
void spatial_Histogram(LBP lbp, Mat lbpImg, int width, int height, vector<double> &histC, int block=3);
