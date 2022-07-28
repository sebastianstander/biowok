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
	for emission in enumerate (sequence) :
		for state in HMM['state'] :
			if emission[0] is 0 :
				previous_sum = HMM['starting_probabilty'][state]
			else :
				previous_sum = sum ( table[emission[0]-1][previous_state] * HMM['TP'][previous_state][state] for previous_state in HMM['state'] )
			table[emission[0]][state] = HMM['EM'][state][emission[1]] * previous_sum
	probability = sum ( table[-1][state] for state in HMM['state'] )
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
def viterbi ( seq, ) :
	print ("%...VTRB :......conducting viterbi algorithim...")
	out = []
	tb = [{}]
	are_n_opt_paths = False

	# Calculating First Column in Viterbi Table
	for state in HMM['state'] :
		Table[0][state] = [ HMM['starting_probabilty'][state] 
                            *   HMM['EM'][state][seq[0]] 
                            ,   None ] 
		print (tb[0][state])
	print (tb)

	# Iterating Column by Column over the Viterbi Table
	for i in range ( 1 , len(seq) ) :
		tb.append ({})
		for state in HMM['state'] :
			maximum_TP = tb[i-1][HMM['state'][0]][0] 
                         * HMM['TP'][HMM['state'][0]][state]
			pr_slct_state = HMM ['state'][0]
			for pr_state in HMM['state'][1:] :
				TP = tb[i-1][pr_state][0] 
                     * HMM['TP'][pr_state][state]
				if (TP > maxTP) :
					maxTP = TP
					pr_slct_state =	pr_state
				elif (TP == maxTP) :
					are_n_opt_paths = True 
			maxProb = maxTP * HMM['EM'][state][seq[i]]
			Table[i][state] = [ maxProb , pr_slct_state ]
	maxProb = max ( x[0] for x in tb[-1].values() )
	out.append ( maxProb )
	x = ["-\t\t0\t\t","0\t\t1\t\t","H\t\t0\t\t","L\t\t0\t\t"]
	for y in range (1,len(tb)):
		x[0] += (seq[y]+"\t\t")
		x[1] += ('0'+"\t\t")
		x[2] += (str("{:.2e}".format(tb[y]['H'][0]))+"\t")
		x[3] += (str("{:.2e}".format(tb[y]['L'][0]))+"\t")
	parsed = ''.join([row+"\n" for row in rows])
	out.append (parsed)
	MP_PATH = ""
	prev = None
	for stt, pr in Table[-1].items() :
		if pr[0] == maxProb :
			prev = state
			break
	for state in range(len(Table) - 2, -1, -1) :
		most_probable_path += Table[state + 1][previous][1]
		previous = Table[state + 1][previous][1]
	most_probable_path = most_probable_path[::-1]
	results.append (most_probable_path)
	results.append (multiple_optimal_paths)
	return results

def posterior_probability ( sequence , index ) :
	results = []
	forward_likelyhood = forward ( sequence )
	backward_likelyhood = backward ( sequence )
	forward_probability = forward_likelyhood[len(forward_likelyhood)-1]
	del forward_likelyhood [len(forward_likelyhood)-1]
	for emission in range (0,len(sequence)) :
		results.append ( {state : ((forward_likelyhood[emission][state] * backward_likelyhood[emission][state]) / forward_probability) for state in HMM['state']} )
	return [forward_probability,results[index-1]]

def for_assignment_4 ( input_filename ) :
	sequences = parse_input ( input_filename )
	for sequence in sequences :
		results = []
		results.append ( viterbi ( sequence ) )
		#results.append ( forward ( sequence ) )
		results.append ( posterior_probability ( sequence , 4 ) )
		output_results ( results , sequence )

def parse_input ( input_filename ) :
	sequence = ""
	with open ( input_filename ,'r' ) as input_file :
		data = input_file.read () 
	input_file.close()
	sequences = data.split ("\n")
	del sequences [::2]
	return sequences

def output_results ( results , output_filename ) :
	with open ( "Results ("+output_filename+").txt" ,'w' ) as output_file :
		output_file.write( "4.o1:\n" )
		output_file.write( str("{:.2e}".format(results[1][0]))+"\n\n" )
		output_file.write( "4.o2:\n" )
		output_file.write( str(results[0][1])+"\n\n" )
		output_file.write( "4.o3:\n" )
		output_file.write( str(results[0][2])+"\n\n" )
		output_file.write( "4.o4:\n" )
		output_file.write( str("{:.2e}".format(results[0][0]))+"\n\n" )
		output_file.write( "4.o5:\n" )
		if results[0][3] :
			output_file.write( "YES\n\n"  )
		else :
			output_file.write( "NO\n\n" )
		output_file.write( "4.o6:\n" )
		for state in HMM['state'] :
			output_file.write( str("{:.2e}".format(results[1][1][state]))+"\n" )	
		output_file.write( "\n" )
		output_file.write( "4.o7:\n" )
		output_file.write( str('<INCOMPLETE>')+"\n\n" )
	output_file.close()
	return
for_assignment_4 ( sys.argv[1] ) 



X[x1...xt]              // Path
xn in S[s1...sk]        // Sequence of Possible States, State-Space
Y[y1...yt]              // State-Generated Observations, Observation-Space
A                       // Transition Matrix
B                       // Emission Matrix
yn in O[o1...oN] ,, N = # of possible observation in obs space O

build : 
    n = k*t 
    tb[n*2];
    for(int i=0;i<n;i++){
        tb[i,j-1] = 
        tb[n+i,j-1] = 
        for(int st=0;st<n;st++){
            tb[i]   max(    tb[i,j-1] ,
                            tb[st,j-1] * transition(st) * emit())
            tb[n+i] argmax( tb[n+i,j-1] ,
                            tb[n+i,j-1] * transition(st) * emit())
        }
    }



# probability == p. Tm: the transition matrix. Em: the emission matrix.
function viterbi(O, S, Π, Tm, Em): best_path
    trellis ← matrix(length(S), length(O))  # To hold p. of each state given each observation.
    pointers ← matrix(length(S), length(O)) # To hold backpointer to best prior state
    # Determine each hidden state's p. at time 0...
    for s in range(length(S)):
        trellis[s, 0] ← Π[s] * Em[s, O[0]]
    # ...and afterwards, tracking each state's most likely prior state, k.
    for o in range(1, length(O)):
        for s in range(length(S)):
            k ← argmax(k in trellis[k, o-1] * Tm[k, s] * Em[s, o])
            trellis[s, o] ← trellis[k, o-1] * Tm[k, s] * Em[s, o]
            pointers[s, o] ← k
    best_path ← list()
    k ← argmax( k in trellis[k, length(O)-1] )   # Find k of best final state
    for o in range(length(O)-1, -1, -1):  # Backtrack from last observation.
        best_path.insert(0, S[k])         # Insert previous state on most likely path
        k ← pointers[k, o]                # Use backpointer to find best previous state
    return best_path




//      ob0       ob1       ob2     ob3     ob4
//      st0  st1  st2  st3  st4 st5 st6 st7 st8 st9


st0 = 