set terminal post enhanced colour solid font 20  # wybor formatu, w jakim chcemy utworzyc wynikowy rysunek

set output "wynikE3.eps" # nazwa pliku wynikowego
set title "Energia" # tytul wykresu
set xlabel "t" # etykieta osi OX
set ylabel "Ener" # etykieta osi OY
set grid # wlaczenie widoczności siatki pomocniczej
plot "energia3.dat" u 1:2 w l t "wykres" 
# plot - polecenie rysowania pliku o podanej nazwie "out.dat"
# w p == with points
# t "dt = 0.1" == title "dt = 0.1"
