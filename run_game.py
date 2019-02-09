import sys
import os 
import gzip 
import pygame

if '--profile' in sys.argv:
    import cProfile as profile

try:
    import cPickle as pickle
except:
    import pickle

try: 
    import psyco
    psyco.full()
except:
    print ("no psyco... maybe you should install it...")

sys.path.append(os.path.join('.','scr'))

import engine 
from pdcglobal import * 
for file in os.listdir('.'):
    if file[0:3]=='MAP':
        os.remove(file)
