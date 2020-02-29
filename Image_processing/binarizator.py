#!/usr/bin/python3
import cv2
import numpy as np
import sys
import math

def greyscale(im):
    grey_im = np.ndarray((im.shape[0], im.shape[1]))
    # print("Loaded image with shape: " + str(np.shape(im)))
    grey_im = np.matmul(im, np.transpose((0.299, 0.587, 0.114)), axes=[(0,2), 0, 0])
    cv2.imwrite("george.jpg",grey_im)
    return grey_im/255

def q(t, hist, pixCount):
    wyn1 = 0
    wyn2 = 0
    for i in range(1, t):
        wyn1 += hist[i]/pixCount
    for j in range(t, 256):
        wyn2 += hist[j]/pixCount
    if wyn1 == 0:
        wyn1 = 1E-10
    if wyn2 == 0:
        wyn2 = 1E-10
    return (wyn1, wyn2)

def mi(t, hist, pixCount):
    Q = q(t, hist, pixCount)
    wyn1 = 0
    wyn2 = 0
    for i in range(1, t):
        wyn1 += i*hist[i]/pixCount
    for j in range(t, 256):
        wyn2 += j*hist[j]/pixCount
    wyn1 = wyn1/Q[0]
    wyn2 = wyn2/Q[1]
    return (wyn1, wyn2)

def omega(t, hist, pixCount):
    Q = q(t, hist, pixCount)
    MI = mi(t, hist, pixCount)
    wyn1 = 0
    wyn2 = 0
    for i in range(1, t):
        wyn1 += pow(i - MI[0], 2) * hist[i] / pixCount
    for j in range(t, 256):
        wyn2 += pow(j - MI[1], 2) * hist[j] / pixCount
    wyn1 = wyn1 / Q[0]
    wyn2 = wyn2 / Q[1]
    return (wyn1, wyn2)

def hist(im):
    hist = []
    for i in range(256):
        hist.append(0)
    for i in range(im.shape[0]):
        for j in range(im.shape[1]):
            hist[math.ceil(im[i][j] * 255)] += 1
    return hist

def otsu(im):
    H = hist(im)
    C = im.shape[0] * im.shape[1]
    wyn = (0, 1E+10)
    for t in range(255):
        Q = q(t, H, C)
        O = omega(t, H, C)
        if Q[0]*O[0] + Q[1]*O[1] < wyn[1]:
            wyn = (t, Q[0]*O[0] + Q[1]*O[1])
    # print("Otsu Out:")
    # print(wyn)
    return regular_bin(im, wyn[0])

def regular_bin(im, thresh):
    thresh = thresh/255
    cv2.imwrite("george.jpg",np.greater(im, thresh).astype(float)*255)
    return np.greater(im, thresh).astype(float)

def rgbBin(im, rt, gt, bt):
    # print("R: %s G: %s B: %s" % (rt, gt, bt))
    R = np.matmul(im, np.transpose((1, 0, 0)), axes=[(0,2), 0, 0])/255
    G = np.matmul(im, np.transpose((0, 1, 0)), axes=[(0,2), 0, 0])/255
    B = np.matmul(im, np.transpose((0, 0, 1)), axes=[(0,2), 0, 0])/255
    R = regular_bin(R, rt)
    G = regular_bin(G, gt)
    B = regular_bin(B, bt)
    wyn = np.logical_or(R, G).astype(float)
    wyn = np.logical_or(wyn, B).astype(float)
    cv2.imwrite("george.jpg",wyn*255)
    return wyn



def adaptive_bin(im):
    C = 5
    mean = mean_for_adaptive(im)
    diff = im - mean
    tres = regular_bin(diff,C)
    cv2.imwrite("george.jpg",tres*255)
    return tres


def mean_for_adaptive(im):
    rows = im.shape[0]
    cols = im.shape[1]
    outputPixelValue = np.zeros((rows, cols))

    for i in range(1,rows-1):
        for j in range(1,cols-1):
            p = im[i-1][j-1]
            q = im[i-1][j-1]
            r = im[i-1, j+1]
            s = im[i, j-1]
            t = im[i, j]
            u = im[i, j+1]
            v = im[i+1, j-1]
            w = im[i+1, j]
            x = im[i+1, j+1]
            val = np.power(p*q*r*s*t*u*v*w*x,1/9)
            outputPixelValue[i][j] = val
            val = 1
        
    return outputPixelValue




# file = sys.argv[1]
# print(file)
# print(sys.argv[2])
# im = cv2.imread(file)
# # cv2.imshow("Init Image", im)
# test_im = grayscale(im)
# print(test_im.shape[1])
# cv2.imshow("Grey Image", test_im)
# cv2.imshow("Bin Image", regular_bin(test_im, int(sys.argv[2])))
# cv2.imshow("Otsu Bin Image", otsu(test_im))
# cv2.imshow("RGB Bin Image", rgbBin(im, 70, 130, 230))

# cv2.imshow("Adaptive",adaptive_bin(test_im))
# # src = cv2.imread(file, cv2.CV_8UC1);
# # th2 = cv2.adaptiveThreshold(src,255,cv2.ADAPTIVE_THRESH_MEAN_C, cv2.THRESH_BINARY,9,5)
# # cv2.imshow("prof",th2)
# cv2.imwrite("out/"+file, im*255)
# cv2.waitKey(0)
# cv2.destroyAllWindows()