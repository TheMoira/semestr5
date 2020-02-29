#!/usr/bin/python
import os
import cgi
import cgitb; cgitb.enable()


form = cgi.FieldStorage()
info = form.getvalue("liczba", "(no info)")

# data = open("data.txt", "w")
# data.truncate()
# data.write(info)
# data.close()

# data = open("data.txt", "r")
# out = ""
# lines = data.readlines()
# for line in lines:
#     out += line
# data.close()

print "Content-Type: text/plain"
print
print "%s"%info