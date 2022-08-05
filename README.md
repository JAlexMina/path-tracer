README for PathTracer

----------------------------------------------------------------------
Usage
----------------------------------------------------------------------
You run it from QT Creator, passing in 
	[1] scene filename, 
	[2] an output filename,



Pathtracing:
------
My path tracer outputs its resulting image to a png as the support code allows as well as it renders it to its own window in real time. I was planning on using gpu multithreading to speed this process up so that it might run in a decent time updating the current image with more samples if the camera has not moved however I did not get to implementing that. 

My path tracer handles diffuse lighting and some specular however it is very buggy and needs a lot more work to be
considered complete.



----------------------------------------------------------------------
Rendered Images
----------------------------------------------------------------------


<img src="./Rendered Images/output500S.PNG"
     alt="Original with 500 samples">


<img src="./Rendered Images/capturee2.PNG"
     alt="">