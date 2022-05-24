import sys

HMM	 = {	'emission'	: 					('A','T','C','G') ,
			'state' : 						('H','L') ,
			'starting_probabilty' : 		{ 'H':0.5,'L':0.5 } ,
			'TP' : 							{ 'H': {'H':0.5,'L':0.5} ,
											  'L': {'H':0.4,'L':0.6} } ,
			'EM' :							{ 'H': {'A':0.2,'T':0.2,'C':0.3,'G':0.3} ,
											  'L': {'A':0.3,'T':0.3,'C':0.2,'G':0.2} } }
'''
Uses the forward algorithim to calculate the probability of the given emitted sequence.
Returns a table of probabilites for each hidden state given the emitted one and a float 
containing the overall probability 
'''
def forward ( sequence ) :
	print ("%...FRWD :......conducting forward algorithim...")
	table = []
	for emission in enumerate (sequence) :
		print ("%...FRWD :.........for emission "+str(emission[0])+" (\'"+emission[1]+"\'')...")
		table.append ({})
		for state in HMM['state'] :
			print ("%...FRWD :............for state \'"+str(state)+"\'...")
			if emission[0] is 0 :
				previous_sum = HMM['starting_probabilty'][state]
				print ("%...FRWD :...............calculating a base case ("+str(previous_sum)+")...")
			else :
				# print ( ".........variable \'\' = " +str()+ " ("+str(type())+")...")
				for previous_state in HMM['state'] :
					print ("%...BKWD :...............caluclating: (" + str(HMM['TP'][previous_state][state]) +"*"+str(table[emission[0]-1][previous_state])+")" )
				previous_sum = sum ( table[emission[0]-1][previous_state] * HMM['TP'][previous_state][state] for previous_state in HMM['state'] )
				print ("%...FRWD :...............calculating a midling case("+str(previous_sum)+")...")
			table[emission[0]][state]	 = HMM['EM'][state][emission[1]] * previous_sum
			print ("%...FRWD :...............adding sum to table, ["+str(emission[0])+"]["+state+"] ("+str(table[emission[0]][state])+")...")
			#print ("%...FRWD :............current table:")
			#print ("\t"+str(table))
	print ("%...FRWD :......results of forward:")
	print(str(table)+"\n")
	probability = sum ( table[-1][state] for state in HMM['state'] )
	print ("%...FRWD :......probability of this emission given the HMM : " + str(probability) + "...")
	table.append(probability)
	return table

'''
Uses the backward algorithim to calculate the probability of the given emitted sequence.
Returns a table of probabilites for each hidden state given the emitted one.
'''
def backward ( sequence ) :
	print ("%...BKWD :......conducting backward algorithim...")
	table = []
	sequence = 	sequence[::-1]
	sequential_list = list(sequence)
	print ( sequential_list )
	for emission in enumerate(sequential_list):
		print ("%...BKWD :.........for emission "+str(emission[0])+" (\'"+emission[1]+"\'')...")
		table.append ({})
		for state in HMM['state'] :
			if emission[0] is 0 :
				table[emission[0]].update ( { state : 1 } )
				print ("%...BKWD :...............calculating a base case (1)...")
			else :
				# b_curr[st] 	= 	sum(trans_prob [st] [l] 			* 
				#					emm_prob [l] [observation_i_plus] 	* 
				#					b_prev[l] 
				#															for l in states
				#)
				for previous_state in HMM['state'] :	
					print ("%...BKWD :...............caluclating: (" 	+ str(		HMM['TP'][state][previous_state]						) + "*" 
																		+ str(		HMM['EM'][previous_state][sequence[emission[0]-1]]		) + "*" 
																		+ str(		table[emission[0]-1][previous_state])					+ ")"  )
				table[emission[0]].update ( { state : sum (							HMM['TP'][state][previous_state] 						* 
																					HMM['EM'][previous_state][sequence[emission[0]-1]] 		* 
																					table[emission[0]-1][previous_state] 
																																			for previous_state in HMM['state'])} )
				print ("%...BKWD :...............calculating a midling case("+str(table[emission[0]])+")...")
	table.reverse ()

	probability = sum ( table[0][state] for state in HMM['state'] )
	print ("%...BKWD :......probability of this emission given the HMM : " + str(probability) + "...")
	print ("%...BKWD :......results of backward:")
	print(str(table)+"\n")
	return table

