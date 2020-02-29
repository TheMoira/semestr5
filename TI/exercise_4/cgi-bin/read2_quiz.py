#!/usr/bin/python
import os
import cgi
import cgitb; cgitb.enable()


def check_season(season):
    if season == "Spring":
        number = 0
    elif season == "Summer":
        number = 1
    elif season == "Autumn":
        number = 2
    elif season == "Winter":
        number = 3
    else:
        number = 0
    return number


def update_file(wyniki, len, num):
    #jesli pierwszy rekord
    if(len == 0):
        for line in range(4):
            if line == num:
                wyniki.write(str(1)+" ")
            else:
                wyniki.write(str(0)+" ")
    else:   #jak juz sa dane
        wyniki = open("../ajax_zad1/wyniki.txt", "rw+")
        lines = wyniki.readlines()
        iter = 0
        int_tab = ""
        for line in lines:
            for i in line.split(" "):
                if iter == num:
                    new_value = int(i) + 1
                    i = str(new_value)
                iter += 1
                int_tab += i + " "        
        
        wyniki.seek(0)
        wyniki.truncate()
        wyniki.write(int_tab)



form = cgi.FieldStorage()
info = form.getvalue("sel", "(no info)")

# tutaj wrzucam tworzenie pliku txt do zapisywania ilosci odp
wyniki = open("../ajax_zad1/wyniki.txt", "rw+")
num = check_season(info)
len = sum(1 for line in wyniki)
update_file(wyniki,len, num)
wyniki.close()

# tutaj dodaje wartosci do wyniki.html z pliku txt

wyniki = open("../ajax_zad1/wyniki.txt", "r")

out = ""
iter = 0

lines_w = wyniki.readlines()
for line_w in lines_w:
    for i in line_w.split(" "):
        if i != "":
            out += i
            if iter<3:
                out += ","
            iter += 1

wyniki.close()

# #  tutaj musimy wsadzic htmla z grafikami i to beszie w js response
print "Content-Type: text/plain"
print 
print """{"wyniki": [%s]}""" %out

# file = open("../ajax_zad1/wyniki.html", "r")
# wyniki = open("../ajax_zad1/wyniki.txt", "r")

# out = ""
# lines = file.readlines()
# # out += "<p>lol</p>"
# for line in lines:
#     if line =="//START\n":
#         this = "var inputData = ["
#         lines_w = wyniki.readlines()
#         for line_w in lines_w:
#             for i in line_w.split(" "):
#                 if i != "":
#                     this += i + ","
#         this += "0];\n"
#         out += this
#     else:
#         out += line


# #  tutaj musimy wsadzic htmla z grafikami i to beszie w js response
# # print "Content-Type: text/html"
# # print
# # print "\ "
# print "%s" %out