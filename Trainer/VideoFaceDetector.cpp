#include "VideoFaceDetector.h"

using namespace std;

const double VideoFaceDetector::TICK_FREQUENCY = cv::getTickFrequency();

VideoFaceDetector::VideoFaceDetector(const std::string cascadeFilePath, cv::VideoCapture &videoCapture)
{
	setFaceCascade(cascadeFilePath);
	setVideoCapture(videoCapture);
}

void VideoFaceDetector::setVideoCapture(cv::VideoCapture &videoCapture)
{
	m_videoCapture = &videoCapture;
}

cv::VideoCapture *VideoFaceDetector::videoCapture() const
{
	return m_videoCapture;
}

void VideoFaceDetector::setFaceCascade(const std::string cascadeFilePath)
{
	if (m_faceCascade == NULL) {
		m_faceCascade = new cv::CascadeClassifier(cascadeFilePath);
	}
	else {
		m_faceCascade->load(cascadeFilePath);
	}

	if (m_faceCascade->empty()) {
		std::cerr << "Error creating cascade classifier. Make sure the file" << std::endl
			<< cascadeFilePath << " exists." << std::endl;
	}
}

cv::CascadeClassifier *VideoFaceDetector::faceCascade() const
{
	return m_faceCascade;
}



void VideoFaceDetector::setResizedWidth(const int width)
{
	m_resizedWidth = std::max(width, 1);
}

int VideoFaceDetector::resizedWidth() const
{
	return m_resizedWidth;
}

cv::Rect VideoFaceDetector::face() const
{
	cv::Rect faceRect;
	if (m_facePosition != Point(0, 0)) {
		faceRect = m_trackedFace;
		faceRect.x = (int)(faceRect.x / m_scale);
		faceRect.y = (int)(faceRect.y / m_scale);
		faceRect.width = (int)(faceRect.width / m_scale);
		faceRect.height = (int)(faceRect.height / m_scale);
	}

	return faceRect;
}

cv::Point VideoFaceDetector::facePosition() const
{
	cv::Point facePos;
	facePos.x = (int)(m_facePosition.x / m_scale);
	facePos.y = (int)(m_facePosition.y / m_scale);
	return facePos;
}

void VideoFaceDetector::setTemplateMatchingMaxDuration(const double s)
{
	m_templateMatchingMaxDuration = s;
}

double VideoFaceDetector::templateMatchingMaxDuration() const
{
	return m_templateMatchingMaxDuration;
}

/*VideoFaceDetector::~VideoFaceDetector()
{
if (m_faceCascade != NULL) {
delete m_faceCascade;
}
}
*/
cv::Rect VideoFaceDetector::doubleRectSize(const cv::Rect &inputRect, const cv::Rect &frameSize) const
{
	cv::Rect outputRect;
	// creo un Double-rect centrato sul rect originale
	outputRect.width = inputRect.width * 2;
	outputRect.height = inputRect.height * 2;

	// mi sposto nel vertice in alto a sx del rect double
	outputRect.x = inputRect.x - inputRect.width / 2;
	outputRect.y = inputRect.y - inputRect.height / 2;

	// casi limite...
	if (outputRect.x < frameSize.x) {  // <0
		outputRect.width += outputRect.x;
		outputRect.x = frameSize.x;
	}
	if (outputRect.y < frameSize.y) {
		outputRect.height += outputRect.y;
		outputRect.y = frameSize.y;
	}

	/*
	*  nei primi 2 casi si fa in modo che, nel caso in cui la faccia identificata sia tutta sul lato del frame
	*  (cioè con coordinate su x o y prossime a zero), nella costruzione del double-rect si vada oltre il frame
	*/

	/*
	*  negli altri 2 casi invece si evitano le situazioni speculari alle prime 2, ossia che, nel caso in cui la
	*  faccia identificata sia tutta sul lato del frame
	*  (cioè con coordinate su x o y prossime a zero), nella costruzione del double-rect si vada oltre il frame
	*/

	//cout << outputRect.x + outputRect.width <<"frame  "<< frameSize.width<< endl;

	if (outputRect.x + outputRect.width > frameSize.width) {
		outputRect.width = frameSize.width - outputRect.x;
	}
	if (outputRect.y + outputRect.height > frameSize.height) {
		outputRect.height = frameSize.height - outputRect.y;
	}

	return outputRect;
}

cv::Point VideoFaceDetector::centerOfRect(const cv::Rect &rect) const
{
	return cv::Point(rect.x + rect.width / 2, rect.y + rect.height / 2);
}

cv::Rect VideoFaceDetector::biggestFace(std::vector<cv::Rect> &faces) const
{
	assert(!faces.empty());

	cv::Rect *biggest = &faces[0];
	for (auto &face : faces) {
		if (face.area() < biggest->area())
			biggest = &face;
	}
	return *biggest;
}

