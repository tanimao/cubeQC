/*


*/
#include <csignal>
#include <iostream>
#include <time.h>
#include <opencv2/opencv.hpp>
#include "matplotlibcpp_starter.h"
//#include "matplotlibcpp.h"

#define DRAWING

volatile std::sig_atomic_t gSignalStatus;

void signal_handler(int signal)
{ 
  gSignalStatus = signal;
}

// C++のコードから簡単にmatplotlibを使ってグラフを作成する方法
//  https://myenigma.hatenablog.com/entry/2016/01/16/093912
namespace plt = matplotlibcpp;

// grep -r "imread" /usr/local/Cellar/opencv/4.1.0_2/include/opencv4/opencv2
// OpenCV(C++)の画像処理メモ https://qiita.com/yoyoyo_/items/aada199371f6802bb887


// ##### 画像情報
void Get_FigureInfo(cv::Mat img)
{
	std::cerr << "\033[32mcalled: Get_FigureInfo\033[m" << std::endl;	
   // 次元数（画像なので縦・横の2次元）
   std::cerr << "dims: " << img.dims << std::endl; // 
   // チャンネル数
   std::cerr << "channels: " << img.channels() << std::endl; // 3
   std::cerr << "img.rows, img.cols: " << img.rows << " " << img.cols << std::endl; // 3
}


// ##### Scaling
void Set_ResizeFigure(cv::Mat img, double scale)
{
   std::cerr << "\033[32mcalled: Set_ResizeFigure\033[m" << std::endl;
	cv::Mat out; 
   int height = img.rows;
   int width  = img.cols;
	std::cerr << "width " << width << " height" << height << std::endl; 
	//cv::resize(img , ret, cv::Size(), 0.5,0.5, cv::INTER_NEAREST);//, cv::);//int(width*scale), int(height*scale)));
	cv::resize(img, out, cv::Size(), scale, scale);

	#ifdef DRAWING
   cv::namedWindow("Scaling", cv::WINDOW_AUTOSIZE);
   cv::imshow("Scaling", out);
   //cv::waitKey(0);
   //cv::destroyAllWindows();
	#endif
}


// ##### ２値化閾値処理
// need to put gray scale
// cv::threshold
// cv::adaptiveThreshold
void Draw_TypicalThresholdProcessing(cv::Mat imgCol, cv::Mat imgGray)
{
   std::cerr << "\033[32mcalled: Draw_TypicalThresholdProcessing\033[m" << std::endl;
   cv::Mat imgRet[6];
	// Apply a fixed-level threshold to each pixel
	cv::threshold(imgGray, imgRet[0],127,256, cv::THRESH_BINARY    |cv::THRESH_OTSU);
  	cv::threshold(imgGray, imgRet[1],127,256, cv::THRESH_BINARY_INV|cv::THRESH_OTSU);
  	cv::threshold(imgGray, imgRet[2],127,256, cv::THRESH_TRUNC     |cv::THRESH_OTSU);
  	cv::threshold(imgGray, imgRet[3],127,256, cv::THRESH_TOZERO    |cv::THRESH_OTSU);
  	cv::threshold(imgGray, imgRet[4],127,256, cv::THRESH_TOZERO_INV|cv::THRESH_OTSU);

	// Apply an adaptive threshold to a grayscale image
	// thresholdType – 閾値の種類． THRESH_BINARY または THRESH_BINARY_INV のどちらか．
  	//cv::adaptiveThreshold(imgGray, imgRet[5], 255, cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, 7, 8);
  	cv::adaptiveThreshold(imgGray, imgRet[5], 255, cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY_INV, 7, 8);
  
   const char *titles[] = {"BINARY", "BINARY_INV", 
                           "TRUNC", "TOZERO", "TOZERO_INV","ADAPTIVE"};

	#ifdef DRAWING
	for (int i=0; i<6; i++) {
		cv::namedWindow(titles[i], cv::WINDOW_AUTOSIZE);
  		cv::imshow(titles[i], imgRet[i]);
	}
   //cv::waitKey(0);
   //cv::destroyAllWindows();
	#endif
}


