#ifndef _config_h
#define _config_h

#include <string>
#include <cstdarg>
#include <vector>
#include <sstream>
#include <limits>
#include <cstring>
#include <sys/stat.h>

#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


#ifdef _WIN32
#include <ctime>
#include <direct.h>
#else
#include<dirent.h>
#include <time.h>
#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#endif

//undefying dangerous macros if any
#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif 

/*******************************************************************************************************************************
 *   Forward declarations, types, parameters, constants, exceptions and utility functions   										       *
 *******************************************************************************************************************************/
namespace thesis
{
	/*******************
	*   DECLARATIONS   *
	********************
	---------------------------------------------------------------------------------------------------------------------------*/
	class failure;								//failure exception thrown by functions in the current module
	enum  failure_type { UNDEFINED };
	enum  debug_level { NO_DEBUG, LEV1, LEV2, LEV3 };
	enum  axis { INVALID_AXIS, X, Y, Z };
	/*-------------------------------------------------------------------------------------------------------------------------*/


	/*******************
	*       TYPES      *
	********************
	---------------------------------------------------------------------------------------------------------------------------*/
	typedef signed char	sint8;					//8-bit  signed   integers (-128                       -> +127)
	typedef short sint16;						//16-bit signed   integers (-32,768                    -> +32,767)
	typedef int sint32;							//32-bit signed   integers (-2,147,483,648             -> +2,147,483,647)
	typedef long long sint64;					//64-bit signed   integers (�9,223,372,036,854,775,808 -> +9,223,372,036,854,775,807)
	typedef unsigned char uint8;				//8-bit  unsigned integers (0 -> +255)
	typedef unsigned short int uint16;			//16-bit unsigned integers (0 -> +65,535)
	typedef unsigned int uint32;				//32-bit unsigned integers (0 -> +4,294,967,295)
	typedef unsigned long long uint64;			//64-bit unsigned integers (0 -> +18,446,744,073,709,551,615
	typedef float real32;						//real single precision
	typedef double real64;						//real double precision
	/*-------------------------------------------------------------------------------------------------------------------------*/


	/*******************
	*    CONSTANTS     *
	********************
	---------------------------------------------------------------------------------------------------------------------------*/
	const double PI = 3.14159265358979323846;	//pi
	/*-------------------------------------------------------------------------------------------------------------------------*/


	/*******************
	*    PARAMETERS    *
	********************
	---------------------------------------------------------------------------------------------------------------------------*/
	//extern int DEBUG;							//debug level of current module
	extern int SCREEN_WIDTH;					//screen width (in pixels)
	extern int SCREEN_HEIGHT;					//screen height (in pixels)
	/*-------------------------------------------------------------------------------------------------------------------------*/


	/********************************************
	 *   Cross-platform UTILITY functions	    *
	 ********************************************
	---------------------------------------------------------------------------------------------------------------------------*/
	//infinity 
	template<class T> T inf() {
		if (std::numeric_limits<T>::has_infinity)
			return std::numeric_limits<T>::infinity();
		else
			return std::numeric_limits<T>::max();
	}
	template<class T> T ninf() {
		if (std::numeric_limits<T>::has_infinity)
			return -std::numeric_limits<T>::infinity();
		else
			return std::numeric_limits<T>::min();
	}

	//the case insensitive version of C strstr() function
	inline const char* stristr(const char *str1, const char *str2) {
		if (!*str2)
			return str1;
		for (; *str1; ++str1) {
			if (toupper(*str1) == toupper(*str2)) {
				const char *h, *n;
				for (h = str1, n = str2; *h && *n; ++h, ++n) {
					if (toupper(*h) != toupper(*n)) {
						break;
					}
				}
				if (!*n) /* matched all of 'str2' to null termination */
					return str1; /* return the start of the match */
			}
		}
		return 0;
	}

	//the case insensitive version of C strcmp() function
	inline int stricmp(const char *s1, const char *s2) {
		if (s1 == 0) return s2 == 0 ? 0 : -(*s2);
		if (s2 == 0) return *s1;

		char c1, c2;
		while ((c1 = tolower(*s1)) == (c2 = tolower(*s2)))
		{
			if (*s1 == '\0') break;
			++s1; ++s2;
		}

		return c1 - c2;
	}

	//stringstream-based integer-to-string conversion
	inline std::string int2str(const int& val) {
		std::stringstream ss;
		ss << val;
		return ss.str();
	}

