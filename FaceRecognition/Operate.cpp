#include <opencv2\opencv.hpp>
#include <string>
#include <iostream>

using namespace cv;
using namespace std;

void getFaceData(){	//获取人脸

	Mat frame;	//捕获摄像头图像
	int num = 0;	//用于做截图信号

	VideoCapture capture(0);	//打开摄像头

	if (!capture.isOpened()){
		//如果打不开摄像头
		cout << "打不开摄像头" << endl;
	}

	/*
	Size size = Size((int)capture.get(CV_CAP_PROP_FRAME_WIDTH), (int)capture.get(CV_CAP_PROP_FRAME_HEIGHT));	//获取摄像头捕获图像的尺寸
	int fps = capture.get(CV_CAP_PROP_FPS);	//捕获摄像头的频率
	*/
	CascadeClassifier faceDetector;	//用于人脸检测
	string haar_face_datapath
		= "C:/Users/Administrator/Desktop/openCV/opencv 3.0.0/opencv/build/etc/haarcascades/haarcascade_frontalface_alt.xml";	//OpenCV自带检测人脸文件
	faceDetector.load(haar_face_datapath);	//加装该文件

	vector<Rect> faces;	//用来装脸
	while (capture.read(frame)){
		//显示摄像头
		flip(frame, frame, 1);	//左右倒置

		faceDetector.detectMultiScale(frame, faces, 1.1, 1, 0, Size(100, 120), Size(380, 400));	//检测人脸
		if (faces.size()>0) cout << "人脸个数：" << faces.size() << endl;
		for (int i = 0; i < faces.size(); i++){	//faces有内容 检测到人脸

			if (num % 10 == 0){
				Mat dst;
				resize(frame(faces[i]), dst, Size(120, 120));	//将脸部区域以120*120方阵储存在dst中
				imwrite(format("C:/Users/Administrator/Desktop/faces_database/face%d.jpg", num), frame(faces[i]));//把人脸部分写到文件中
			}
			rectangle(frame, faces[i], Scalar(0, 0, 255), 2, 8, 0);	//把人脸区域用红色方框画出
		}

		imshow("摄像头", frame);	//画完方框再show才能看到有方框

		char key = waitKey(100);	//100ms内等待输入，有输入赋值输入给key
		num++;

		if (num == 150) break;
	}
	capture.release();
}