// ##### HSVでの色抽出
// cv::inRange
/*
① 色相(H)：0～180 (×2すると度数になり、0～360度を示す)
② 彩度(S)：0～255
③ 明度(V)：0～255
OpenCVでは値が次のように決まっています。彩度と明度が0～255は感覚的に理解しやすいですが、
色相(H)は0～180となる点には注意が必要です。この値をオーバーした場合、255までは循環するので
0～255の値を使う分には問題ないですが、この認識がないと狙った色を抜くことができません。
*/
//void Get_SpecifiedFigureByHSV(cv::Mat img, int minHSV[], int maxHSV[])
void Get_SpecifiedFigureByHSV(cv::Mat img, int minHSV[])
{
   std::cerr << "\033[32mcalled: Get_SpecifiedFigureByHSV\033[m" << std::endl;
  	cv::Mat hsv, mask, output;//画像オブジェクトの宣言
   // RGB -> HSV
   cv::cvtColor(img, hsv, cv::COLOR_RGB2HSV, 3);

   // inRangeによるフィルタ : 抽出する画像の輝度値の範囲を指定
	cv::Scalar sMinHSV = cv::Scalar(minHSV[0],minHSV[1],minHSV[2]);
	//cv::Scalar sMaxHSV = cv::Scalar(maxHSV[0],maxHSV[1],maxHSV[2]);
	cv::Scalar sMaxHSV = cv::Scalar(180,256,256);
   cv::inRange(hsv, sMinHSV, sMaxHSV, mask); //色検出でマスク画像の生成

	// マスクを基に入力画像をフィルタリング
	img.copyTo(output, mask);

	#ifdef DRAWING
   cv::namedWindow("HSV", cv::WINDOW_AUTOSIZE);
   cv::imshow("HSV", hsv);
   cv::namedWindow("Mask-HSV", cv::WINDOW_AUTOSIZE);
   cv::imshow("Mask-HSV", mask);
   cv::namedWindow("HSV-Output", cv::WINDOW_AUTOSIZE);
   cv::imshow("HSV-Output", output);
   //cv::waitKey(0);
   //cv::destroyAllWindows();
	#endif
}


// ##### BGRでの白色抽出
cv::Mat Get_SpecifiedFigureByBGR(cv::Mat img, int minBGR[])
{
   std::cerr << "\033[32mcalled: Get_SpecifiedFigureByBGR\033[m" << std::endl;
   cv::Mat mask, output;//画像オブジェクトの宣言

   // inRangeによるフィルタ : 抽出する画像の範囲を指定
   cv::Scalar sMinBGR = cv::Scalar(minBGR[0],minBGR[1],minBGR[2]);
   //cv::Scalar sMaxBGR = cv::Scalar(maxHSV[0],maxHSV[1],maxHSV[2]);
   cv::Scalar sMaxBGR = cv::Scalar(256,256,256);
   cv::inRange(img, sMinBGR, sMaxBGR, mask); //色検出でマスク画像の生成

   // マスクを基に入力画像をフィルタリング
   img.copyTo(output, mask);

	#ifdef DRAWING
   cv::namedWindow("Mask-BGR", cv::WINDOW_AUTOSIZE);
   cv::imshow("Mask-BGR", mask);
   cv::namedWindow("BGR-Output", cv::WINDOW_AUTOSIZE);
   cv::imshow("BGR-Output", output);
   //cv::waitKey(0);
   //cv::destroyAllWindows();
	#endif
	return output;
}


// ##### 画像抜き出し/トリミング
//void Get_TrimmedFigure(cv::Mat img, int minXY[], int maxXY[])
cv::Mat Get_TrimmedFigure(cv::Mat img, int minXY[], int maxXY[])
{
   std::cerr << "\033[32mcalled: Get_TrimmedFigure\033[m" << std::endl;
	// Setup a rectangle to define your region of interest
	// x1, y1, x2, y2
	cv::Rect myROI(minXY[0], minXY[1], maxXY[0], maxXY[1]); 
	// Crop the full image to that image contained by the rectangle myROI
	// Note that this doesn't copy the data
	cv::Mat croppedImg = img(myROI);

	#ifdef DRAWING
   cv::namedWindow("Cropped", cv::WINDOW_AUTOSIZE);
   cv::imshow("Cropped", croppedImg);
   //cv::waitKey(0);
   //cv::destroyAllWindows();
	#endif
	return croppedImg;
}


