Nussinov.py
	Last edited by : Sebastian Stander (V00734252) on 04/11/19

	This program assesses various probabilities to form the output desired
	in the
	assignment 4 specifications of an internally fixed Hidden Markov mMdel given an
	number of sequences containe within a FASTA-format input file.

Design :
	Unfortunately, the program is only somewhat capable of finding the 
	MFE
	The program is also incapable of reporting what multiple most
	probably paths exist.

Input :
	<>.txt
		Holds the FASTA format input necessary to produce the 
		desired input of sequences. 
	
		Each sequence needs to be at least 4 bases in length in order
		to produce the required posterior probability.

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
		produces a seperate output file containing the outputs specified 
		in the Assignment 4 documentation for each FASTA format sequence
		in the input file.

Console Compile/Run Line :
	Using python 3.6.4 : 
		python3.6 HMM.py <input_file>.txt 