	//infinity-compliant string-to-double conversion
	inline double str2f(const char* str) {
		if (stristr(str, "1.#inf") == str)
			return std::numeric_limits<double>::infinity();
		else if (stristr(str, "-1.#inf") == str)
			return -std::numeric_limits<double>::infinity();
		else if (stristr(str, "-inf") == str)
			return -std::numeric_limits<double>::infinity();
		else if (stristr(str, "inf") == str)
			return std::numeric_limits<double>::infinity();
		else
			return atof(str);
	}

	//fgetstr() - mimics behavior of fgets(), but removes new-line character at end of line if it exists
	inline char *fgetstr(char *string, int n, FILE *stream) {
		char *result;
		result = fgets(string, n, stream);
		if (!result)
			return(result);

		char *nl = strrchr(string, '\r');
		if (nl) *nl = '\0';
		nl = strrchr(string, '\n');
		if (nl) *nl = '\0';

		return(string);
	}

	//string-based tokenization function
	inline void	split(std::string& theString, std::string delim, std::vector<std::string>& tokens) {
		size_t  start = 0, end = 0;
		while (end != std::string::npos)
		{
			end = theString.find(delim, start);

			// If at end, use length=maxLength.  Else use length=end-start.
			tokens.push_back(theString.substr(start,
				(end == std::string::npos) ? std::string::npos : end - start));

			// If at end, use start=maxSize.  Else use start=end+delimiter.
			start = ((end > (std::string::npos - delim.size()))
				? std::string::npos : end + delim.size());
		}
	}

	//extracts the filename from the given path and stores it into <filename>
	inline std::string getFileName(std::string const & path, bool save_ext = true) {

		std::string filename = path;

		// Remove directory if present.
		// Do this before extension removal in case directory has a period character.
		const size_t last_slash_idx = filename.find_last_of("\\/");
		if (std::string::npos != last_slash_idx)
			filename.erase(0, last_slash_idx + 1);

		// Remove extension if present.
		if (!save_ext)
		{
			const size_t period_idx = filename.rfind('.');
			if (std::string::npos != period_idx)
				filename.erase(period_idx);
		}

		return filename;
	}

	//string-based sprintf function
	inline std::string strprintf(const std::string fmt, ...) {
		int size = 100;
		std::string str;
		va_list ap;
		while (1) {
			str.resize(size);
			va_start(ap, fmt);
			int n = vsnprintf((char *)str.c_str(), size, fmt.c_str(), ap);
			va_end(ap);
			if (n > -1 && n < size) {
				str.resize(n);
				return str;
			}
			if (n > -1)
				size = n + 1;
			else
				size *= 2;
		}
		return str;
	}


	//round functions
	inline int round(float  x) { return static_cast<int>(x > 0.0f ? x + 0.5f : x - 0.5f); }
	inline int round(double x) { return static_cast<int>(x > 0.0 ? x + 0.5 : x - 0.5); }

	//returns true if the given path is a directory
	inline bool isDirectory(std::string path) {
		struct stat s;
		if (stat(path.c_str(), &s) == 0)
		{
			if (s.st_mode & S_IFDIR)
				return true;
			else if (s.st_mode & S_IFREG)
				return false;
			else return false;
		}
		else return false;
	}

	//returns true if the given path is a file
	inline bool isFile(std::string path) {
		struct stat s;
		if (stat(path.c_str(), &s) == 0)
		{
			if (s.st_mode & S_IFDIR)
				return false;
			else if (s.st_mode & S_IFREG)
				return true;
			else return false;
		}
		else return false;
	}

	//returns true if the given string <fullString> ends with <ending>
	inline bool hasEnding(std::string const &fullString, std::string const &ending) {
		if (fullString.length() >= ending.length()) {
			return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
		}
		else {
			return false;
		}
	}

	//returns file extension, if any (otherwise returns "")
	inline std::string getFileExtension(const std::string& FileName) {
		if (FileName.find_last_of(".") != std::string::npos)
			return FileName.substr(FileName.find_last_of(".") + 1);
		return "";
	}

	//number to string conversion function and vice versa
	template <typename T>
	std::string num2str(T Number) {
		std::stringstream ss;
		ss << Number;
		return ss.str();
	}
	template <typename T>
	T str2num(const std::string &Text) {
		std::stringstream ss(Text);
		T result;
		return ss >> result ? result : 0;
	}

	//time computation
#ifdef _WIN32
	inline double getTimeSeconds() {
		return static_cast<double>(clock()) / CLOCKS_PER_SEC;
	}
#else
	inline double getTimeSeconds() {
		timespec event;
		clock_gettime(CLOCK_REALTIME, &event);
		return (event.tv_sec*1000.0 + event.tv_nsec / 1000000.0) / 1000.0;
	}
#endif



