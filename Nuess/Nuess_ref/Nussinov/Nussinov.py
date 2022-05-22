import sys 

minimum_loop_length = 3
unpaired_in_loop_penalty = 0.1
AUG_pairing_bonus = -2
CG_pairing_bonus = -3
minimal_structures = []
AUG_parings = [ ('A','U') , ('U','A') , ('U','G') , ('G','U') ]
CG_parings = [ ('G','C') , ('C','G') ]
current_MRE = 0
sequence = []
L = 0

def calculate_pairing_cost (iA,iB) :
	pair = ( sequence[iA] , sequence[iB] )
	if pair in AUG_parings :
		return -2
	elif pair in CG_parings :
		return -3
	return 0

def isolate_selected_pair (iA,iB) :
    copy = list(sequence)
    for base in range(L) :
        if not base == iA  and not base == iB :
       		copy[base] = '_'
    return "".join(copy)

def get_minimum_energy (iA,iB) :
	global multiple_detector, multiple_count
	if iA >= iB-minimum_loop_length :
		return 0 
	else :
		print ("%...GOPT :...START CASE <"+str(iA)+","+str(iB)+"> (i.e. "+isolate_selected_pair(iA,iB)+")...")
		cases = [0]
		
		print ("%...GOPT :...calculating case 2 : Unpaired Vertical Step... ")
		cases.append ( get_minimum_energy (iA+1,iB) )
		print ("%...GOPT :...case 2 = "+str(cases[1])+" ... ")

		print ("%...GOPT :...calculating case 1 : Upaired Horizontal Step... ")
		cases.append ( get_minimum_energy (iA,iB-1) )
		print ("%...GOPT :...case 1 = "+str(cases[2])+" ... ")

		print ("%...GOPT :...calculating case 3 : Diagonal Loop Check... ")
		cases.append ( get_minimum_energy (iA+1,iB-1) + calculate_pairing_cost (iA,iB)  + (unpaired_in_loop_penalty*(iB-iA-1)) )

		print ("%...GOPT :...case 3 = "+str(cases[3])+" ... ")
		bifurication = [0]
		for k in range (iA,iB) :
			bifurication.append ( get_minimum_energy (iA,k) + get_minimum_energy (k+1,iB) )
		cases.append ( min (bifurication) )
		minimum = min(cases)

		print ("%...GOPT :...CASE <"+str(iA)+","+str(iB)+"> results = "+str(minimum)+" ... ")
		return minimum
		print ("%...GOPT :...END CASE <"+str(iA)+","+str(iB)+"> (i.e. "+isolate_selected_pair(iA,iB)+") = 0 ...")

def traceback ( SM , iA , iB ) :
	global sequence, L
	structure = []
	stack = [(iA,iB)]
	while len(stack) :
		current = stack.pop()
		jA = current[0]
		jB = current[1]
		print ("%...<"+str(jA)+","+str(jB)+"> ("+str(SM [jA][jB])+" = "+str(SM [jA+1][jB])+")...")
		print ("%...<"+str(jA)+","+str(jB)+"> ("+str(SM [jA][jB])+" = "+str(SM [jA][jB-1])+")...")
		print ("%...<"+str(jA)+","+str(jB)+"> ("+str(SM [jA][jB])+" = "+str((SM [jA+1][jB-1]) + calculate_pairing_cost(jA,jB) + (unpaired_in_loop_penalty*(jB-jA-1)))+")...")
		if jA >= jB :
			print ("%...TRBK :...base case reached...")
			print ("%...TRBK :...END CASE <"+str(jA)+","+str(jB)+"> (i.e. "+isolate_selected_pair(jA,jB)+")...")
			return structure
		
		elif SM [jA][jB] == SM [jA][jB-1]  :
			print ("%...TRBK :...vertical case reached "+str(SM [jA][jB-1])+"...")
			stack.append ( (jA,jB-1) )

		elif SM [jA][jB] == SM [jA+1][jB]  :
			print ("%...TRBK :...horizontal case reached "+str(SM [jA+1][jB])+"...")
			stack.append ( (jA+1,jB) )
	
		elif SM [jA][jB] == SM [jA+1][jB-1] + calculate_pairing_cost(jA,jB) + (unpaired_in_loop_penalty*(jB-jA-1)) :
			print ("%...TRBK :...diagonal case reached "+str(SM [jA+1][jB-1])+"...")
			structure.append ( (jA+1,jB-1) )
			stack.append ( (jA+1,jB-1) )
		
		else :
			for k in range (jA+1,jB-1) :
				if SM [jA][jB] == SM [jA][k-1] + SM [k+1][jB-1] :
					print ("%...TRBK :...bifurication case reached "+str(SM [jA+1][jB])+"...")
					stack.append ( (jA,k) )
					stack.append ( (k+1,jB) )
					break
		print ("%...TRBK :...END CASE <"+str(jA)+","+str(jB)+"> (i.e. "+isolate_selected_pair(jA,jB)+")...")	
	
	return structure	

