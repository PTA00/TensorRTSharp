#include"common.h"


// @brief ��wchar_t*�ַ���ָ��ת��Ϊstring�ַ�����ʽ
// @param wchar �����ַ�ָ��
// @return ת������string�ַ��� 
std::string wchar_to_string(const wchar_t* wchar) {
    // ��ȡ����ָ��ĳ���
    int path_size = WideCharToMultiByte(CP_OEMCP, 0, wchar, wcslen(wchar), NULL, 0, NULL, NULL);
    char* chars = new char[path_size + 1];
    // ��˫�ֽ��ַ���ת���ɵ��ֽ��ַ���
    WideCharToMultiByte(CP_OEMCP, 0, wchar, wcslen(wchar), chars, path_size, NULL, NULL);
    chars[path_size] = '\0';
    std::string pattern = chars;
    delete chars; //�ͷ��ڴ�
    return pattern;
}

// @brief ��wchar_t*�ַ���ָ��ת��Ϊstring�ַ�����ʽ
// @param wchar �����ַ�ָ��
// @return ת������string�ַ��� 
char* wchar_to_char(const wchar_t* wchar) {
    // ��ȡ����ָ��ĳ���
    int path_size = WideCharToMultiByte(CP_OEMCP, 0, wchar, wcslen(wchar), NULL, 0, NULL, NULL);
    char* chars = new char[path_size + 1];
    // ��˫�ֽ��ַ���ת���ɵ��ֽ��ַ���
    WideCharToMultiByte(CP_OEMCP, 0, wchar, wcslen(wchar), chars, path_size, NULL, NULL);
    chars[path_size] = '\0';
    return chars;
}

// @brief ��ͼƬ�ľ�������ת��Ϊopencv��mat����
// @param data ͼƬ����
// @param size ͼƬ���󳤶�
// @return ת�����mat����
cv::Mat data_to_mat(uchar* data, size_t size) {
    //��ͼƬ�������ݶ�ȡ��������
    std::vector<uchar> buf;
    for (int i = 0; i < size; i++) {
        buf.push_back(*data);
        data++;
    }
    // ����ͼƬ���룬�������е�����ת��Ϊmat����
    return cv::imdecode(cv::Mat(buf), 1);
}



// @brief ��������任����
// @param center ���ĵ�
// @param input_size ����ߴ�
// @param rot �Ƕ�
// @param output_size ����ߴ�
// @param shift 
// @rrturn �任����
cv::Mat get_affine_transform(cv::Point center, cv::Size input_size, int rot, cv::Size output_size,
    cv::Point2f shift) {

    // ����ߴ���
    int src_w = input_size.width;

    // ����ߴ�
    int dst_w = output_size.width;
    int dst_h = output_size.height;

    // ��ת�Ƕ�
    float rot_rad = 3.1715926f * rot / 180.0;
    int pt = (int)src_w * -0.5;
    float sn = std::sin(rot_rad);
    float cs = std::cos(rot_rad);

    cv::Point2f src_dir(-1.0 * pt * sn, pt * cs);
    cv::Point2f dst_dir(0.0, dst_w * -0.5);
    // ����������
    cv::Point2f src[3];
    src[0] = cv::Point2f(center.x + input_size.width * shift.x, center.y + input_size.height * shift.y);
    src[1] = cv::Point2f(center.x + src_dir.x + input_size.width * shift.x, center.y + src_dir.y + input_size.height * shift.y);
    cv::Point2f direction = src[0] - src[1];
    src[2] = cv::Point2f(src[1].x - direction.y, src[1].y - direction.x);
    // ���������
    cv::Point2f dst[3];
    dst[0] = cv::Point2f(dst_w * 0.5, dst_h * 0.5);
    dst[1] = cv::Point2f(dst_w * 0.5 + dst_dir.x, dst_h * 0.5 + dst_dir.y);
    direction = dst[0] - dst[1];
    dst[2] = cv::Point2f(dst[1].x - direction.y, dst[1].y - direction.x);

    return cv::getAffineTransform(src, dst);

}
