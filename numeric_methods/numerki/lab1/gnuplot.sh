set terminal post enhanced colour solid font 20  # wybor formatu, w jakim chcemy utworzyc wynikowy rysunek

set output "x_t.eps" # nazwa pliku wynikowego
set title "Wychylenie f(t)" # tytul wykresu
set xlabel "t" # etykieta osi OX
set ylabel "f(t)" # etykieta osi OY
set grid # wlaczenie widoczności siatki pomocniczej
plot "out.dat" w l t "f(t), dt = 0.1", "" u 1:3 t "splot" 
# plot - polecenie rysowania pliku o podanej nazwie "out.dat"
# w p == with points
# t "dt = 0.1" == title "dt = 0.1"
