#!/usr/bin/env python
# -*- coding:utf-8 -*-
###
# Filename: f:\worksend\lab\bomb\bomb\phase_5_findx.py
# Path: f:\worksend\lab\bomb\bomb
# Created Date: Friday, December 31st 2021, 2:31:10 pm
# Author: Cracer
# 
# Copyright (c) 2021 Cracer Inc.
###

def findx():
    list_9 = []
    list_15 = []
    list_14 = []
    list_5 = []
    list_6 = []
    list_7 = []
    # 标准ASCII打印字符取值范围32～126
    for i in range(32, 127):
        if i & 0xf == 9:
            list_9.append(chr(i))
        if i & 0xf == 15:
            list_15.append(chr(i))
        if i & 0xf == 14:
            list_14.append(chr(i))
        if i & 0xf == 5:
            list_5.append(chr(i))
        if i & 0xf == 6:
            list_6.append(chr(i))
        if i & 0xf == 7:
            list_7.append(chr(i))

    print(list_9)
    print(list_15)
    print(list_14)
    print(list_5)
    print(list_6)
    print(list_7)


if __name__ == '__main__':
    findx()