	//make dir
#ifdef _WIN32
	inline bool make_dir(const char* arg) {
		//printf("Creating directory \"%s\" ...", arg);
		bool done = _mkdir(arg) == 0;
		bool result = done || errno != ENOENT;
		//printf("%s\n", result? "DONE!" : "ERROR!");
		return result;
	}
#else
	inline bool make_dir(const char* arg) {
		//printf("Creating directory \"%s\" ...", arg);
		bool done = mkdir(arg, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == 0;
		bool result = done || errno == EEXIST;
		//printf("%s\n", result ? "DONE!" : "ERROR!");
		return result;
	}
#endif


	//file deleting
#ifdef _WIN32
	inline void delete_file(const char* arg) {
		//if(system(strprintf("del /F /Q /S \"%s\"", arg).c_str())!=0)
		// Se metto la /S mi stampa tutti i file eliminati....

		/*if (system(strprintf("del /F /Q  \"%s\"", arg).c_str()) != 0)
			fprintf(stderr,"Can't delete file \"%s\"\n", arg);*/

		//system(strprintf("del /F /Q  \"%s\"", arg).c_str());
		//system("cls");

		remove(arg);
	}
#else
	inline void delete_file(const char* arg) {
		if (system(strprintf("rm -f \"%s\"", arg).c_str()) != 0)
			fprintf(stderr, "Can't delete file \"%s\"\n", arg);
	}
#endif


	// folder Deleting (Only WIN)
	//file deleting
#ifdef _WIN32
	inline void delete_folder(const char* arg) {
		//if(system(strprintf("del /F /Q /S \"%s\"", arg).c_str())!=0)
		// Se metto la /S mi stampa tutti i file eliminati....
		if (system(strprintf("rd /S /Q  \"%s\"", arg).c_str()) != 0)
			fprintf(stderr, "Can't delete file \"%s\"\n", arg);
	}
#else
	inline void delete_folder(const char *path)
	{
		struct dirent *entry = NULL;
		DIR *dir; dir = NULL;
		dir = opendir(path);
		while (entry = readdir(dir))
		{
			DIR *sub_dir = NULL;
			FILE *file = NULL;
			char abs_path[100] = { 0 };
			if (*(entry->d_name) != '.')
			{
				sprintf(abs_path, "%s/%s", path, entry->d_name);
				if (sub_dir = opendir(abs_path))
				{
					closedir(sub_dir);
					delete_folder(abs_path);
				}
				else
				{
					if (file = fopen(abs_path, "r"))
					{
						fclose(file);
						remove(abs_path);
					}
				}
			}
		}
		remove(path);
	}
#endif


//cross-platform current function macro
#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600))
# define _eeid_current_function __PRETTY_FUNCTION__
#elif defined(__DMC__) && (__DMC__ >= 0x810)
# define _eeid_current_function __PRETTY_FUNCTION__
#elif defined(__FUNCSIG__)
# define _eeid_current_function __FUNCSIG__
#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
# define _eeid_current_function __FUNCTION__
#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
# define _eeid_current_function __FUNC__
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
# define _eeid_current_function __func__
#else
# define _eeid_current_function "(unknown)"
#endif
/*-------------------------------------------------------------------------------------------------------------------------*/

/*******************************************
*   OpenCV UTILITY functions	           *
********************************************
---------------------------------------------------------------------------------------------------------------------------*/
inline void imshow(const std::string winname, const cv::InputArray& arr)
{
	// create window
	cv::namedWindow(winname, CV_WINDOW_FREERATIO);

	// resize window so as to fit screen size while maintaining image aspect ratio
	int win_height = arr.size().height, win_width = arr.size().width;
	if (win_height > thesis::SCREEN_HEIGHT)
	{
		win_height = thesis::SCREEN_HEIGHT;
		win_width = round(win_height * static_cast<float>(arr.size().width) / arr.size().height);
	}
	if (win_width > thesis::SCREEN_WIDTH)
	{
		win_width = thesis::SCREEN_WIDTH;
		win_height = round(win_width * static_cast<float>(arr.size().height) / arr.size().width);
	}
	cv::resizeWindow(winname, win_width, win_height);

	// display image
	cv::imshow(winname, arr);

	// wait for key pressed
	cv::waitKey(0);
}

inline int depth(int ocv_depth)
{
	switch (ocv_depth)
	{
	case CV_8U:  return 8;
	case CV_8S:  return 8;
	case CV_16U: return 16;
	case CV_16S: return 16;
	case CV_32S: return 32;
	case CV_32F: return 32;
	case CV_64F: return 64;
	default:     return -1;
	}
}


}
#endif /* _config_h */
