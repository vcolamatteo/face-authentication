# face-authentication

Welcome Sir/Madame and thanks to be here!
<br /><br /><br /><br />
<div algn="justfy">This is a <b>complete</b> face-authentication system.  
I developed it during my <a href="http://vcolamatteo.altervista.org/Resources/Tesi_Ing_VALERIO_COLAMATTEO_Sistema_di_FaceAuthentication_basato_su_Local__quantized_Pattern.pdf" target="_blank">degree-thesis</a> (italian language) in Computer Engineering. <br/>It is entrely written in <b>C++</b>. <br/>
<u>The whole computative process mainly consists of the following functional modules:</div></u>   
<br /><br />
<ul tye="disc">
<li><b>face-tracking</b></li> 
OpenCV classifier + template matching technique for angled head-posture detection
<br /><br />
<li><b>eyes-tracking</b></li> 
for face-cropping (missing a complete face landamaks detection system...) and geometric normalization  
(a planar face rotation to normalize user's head-posture)  
<br /><br />
<li><b>brightness-normalization</b></li>  
For reducing environment lihtondition variabilitythe system works with just a RGB webcam) 
<br /><br />
<li><b>face-antispoofing</b></li>  
Multiresolution/Multiscale LBP and SVM with radial filter classification.   
The system is able to work without any kind of liveness-detection, so it doesn't need user cooperation and it's
absolutely transparent for user.  
<br /><br />
<li><b>features extraction</b></li> 
The features-extraction module is based on the Local Quantized Pattern methodology (LQP), with vector
quantization (clustering) performed with k-means algorithm (scratch programmed).  
</ul>
<br /><br />
Wndows/Linux OS compatibility. Third party library involved: <b>OpenCV</b> 2.4.9, <b>Qt</b> 5.1. <br />
More info at: <a href="http://www.vcolamatteo.com/computervision" target="_blank">vcolamatteo/computervision</a>
