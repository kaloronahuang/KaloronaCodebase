# 520.py
import cv2
import csv
import numpy as np
import math
from matplotlib import pyplot as plt

dstImage = np.zeros((27, 227, 3), np.uint8)

with open('large.csv') as src:
    fileSrc = csv.reader(src)
    x = 0
    y = 0
    for row in fileSrc:
        y = 0
        for col in row:
            tk = int(col)
            cpx = x * 100 + 50
            cpy = y * 100 + 50
            hours = tk / 3600
            minutes = (tk - 3600 * hours) / 60
            angel = tk / 86400 * 2 * math.pi
            cv2.line(dstImage, (cpx, cpy), (cpx + math.cos(angel) * 40, cpy + math.sin(angel) * 40), 255)
            y = y + 1
        x = x + 1

plt.imshow(dstImage,'gray')