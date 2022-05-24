Nussinov.py
	Last edited by : Sebastian Stander (V00734252) on 04/11/19

	This program attempts to do nussinov. It was salvaged from a more elaborate
	attempt to do MFold.

Design :
	Unfortunately, the program is very much so incomplete

Input :
	<>.txt
		Holds the FASTA format input necessary to produce the 
		desired input of sequences. 
	
		Since the program 
		iterates in it's entirety over each sequence, the sequences do 
		not need to any additional formatting outside of the FASTA standard to 
		be accepted by the program. 

		Preferably each sequence should read , (using <> as instance specific) :
			> S<number, ignored by the program>
			<sequence string of base A,T,C,G>
		...without any additional spaces, tabs or newline characters
	
		
Output :
	Results<S1>.txt , Results<S2>.txt , ... ,  Results<Sn>.txt 
		produces a separate output file containing the outputs specified 
		in the Assignment 5 documentation for each FASTA format sequence
		in the input file.

Console Compile/Run Line :
	Using python 3.6.4 : 
		python3.6 Nussinov.py <input_file>.txt