'''
Uses the viterbi algorithim to calculate the most probable path of hidden states of the 
given emitted ones.
Returns :
	- The probability of the most probable path.
	- A parsed string containing table of probabilites for each most probable hidden state given the emitted one.
	- The most probable path
'''
def viterbi ( sequence, ) :
	print ("%...VTRB :......conducting viterbi algorithim...")
	results = []
	Table = [{}]
	multiple_optimal_paths = False

	# Calculating First Column in Viterbi Table
	for possible_state in HMM['state'] :
		Table[0][possible_state] = [ HMM['starting_probabilty'][possible_state] * HMM['EM'][possible_state][sequence[0]] , None ] 
		print (Table[0][possible_state])
	print (Table)

	# Iterating Column by Column over the Viterbi Table
	for emission in range ( 1 , len(sequence) ) :
		print ("%...VTRB :..........for observed emission "+str(emission)+"...")
		Table.append ({})
		for possible_state in HMM['state'] :
			print ("%...VTRB :.............calculating possible state \'"+str(possible_state)+"\'...")
			maximum_TP 	= 	Table[emission-1][HMM['state'][0]][0] * HMM['TP'][HMM['state'][0]][possible_state]
			previous_state_selected 		= 	HMM ['state'][0]
			for previous_state in HMM['state'][1:] :
				TP 		=	Table[emission-1][previous_state][0] * HMM['TP'][previous_state][possible_state]
				if TP > maximum_TP :
					maximum_TP 	= 	TP
					previous_state_selected			=	previous_state
				elif TP == maximum_TP :
					multiple_optimal_paths = True 

			maximum_probability = maximum_TP * HMM['EM'][possible_state][sequence[emission]]
			Table[emission][possible_state] = [ maximum_probability , previous_state_selected ]
			
		print (Table[emission][possible_state])

	print (str(Table))

	# For 4o.4, Tally the Overall Probability of the This Path
	maximum_probability = max ( entry[0] for entry in Table[-1].values() )
	results.append ( maximum_probability )
	print ("%...VTRB :..........final probaility = "+str(results[0])+"...")
	print ("\t"+str(Table))
	print ("\t"+str(Table[-1]))

	# For 4o.2, Parse the Viterbi Table
	rows = ["-\t\t0\t\t","0\t\t1\t\t","H\t\t0\t\t","L\t\t0\t\t"]
	for column in range (1,len(Table)):
		rows[0] += (sequence[column]+"\t\t")
		rows[1] += ('0'+"\t\t")
		rows[2] += (str("{:.2e}".format(Table[column]['H'][0]))+"\t")
		rows[3] += (str("{:.2e}".format(Table[column]['L'][0]))+"\t")
	parsed = ''.join([row+"\n" for row in rows])
	results.append (parsed)
	print ("%...VTRB :..........parsed viterbi table = ")
	print("\t"+str(results[1]))

	# For 4o.3, Find the State Containing the Maximum Probability
	most_probable_path = ""
	previous = None
	for state, probability in Table[-1].items() :
		print ("%...VTRB :.............backtracking to : ( "+str(state)+" , "+str(probability)+" )...")
		if probability[0] == maximum_probability :
			previous = state
			break

	# Traceback to through List to Assemble the Most Probable State Path in String Format
	for state in range(len(Table) - 2, -1, -1) :
		print ("%...VTRB :.............backtracking to : ( "+str(state)+" )...")
		most_probable_path += Table[state + 1][previous][1]
		previous = Table[state + 1][previous][1]
		print ("%...VTRB :.............backtracking to : ( "+str(state)+" : "+most_probable_path+" ("+previous+") )...")
	most_probable_path = most_probable_path[::-1]
	results.append (most_probable_path)

	# For 4o.5, Report the discovery of multiple most probable paths
	results.append (multiple_optimal_paths)

	print ("%...VTRB :..........most probable path = "+results[2]+"...")
	print ("%...VTRB :..........final results for conducting viterbi...")
	print ("\t"+str(results))

	return results

''' 
Calculates the posterior probabilities for each emitted state within a given sequence using values from both the forward and . 
Returns both the probability of the emiited model found from conduct the forward algorithim and the posterier probabilities at 
a specific index (in the case of this assignment, strictly the 4th). 
'''
def posterior_probability ( sequence , index ) :
	results = []
	print ("%...CPST :......running both forward and backward algorithims...")
	forward_likelyhood = forward ( sequence )
	backward_likelyhood = backward ( sequence )
	
	forward_probability = forward_likelyhood[len(forward_likelyhood)-1]
	del forward_likelyhood [len(forward_likelyhood)-1]
	print ("%...CPST :......calculating posterior probability...")
	for emission in range (0,len(sequence)) :
		results.append ( {state : ((forward_likelyhood[emission][state] * backward_likelyhood[emission][state]) / forward_probability) for state in HMM['state']} )
	print ("%...CPST :.........resulting posterior values:")
	print (str(results))
	return [forward_probability,results[index-1]]

