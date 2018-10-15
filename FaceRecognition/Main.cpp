#include <opencv2\opencv.hpp>
#include <opencv2\face.hpp>
#include <string>
#include <iostream>
#include <fstream>

using namespace cv;
using namespace std;

//void calcPCAOrientation(vector<Point> &points, Mat &image);

int main()	//训练人脸
{
	string filename = string("C:/Users/Administrator/Desktop/faces_database/image.csv");
	ifstream file(filename.c_str(),ifstream::in);
	if (!file){
		cout << "打不开文件" << endl;
	}
	string line, path, classlabel;
	vector<Mat> images;
	waitKey(0);
	return 0;
}
/*
void calcPCAOrientation(vector<Point> &points, Mat &image){
	int size = static_cast<int>(points.size());	//获取由多个点组成的图形的size，并强制转换成int型赋值给size
	Mat data_points = Mat(size, 2, CV_64FC1);	//写出size行、2列，精度为double的矩阵（2列用来记录x、y两个维度的数据）
	for (int i = 0; i < size; i++){
		//矩阵获取点的两个维度数据
		data_points.at<double>(i, 0) = points[i].x;	//将第i个点的x维度的值赋值给矩阵的第1列的第i行
		data_points.at<double>(i, 1) = points[i].y;	//将第i个点的y维度的值赋值给矩阵的第2列的第i行
	}

	PCA pca_analysis(data_points,Mat(),CV_PCA_DATA_AS_ROW);	//将数据换成PCA（降维）

	Point cnt = Point(static_cast<int>(pca_analysis.mean.at<double>(0, 0)),
		static_cast<int>(pca_analysis.mean.at<double>(0, 1)));	//找出x维度均值与y维度均值的交点
	circle(image, cnt, 2, Scalar(0, 255, 0), 2, 8, 0);	//将该点用绿色画出

	vector<double> eigen_vals(2);	//用于存储特征值
	vector<Point2d> eigen_vector(2);	//用于存储特征向量(点的x、y为：2位有效值的double)
	
	{
		//获取PAC第1列（x维度）的特征值、特征向量
		eigen_vals[0] = pca_analysis.eigenvalues.at<double>(0, 0);
		eigen_vector[0] = Point2d(pca_analysis.eigenvectors.at<double>(0, 0), pca_analysis.eigenvectors.at<double>(0, 1));				
	}

	{
		//获取PAC第2列（y维度）的特征值、特征向量
		eigen_vals[0] = pca_analysis.eigenvalues.at<double>(1, 0);
		eigen_vector[0] = Point2d(pca_analysis.eigenvectors.at<double>(1, 0), pca_analysis.eigenvectors.at<double>(1, 1));
	}
	
	//特征值*特征向量得到特征（λ*I*x），然后在x、y两个维度上找两个点P0、P1
	Point p0 = cnt + 0.2*Point(static_cast<int>(eigen_vector[0].x*eigen_vals[0]),static_cast<int>(eigen_vector[0].y*eigen_vals[0]));
	Point p1 = cnt - 0.2*Point(static_cast<int>(eigen_vector[1].x*eigen_vals[1]), static_cast<int>(eigen_vector[1].y*eigen_vals[1]));
	//在image上用蓝色画出cnt到P0、P1之间的线
	line(image, cnt, p0, Scalar(255, 0, 0), 2, 8, 0);
	line(image, cnt, p1, Scalar(255, 0, 0), 2, 8, 0);
}*/