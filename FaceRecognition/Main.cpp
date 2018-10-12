#include <opencv2\opencv.hpp>
#include <opencv2\core\matx.hpp>
#include <opencv2\imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void calcPCAOrientation(vector<Point> &points, Mat &image);
int main()
{
	Mat image = imread("trump.jpg");	//ʹ�þ����ͼƬ
	if (image.empty()){	//���ͼƬΪ��
		cout << "Could not loading image" << endl;
		waitKey(0);
		return -1;
	}
	Mat gray, binary;	//ʹ�þ��󴢴��ͼƬ�ĻҶ�ͼ�Ͷ�ֵͼ
	cvtColor(image, gray, COLOR_BGR2GRAY);	//��ȡ��ͼƬ�ĻҶ�ͼ
	threshold(gray, binary, 0, 255, THRESH_BINARY | THRESH_OTSU);	//�ӻҶ�ͼ��ȡͼƬ�Ķ�ֵͼ
	
	vector<vector<Point>> contours;	//��¼ͼƬ����������
	vector<Vec4i> hireachy;	//�ĸ�int�������ֱ��ʾ�����ĺ�һ��������ǰһ������������������Ƕ����������


	findContours(binary, contours, hireachy, CV_RETR_TREE, CV_CHAIN_APPROX_NONE, Point());	//�Ӷ�ֵͼ��ȡͼƬ����
	
	Mat result = image.clone();	//��ԭͼ��¡һ��ͼƬ
	for (int i = 0; i < contours.size(); i++){
		double area = contourArea(contours[i]);	//��ȡ��iƬ����������
		if (area >1e5 || area < 1e2) continue;	//����̫��̫С������
		drawContours(result, contours, i, Scalar(0, 0, 255), 2, 8);//�ú�ɫ��������
		calcPCAOrientation(contours[i],result);
	}

	imshow("result", result);
	
	waitKey(0);
	return 0;
}

void calcPCAOrientation(vector<Point> &points, Mat &image){
	int size = static_cast<int>(points.size());	//��ȡ�ɶ������ɵ�ͼ�ε�size����ǿ��ת����int�͸�ֵ��size
	Mat data_points = Mat(size, 2, CV_64FC1);	//д��size�С�2�У�����Ϊdouble�ľ���2��������¼x��y����ά�ȵ����ݣ�
	for (int i = 0; i < size; i++){
		//�����ȡ�������ά������
		data_points.at<double>(i, 0) = points[i].x;	//����i�����xά�ȵ�ֵ��ֵ������ĵ�1�еĵ�i��
		data_points.at<double>(i, 1) = points[i].y;	//����i�����yά�ȵ�ֵ��ֵ������ĵ�2�еĵ�i��
	}

	PCA pca_analysis(data_points,Mat(),CV_PCA_DATA_AS_ROW);	//�����ݻ���PCA����ά��

	Point cnt = Point(static_cast<int>(pca_analysis.mean.at<double>(0, 0)),
		static_cast<int>(pca_analysis.mean.at<double>(0, 1)));	//�ҳ�xά�Ⱦ�ֵ��yά�Ⱦ�ֵ�Ľ���
	circle(image, cnt, 2, Scalar(0, 255, 0), 2, 8, 0);	//���õ�����ɫ����

	vector<double> eigen_vals(2);	//���ڴ洢����ֵ
	vector<Point2d> eigen_vector(2);	//���ڴ洢��������(���x��yΪ��2λ��Чֵ��double)
	
	{
		//��ȡPAC��1�У�xά�ȣ�������ֵ����������
		eigen_vals[0] = pca_analysis.eigenvalues.at<double>(0, 0);
		eigen_vector[0] = Point2d(pca_analysis.eigenvectors.at<double>(0, 0), pca_analysis.eigenvectors.at<double>(0, 1));				
	}

	{
		//��ȡPAC��2�У�yά�ȣ�������ֵ����������
		eigen_vals[0] = pca_analysis.eigenvalues.at<double>(1, 0);
		eigen_vector[0] = Point2d(pca_analysis.eigenvectors.at<double>(1, 0), pca_analysis.eigenvectors.at<double>(1, 1));
	}
	
	//����ֵ*���������õ���������*I*x����Ȼ����x��y����ά������������P0��P1
	Point p0 = cnt + 0.2*Point(static_cast<int>(eigen_vector[0].x*eigen_vals[0]),static_cast<int>(eigen_vector[0].y*eigen_vals[0]));
	Point p1 = cnt - 0.2*Point(static_cast<int>(eigen_vector[1].x*eigen_vals[1]), static_cast<int>(eigen_vector[1].y*eigen_vals[1]));
	//��image������ɫ����cnt��P0��P1֮�����
	line(image, cnt, p0, Scalar(255, 0, 0), 2, 8, 0);
	line(image, cnt, p1, Scalar(255, 0, 0), 2, 8, 0);
}