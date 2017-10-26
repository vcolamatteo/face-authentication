# face-authentication

Welcome Sir/Madame and thanks to be here!
<br /><br /><br /><br />
<div algn="justfy">This is a <b>complete</b> face-authentication system.  
I developed it during my <a href="http://vcolamatteo.altervista.org/Resources/Tesi_Ing_VALERIO_COLAMATTEO_Sistema_di_FaceAuthentication_basato_su_Local__quantized_Pattern.pdf" target="_blank">degree-thesis</a> (italian language) in Computer Engineering. <br/>It is entrely written in <b>C++</b>. <br/>
<u>The whole computative process mainly consists of the following functional modules:</div></u>   
<br /><br />
<ul tye="disc">
<li><b>face-tracking</b></li> 
OpenCV classifier + template matching technique for angled head-posture detection and a continuos <a href="https://youtu.be/-6J7EZnBn6g" target="_blank"><b>tracking</b> without any visual freeze.   
<br /><br />
<li><b>eyes-tracking</b></li> 
for face-cropping (missing a complete face landamaks detection system...) and geometric normalization  
(a planar face rotation to <a href="https://youtu.be/recchADslj0" target="_blank"><b>normalize</b> user's head-posture)  
<br /><br />
<li><b>brightness-normalization</b></li>  
For reducing environment light condition variability (the system works with just a RGB webcam) 
<br /><br />
<li><b>face-antispoofing</b></li>  
Multiresolution/Multiscale LBP and SVM with radial filter classification.   
  <a href="https://youtu.be/3VS_uQKb4CA" target="_blank"><b>The system</b></a> is able to work without any kind of liveness-detection, so it doesn't need user cooperation and it's
absolutely transparent for user.  
<br /><br />
<li><b>features-extraction</b></li> 
The features-extraction module is based on the Local Quantized Pattern methodology (LQP), with vector
quantization (clustering) performed with k-means algorithm (scratch programmed).  
</ul>
<br /><br />
<b>The system is provided of a GUI for helping user during the <a href="https://www.youtube.com/embed/4Z74uxv9TAk?list=PLxvtf3ll_ZIinQVWEgSNQxxXJ2YkeD99a" target="_blank">enollment</a> and the <a href="https://www.youtube.com/embed/bRkwsEhyvvI?list=PLxvtf3ll_ZIinQVWEgSNQxxXJ2YkeD99a" target="_blank">classification</a> phases of the authentication process. </b><br /><br />
<br /><br />
Windows/Linux OS compatibility. Third party library involved: <b>OpenCV</b> 2.4.9, <b>Qt</b> 5.1. <br />
System divided in a <b>Trainer</b> application and a <b>Recognizer</b> application.<br />
More info at: <a href="http://www.vcolamatteo.com/computervision" target="_blank">vcolamatteo/computervision</a>.<br />
For any info request email me at: v.colamatteo@yahoo.it
