#script to plot the results in dados.txt(points) and the analitical solution cos(x) (Lines)

reset
set xrange[0:pi/2]
plot "dados.txt" u ($1):($2) w points, cos(x)

#end