/*
* Calcola una ROI nel riquadro centrale del viso eliminando il 25% dei dati
*/
cv::Mat VideoFaceDetector::getFaceTemplate(const cv::Mat &frame, cv::Rect face)
{
	face.x += face.width / 4;
	face.y += face.height / 4;
	face.width /= 2;
	face.height /= 2;

	cv::Mat faceTemplate = frame(face).clone();
	return faceTemplate;
}

void VideoFaceDetector::detectFaceAllSizes(const cv::Mat &frame)
{
	// Minimum face size is 1/5th of screen height
	// Maximum face size is 2/3rds of screen height
	//m_faceCascade->detectMultiScale(frame, m_allFaces, 1.1, 3, 0, cv::Size(frame.rows / 5, frame.rows / 5), cv::Size(frame.rows * 2 / 3, frame.rows * 2 / 3));
	//m_faceCascade->detectMultiScale(frame, m_allFaces, 1.1, 2, 0, cv::Size(frame.rows / 5, frame.rows / 5), cv::Size(frame.rows * 2 / 3, frame.rows * 2 / 3));
	m_faceCascade->detectMultiScale(frame, m_allFaces, 1.1, 10, 0), cv::Size(frame.rows / 5, frame.rows / 5), cv::Size(frame.rows * 2 / 3, frame.rows * 2 / 3);
	if (m_allFaces.empty()) { m_facePosition = cv::Point(0, 0); return; }

	m_foundFace = true;

	// Locate biggest face
	m_trackedFace = biggestFace(m_allFaces);
	// Copy face template
	m_faceTemplate = getFaceTemplate(frame, m_trackedFace);
	//imshow("", m_faceTemplate);cvWaitKey(0);
	// Calculate roi
	m_faceRoi = doubleRectSize(m_trackedFace, cv::Rect(0, 0, frame.cols, frame.rows));

	// Update face position
	m_facePosition = centerOfRect(m_trackedFace);

}

void VideoFaceDetector::detectFaceAroundRoi(const cv::Mat &frame)
{
	// Detect faces sized +/-20% off biggest face in previous search
	/*m_faceCascade->detectMultiScale(frame(m_faceRoi), m_allFaces, 1.2, 2, 0,
	cv::Size(m_trackedFace.width * 5 / 10, m_trackedFace.height * 5 / 10),
	cv::Size(m_trackedFace.width * 15 / 10, m_trackedFace.width * 15 / 10));*/
	m_faceCascade->detectMultiScale(frame(m_faceRoi), m_allFaces, 1.2, 5, 0,
		cv::Size(m_trackedFace.width * 6 / 10, m_trackedFace.height * 6 / 10),
		cv::Size(m_trackedFace.width * 14 / 10, m_trackedFace.width * 14 / 10));

	if (m_allFaces.empty())
	{
		// Activate template matching if not already started and start timer
		m_templateMatchingRunning = true;
		if (m_templateMatchingStartTime == 0)
			m_templateMatchingStartTime = cv::getTickCount();
		return;
	}

	// Turn off template matching if running and reset timer
	m_templateMatchingRunning = false;
	m_templateMatchingCurrentTime = m_templateMatchingStartTime = 0;

	// Get detected face
	m_trackedFace = biggestFace(m_allFaces);

	// Add roi offset to face
	m_trackedFace.x += m_faceRoi.x;
	m_trackedFace.y += m_faceRoi.y;

	// Get face template
	m_faceTemplate = getFaceTemplate(frame, m_trackedFace);

	// Calculate roi
	m_faceRoi = doubleRectSize(m_trackedFace, cv::Rect(0, 0, frame.cols, frame.rows));

	// Update face position
	m_facePosition = centerOfRect(m_trackedFace);
}