// ##### ハフ変換による円検出
// http://opencv.jp/opencv-2svn/cpp/feature_detection.html#cv-houghcircles
void Detect_HoughCircles_GrayFigure(cv::Mat col, cv::Mat gray)
{
	std::cerr << "\033[32mcalled: Detect_HoughCircles_GrayFigure\033[m" << std::endl;	
   // 平滑化を行います．これがないと誤検出が起こりやすくなります．
   cv::GaussianBlur(gray, gray, cv::Size(9, 9), 2, 2);
   std::vector<cv::Vec3f> circles;
	// http://opencv.jp/opencv-2svn/cpp/feature_detection.html#cv-houghcircles
   //cv2.HoughCircles(gray, cv2.HOUGH_GRADIENT, 1, 20, param1=50,param2=30,minRadius=0,maxRadius=0)
   //cv::HoughCircles(gray, circles, cv::HOUGH_GRADIENT, 2, gray.rows/4, 200, 100);
   cv::HoughCircles(gray, circles, cv::HOUGH_GRADIENT, 1, /*minDist*/100, 50, 30, /*minRadius*/10, 0);
   std::cerr << "#of Hough Circles : " << circles.size() << "" << std::endl;

	   	// test: make Binarization 
   		cv::Mat binary;
   		//cv::threshold(gray, binary, 10, 55, cv::THRESH_BINARY|cv::THRESH_OTSU);
	      //cv::threshold(gray, binary, 0,200, cv::THRESH_BINARY_INV|cv::THRESH_OTSU);
	   	cv::threshold(gray, binary,127,156, cv::THRESH_TRUNC     |cv::THRESH_OTSU);
   		//cv::adaptiveThreshold(gray, binary, 220, cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, 3, 0);

	for (size_t i=0; i<circles.size(); i++) {
   	cv::Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
      int radius = cvRound(circles[i][2]);
		//cv::Scalar colCenter(0,255,0);
		cv::Scalar colCenter(255,255,255);
		//cv::Scalar colRad(0,0,255);
		cv::Scalar colRad(255,255,255);
      // 円の中心を描画します．
      //cv::circle(col,  center, 3, colCenter, -1, 8, 0 );
      //cv::circle(gray, center, 3, colCenter, -1, 8, 0 );
      cv::circle(binary, center, 3, colCenter, -1, 8, 0 );
      // 円を描画します．
      //cv::circle(col,  center, radius, colRad, 3, 8, 0 );
      //cv::circle(gray, center, radius, colRad, 3, 8, 0 );
      cv::circle(binary, center, radius, colRad, 3, 8, 0 );
		std::cerr << "	circle : " << i << " center=" << center << " radius=" << radius << std::endl;
      char strtemp[48];
      snprintf(strtemp, sizeof(strtemp), "c(%u,%u), r=%u", center.x,center.y,radius);
      cv::String labelstr = strtemp;
      int fontFace = cv::FONT_HERSHEY_COMPLEX_SMALL;
		// http://opencv.jp/cookbook/opencv_drawing.html
		// 画像，テキスト，位置（左下），フォント，スケール，色，線太さ，種類
      cv::putText(binary, labelstr, cv::Point(center.x*0.50,center.y*0.7),  
                  fontFace, 1.4, cv::Scalar(0, 152, 243), 2, 8);
 	}
	#ifdef DRAWING
   cv::namedWindow("HoughCircles", cv::WINDOW_AUTOSIZE);
   cv::imshow("HoughCircles", binary);	
	#endif
}


