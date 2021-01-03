import numpy as np
import time
from numba.decorators import jit
############サインコサイン
@jit
def sine(theta):
    a = np.sin(theta)
    return a
@jit
def cosine(theta):
    a = np.cos(theta)
    return a

def SearchCenter( x_hole, y_hole, r_hole, edges2):
    startsearch= time.time()
    nrad = 16
    nradhalf = nrad/2
    Estimate = np.zeros(1)
    sine_iphi = np.zeros(nrad)
    cosine_iphi = np.zeros(nrad)
    edgexi_ = []
    edgeyi_ = []
    #こいつらのなかに、再度リストをアペンドする。


    edgexi = np.zeros(nrad)
    edgeyi = np.zeros(nrad)
    #最後に使う配列
    
    file = open('edgedata.txt', 'w')
    file.write(str(x_hole)+ ' ' +str(y_hole)+ ' ' +str(r_hole)+'\n')
    for iphi in range(nrad):

        sine_iphi[iphi]   = sine(iphi*np.pi/nradhalf)
        cosine_iphi[iphi] = cosine(iphi*np.pi/nradhalf)  

        redge = np.zeros(nrad)
        
    for irad in range(nrad):
    
        print("irad = {}:".format(irad))

        
        dr_semi = []
        edgexi_.append([])
        edgeyi_.append([])
        #リストの中にリストをアペンド
        
        for dr in range(20):
            
            if edges2[int(y_hole - (r_hole + dr)*sine_iphi[irad]), int(x_hole + (r_hole + dr)*cosine_iphi[irad])] > 200 :
                dr_semi.append(dr)
                
                print("+:edge(y, x) = ({}, {}).".format(int(y_hole - (r_hole + dr)*sine_iphi[irad]), int(x_hole + (r_hole + dr)*cosine_iphi[irad])))
                edgexi_[irad].append( int(x_hole + (r_hole + dr)*cosine_iphi[irad]))
                edgeyi_[irad].append( int(y_hole - (r_hole + dr)*sine_iphi[irad]))
                print(edgexi_[irad]) 
            
            elif edges2[int(y_hole+1 - (r_hole + dr)*sine_iphi[irad]), int(x_hole + (r_hole + dr)*cosine_iphi[irad])] > 200 or \
                 edges2[int(y_hole - (r_hole + dr)*sine_iphi[irad]), int(x_hole+1 + (r_hole + dr)*cosine_iphi[irad])] > 200: 
                #if の2,3行目：ピクセルの上などを斜めに通り抜けてしまうことがある。
                dr_semi.append(dr)
                
                print("+:edge(y, x) = ({}, {}).".format(int(y_hole - (r_hole + dr)*sine_iphi[irad]), int(x_hole + (r_hole + dr)*cosine_iphi[irad])))
                edgexi_[irad].append( int(x_hole + (r_hole + dr)*cosine_iphi[irad]))
                edgeyi_[irad].append( int(y_hole - (r_hole + dr)*sine_iphi[irad]))
                print(edgexi_[irad]) 
            
            if edges2[int(y_hole - (r_hole - dr)*sine_iphi[irad]), int(x_hole + (r_hole - dr)*cosine_iphi[irad])] > 200 :  
                dr_semi.append(-dr)
                print("-:edge(y, x) = ({}, {}).".format(int(y_hole - (r_hole - dr)*sine_iphi[irad]), int(x_hole + (r_hole - dr)*cosine_iphi[irad])))
                edgexi_[irad].append( int(x_hole + (r_hole - dr)*cosine_iphi[irad]))
                edgeyi_[irad].append( int(y_hole - (r_hole - dr)*sine_iphi[irad]))
                print(edgexi_[irad]) 
                
            elif edges2[int(y_hole+1 - (r_hole - dr)*sine_iphi[irad]), int(x_hole + (r_hole - dr)*cosine_iphi[irad])] > 200 or \
                 edges2[int(y_hole - (r_hole - dr)*sine_iphi[irad]), int(x_hole+1 + (r_hole - dr)*cosine_iphi[irad])] > 200:
                dr_semi.append(-dr)
                print("-:edge(y, x) = ({}, {}).".format(int(y_hole - (r_hole - dr)*sine_iphi[irad]), int(x_hole + (r_hole - dr)*cosine_iphi[irad])))
                edgexi_[irad].append( int(x_hole + (r_hole - dr)*cosine_iphi[irad]))
                edgeyi_[irad].append( int(y_hole - (r_hole - dr)*sine_iphi[irad]))
                print(edgexi_[irad]) 
                
        if irad < 4:
            if edgexi_[irad] == []:
                edgexi[irad] = 0
                edgeyi[irad] = 0
            else:
                edgexi[irad] = max(edgexi_[irad])
                print('edgexi[{}]={}'.format(irad, edgexi[irad]))
                xindex = np.argmax(edgexi_[irad])
                print('xindex = {}'.format(xindex))
                #edgeyi[irad] = min(edgeyi_[irad])
                edgeyi[irad] = edgeyi_[irad][xindex]
        if irad >= 4 and irad < 8:
            if edgexi_[irad] == []:
                edgexi[irad] = 0
                edgeyi[irad] = 0
            else:
                edgexi[irad] = min(edgexi_[irad])
                print('edgexi[{}]={}'.format(irad, edgexi[irad]))
                xindex = np.argmin(edgexi_[irad])
                print('xindex = {}'.format(xindex))
                #edgeyi[irad] = min(edgeyi_[irad])
                edgeyi[irad] = edgeyi_[irad][xindex]
        if irad >= 8 and irad < 12:
            if edgexi_[irad] == []:
                edgexi[irad] = 0
                edgeyi[irad] = 0
            else:
                edgexi[irad] = min(edgexi_[irad])
                print('edgexi[{}]={}'.format(irad, edgexi[irad]))
                xindex = np.argmin(edgexi_[irad])
                print('xindex = {}'.format(xindex))
                #edgeyi[irad] = max(edgeyi_[irad])
                edgeyi[irad] = edgeyi_[irad][xindex]
        if irad >= 12 and irad < 16:
            if edgexi_[irad] == []:
                edgexi[irad] = 0
                edgeyi[irad] = 0
            else:
                edgexi[irad] = max(edgexi_[irad])
                print('edgexi[{}]={}'.format(irad, edgexi[irad]))
                xindex = np.argmax(edgexi_[irad])
                print('xindex = {}'.format(xindex))
                #edgeyi[irad] = max(edgeyi_[irad])
                edgeyi[irad] = edgeyi_[irad][xindex]
            
        print(str(edgexi[irad])+ ' ' +str(edgeyi[irad])+'\n') 
        file.write(str(edgexi[irad])+ ' ' +str(edgeyi[irad])+'\n') 
        
        if dr_semi == []:
            redge[irad] = 0
        else:
            redge[irad] = abs(max(dr_semi)) 
        
    
        Estimate = np.sum(redge)
    print('edgexi, edgeyi ={}, {}'.format(edgexi, edgeyi))
    print('Estimete = \n{}'.format(Estimate))
    Emin = Estimate.min()
    file.close()
    print('search Center time : {} sec'.format(time.time() - startsearch))




 