void VideoFaceDetector::detectFacesTemplateMatching(const cv::Mat &frame)
{
	// Calculate duration of template matching
	m_templateMatchingCurrentTime = cv::getTickCount();
	double duration = (double)(m_templateMatchingCurrentTime - m_templateMatchingStartTime) / TICK_FREQUENCY;

	// If template matching lasts for more than 2 seconds face is possibly lost
	// so disable it and redetect using cascades
	if (duration > m_templateMatchingMaxDuration) {
		m_foundFace = false;
		m_templateMatchingRunning = false;
		m_templateMatchingStartTime = m_templateMatchingCurrentTime = 0;
		//cout << "TIME" << endl;
		//	m_templateMatchingMaxDuration = 10;
	}

	// Template matching with last known face 
	//cv::matchTemplate(frame(m_faceRoi), m_faceTemplate, m_matchingResult, CV_TM_CCOEFF);
	cv::matchTemplate(frame(m_faceRoi), m_faceTemplate, m_matchingResult, CV_TM_SQDIFF);
	//cv::normalize(m_matchingResult, m_matchingResult, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());
	//cout << "m_faceRoi:  "<< m_faceRoi<<"   matchingResult:  " << m_matchingResult.size() << endl;
	//imshow("", m_matchingResult); //cvWaitKey(0);
	double min, max;
	cv::Point minLoc, maxLoc;
	cv::minMaxLoc(m_matchingResult, &min, &max, &minLoc, &maxLoc);
	//cout << (min) << endl;

	/*if (abs(max) > 10.0e-9 && min != 0) {
	cout << "HERE" << endl << endl << endl << endl << endl;
	m_templateMatchingMaxDuration = 0;
	reset = 1;
	}*/
	// Add roi offset to face position
	minLoc.x += m_faceRoi.x;
	minLoc.y += m_faceRoi.y;

	// Get detected face
	//m_trackedFace = cv::Rect(maxLoc.x, maxLoc.y, m_trackedFace.width, m_trackedFace.height);
	m_trackedFace = cv::Rect(minLoc.x, minLoc.y, m_faceTemplate.cols, m_faceTemplate.rows);
	m_trackedFace = doubleRectSize(m_trackedFace, cv::Rect(0, 0, frame.cols, frame.rows));

	// Get new face template
	m_faceTemplate = getFaceTemplate(frame, m_trackedFace);
	//cout << "template_size:  " << m_faceTemplate.size() << endl;
	//imshow("template", m_faceTemplate); cvWaitKey(0);
	// Calculate face roi
	m_faceRoi = doubleRectSize(m_trackedFace, cv::Rect(0, 0, frame.cols, frame.rows));
	//cout << m_faceRoi << endl;
	//if (m_faceRoi.width/m_faceRoi.height > 1.3 || m_faceRoi.width / m_faceRoi.height < 0.733 || m_faceRoi.height<120) {
	if (m_faceRoi.width / m_faceRoi.height > 1.25 || m_faceRoi.width / m_faceRoi.height < 0.633 || m_faceRoi.height < 120) {
		//cout << "HERE    " << (float)m_faceRoi.width/(float)m_faceRoi.height <<"  "<<m_faceRoi.width<<"  "<< m_faceRoi.height<<"   "<< m_faceRoi.height<<endl << endl << endl << endl << endl;
		m_templateMatchingMaxDuration = 0;
		//reset = 1;
		if (duration > m_templateMatchingMaxDuration) {
			m_foundFace = false;
			m_templateMatchingRunning = false;
			m_templateMatchingStartTime = m_templateMatchingCurrentTime = 0;
			//cout << "TIME____2" << endl;
			m_templateMatchingMaxDuration = 10;
		}
	}
	// Update face position
	m_facePosition = centerOfRect(m_trackedFace);


}

cv::Point VideoFaceDetector::getFrameAndDetect(cv::Mat &frame)
{
	//*m_videoCapture >> frame;
	//cv::flip(frame, frame, 1);
	// se metto il system("pause") blocca fotogramma x fotogramma
	//cv::imshow("*m_videoCapture",frame);
	//system("pause");

	// Downscale frame to m_resizedWidth width - keep aspect ratio
	//cout << "cols   " << frame.cols << endl;  
	//m_scale = (double)std::min(m_resizedWidth, frame.cols) / frame.cols;  // le colonne sono sempre 640 xkè il frame della webcam è 640x480
	//cout<<"m scale   "<<m_scale<<endl;  // 0.5 sempre
	m_scale = 0.35;
	cv::Size resizedFrameSize = cv::Size((int)(m_scale*frame.cols), (int)(m_scale*frame.rows));
	//cout << "resizedFrameSize   " << resizedFrameSize << endl;  // sempre 320X240
	//system("pause");

	cv::Mat resizedFrame;
	cv::resize(frame, resizedFrame, resizedFrameSize);
	//cv::imshow("frame resized", resizedFrame);
	//imwrite("C:\\Users\\Valerio\\Desktop\\Face-rec\\Images\\Allegati_2016310\\frame.jpg", frame);
	//system("pause");


	if (!m_foundFace)
		detectFaceAllSizes(resizedFrame); // Detect using cascades over whole image  (solo se m_foundface==false)
	else {
		detectFaceAroundRoi(resizedFrame); // Detect using cascades only in ROI
		if (m_templateMatchingRunning) {
			detectFacesTemplateMatching(resizedFrame); // Detect using template matching
		}
	}

	return m_facePosition;
}


bool VideoFaceDetector::isFaceFound() const {


	return m_foundFace;


}

void VideoFaceDetector::SecureVideoCapt(cv::Mat &frame) {

	while (frame.empty()) {
		*m_videoCapture >> frame;

	}

	*m_videoCapture >> frame;

}

void VideoFaceDetector::VideoCapt(cv::Mat &frame) {


	*m_videoCapture >> frame;

}