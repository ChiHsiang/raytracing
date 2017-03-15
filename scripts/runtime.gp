reset
set ylabel 'time(sec)'
set auto x
set style fill solid
set title 'perfomance comparison'
set style data histogram
set style histogram cluster gap 1
set boxwidth 0.9
set format y "%.0f"
set xtic rotate by -45 scale 0
set term png enhanced font 'Verdana,10'
set yrange [0.1:10.0]
set output 'runtime.png'

plot 'output.txt' using 2:xticlabels(1) title ''
