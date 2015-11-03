Somatopia
=========

A set of four interactions for the Raspberry Pi computer

Controls:

'd': Display Debug frames

's': return to splash screen

'v': toggle video display on and off

Addons required:

ofxOpenCV: included in oF by default

ofxStateMachine (use my fork!): https://github.com/Bentleyj/ofxStateMachine

ofxCV: https://github.com/kylemcdonald/ofxCv

ofxJSON: https://github.com/jefftimesten/ofxJSON

ofxCvPiCam: https://github.com/orgicus/ofxCvPiCam

Ensure ofxCvPiCam is listed in the addons.make file.

Also you'll possibly need to download the newest .a files to compile openCV stuff. Download the files from here: http://files.fieldofview.com/temp/ofxopencv_armv7_libs.tar.gz and place the file extracted into the following location: 

addons/ofxOpenCv/libs/opencv/lib/linuxarmv7l/
