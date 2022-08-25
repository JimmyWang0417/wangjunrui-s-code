#!/usr/bin/python3
import os

infile = open('README.md', 'r')
left = right = ""
flag = 0
for line in infile:
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
onfile = open('README.md', 'w')
onfile.write(left + "```plain\n")
onfile.close()
os.system("sh directory\\ tree.sh")
onfile = open('README.md', 'a+')
onfile.write("```\n" + right)
onfile.close()
