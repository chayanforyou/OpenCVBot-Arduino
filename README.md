## Object Tracking Robot
Here is the demonstration of object tracking robot with Android an Arduino microntroller. I have written an Arduino and Android libraries to allow an Android device to control the robot through Bluetooth. The robot is designed to track objects by spinning left and right to keep the object in sight and driving forward and backward to maintain a constant distance between the robot and the object. Images are acquired through the camera of an Android device which is attached to the robot. The camera is attached to servos on the robot which allow the camera to pan and tilt. Several image processing techniques are used to detect the location of the object being tracked in the images. The Android applicaton actually uses color based tracking methods. The Application is developed using OpenCV library to help with the image processing.

__Demo Video:__ https://www.youtube.com/watch?v=pk7tU3--Ypw

__APP Link:__ https://www.dropbox.com/s/wclwrjw18qjvdcm/OpenCV%20Bot%20V1.2.apk?dl=0
