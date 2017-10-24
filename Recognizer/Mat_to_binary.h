#pragma once
#include <opencv2/core/core.hpp>
#include <fstream>

//! Write cv::Mat as binary
/*!
\param[out] ofs output file stream
\param[in] out_mat mat to save
*/

inline bool writeMatBinary(std::ofstream& ofs, const cv::Mat& out_mat)
{
	if (!ofs.is_open()) {
		return false;
	}
	if (out_mat.empty()) {
		int s = 0;
		ofs.write((const char*)(&s), sizeof(int));
		return true;
	}
	int type = out_mat.type();
	ofs.write((const char*)(&out_mat.rows), sizeof(int));
	ofs.write((const char*)(&out_mat.cols), sizeof(int));
	ofs.write((const char*)(&type), sizeof(int));
	ofs.write((const char*)(out_mat.data), out_mat.elemSize() * out_mat.total());

	return true;
}


//! Save cv::Mat as binary
/*!
\param[in] filename filaname to save
\param[in] output cvmat to save
*/
inline bool SaveMatBinary(const std::string& filename, const cv::Mat& output) {
	std::ofstream ofs(filename, std::ios::binary);
	return writeMatBinary(ofs, output);
	ofs.close();
}

inline bool SaveMatBinary_2(ofstream &ofs, const cv::Mat& output) {
	//	std::ofstream ofs(filename, std::ios::binary);
	return writeMatBinary(ofs, output);
}

//! Read cv::Mat from binary
/*!
\param[in] ifs input file stream
\param[out] in_mat mat to load
*/

// ATTENZIONE FUNZIONA SOLO CON I FLOAT, BISOGNEREBBE FARE UN TEMPLATE E AGGIUNGERE UN TERZO ARGOMENTO IN INGRESSO PARI AL TIPO...
inline bool readMatBinary(std::ifstream& ifs, cv::Mat& in_mat)
{
	if (!ifs.is_open()) {
		return false;
	}

	int rows, cols, type;
	ifs.read((char*)(&rows), sizeof(float));
	if (rows == 0) {
		return true;
	}
	ifs.read((char*)(&cols), sizeof(float));
	ifs.read((char*)(&type), sizeof(float));

	in_mat.release();
	in_mat.create(rows, cols, type);
	ifs.read((char*)(in_mat.data), in_mat.elemSize() * in_mat.total());

	return true;
}


//! Load cv::Mat as binary
/*!
\param[in] filename filaname to load
\param[out] output loaded cv::Mat
*/
//bool LoadMatBinary(const std::string& filename, cv::Mat& output) {
//	std::ifstream ifs(filename, std::ios::binary);
//	return readMatBinary(ifs, output);
//}

inline bool LoadMatBinary(ifstream &ifs, cv::Mat& output) {
	//	std::ifstream ifs(filename, std::ios::binary);
	return readMatBinary(ifs, output);
}


