#!/usr/bin/python
import os
import cgi
import cgitb; cgitb.enable()


form = cgi.FieldStorage()
n = form.getvalue("rozmiar", "0")
color = form.getvalue("color", "red")
is_checked = form.getvalue("pola", "false")


#dodaj do tablicy 
out1 = '"size":' + n + ","
out2 = '"color":"' + color + '",'
out3 = '"is_checked":"' + is_checked + '"'
out = out1 + out2 + out3

print "Content-Type: text/plain"
print
print """{%s}"""%out

