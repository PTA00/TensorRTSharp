#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <numeric>
#include "NvInfer.h"
#include "NvOnnxParser.h"
#include <opencv2/opencv.hpp>
#include<windows.h>


// @brief ���ڴ���IBuilder��IRuntime��IRefitterʵ���ļ�¼������ͨ���ýӿڴ��������ж���
// ���ͷ����д����Ķ���֮ǰ����¼��Ӧһֱ��Ч��
// ��Ҫ��ʵ����ILogger���µ�log()������
class Logger : public nvinfer1::ILogger {
	void log(Severity severity, const char* message)  noexcept {
		// suppress info-level messages
		if (severity != Severity::kINFO)
			std::cout << message << std::endl;
	}
} gLogger;

// @brief ������Ľṹ��
typedef struct tensorRT_nvinfer {
	Logger logger;
	// �����л�����
	nvinfer1::IRuntime* runtime;
	// ��������
	// ����ģ�͵�ģ�ͽṹ��ģ�Ͳ����Լ����ż���kernel���ã�
	// ���ܿ�ƽ̨�Ϳ�TensorRT�汾��ֲ
	nvinfer1::ICudaEngine* engine;
	// ������
	// �����м�ֵ��ʵ�ʽ�������Ķ���
	// ��engine�������ɴ���������󣬽��ж���������
	nvinfer1::IExecutionContext* context;
	// cudn�����־
	cudaStream_t stream;
	// GPU�Դ�����/�������
	void** data_buffer;
} NvinferStruct;

// @brief ������onnxģ��תΪtensorrt�е�engine��ʽ�������浽����
EXTERN_C __MIDL_DECLSPEC_DLLEXPORT void STDMETHODCALLTYPE  onnx_to_engine(const wchar_t* onnx_file_path_wchar,
	const wchar_t* engine_file_path_wchar, int type);
// @brief ��ȡ����engineģ�ͣ�����ʼ��NvinferStruct
EXTERN_C __MIDL_DECLSPEC_DLLEXPORT void* STDMETHODCALLTYPE nvinfer_init(const wchar_t* engine_filename_wchar);
// @brief ����GPU�Դ�����/���������
EXTERN_C __MIDL_DECLSPEC_DLLEXPORT void* STDMETHODCALLTYPE creat_gpu_buffer(void* nvinfer_ptr);
// @brief ����ͼƬ�������ݵ�������
EXTERN_C __MIDL_DECLSPEC_DLLEXPORT void* STDMETHODCALLTYPE load_image_data(void* nvinfer_ptr,
	const wchar_t* node_name_wchar, uchar * image_data, size_t image_size, int BN_means);
// @brief ģ������
EXTERN_C __MIDL_DECLSPEC_DLLEXPORT void* STDMETHODCALLTYPE infer(void* nvinfer_ptr);
// @brief ��ȡ��������
EXTERN_C __MIDL_DECLSPEC_DLLEXPORT void STDMETHODCALLTYPE  read_infer_result(void* nvinfer_ptr,
	const wchar_t* node_name_wchar, float* output_result);
// @brief ɾ���ڴ��ַ
EXTERN_C __MIDL_DECLSPEC_DLLEXPORT void STDMETHODCALLTYPE nvinfer_delete(void* nvinfer_ptr);
