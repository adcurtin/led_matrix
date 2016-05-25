const PROGMEM byte font[][7] = {
	{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0},
        {1,1,1,1,1,1,1},{3,3,3,3,3,3,3},{7,7,7,7,7,7,7},{15,15,15,15,15,15,15},{31,31,31,31,31,31,31},{30,30,30,30,30,30,30},{28,28,28,28,28,28,28},{24,24,24,24,24,24,24},{16,16,16,16,16,16,16},{4,12,20,20,22,7,3},{3,3,0,28,2,2,28},{3,3,0,30,2,14,2},{0,0,31,14,4,0,0},{0,2,6,14,6,2,0},{0,8,12,14,12,8,0},{0,0,4,14,31,0,0},
	{0,0,0,0,0,0,0},{4,4,4,4,0,0,4},{10,10,10,0,0,0,0},{10,10,31,10,31,10,10},{4,30,5,14,20,15,4},{3,19,8,4,2,25,24},{6,9,5,2,21,9,22},{6,4,2,0,0,0,0},{8,4,2,2,2,4,8},{2,4,8,8,8,4,2},{0,4,21,14,21,4,0},{0,4,4,31,4,4,0},{0,0,0,0,6,4,2},{0,0,0,31,0,0,0},{0,0,0,0,0,6,6},{0,16,8,4,2,1,0},
	{14,17,25,21,19,17,14},{4,6,4,4,4,4,14},{14,17,16,8,4,2,31},{31,8,4,8,16,17,14},{8,12,10,9,31,8,8},{31,1,15,16,16,17,14},{12,2,1,15,17,17,14},{31,16,8,4,2,2,2},{14,17,17,14,17,17,14},{14,17,17,30,16,8,6},{0,6,6,0,6,6,0},{0,6,6,0,6,4,2},{8,4,2,1,2,4,8},{0,0,31,0,31,0,0},{2,4,8,16,8,4,2},{14,17,16,8,4,0,4},
        {14,17,16,22,21,21,14},{14,17,17,17,31,17,17},{15,17,17,15,17,17,15},{14,17,1,1,1,17,14},{7,9,17,17,17,9,7},{31,1,1,15,1,1,31},{31,1,1,15,1,1,1},{14,17,1,29,17,17,30},{17,17,17,31,17,17,17},{14,4,4,4,4,4,14},{28,8,8,8,8,9,6},{17,9,5,3,5,9,17},{1,1,1,1,1,1,31},{17,27,21,21,17,17,17},{17,17,19,21,25,17,17},{14,17,17,17,17,17,14},
	{15,17,17,15,1,1,1},{14,17,17,17,21,9,22},{15,17,17,15,5,9,17},{30,1,1,14,16,16,15},{31,4,4,4,4,4,4},{17,17,17,17,17,17,14},{17,17,17,17,17,10,4},{17,17,17,21,21,21,10},{17,17,10,4,10,17,17},{17,17,17,10,4,4,4},{31,16,8,4,2,1,31},{14,2,2,2,2,2,14},{17,10,31,4,31,4,4},{14,8,8,8,8,8,14},{4,10,17,0,0,0,0},{0,0,0,0,0,0,31},
	{2,4,8,0,0,0,0},{0,0,14,16,30,17,30},{1,1,1,13,19,17,15},{0,0,14,1,1,17,14},{16,16,16,22,25,17,30},{0,0,14,17,31,1,14},{12,18,2,7,2,2,2},{0,30,17,17,30,16,14},{1,1,13,19,17,17,17},{0,4,0,4,4,4,4},{8,0,12,8,8,9,6},{1,1,9,5,3,5,9},{6,4,4,4,4,4,14},{0,0,11,21,21,17,17},{0,0,13,19,17,17,17},{0,0,14,17,17,17,14},
	{0,0,15,17,15,1,1},{0,0,22,25,30,16,16},{0,0,13,19,1,1,1},{0,0,14,1,14,16,15},{2,2,7,2,2,18,12},{0,0,17,17,17,25,22},{0,0,17,17,17,10,4},{0,0,17,17,21,21,10},{0,0,17,10,4,10,17},{0,0,17,17,30,16,14},{0,0,31,8,4,2,31},{8,4,4,2,4,4,8},{4,4,4,4,4,4,4},{2,4,4,8,4,4,2},{0,4,8,31,8,4,0},{0,4,2,31,2,4,0},
	{10,0,4,10,17,31,17},{10,0,4,10,17,31,17},{4,0,4,10,17,31,17},{4,10,4,10,17,31,17},{8,4,14,16,30,17,30},{31,3,3,31,3,3,31},{17,14,17,17,17,17,14},{0,10,0,14,17,17,14},{16,14,25,21,19,14,1},{0,8,14,21,21,14,2},{17,0,17,17,17,17,14},{0,10,0,17,17,25,22},{0,1,2,4,8,16,0},{16,8,31,4,31,2,1},{0,2,21,21,8,0,0},{30,1,14,17,14,16,15},
	{30,5,5,31,5,5,5},{0,0,11,20,31,5,26},{12,18,2,15,2,2,31},{7,9,7,9,29,9,25},{0,14,31,31,31,14,0},{0,14,17,17,17,14,0},{0,4,14,31,14,4,0},{0,4,10,17,10,4,0},{4,4,4,0,4,4,4},{30,1,1,1,30,4,2},{0,16,24,20,18,17,31},{8,4,2,4,8,0,31},{2,4,8,4,2,0,31},{16,16,20,18,31,2,4},{4,14,21,4,4,4,4},{4,4,4,4,21,14,4},
	{0,0,0,0,0,0,0},{0,0,0,0,7,5,7},{28,4,4,4,0,0,0},{0,0,0,4,4,4,7},{0,0,0,0,1,2,4},{0,0,0,6,6,0,0},{0,31,16,31,16,8,4},{0,0,31,16,12,4,2},{0,0,8,4,6,5,4},{0,0,4,31,17,16,12},{0,0,0,31,4,4,31},{0,0,8,31,12,10,9},{0,0,2,31,18,10,2},{0,0,0,14,8,8,31},{0,0,15,8,15,8,15},{0,0,0,21,21,16,12},
	{0,0,0,31,0,0,0},{31,16,20,12,4,4,2},{16,8,4,6,5,4,4},{4,31,17,17,16,8,4},{0,31,4,4,4,4,31},{8,31,8,12,10,9,8},{2,31,18,18,18,18,9},{4,31,4,31,4,4,4},{0,30,18,17,16,8,6},{2,30,9,8,8,8,4},{0,31,16,16,16,16,31},{10,31,10,10,8,4,2},{0,3,16,19,16,8,7},{0,31,16,8,4,10,17},{2,31,18,10,2,2,28},{0,17,17,18,16,8,6},
	{0,30,18,21,24,8,6},{8,7,4,31,4,4,2},{0,21,21,21,16,8,4},{14,0,31,4,4,4,2},{2,2,2,6,10,2,2},{4,4,31,4,4,2,1},{0,14,0,0,0,0,31},{0,31,16,10,4,10,1},{4,31,8,4,14,21,4},{8,8,8,8,8,4,2},{0,4,8,17,17,17,17},{1,1,31,1,1,1,30},{0,31,16,16,16,8,6},{0,2,5,8,16,16,0},{4,31,4,4,21,21,4},{0,31,16,16,10,4,8},
	{0,14,0,14,0,14,16},{0,4,2,1,17,21,16},{0,16,16,10,4,10,1},{0,31,2,31,2,2,28},{2,2,31,18,10,2,2},{0,14,8,8,8,8,31},{0,31,16,31,16,16,31},{14,0,31,16,16,8,4},{9,9,9,9,8,4,2},{0,4,5,5,21,21,13},{0,1,1,17,9,5,3},{0,31,17,17,17,17,31},{0,31,17,17,16,8,4},{0,3,0,16,16,8,7},{4,9,2,0,0,0,0},{7,5,7,0,0,0,0},
	{0,0,18,21,9,9,22},{10,0,14,16,30,17,30},{0,14,17,15,16,15,1},{0,0,14,1,6,17,14},{0,17,17,25,23,1,1},{0,0,30,5,9,17,14},{0,12,18,17,15,1,1},{0,0,30,17,30,16,14},{0,0,28,4,4,5,2},{8,11,8,0,0,0,0},{8,0,12,8,8,9,6},{5,2,5,0,0,0,0},{0,4,14,5,21,14,4},{2,2,7,2,7,2,30},{14,0,13,19,17,17,17},{10,0,14,17,17,17,14},
	{0,13,19,17,15,1,1},{0,22,25,17,30,16,16},{0,14,17,31,17,17,14},{0,0,0,26,21,11,0},{0,0,14,17,17,10,27},{10,0,17,17,17,25,22},{31,1,2,4,2,1,31},{0,0,31,10,10,10,25},{31,0,17,10,4,10,17},{0,0,17,17,30,16,14},{0,16,15,4,31,4,4},{0,0,31,2,30,18,17},{0,0,31,21,31,17,17},{0,4,0,31,0,4,0},{0,0,0,0,0,0,0},{31,31,31,31,31,31,31}
};