// ##### 四角の輪郭抽出
// void findContours(const Mat& image, vector<vector<Point> >& contours, int mode, int method, Point offset=Point())
// http://opencv.jp/opencv-2svn/cpp/imgproc_structural_analysis_and_shape_descriptors.html?highlight=drawcontours#cv-drawcontours
void Detect_SquareOutline_GrayFigure(cv::Mat col, cv::Mat gray)
{
	std::cerr << "\033[32mcalled: Detect_SquareOutline_GrayFigure\033[m" << std::endl;
	std::vector<std::vector<cv::Point>> contours; //輪郭データ
	// need to make Binarization !! before detecting contours
	cv::Mat binary;
   //cv::threshold(gray, binary, 0, 255, cv::THRESH_BINARY|cv::THRESH_OTSU);
   cv::threshold(gray, binary, 120, 255, cv::THRESH_BINARY|cv::THRESH_OTSU);

	#ifdef DRAWING
	// check above situation 
   cv::namedWindow("SquareOutline binary", cv::WINDOW_AUTOSIZE);
   cv::imshow("SquareOutline binary", binary);
	#endif

	// detecting contours
   cv::findContours(gray, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
   //cv::findContours(binary, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
   //cv::findContours(binary, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
   int objs = contours.size();    //検出オブジェクト数
   std::cerr << "#of contours : " << objs << "\n" << std::endl;

	for (int i=0; i<objs; i++) {
		/*
      cv::Mat inputpoints;
      cv::Mat(contours[i]).convertTo(inputpoints, CV_32F);
      cv::RotatedRect box = minAreaRect(inputpoints);    //楕円フィッティング
      cv::RotatedRect box1 = fitEllipse(inputpoints);    //最小矩形(回転を考慮)算出
      //結果代入
      LabellingResd[i, 0] = box.center.x;                       //Cx(中心座標x)
      LabellingResd[i, 1] = box.center.y;                       //Cy(中心座標y)
      LabellingResd[i, 2] = box.size.width;                     //width
      LabellingResd[i, 3] = box.size.height;                    //height
      LabellingResd[i, 4] = contourArea(contours[i], false);    //area 領域が囲む面積を算出
      LabellingResd[i, 5] = box1.angle;                         //angle
      */ 
      double arclen = cv::arcLength(contours[i], true); // 対象領域が閉曲線の場合、True
      double arcare = cv::contourArea(contours[i]);
		if (arclen<500) continue;
		std::cerr << "contours : " << i << " length=" << arclen << " area=" << arcare << std::endl;

      cv::drawContours(col, contours, (int)i, cv::Scalar(0,200,0), 4, 1);    //結果画像(輪郭)描画

		// CV_*C2型のMatに変換してから，外接矩形を計算
  		cv::Rect boundingRect = cv::boundingRect(cv::Mat(contours[i]).reshape(2));  
  		// 外接矩形を描画
		// cv::Rect a{10, 10, 100, 200}; // topleft=(10, 10), (width, height)=(100, 200)
		// good reference! https://book.mynavi.jp/support/pc/opencv2/c3/opencv_img.html
		cv::rectangle(col, boundingRect.tl(), boundingRect.br(), cv::Scalar(200, 0, 0), 4, 1);
		double lengthRectangle = boundingRect.width*2 + boundingRect.height*2 ;
		std::cout << "		bounding Rectangle length = " << lengthRectangle << std::endl;
		std::cout << "			difference = " << fabs(lengthRectangle-arclen) << std::endl;
		//std::cout << "			" << boundingRect.tl() << std::endl; // 
		//std::cout << "			" << boundingRect.br() << std::endl; // 
		//std::cout << "				" << boundingRect.width << " " << boundingRect.height << std::endl; // 
	
      char strtemp[48];
      snprintf(strtemp, sizeof(strtemp), "%u: outl=%.1f, recta=%.1f", i, arclen, lengthRectangle);
      cv::String labelstr = strtemp;
		//int fontFace = cv::FONT_HERSHEY_SCRIPT_SIMPLEX;
		int fontFace = cv::FONT_HERSHEY_COMPLEX_SMALL;
		// http://opencv.jp/cookbook/opencv_drawing.html
		// 画像，テキスト，位置（左下），フォント，スケール，色，線太さ，種類
      //cv::putText(col, labelstr, boundingRect.tl(), true, fontFace, cv::Scalar(0, 210, 210), 5, 8) ;
      cv::putText(col, labelstr, cv::Point(boundingRect.x*0.82,boundingRect.y*0.95),  
                  fontFace, 1.5, cv::Scalar(0, 162, 253), 2, 8) ;

		std::cout << std::endl; 
   } 	
	#ifdef DRAWING
   cv::namedWindow("SquareOutline", cv::WINDOW_AUTOSIZE);
   cv::imshow("SquareOutline", col);	
	#endif
}


// 画素値の抜き出し
// https://minus9d.hatenablog.com/entry/20130126/1359194404
void Get_PixelValues_FromGrayScale(cv::Mat gray)
{
   int height = gray.rows;
   int width  = gray.cols;
   std::cerr << "width " << width << " height" << height << std::endl;

	#ifdef DRAWING
   // check figure 
   cv::namedWindow("Get PixelValues", cv::WINDOW_AUTOSIZE);
   cv::imshow("Get PixelValues", gray);
	#endif

   std::vector<int> x_hori1;
   std::vector<int> y_hori1, y_hori2, y_hori3; 
   for(int i=0; i<width; ++i) {
		int intensity1 = gray.at<unsigned char>(int(height/10*2), i); // X座標がx, Y座標がyに位置するピクセルの値を取得
		int intensity2 = gray.at<unsigned char>(int(height/10*5), i); // X座標がx, Y座標がyに位置するピクセルの値を取得
		int intensity3 = gray.at<unsigned char>(int(height/10*8), i); // X座標がx, Y座標がyに位置するピクセルの値を取得
		x_hori1.push_back(i);
		y_hori1.push_back(intensity1);
		y_hori2.push_back(intensity2);
		y_hori3.push_back(intensity3);
	}

   std::vector<int> x_vert1;
   std::vector<int> y_vert1, y_vert2, y_vert3;
   for(int i=0; i<height; ++i) {
      int intensity1 = gray.at<unsigned char>(i, int(width/10*2)); // X座標がx, Y座標がyに位置するピクセルの値を取得
      int intensity2 = gray.at<unsigned char>(i, int(width/10*5)); // X座標がx, Y座標がyに位置するピクセルの値を取得
      int intensity3 = gray.at<unsigned char>(i, int(width/10*8)); // X座標がx, Y座標がyに位置するピクセルの値を取得
      x_vert1.push_back(i);
      y_vert1.push_back(intensity1);
      y_vert2.push_back(intensity2);
      y_vert3.push_back(intensity3);
   }


	#ifdef DRAWING
	//plt::xkcd();
   //plt::figure();//figsize=(4, 4), dpi=100);
   plt::figure_size(1200,480);//figsize=(4, 4), dpi=100);
   plt::subplot(1,2,1);
	plt::xlabel("pix position horizontal");
	plt::ylabel("pix value");
   plt::plot(x_hori1, y_hori1, "-or");
   plt::plot(x_hori1, y_hori2, "-og");
   plt::plot(x_hori1, y_hori3, "-ob");
   //plt::figure(4, 4);//), dpi=100)
   //plt::figure();//figsize=(4, 4), dpi=100);
   plt::subplot(1,2,2);
	plt::xlabel("pix position vertical");
	plt::ylabel("pix value");
   plt::plot(x_vert1, y_vert1, "-or");
   plt::plot(x_vert1, y_vert2, "-og");
   plt::plot(x_vert1, y_vert3, "-ob");
	#endif
}


int main(int argc, char **argv)
{
   clock_t start = clock();
  	std::signal(SIGINT, signal_handler);

   //const char* imgName = argc > 1 ? argv[1] : "lena.jpg";
   //const char* imgName = argc > 1 ? argv[1] : "cube1.jpg";
   const char* imgName = argc > 1 ? argv[1] : "cube2.jpg";
   std::cerr << "\n\033[32mGiven imgName : " << imgName << "\033[m\n" << std::endl;
/*
C++                  | Python               |値|説明
cv::IMREAD_COLOR     | cv2.IMREAD_COLOR     | 1|常に３チャネル（デフォルト）  
cv::IMREAD_GRAYSCALE | cv2.IMREAD_GRAYSCALE | 0|常に１チャネル（グレースケール）  
cv::IMREAD_ANYCOLOR  | cv2.IMREAD_ANYCOLOR  | 4|３チャネルまでのよみこみ
cv::IMREAD_ANYDEPTH  | cv2.IMREAD_ANYDEPTH  | 2|８ビットより深い画像の読み込み可 
cv::IMREAD_UNCHANGED | cv2.IMREAD_UNCHANGED |-1|アルファチャネルまでOK   
*/
	cv::Mat imgCol = cv::imread(imgName, cv::IMREAD_COLOR); 
	cv::Mat imgGray;
   if ( imgCol.empty() ) return -1;
	else cv::cvtColor(imgCol, imgGray, cv::COLOR_BGR2GRAY);
/* 
C++                  | Python               |値|説明
---------------------------------------------------------------------
cv::WINDOW_AUTOSIZE | cv2.WINDOW_AUTOSIZE | 1|自動調整（デフォルト）  
cv::WINDOW_NORMAL   | cv2.WINDOW_NORMAL   | 0|ユーザがウィンドウを変えることができる
 -> namedWindowとimshowの名前が異なる場合には、２つのウィンドウが生成されることになるようです。
*/
   cv::namedWindow("original color", cv::WINDOW_AUTOSIZE);
   cv::imshow("original color", imgCol); 
   cv::namedWindow("original gray", cv::WINDOW_AUTOSIZE);
   cv::imshow("original gray", imgGray); 
	//return 0;

	// ##### 
	Get_FigureInfo(imgCol);
	//Set_ResizeFigure(imgCol, 0.5);	

	Draw_TypicalThresholdProcessing(imgCol, imgGray);

	int minHSV[3]={50,40,40};
	//Get_SpecifiedFigureByHSV(imgCol, minHSV);	
	int minBGR[3]={100,100,100}; // cube1.jpg
	//int minBGR[3]={160,160,160}; // cube2.jpg
	cv::Mat imgCol_ExtractWhite = Get_SpecifiedFigureByBGR(imgCol, minBGR);	

	#if 0 // cube1.jpg
	int minXY[2]={220, 220};
	int maxXY[2]={620, 580};
	#endif
   #if 1 // cube2.jpg
   int minXY[2]={200, 140};
   int maxXY[2]={500, 520};
   #endif
	cv::Mat imgCol_trimLarge = Get_TrimmedFigure(imgCol, minXY, maxXY);
   cv::Mat imgGray_trimLarge;
   cv::cvtColor(imgCol_trimLarge, imgGray_trimLarge, cv::COLOR_BGR2GRAY);

	#if 0 // cube1.jpg
   int minXY_S[2]={300, 300};
   int maxXY_S[2]={500, 500};
	#endif
   #if 1 // cube2.jpg
   int minXY_S[2]={220, 200};
   int maxXY_S[2]={420, 400};
   #endif
   cv::Mat imgCol_trimSmall = Get_TrimmedFigure(imgCol, minXY_S, maxXY_S);
   cv::Mat imgGray_trimSmall; 
   cv::cvtColor(imgCol_trimSmall, imgGray_trimSmall, cv::COLOR_BGR2GRAY);

	//Detect_HoughCircles_GrayFigure(imgCol, imgGray);
	Detect_HoughCircles_GrayFigure(imgCol_trimSmall, imgGray_trimSmall);

	// 白色抜き出しした後、グレースケール変換を、インプットする方が良い
   cv::Mat imgGray_ExtractWhite; 
   cv::cvtColor(imgCol_ExtractWhite, imgGray_ExtractWhite, cv::COLOR_BGR2GRAY);
	//Detect_SquareOutline_GrayFigure(imgCol, imgGray);
	//Detect_SquareOutline_GrayFigure(imgCol_trimLarge, imgGray_trimLarge);
	Detect_SquareOutline_GrayFigure(imgCol_ExtractWhite,imgGray_ExtractWhite);

	//Get_PixelValues_FromGrayScale(imgGray_trimLarge);
	Get_PixelValues_FromGrayScale(imgGray_ExtractWhite);

   clock_t end = clock();
   const double time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000.0;
   printf("time %lf[ms]\n", time);

   plt::show();
   cv::waitKey(0);
   cv::destroyAllWindows();
}


