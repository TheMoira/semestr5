set terminal post enhanced colour solid font 20  # wybor formatu, w jakim chcemy utworzyc wynikowy rysunek

set output "wynik.eps" # nazwa pliku wynikowego
set title "St(it) globalna" # tytul wykresu
set xlabel "it" # etykieta osi OX
set ylabel "S(it)" # etykieta osi OY
set grid # wlaczenie widoczności siatki pomocniczej
plot "stGlob.dat" u 1:2 t "wykres" 
# plot - polecenie rysowania pliku o podanej nazwie "out.dat"
# w p == with points
# t "dt = 0.1" == title "dt = 0.1"
