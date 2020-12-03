import tkinter
import cv2
import PIL.Image, PIL.ImageTk
import time
import threading
import guimaking
import MainAnalysis

class App:
    def __init__(self, window, window_title, video_source1=0, video_source2=2, video_source3=4):
        self.window = window
        self.window.title(window_title)
        self.video_source1 = video_source1
        self.video_source2 = video_source2
        self.video_source3 = video_source3
        self.window.grid()
        
        
        self.analysisframe = tkinter.Toplevel()
        self.analysisframe.title('analysis')
        self.analysisframe.grid()
        self.cubename = 1
        self.analysiswindow = guimaking.AnalysisWindow(self.analysisframe)



        
        # open video source (by default this will try to open the computer webcam)
        self.vid1 = MyVideoCapture(self.video_source1)
        self.vid2 = MyVideoCapture(self.video_source2)
        self.vid3 = MyVideoCapture(self.video_source3)
        
        self.frame = tkinter.Frame(window, width = self.vid1.width, height = self.vid1.height, relief='groove')
        self.frame.pack() 
        # Create a canvas that can fit the above video source size
        self.canvas1 = tkinter.Canvas(self.frame, width = self.vid1.width//2, height = self.vid1.height//2)
        self.canvas2 = tkinter.Canvas(self.frame, width = self.vid2.width//2, height = self.vid2.height//2)
        self.canvas3 = tkinter.Canvas(self.frame, width = self.vid3.width//2, height = self.vid3.height//2)
        self.canvas1.grid(row=0, column=0)
        self.canvas2.grid(row=0, column=1)
        self.canvas3.grid(row=1, column=0)
        print('(width,height)=({},{})'.format(self.vid1.width, self.vid1.height))



        # Button that lets the user take a snapshot
        #self.btn_snapshot1=tkinter.Button(self.frame, text="Snapshot1", width=50, command=self.snapshot1)
        self.btn_snapshot1=tkinter.Button(self.frame, text="Snapshot1", width=50, command=self.Thread_snapshot1)
        self.btn_snapshot1.grid(row=2, column=0)
        self.btn_snapshot2=tkinter.Button(self.frame, text="Snapshot2", width=50, command=self.snapshot2)
        self.btn_snapshot2.grid(row=2, column=1)
        self.btn_snapshot2.configure(state='disabled')
        # After it is called once, the update method will be automatically called every delay milliseconds
        self.delay = 10
        self.update()

        self.window.mainloop()

    def Thread_snapshot1(self):
        print('called Thread_snapshot1')
        mainThread1 = threading.Thread(target = self.snapshot1)
        mainThread1.start()
        mainThread1.join() 
    def snapshot1(self):
        print('called snapshot1')
        self.btn_snapshot1.configure(state='disabled')
        
        # Get a frame from the video source
        ret, frame1 = self.vid1.get_frame()
        ret, frame2 = self.vid2.get_frame()
        ret, frame3 = self.vid3.get_frame()

        if ret:
            cv2.imwrite("mao_pictures/pic0213/cube"+str(self.cubename)+"1.jpg", cv2.cvtColor(frame1, cv2.COLOR_RGB2BGR))
            cv2.imwrite("mao_pictures/pic0213/cube"+str(self.cubename)+"2.jpg", cv2.cvtColor(frame2, cv2.COLOR_RGB2BGR))
            cv2.imwrite("mao_pictures/pic0213/cube"+str(self.cubename)+"3.jpg", cv2.cvtColor(frame3, cv2.COLOR_RGB2BGR))
        
        self.analysiswindow.SetCubename(self.cubename)
        self.cubedata1 = MainAnalysis.ANALYSIS(self.cubename, 1)
        self.cubedata2 = MainAnalysis.ANALYSIS(self.cubename, 2)
        self.cubedata3 = MainAnalysis.ANALYSIS(self.cubename, 3)
       # thread1 = threading.Thread(target=MainAnalysis.ANALYSIS, args=[self.cubename, 1])
       # self.cubedata1 = thread1.start()
       # thread2 = threading.Thread(target=MainAnalysis.ANALYSIS, args=[self.cubename, 2])
       # self.cubedata2 = thread2.start()
       # thread3 = threading.Thread(target=MainAnalysis.ANALYSIS, args=[self.cubename, 3])
       # self.cubedata3 = thread3.start()


       # thread1.join()
       # thread2.join()
       # thread3.join()
        print('cubedata1:{}'.format(self.cubedata1)) 
        self.analysiswindow.takeim1(self.cubedata1, self.cubedata2, self.cubedata3)
        self.btn_snapshot2.configure(state='normal')



    def snapshot2(self):

        self.btn_snapshot1.configure(state='normal')
        self.btn_snapshot2.configure(state='disabled')
        # Get a frame from the video source
        ret, frame1 = self.vid1.get_frame()
        ret, frame2 = self.vid2.get_frame()
        ret, frame3 = self.vid3.get_frame()

        if ret:
            cv2.imwrite("mao_pictures/pic0213/cube"+str(self.cubename)+"4.jpg", cv2.cvtColor(frame1, cv2.COLOR_RGB2BGR))
            cv2.imwrite("mao_pictures/pic0213/cube"+str(self.cubename)+"5.jpg", cv2.cvtColor(frame2, cv2.COLOR_RGB2BGR))
            cv2.imwrite("mao_pictures/pic0213/cube"+str(self.cubename)+"6.jpg", cv2.cvtColor(frame3, cv2.COLOR_RGB2BGR))

        self.cubedata4 = MainAnalysis.ANALYSIS(self.cubename, 4)
        self.cubedata5 = MainAnalysis.ANALYSIS(self.cubename, 5)
        self.cubedata6 = MainAnalysis.ANALYSIS(self.cubename, 6) 
        self.analysiswindow.takeim2(self.cubedata4, self.cubedata5, self.cubedata6)
        self.cubename += 1
    
    


    def update(self):
        # Get a frame from the video source
        ret, frame1 = self.vid1.get_frame()
        ret, frame2 = self.vid2.get_frame()
        ret, frame3 = self.vid3.get_frame()

        if ret:
            full1image = PIL.Image.fromarray(frame1)
            half1image = full1image.resize((int(self.vid1.width/2), int(self.vid1.height/2)))
            self.photo1half = PIL.ImageTk.PhotoImage(image = half1image)
            self.canvas1.create_image(0, 0, image = self.photo1half, anchor = tkinter.NW)

            full2image = PIL.Image.fromarray(frame2)
            half2image = full2image.resize((int(self.vid2.width/2), int(self.vid2.height/2)))
            self.photo2half = PIL.ImageTk.PhotoImage(image = half2image)
            self.canvas2.create_image(0, 0, image = self.photo2half, anchor = tkinter.NW)

            full3image = PIL.Image.fromarray(frame3)
            half3image = full3image.resize((int(self.vid3.width/2), int(self.vid3.height/2)))
            self.photo3half = PIL.ImageTk.PhotoImage(image = half3image)
            self.canvas3.create_image(0, 0, image = self.photo3half, anchor = tkinter.NW)

        self.window.after(self.delay, self.update)


class MyVideoCapture:
    def __init__(self, video_source):
        # Open the video source
        self.vid = cv2.VideoCapture(video_source)
        if not self.vid.isOpened():
            raise ValueError("Unable to open video source", video_source)

        # Get video source width and height
        self.width = self.vid.get(cv2.CAP_PROP_FRAME_WIDTH)
        self.height = self.vid.get(cv2.CAP_PROP_FRAME_HEIGHT)

    def get_frame(self):
        if self.vid.isOpened():
            ret, frame = self.vid.read()
            if ret:
                # Return a boolean success flag and the current frame converted to BGR
                return (ret, cv2.cvtColor(frame, cv2.COLOR_BGR2RGB))
            else:
                return (ret, None)
        else:
            return (ret, None)

    # Release the video source when the object is destroyed
    def __del__(self):
        if self.vid.isOpened():
            self.vid.release()

#class MyThread(threading.Thread):
#    def __init__(self, )



# Create a window and pass it to the Application object
App(tkinter.Tk(), "Tkinter and OpenCV")