''' 
Iterates over every sequence in the input file, conducting the operations specified in Assignment 4's documentation.
'''
def for_assignment_4 ( input_filename ) :
	print ("\n\n%...FAS4 :...processing algorithims for assignment 4 using sequences in \'"+input_filename+"\'...")
	sequences = parse_input ( input_filename )
	for sequence in sequences :
		print ("\n%...FAS4 :...for sequence \'"+sequence+"\'...")
		results = []
		results.append ( viterbi ( sequence ) )
		#results.append ( forward ( sequence ) )
		results.append ( posterior_probability ( sequence , 4 ) )
		print ("%...FAS4 :...results obtained:")
		print ("\t"+str(results))		
		output_results ( results , sequence )
	print ("\n\n")

''' 
A somewhat sloppy way of parsing each sequence in the input file into the program.
'''
def parse_input ( input_filename ) :
	print ("%...PSIN :......parsing input from \'"+input_filename+"\'...")
	sequence = ""
	with open ( input_filename ,'r' ) as input_file :
		data = input_file.read () 
	input_file.close()
	print ("%...PSIN :.........splitting array of sequences...")
	sequences = data.split ("\n")
	del sequences [::2]
	print ("%...PSIN :.........parsed data : \n\t"+str(sequences))
	return sequences

''' 
Constructs each output file as specified in the documentation.
'''
def output_results ( results , output_filename ) :
	print ("%...OUTR :......printing results to \'Results ("+output_filename+").txt\'...")
	with open ( "Results ("+output_filename+").txt" ,'w' ) as output_file :

		#4.o1 | Probability of the Current Emissions, given the HMM (For GGCA => Need 3.84e-3)
		print ("%...OUTR :.........outputing \'4.o1\'("+str(results[1][0])+")....")
		output_file.write( "4.o1:\n" )
		output_file.write( str("{:.2e}".format(results[1][0]))+"\n\n" )

		#4.o2 | The Complete Viterbi Table (Normal Format)
		print ("%...OUTR :.........outputing \'4.o2\'("+str(results[0][1])+")....")
		output_file.write( "4.o2:\n" )
		output_file.write( str(results[0][1])+"\n\n" )

		#4.o3 | Most Probable State Path, given the HMM (Need HHHLLLLLL)
		print ("%...OUTR :.........outputing \'4.o3\'("+str(results[0][2])+")....")
		output_file.write( "4.o3:\n" )
		output_file.write( str(results[0][2])+"\n\n" )

		#4.o4 | Probability of the Most Probable State Path , given this HMM (For GGCACTGAA => Need 4.25e-8)
		print ("%...OUTR :.........outputing \'4.o4\'("+str(results[0][0])+")....")
		output_file.write( "4.o4:\n" )
		output_file.write( str("{:.2e}".format(results[0][0]))+"\n\n" )

		#4.o5 | Are There Multiple Most Probable Paths?
		print ("%...OUTR :.........outputing \'4.o5\'("+str(results[0][3])+")....")
		output_file.write( "4.o5:\n" )
		if results[0][3] :
			output_file.write( "YES\n\n"  )
		else :
			output_file.write( "NO\n\n" )
		

		#4.o6 | Posterior Probability of H and Posterior Probability of L in the 4th Position (For GGCA => need 3.58e-1 \n 6.42e-1)
		print ("%...OUTR :.........outputing \'4.o6\'("+str(results[1][1])+")....")
		output_file.write( "4.o6:\n" )
		for state in HMM['state'] :
			output_file.write( str("{:.2e}".format(results[1][1][state]))+"\n" )	
		output_file.write( "\n" )

		#4.o7 | Report all possible most probable paths.
		print ("%...OUTR :.........outputing \'4.o7\'....")
		output_file.write( "4.o7:\n" )
		output_file.write( str('<INCOMPLETE>')+"\n\n" )

	output_file.close()
	
	return

'''
The program's static entry point.
''' 
for_assignment_4 ( sys.argv[1] ) 