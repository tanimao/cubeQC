import sys 
import tkinter

class AnalysisWindow:
        
    def __init__(self, root):  
        self.root = root
        self.frame = tkinter.Frame(
            root,
            height=400,
            width=500,
            relief='ridge',
            borderwidth=15
        )
        self.frame.grid()
        #################
        self.kaiseki_f1 = tkinter.LabelFrame(self.frame,text='解析結果:1面',foreground='blue', relief='raised')
        self.kaiseki_f1.grid(row=7,column=0,columnspan=2)
        self.kaiseki_f2 = tkinter.LabelFrame(self.frame,text='解析結果:2面',foreground='blue')
        self.kaiseki_f2.grid(row=7,column=2,columnspan=2)
        self.kaiseki_f3 = tkinter.LabelFrame(self.frame,text='解析結果:3面',foreground='blue')
        self.kaiseki_f3.grid(row=7,column=4,columnspan=2)
        
        
        self.kaiseki_f4 = tkinter.LabelFrame(self.frame,text='解析結果:4面',foreground='blue')
        self.kaiseki_f4.grid(row=8,column=0,columnspan=2)
        self.kaiseki_f5 = tkinter.LabelFrame(self.frame,text='解析結果:5面',foreground='blue')
        self.kaiseki_f5.grid(row=8,column=2,columnspan=2)
        self.kaiseki_f6 = tkinter.LabelFrame(self.frame,text='解析結果:6面',foreground='blue')
        self.kaiseki_f6.grid(row=8,column=4,columnspan=2)
        ########撮影ボタン、画像名出力#############
        self.dumpdata1=[0,0,0,0,0,0]
       
        self.text1=tkinter.StringVar()
        self.text2=tkinter.StringVar() 
        self.text3=tkinter.StringVar() 
        self.text4=tkinter.StringVar() 
        self.text5=tkinter.StringVar() 
        self.text6=tkinter.StringVar() 
        self.imagelabel1=tkinter.Label(self.frame, textvariable=self.text1, width=10, height=1, background='yellow', relief='ridge')
        self.imagelabel2=tkinter.Label(self.frame, textvariable=self.text2, width=10, height=1, background='yellow', relief='ridge')
        self.imagelabel3=tkinter.Label(self.frame, textvariable=self.text3, width=10, height=1, background='yellow', relief='ridge')
        self.imagelabel4=tkinter.Label(self.frame, textvariable=self.text4, width=10, height=1, background='yellow', relief='ridge')
        self.imagelabel5=tkinter.Label(self.frame, textvariable=self.text5, width=10, height=1, background='yellow', relief='ridge')
        self.imagelabel6=tkinter.Label(self.frame, textvariable=self.text6, width=10, height=1, background='yellow', relief='ridge')

        self.imagelabel1.grid(row=4,column=0)
        self.imagelabel2.grid(row=5,column=0)
        self.imagelabel3.grid(row=6,column=0)
        self.imagelabel4.grid(row=4,column=1)
        self.imagelabel5.grid(row=5,column=1)
        self.imagelabel6.grid(row=6,column=1)

        self.text1s=tkinter.StringVar()
        self.text1b=tkinter.StringVar()
        self.text1h=tkinter.StringVar()
        self.text1E=tkinter.StringVar()
        self.text1r=tkinter.StringVar()

        self.sizeLabel1 = tkinter.Label(self.kaiseki_f1, width=15, height=1, textvariable=self.text1s)
        self.bumpLabel1 = tkinter.Label(self.kaiseki_f1, width=15, height=1, textvariable=self.text1b)
        self.holeLabel1 = tkinter.Label(self.kaiseki_f1, width=15, height=1, textvariable=self.text1h)
        self.EminLabel1 = tkinter.Label(self.kaiseki_f1, width=15, height=1, textvariable=self.text1E)
        self.radiLabel1 = tkinter.Label(self.kaiseki_f1, width=15, height=1, textvariable=self.text1r)

        self.sizeLabel1.grid(row=0,column=0)
        self.bumpLabel1.grid(row=0,column=1)
        self.holeLabel1.grid(row=1,column=0)
        self.EminLabel1.grid(row=1,column=1)
        self.radiLabel1.grid(row=2,column=1)


        self.text2s=tkinter.StringVar()
        self.text2b=tkinter.StringVar()
        self.text2h=tkinter.StringVar()
        self.text2E=tkinter.StringVar()
        self.text2r=tkinter.StringVar()

        self.sizeLabel2 = tkinter.Label(self.kaiseki_f2, width=15, height=1, textvariable=self.text2s)
        self.bumpLabel2 = tkinter.Label(self.kaiseki_f2, width=15, height=1, textvariable=self.text2b)
        self.holeLabel2 = tkinter.Label(self.kaiseki_f2, width=15, height=1, textvariable=self.text2h)
        self.EminLabel2 = tkinter.Label(self.kaiseki_f2, width=15, height=1, textvariable=self.text2E)
        self.radiLabel2 = tkinter.Label(self.kaiseki_f2, width=15, height=1, textvariable=self.text2r)

        self.sizeLabel2.grid(row=0,column=0)
        self.bumpLabel2.grid(row=0,column=1)
        self.holeLabel2.grid(row=1,column=0)
        self.EminLabel2.grid(row=1,column=1)
        self.radiLabel2.grid(row=2,column=1)

        self.text3s=tkinter.StringVar()
        self.text3b=tkinter.StringVar()
        self.text3h=tkinter.StringVar()
        self.text3E=tkinter.StringVar()
        self.text3r=tkinter.StringVar()

        self.sizeLabel3 = tkinter.Label(self.kaiseki_f3, width=15, height=1, textvariable=self.text3s)
        self.bumpLabel3 = tkinter.Label(self.kaiseki_f3, width=15, height=1, textvariable=self.text3b)
        self.holeLabel3 = tkinter.Label(self.kaiseki_f3, width=15, height=1, textvariable=self.text3h)
        self.EminLabel3 = tkinter.Label(self.kaiseki_f3, width=15, height=1, textvariable=self.text3E)
        self.radiLabel3 = tkinter.Label(self.kaiseki_f3, width=15, height=1, textvariable=self.text3r)

        self.sizeLabel3.grid(row=0,column=0)
        self.bumpLabel3.grid(row=0,column=1)
        self.holeLabel3.grid(row=1,column=0)
        self.EminLabel3.grid(row=1,column=1)
        self.radiLabel3.grid(row=2,column=1)

        self.text4s=tkinter.StringVar()
        self.text4b=tkinter.StringVar()
        self.text4h=tkinter.StringVar()
        self.text4E=tkinter.StringVar()
        self.text4r=tkinter.StringVar()

        self.sizeLabel4 = tkinter.Label(self.kaiseki_f4, width=15, height=1, textvariable=self.text4s)
        self.bumpLabel4 = tkinter.Label(self.kaiseki_f4, width=15, height=1, textvariable=self.text4b)
        self.holeLabel4 = tkinter.Label(self.kaiseki_f4, width=15, height=1, textvariable=self.text4h)
        self.EminLabel4 = tkinter.Label(self.kaiseki_f4, width=15, height=1, textvariable=self.text4E)
        self.radiLabel4 = tkinter.Label(self.kaiseki_f4, width=15, height=1, textvariable=self.text4r)

        self.sizeLabel4.grid(row=0,column=0)
        self.bumpLabel4.grid(row=0,column=1)
        self.holeLabel4.grid(row=1,column=0)
        self.EminLabel4.grid(row=1,column=1)
        self.radiLabel4.grid(row=2,column=1)

        self.text5s=tkinter.StringVar()
        self.text5b=tkinter.StringVar()
        self.text5h=tkinter.StringVar()
        self.text5E=tkinter.StringVar()
        self.text5r=tkinter.StringVar()

        self.sizeLabel5 = tkinter.Label(self.kaiseki_f5, width=15, height=1, textvariable=self.text5s)
        self.bumpLabel5 = tkinter.Label(self.kaiseki_f5, width=15, height=1, textvariable=self.text5b)
        self.holeLabel5 = tkinter.Label(self.kaiseki_f5, width=15, height=1, textvariable=self.text5h)
        self.EminLabel5 = tkinter.Label(self.kaiseki_f5, width=15, height=1, textvariable=self.text5E)
        self.radiLabel5 = tkinter.Label(self.kaiseki_f5, width=15, height=1, textvariable=self.text5r)

        self.sizeLabel5.grid(row=0,column=0)
        self.bumpLabel5.grid(row=0,column=1)
        self.holeLabel5.grid(row=1,column=0)
        self.EminLabel5.grid(row=1,column=1)
        self.radiLabel5.grid(row=2,column=1)

        self.text6s=tkinter.StringVar()
        self.text6b=tkinter.StringVar()
        self.text6h=tkinter.StringVar()
        self.text6E=tkinter.StringVar()
        self.text6r=tkinter.StringVar()

        self.sizeLabel6 = tkinter.Label(self.kaiseki_f6, width=15, height=1, textvariable=self.text6s)
        self.bumpLabel6 = tkinter.Label(self.kaiseki_f6, width=15, height=1, textvariable=self.text6b)
        self.holeLabel6 = tkinter.Label(self.kaiseki_f6, width=15, height=1, textvariable=self.text6h)
        self.EminLabel6 = tkinter.Label(self.kaiseki_f6, width=15, height=1, textvariable=self.text6E)
        self.radiLabel6 = tkinter.Label(self.kaiseki_f6, width=15, height=1, textvariable=self.text6r)

        self.sizeLabel6.grid(row=0,column=0)
        self.bumpLabel6.grid(row=0,column=1)
        self.holeLabel6.grid(row=1,column=0)
        self.EminLabel6.grid(row=1,column=1)
        self.radiLabel6.grid(row=2,column=1)

        self.button= tkinter.Button(
            self.frame,
            text='終了する',
            width=10,
            height=3,
            command=self.button_clicked)
        self.button.grid(row=0,column=2, columnspan=2, rowspan=1)

        self.result = tkinter.StringVar()
        self.kekka = tkinter.Label(
            self.frame,
            textvariable=self.result,
            width=15,
            height=3,
            background='red',
            foreground='white')
        self.kekka.grid(row=1, column=2, columnspan=2)

    ########キューブ名
    def SetCubename(self, cubename):
        self.cubename = cubename
        self.cubelabel = tkinter.Label(
            self.frame,
            width=10,
            height=2,
            text='cube : '+str(self.cubename))
        self.cubelabel.grid(row=0,column=0,columnspan=2)
        self.text1.set('cube'+str(self.cubename)+'1.jpg')
        self.text2.set('cube'+str(self.cubename)+'2.jpg')
        self.text3.set('cube'+str(self.cubename)+'3.jpg')
        self.text4.set('cube'+str(self.cubename)+'4.jpg')
        self.text5.set('cube'+str(self.cubename)+'5.jpg')
        self.text6.set('cube'+str(self.cubename)+'6.jpg')


    #def takeim1(self, ret, frame1, frame2, frame3):
    def takeim1(self, data1, data2, data3):
        
        ########### [xc,       yc,       opt_r,    Emin,     xsizeeff, ysizeeff, bump_judge]
        dumpdata1 = [data1[0], data1[1], data1[2], data1[3], data1[4], data1[5], data1[6]]
        dumpdata2 = [data2[0], data2[1], data2[2], data2[3], data2[4], data2[5], data2[6]]
        dumpdata3 = [data3[0], data3[1], data3[2], data3[3], data3[4], data3[5], data3[6]]
         
        self.sizeLabel1.config(bg='red')
        self.bumpLabel1.config(bg='red')
        self.holeLabel1.config(bg='red')
        self.EminLabel1.config(bg='red')
        self.radiLabel1.config(bg='red')

        self.sizeLabel1.grid(row=0,column=0)
        self.bumpLabel1.grid(row=0,column=1)
        self.holeLabel1.grid(row=1,column=0)
        self.EminLabel1.grid(row=1,column=1)
        self.radiLabel1.grid(row=2,column=0)
    
        
        self.sizeLabel2.config(bg='red')
        self.bumpLabel2.config(bg='red')
        self.holeLabel2.config(bg='red')
        self.EminLabel2.config(bg='red')
        self.radiLabel2.config(bg='red')

        self.sizeLabel2.grid(row=0,column=0)
        self.bumpLabel2.grid(row=0,column=1)
        self.holeLabel2.grid(row=1,column=0)
        self.EminLabel2.grid(row=1,column=1)
        self.radiLabel2.grid(row=2,column=0)
    
    
        self.sizeLabel3.config(bg='red')
        self.bumpLabel3.config(bg='red')
        self.holeLabel3.config(bg='red')
        self.EminLabel3.config(bg='red')
        self.radiLabel3.config(bg='red')
        
        self.sizeLabel3.grid(row=0,column=0)
        self.bumpLabel3.grid(row=0,column=1)
        self.holeLabel3.grid(row=1,column=0)
        self.EminLabel3.grid(row=1,column=1)
        self.radiLabel3.grid(row=2,column=0)
    
        self.text1s.set('size: ({},{})'.format(dumpdata1[4], dumpdata1[5]))
        self.text1b.set('bumprate: {}'.format(dumpdata1[6]))
        self.text1h.set('hole: ({},{})'.format(dumpdata1[0], dumpdata1[1]))
        self.text1E.set('Emin: {}'.format(dumpdata1[3]))
        self.text1r.set('r = {}'.format(dumpdata1[2]))
                
        self.text2s.set('size: ({},{})'.format(dumpdata2[4], dumpdata2[5]))
        self.text2b.set('bumprate: {}'.format(dumpdata2[6]))
        self.text2h.set('hole: ({},{})'.format(dumpdata2[0], dumpdata2[1]))
        self.text2E.set('Emin: {}'.format(dumpdata2[3]))
        self.text2r.set('r = {}'.format(dumpdata2[2]))
                
        self.text3s.set('size: ({},{})'.format(dumpdata3[4], dumpdata3[5]))
        self.text3b.set('bumprate: {}'.format(dumpdata3[6]))
        self.text3h.set('hole: ({},{})'.format(dumpdata3[0], dumpdata3[1]))
        self.text3E.set('Emin: {}'.format(dumpdata3[3]))
        self.text3r.set('r = {}'.format(dumpdata3[2]))
        self.result.set('解析結果:        ')


        self.text4s.set('')
        self.text4b.set('')
        self.text4h.set('')
        self.text4E.set('')
        self.text4r.set('')
                
        self.text5s.set('')
        self.text5b.set('')
        self.text5h.set('')
        self.text5E.set('')
        self.text5r.set('')
                
        self.text6s.set('')
        self.text6b.set('')
        self.text6h.set('')
        self.text6E.set('')
        self.text6r.set('')
    
    def takeim2(self, data4, data5, data6):
    
        ########### [xc,       yc,       opt_r,    Emin,     xsizeeff, ysizeeff, bump_judge]
        dumpdata4 = [data4[0], data4[1], data4[2], data4[3], data4[4], data4[5], data4[6]]
        dumpdata5 = [data5[0], data5[1], data5[2], data5[3], data5[4], data5[5], data5[6]]
        dumpdata6 = [data6[0], data6[1], data6[2], data6[3], data6[4], data6[5], data6[6]]
    
        self.text4s.set('size: ({},{})'.format(dumpdata4[4], dumpdata4[5]))
        self.text4b.set('bumprate: {}'.format(dumpdata4[6]))
        self.text4h.set('hole: ({},{})'.format(dumpdata4[0], dumpdata4[1]))
        self.text4E.set('Emin: {}'.format(dumpdata4[3]))
        self.text4r.set('r = {}'.format(dumpdata4[2]))
                
        self.text5s.set('size: ({},{})'.format(dumpdata5[4], dumpdata5[5]))
        self.text5b.set('bumprate: {}'.format(dumpdata5[6]))
        self.text5h.set('hole: ({},{})'.format(dumpdata5[0], dumpdata5[1]))
        self.text5E.set('Emin: {}'.format(dumpdata5[3]))
        self.text5r.set('r = {}'.format(dumpdata5[2]))
                
        self.text6s.set('size: ({},{})'.format(dumpdata6[4], dumpdata6[5]))
        self.text6b.set('bumprate: {}'.format(dumpdata6[6]))
        self.text6h.set('hole: ({},{})'.format(dumpdata6[0], dumpdata6[1]))
        self.text6E.set('Emin: {}'.format(dumpdata6[3]))
        self.text6r.set('r = {}'.format(dumpdata6[2]))
                
    
        self.sizeLabel4.config(bg='red')
        self.bumpLabel4.config(bg='red')
        self.holeLabel4.config(bg='red')
        self.EminLabel4.config(bg='red')
        self.radiLabel4.config(bg='red')
        
        self.sizeLabel4.grid(row=0,column=0)
        self.bumpLabel4.grid(row=0,column=1)
        self.holeLabel4.grid(row=1,column=0)
        self.EminLabel4.grid(row=1,column=1)
        self.radiLabel4.grid(row=2,column=0)
    
    
        self.sizeLabel5.config(bg='red')
        self.bumpLabel5.config(bg='red')
        self.holeLabel5.config(bg='red')
        self.EminLabel5.config(bg='red')
        self.radiLabel5.config(bg='red')
        
        self.sizeLabel5.grid(row=0,column=0)
        self.bumpLabel5.grid(row=0,column=1)
        self.holeLabel5.grid(row=1,column=0)
        self.EminLabel5.grid(row=1,column=1)
        self.radiLabel5.grid(row=2,column=0)
    
    
        self.sizeLabel6.config(bg='red')
        self.bumpLabel6.config(bg='red')
        self.holeLabel6.config(bg='red')
        self.EminLabel6.config(bg='red')
        self.radiLabel6.config(bg='red')

        self.sizeLabel6.grid(row=0,column=0)
        self.bumpLabel6.grid(row=0,column=1)
        self.holeLabel6.grid(row=1,column=0)
        self.EminLabel6.grid(row=1,column=1)
        self.radiLabel6.grid(row=2,column=0)
    
        self.result.set('解析結果: survive')
    
    
    def button_clicked(self):
        self.root.quit()
    
    #####################################
    #########解析結果出力################
    
    
    
    
    
    
    
    
    
    
    
    
