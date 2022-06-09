#!/usr/bin/python3
import os, re

# qwq = os.system("lsd --tree --ignore-glob Environment")
infile = open('README.md', 'r')
left = right = ""  #创立空的字符串用于储存文件
flag = 0
for line in infile:  #使用迭代器读取每一段文本文件的内容
    if line == '<!-- directory tree begin -->\n':
        left += line
        flag += 1
    elif line == '<!-- directory tree end -->\n':
        flag += 1
    if flag == 0:
        left += line
    elif flag == 2:
        right += line
infile.close()
onfile = open('README.md', 'w')  #以清空原文本文件内容的方式打开文件写入
onfile.write(left + "```plain\n")
onfile.close()
os.system("sh directory\\ tree.sh")
onfile = open('README.md', 'a+')
onfile.write("```\n" + right)
onfile.close()