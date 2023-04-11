#pragma once
#pragma once


#include<time.h>
#include<iostream>
#include<map>
#include<string>
#include<vector>
#include "opencv2/opencv.hpp"
#include<windows.h>


// @brief ��wchar_t*�ַ���ָ��ת��Ϊstring�ַ�����ʽ
std::string wchar_to_string(const wchar_t* wchar);
// @brief ��wchar_t*�ַ���ָ��ת��Ϊstring�ַ�����ʽ
char* wchar_to_char(const wchar_t* wchar);

// @brief ��ͼƬ�ľ�������ת��Ϊopencv��mat����
cv::Mat data_to_mat(uchar* data, size_t size);


// @brief ��������任����
cv::Mat get_affine_transform(cv::Point center, cv::Size input_size, int rot, cv::Size output_size,
	cv::Point2f shift = cv::Point2f(0, 0));