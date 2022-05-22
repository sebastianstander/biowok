UPGMA.py
	Last edited by : Sebastian Stander (V00734252) on 28/10/19

	This program is designed to perform UPGMA on a series of FASTA 
	format input text files.

Design :
	Unfortunately, with a sparring amount of time on hand and
	limited knowledge of python 3, my implementation can only 
	calculate a single tree at best.

Input :
	<>.txt
		Holds the FASTA format input nessisary to produce the 
		desired input. Cannot function if all sequences are not
		the same length. 
		
Output :
	UPGMA_results_for_<>.txt 
		produces a plain text file with text output 				
		formatted to match the assignment. It is not
		optimized for order of digits, and will not pass a
		text-based comparison test

Console Compile/Run Line :
	Using python 3.6.4 : 
		python3.6 UPGMA.py <input1>.txt <input
