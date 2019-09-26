#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Sep 25 20:16:06 2019

@author: hiparco
"""

import numpy as np
import matplotlib.pyplot as plt


G = 1

JEANS05 = -4
JEANS11 = -2

CONDITION = JEANS05;
#CONDITION = JEANS11;

kkj = 0.5
L = 1
Xmin = -L/2
Xmax = Xmin+L
V = 1
Vmin = -V
Vmax = Vmin + 2*V
T = L/V
k = 2 * (2*np.pi/L)

rho = 1.0/(T**2 *G)

sigma = np.sqrt(4*G*np.pi*rho*kkj**2/k**2)

print(2*sigma**2)


























