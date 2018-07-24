import matplotlib.pyplot as plt
import numpy as np
values_colour = [[0,0,0,0,0],[0,0,0,0,0],[75,0,0,0,0],[225,0,0,0,0],[112,0,0,0,0],[0,0,0,225,0],[75,0,75,112,0],[225,112,225,225,0],[112,225,112,0,0],[225,0,0,0,0],[0,112,75,0,0],[0,112,225,0,75]]
values = [[2,0,0,0,0],[2,0,0,0,0],[2,0,0,0,0],[2,0,0,0,0],[2,0,0,0,0],[2,0,0,2,0],[2,0,2,2,0],[2,2,2,2,0],[2,2,2,2,0],[2,2,2,2,0],[2,2,2,2,2],[2,2,2,2,2]]
values_text = [['Label a','No Content','No Content','No Content','No Content'],['Label a','No Content','No Content','No Content','No Content'],['Label d','No Content','No Content','No Content','No Content'],['Label b','No Content','No Content','No Content','No Content'],['Label c','No Content','No Content','No Content','No Content'],['Label a','No Content','No Content','Label b','No Content'],['Label d','No Content','Label d','Label c','No Content'],['Label b','Label c','Label b','Label b','No Content'],['Label c','Label b','Label c','Label a','No Content'],['Label b','Label a','Label a','Label a','No Content'],['Label a','Label c','Label d','Label a','Label a'],['Label a','Label c','Label b','Label a','Label d']]
max_cols = len(values)
max_rows = len(values[0])
values_sums = [sum([r[i] for r in values]) for i in range(max_rows)]
values_norm = [[v / values_sums[i] for i, v in enumerate(row)] for row in values]
fig, ax = plt.subplots(1, figsize = (12, 20))
for row_num in range(max_cols) :
	ax.bar(range(max_rows), values_norm[row_num], bottom = [sum([values_norm[i][j] for i in range(row_num)]) for j in range(max_rows)], width = 1, edgecolor = '#000000', color = [plt.get_cmap('gray')(i) for i in values_colour[row_num]])
ax.set_xlim(-0.5, max_rows - 0.5)
ax.set_xticks([])
ax.set_yticks([])
ax.set_ylim(0, 1)
for x in range(max_rows) :
	for y in range(max_cols) :
		if values[y][x] != 0.0:
				ax.text(x, values_norm[y][x] / 2 + sum([values_norm[newy][x] for newy in range(y)]), values_text[y][x], fontsize = 10, ha='center', va='center', bbox=dict(facecolor='white', edgecolor='white', boxstyle='round,pad=.1'))
plt.savefig("Greyscale_CaledonianMercury_1820615_1.png", bbox_inches='tight')