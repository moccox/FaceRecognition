#include <opencv2\opencv.hpp>
#include <string>
#include <iostream>

using namespace cv;
using namespace std;

void getFaceData(){	//��ȡ����

	Mat frame;	//��������ͷͼ��
	int num = 0;	//��������ͼ�ź�

	VideoCapture capture(0);	//������ͷ

	if (!capture.isOpened()){
		//����򲻿�����ͷ
		cout << "�򲻿�����ͷ" << endl;
	}

	/*
	Size size = Size((int)capture.get(CV_CAP_PROP_FRAME_WIDTH), (int)capture.get(CV_CAP_PROP_FRAME_HEIGHT));	//��ȡ����ͷ����ͼ��ĳߴ�
	int fps = capture.get(CV_CAP_PROP_FPS);	//��������ͷ��Ƶ��
	*/
	CascadeClassifier faceDetector;	//�����������
	string haar_face_datapath
		= "C:/Users/Administrator/Desktop/openCV/opencv 3.0.0/opencv/build/etc/haarcascades/haarcascade_frontalface_alt.xml";	//OpenCV�Դ���������ļ�
	faceDetector.load(haar_face_datapath);	//��װ���ļ�

	vector<Rect> faces;	//����װ��
	while (capture.read(frame)){
		//��ʾ����ͷ
		flip(frame, frame, 1);	//���ҵ���

		faceDetector.detectMultiScale(frame, faces, 1.1, 1, 0, Size(100, 120), Size(380, 400));	//�������
		if (faces.size()>0) cout << "����������" << faces.size() << endl;
		for (int i = 0; i < faces.size(); i++){	//faces������ ��⵽����

			if (num % 10 == 0){
				Mat dst;
				resize(frame(faces[i]), dst, Size(120, 120));	//������������120*120���󴢴���dst��
				imwrite(format("C:/Users/Administrator/Desktop/faces_database/face%d.jpg", num), frame(faces[i]));//����������д���ļ���
			}
			rectangle(frame, faces[i], Scalar(0, 0, 255), 2, 8, 0);	//�����������ú�ɫ���򻭳�
		}

		imshow("����ͷ", frame);	//���귽����show���ܿ����з���

		char key = waitKey(100);	//100ms�ڵȴ����룬�����븳ֵ�����key
		num++;

		if (num == 150) break;
	}
	capture.release();
}