#!/usr/bin/python3

import sys
import psycopg2


def delete(tab):
    conn = psycopg2.connect("dbname=u7korkuc user=u7korkuc password=7korkuc")
    cur = conn.cursor()
    cur.execute('DELETE FROM book_club.' + tab)
    cur.close()

def delete_all():
    conn = psycopg2.connect("dbname=u7korkuc user=u7korkuc password=7korkuc")
    cur = conn.cursor()
    names = ['book', 'book_item', 'user_book','item_description', 'editorial', 'description', 'author', 'series', 'book_genre']
    
    for name in names:
        cur.execute('DELETE FROM book_club.' + name)
    

    cur.close()


if __name__ == '__main__':
    
    if(len(sys.argv) == 0):
    
        tab = input("Table to delete ('all' deletes all): ")
    
    else:
    
        tab = argv[1]
    

    confirmation = input("Do you want to delete all records in table " + tab + "? Y - yes, N - no ")

    if(confirmation == 'y'):
        confirmation2 = input("Really?? ")
        if(confirmation2 == 'y'):
            if(tab == 'all'):
                delete_all()
            else:
                delete(tab)
    
    