import os
from os import listdir

import string
import time
import datetime

import threading

import cv2
import face_recognition
import getpass


class myThreads:
    def __init__(self):
        self.isStart = False
        username = getpass.getuser()        
        username = "/home/"+username
        self.commandfile = username + "/cmpt433/public/myApps/spotabone/comms/camera.txt"
        self.namefile = username + "/cmpt433/public/myApps/spotabone/comms/NFC.txt"

        # Initialize image encodings
        self.photos_dir = username + "/cmpt433/public/myApps/spotabone/stock"
        self.sample_dir = username + "/cmpt433/public/myApps/spotabone/photos"
        self.img_mapping = []

        print("Starting to initialize face recognition")
        start_time = datetime.datetime.now()

        for p in os.listdir(self.photos_dir):
            if (p.endswith('.jpg') or p.endswith('.ppm')):
                img = cv2.imread(self.photos_dir + '/' + p)
                rgb_img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
                img_encoding = face_recognition.face_encodings(rgb_img)[0]
                name = p.replace('.jpg', '').replace('.ppm', '')
                print(name)
                self.img_mapping.append( (img_encoding, name) )
        
        total_time = datetime.datetime.now() - start_time
        print(total_time.total_seconds() , "seconds to complete initialization")
        
        self.start_threads()

    def start_threads(self):
        wait_for_command_thread = threading.Thread(target = self.wait_for_command)
        analyze_photo_thread = threading.Thread(target = self.analyze_photo)
        wait_for_command_thread.start()
        analyze_photo_thread.start()

    def wait_for_command(self):
        print("Ready for a command")
        while(1):
            if (self.isStart):
                time.sleep(0.25)
                continue
            f = open(self.commandfile, "r")
            try:
                line = f.readline()
                if(line):
                    self.isStart = True
            finally:
                f.close()
            open(self.commandfile,"w").close()

    def analyze_photo(self):
        samples = []
        while(1):
            if (not self.isStart):
                time.sleep(0.25)
                continue
            # start analyzing what is in the samples folder
            print("Starting to analyze...")
            start_time = datetime.datetime.now()

            for p in os.listdir(self.sample_dir):
                if (p.endswith('.jpg') or p.endswith('.ppm')):
                    samples.append(p)

            if (len(samples) == 0):
                print("Error: No valid input photos")
                self.isStart = False
                continue

            imgSample = cv2.imread(self.sample_dir + '/' + samples[0])
            if (len(imgSample) == 0):
                print("Error with the input photo")
                return
            rgb_imgSample = cv2.cvtColor(imgSample, cv2.COLOR_BGR2RGB)
            imgSample_encoding = face_recognition.face_encodings(rgb_imgSample)[0]

            recog_threads = []
            names = []
            for (face, name) in self.img_mapping:
                # distinguish_face(self, imgSample_encoding, face, name)
                thread = threading.Thread(target = self.distinguish_face, 
                                          args = (imgSample_encoding, face, name),
                                          kwargs = {"my_list": names})
                recog_threads.append(thread)
                thread.start()

            for th in recog_threads:
                th.join()

            total_time = datetime.datetime.now() - start_time
            print(total_time.total_seconds(), "seconds to analyze photo")
            if (len(names) == 0):
                print("No matches")
            else:
                print(names[0])
                f = open(self.namefile, "w")
                f.write(names[0] + '\n')
                f.close()
            
            self.isStart = False
            samples = []
            print("Ready for a command")
            # should delete the photo from the samples folder, do later

    def distinguish_face(self, imgSample_encoding, face, name, my_list = None):
        result = face_recognition.compare_faces([imgSample_encoding], face)
        if (result == [True]):
            my_list.append(name)
        return
# Now img_mapping is initialized, wait for command from c program to analyze.

def main():
    myclass = myThreads() # starts program


if __name__ == "__main__":
    main()