'''
Was intended to interpret the tracebacked structure,  never got any use.
'''
def tally_energy ( ME_structure ) :
	return tally

def write_structure ( structure ) :
	global sequence
	print ("structure =" + str(structure))
	ME_structure = [ "." for _ in range(L) ]
	for base in structure :
		ME_structure [min(base)] = "("
		ME_structure [max(base)] = ")"
	return "".join( ME_structure )

'''
Lines up the Scoring Matrix to make it more easily readable
'''
def print_matrix ( caption , SM ) :
	print (caption)
	for iA in range(len(SM)) :
		print ("\t"+str(SM[iA]))
	return


'''
Entry Method for the algortim, calls nearly all other methods 
'''
def nussinov ( sequence_string , valid_parings ):
	global sequence, L, multiple_detector, multiple_count
	sequence = list(sequence_string)
	L = len(sequence_string)
	print ("%...NUSS : ...running nussinov algorithim on \""+sequence_string+"\"...")
	SM = [[0 for entry in range(L)] for entry in range(L)]
	print_matrix ("%...NUSS : ...SM intitilaized to : " , SM)
	
	results = []

	print ("%...NUSS : ...running nussinov algorithim on \""+sequence_string+"\"...")

	# Fill SM matrix
	for entry in range (4,L) :
		for iA in range (L-entry) :
			iB = iA + entry
			if iB != iA :
				SM[iA][iB] = get_minimum_energy (iA,iB)

	# Compensate for Null References
	for iA in range (L) :
		for iB in range ( 0 , iA ) :
			SM[iA][iB] = SM[iB][iA]
	
	print_matrix ("%...NUSS : ...SM after nussinov : " , SM)
	structure = traceback ( SM , 0 , L-1 )
	ME_structure = write_structure ( structure )
	print_matrix ("%...NUSS : ...results of traceback : " , SM)
	print ( ME_structure )

	results.append ( [sequence_string,SM[L-1][0],ME_structure] )
	return results

'''
Entry Method for the algortim, calls all of the other methods 
'''
def parse_input ( input_filename ) :
	with open ( input_filename ,'r' ) as input_file :
		data = input_file.read () 
		print ("%...PRIN : ...accessing input file \""+input_filename+"\"...")
	sequences = data.split ("\n")
	del sequences [::2]
	input_file.close()
	return sequences

'''

'''
def output_results ( output_filename, results ) :
	print ("%...OUTR : ....creating output file \""+output_filename+"\"...")
	with open ( "results("+output_filename+").txt" ,'w' ) as output_file :
		print ("%...OUTR : .......outputing 4.o1 ("+str(results[0])+")...")
		output_file.write ("4.o1\n")
		output_file.write (str(results[0][0])+"\n"+str(results[0][1])+"\n"+str(results[0][2]))
		
	output_file.close()
	return -1

def for_assignment_5 ( input_filename ) : 
	print ("%...FAS5 : ....applying specifications for Assignment 5...")
	sequences = parse_input (input_filename)
	valid_parings = [ ('C','G') , ('G','C') , ('A','U') , ('U','A') ]
	for sequence_string in sequences :
		results = nussinov (sequence_string , valid_parings)
		output_results (sequence_string , results)
	return -1

for_assignment_5 ( sys.argv[1] )