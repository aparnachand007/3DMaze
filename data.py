#!/usr/bin/env python3

from PIL import Image
import sys
import os


if __name__ == '__main__':

    if(len(sys.argv)==1):
        print('enter filename to read maze data from!')
        sys.exit(1)
    else:
        filename = sys.argv[1]
        if os.path.isfile(filename):
            img = Image.open(str(sys.argv[1]))
            img.convert('1')
            w,h = img.size
            for i in range(0,w):
                for j in range(0,h):
                    print('{0}x{1}={2}'.format(i,j,img.getpixel((i,j))))
            sys.exit(1)
        else:
            print('filename does not exist!')
            sys.exit(1)
