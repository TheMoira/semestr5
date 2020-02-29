#!/usr/bin/python
import os
import cgi
import cgitb; cgitb.enable()


form = cgi.FieldStorage()
n = form.getvalue("rozmiar", "0")


#dodaj do tablicy 
out = '"size":' + n

print "Content-Type: text/plain"
print
print """{%s}"""%out

