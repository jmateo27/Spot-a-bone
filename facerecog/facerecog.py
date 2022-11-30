import os
from os import listdir

import string
import time

import threading

import cv2
import face_recognition


class myThreads:
    def __init__(self):
        self.isStart = False
        self.commandfile = "analyzeFace.txt"
        self.namefile = "name.txt"

        # Initialize image encodings
        self.photos_dir = 'stock'
        self.sample_dir = 'samples'
            # change later for the actual program
        self.photos = []
        self.names = []
        self.imgs = []
        self.rgb_imgs = []
        self.img_mapping = []

        for p in os.listdir(self.photos_dir):
            if (p.endswith('.jpg')):
                self.photos.append(p)
                self.names.append(p.replace('.jpg', ''))

        photo_threads = []
        for ph in self.photos:
            thr = threading.Thread(target = self.img_encoding_thread, 
                                   args = (ph),
                                   kwargs = {"img_map": img_mapping})
            photo_threads.append(thr)

        for thr in photo_threads:
            thr.join()
        
        print("starting threads")
        self.start_threads() # starts splitting the program into respective threads

    def img_encoding_thread(self, photo, img_map = None):
        img = cv2.imread(self.photos_dir + '/' + photo)
        rgb_img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
        img_encoding = face_recognition.face_encodings(rgb_img)[0]
        img_map.append((img_encoding, photo.replace('.jpg', '')))

    def start_threads(self):
        wait_for_command_thread = threading.Thread(target = self.wait_for_command)
        analyze_photo_thread = threading.Thread(target = self.analyze_photo)
        wait_for_command_thread.start()
        analyze_photo_thread.start()

    def wait_for_command(self):
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
            for p in os.listdir(self.sample_dir):
                if (p.endswith('.jpg')):
                    samples.append(p)

            imgSample = cv2.imread(self.sample_dir + '/' + samples[0])
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

            if (len(names) == 0):
                print("No matches")

            print("printing name now")
            # now put name
            f = open(self.namefile, "w")
            f.write(names[0] + '\n')
            f.close()
            
            self.isStart = False
            # should delete the photo from the samples folder, do later

    def distinguish_face(self, imgSample_encoding, face, name, my_list = None):
        result = face_recognition.compare_faces([imgSample_encoding], face)
        print("done analyzing one")
        if (result == [True]):
            my_list.append(name)
        return
# Now img_mapping is initialized, wait for command from c program to analyze.

def main():
    myclass = myThreads() # starts program


if __name__ == "__main__":
    main()