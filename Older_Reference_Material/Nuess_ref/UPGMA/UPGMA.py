import sys
import copy
import re

# Globals used in a desperate attempt to save time bumbling with locality.
optimal_trees = []
current_mapping = {}
current_estimates = {}

# Calculates the distance matrix
def build_initial_matrix ( input_filename ) :
	print ("...BIMX :...entering build_initial_matrix()....")
	print ("...BIMX :...opening \"" + input_filename + "\"...")
	with open ( input_filename ,'r' ) as input_file :
		data = input_file.read () 
	print ("...BIMX :...converting file_input to a string...")
	print (data)
	print ("...BIMX :...replacing all instances of \'>\' file_input to a string...")
	new = data.replace (">","")
	print (new)
	print ("...BIMX :...splitting string ...")
	newer = new.split ("\n")
	print ("...BIMX :...converting into sequences...")
	seq = [newer[::2],newer[1::2]]
	print (newer)
	print ("...BIMX :...calculating distances ...")
	distances = []
	number_or_seq = len(seq[0])
	for row in range(-1,number_or_seq) :
			for col in range(-1,number_or_seq) :
				if row == -1 and col == -1 :
					print ("...BIMX :......1st Case : calculating entry ["+str(row)+"]["+str(col)+"]...")
					distances.append(["-"])
				elif row == -1 :
					print ("...BIMX :......Col Title Case : calculating entry ["+str(row)+"]["+str(col)+"]...")
					distances[0].append(seq[0][col])
				elif col == -1 :
					print ("...BIMX :......Row Title Case : calculating entry ["+str(row)+"]["+str(col)+"]...")
					distances.append([seq[0][row]])
				else :	
					print ("...BIMX :......Distance Case : calculating entry ["+str(row)+"]["+str(col)+"]...")
					print ("...BIMX :.........calculating distance between S"+str(row)+" and S"+str(col)+"...")
					distances[row+1].append(float(sum(1 for i,j in zip(seq[1][row], seq[1][col]) if i != j)))
	print (distances)
	input_file.close ( )
	all_data = { "sequences" : seq , "distance_matrix" : distances }
	return all_data

# Assembles the string that represents the tree, struggled the most here as I'm unfamilar with regular expressions.
def assemble_tree () :
	global current_mapping, current_estimates
	current_tree = ""
	temp = current_mapping.items()
	current_mapping = sorted(temp, key = lambda s: 2)
	temp = current_estimates.items()
	current_estimates = sorted(temp, key = lambda s: len(s[0]))
	print(str(current_estimates))
	for node in range(0,len(current_mapping)) :
		print ("These nodes occur in this order : " + str(current_mapping[node]))
		print ("These nodes occur in this order : " + str(current_estimates[node]))
		
		print ("These nodes occur in this order : " + str(current_estimates[node][1][1]))
		print ("These nodes occur in this order : " + str(current_mapping[node][1][1]))
		for children in range (0,2) :
			print ("Current Tree 1 = "+current_tree)
			midling = False 
			if current_mapping[node][1][children] in current_tree :
				print ("Found midling ancestor \""+current_mapping[node][1][children]+"\"")
				ancestor = re.search ( current_mapping[node][1][children]+'\(.*?\)\(.*?\)',current_tree)
				ancestor = ancestor.group()
				print ("isolated child ancestor = \t\t"+ancestor)
				ancestor = re.search ( '\(.*?\)\(.*?\)',ancestor)
				ancestor = ancestor.group()
				print ("removed the tag, leaving just descendents = \t"+ancestor)
				print ("targeting this substring = \t\t"+ancestor)
				print ("...while the string = \t\t"+current_tree)
				current_tree = current_tree.replace(	current_mapping[node][1][children]	,
														"" )
				current_tree = current_tree.replace(	ancestor ,
														current_mapping[node][1][children]+":"+str(current_estimates[node][1][children]) + ancestor)
				print ("replaced => "+current_tree)
				midling = True
			else :
				print ("Found leaf")
				current_tree += "("+current_mapping[node][1][children]+":"+str(current_estimates[node][1][children])+")"
			print ("Current Tree 2 = "+current_tree)
		if midling :
			current_tree = current_mapping[node][0] + "(" +  current_tree + ")"
		else :
			current_tree = current_mapping[node][0] + current_tree 

		print ("Current Tree 3 = "+current_tree)
	optimal_trees.append (current_tree)
	#print (current_mapping)
	#print (current_estimates)
	current_mapping = {}
	current_estimates = {}

	return

# Makes matrices in console output easier to read
def print_matrix ( matrix ) :
	for row in range (0,len(matrix)) :
		print ( "\t"+str(matrix[row]))
	return

# The recursive method for calculating each possible optimal tree. Definately needs to be broken into other methods. Currently does not recur.
def cluster ( distance_matrix , parent ) :
	print ("\n...CLST :...entering cluster \""+parent+"\"....")

	# Find the lowest distance score present in the matrix.
	lowest_distance = sys.maxsize
	print ("...CLST :...finding lowest entries (\""+parent+"\")....")
	for row in range (1,len(distance_matrix)-1) :
		print ("...CLST :...... row "+str(row)+"....")
		lowest_in_row = min ( distance_matrix[row][row+1:len(distance_matrix):] )
		if lowest_in_row == "-" :
			lowest_in_row = sys.maxsize
		print ("...CLST :......current lowest entry found = "+str(lowest_in_row)+"/"+str(lowest_distance)+"....")
		if lowest_in_row < lowest_distance :
			print ("...CLST :......lowest found in this row....")
			lowest_distance = lowest_in_row 
	print ("...CLST :...lowest found = "+str(lowest_distance)+"....\n")

	# Cluster() Base Case (i.e. top of the tree reached)
	if lowest_distance is sys.maxsize :
		print ("...CLST :...BASE CASE FOUND....\n")
		return assemble_tree ()

	# Find all the closet pairs present (in the case of multiple optimal trees).
	print ("...CLST :...finding closest pairs....")
	closest_pair = []
	for row in range (1,len(distance_matrix)) :
		for col in range (row+1,len(distance_matrix[row])) :
			print ("...CLST :......analyzing ["+str(row)+"]["+str(col)+"] ("+str(distance_matrix[row][col])+")....")
			if distance_matrix[row][col] is lowest_distance :
				
				closest_pair.append ([row,col])
	print ("...CLST :...closest pairs found ="+str(closest_pair)+"....\n")

	# Negate the old rows and create a new row 
	print ("...CLST :...forming new row....")
	for optimal in range(0 ,len(closest_pair) ) :
		A = closest_pair[optimal][0]
		B = closest_pair[optimal][1]
		print ("...CLST :......for pair ["+str(A)+","+str(B)+"]....")
		UA = copy.deepcopy(distance_matrix)
		new_row = ["S"+str(distance_matrix[A][0][1:]) + str(UA[B][0][1:]) ]
		print ("...CLST :......created new cluster, dubbed \""+str(new_row[0])+"\"....")
		print_matrix (UA)

		print ("...CLST :......calculating distances along row "+str(A)+" and "+str(B)+"....")
		print_matrix (UA)
		print ("\t\t==>")
		for col in range (1,len(distance_matrix[0])) :
			new_distance = round(((distance_matrix[A][col] + distance_matrix[B][col])/2),1) 
			new_row.append ( new_distance )
		UA.append ( new_row )
		print_matrix (UA)

		print ("...CLST :......purging columns "+str(A)+" and "+str(B)+"....")
		for col in range (1,len(distance_matrix[0])) :
			UA[A][col] = float('inf')
			UA[B][col] = float('inf')
		print_matrix (UA)

		print ("...CLST :......purging rows "+str(A)+" and "+str(B)+" while adding new values....")
		new_row_count = len(distance_matrix)
		for row in range (0,len(distance_matrix)+1) :
				print ("...CLST :.........negating entries "+str(UA[row][A])+" and "+str(UA[row][B])+" ....")
				if row > 1 : 
					UA[row][A] = float('inf')
					UA[row][B] = float('inf')
				if row is new_row_count :
					new_row.append (0.0)
				else :
					if row is A or row is B :
						UA[row].append (float('inf'))
					else :
						UA[row].append (UA[new_row_count][row])
		print_matrix (UA) 
		print ("...CLST :......estimating branch length....\n")
		branch_length_estimate = lowest_distance/2
		parent = UA[0][new_row_count]
		right_leaf = "("+UA[0][B]+":"+str(branch_length_estimate)+")"
		left_leaf = "("+UA[0][A]+":"+str(branch_length_estimate)+")"
		print ("...CLST :......index ["+UA[0][A]+","+str(B)+"|"+UA[0][B]+","+str(B)+"]....\n")
		print ("...CLST :......current_mapping ["+str(parent)+"]....\n")
		current_mapping [ parent ] = [ UA[0][A] , UA[0][B] ]
		current_estimates [ parent ] = [ branch_length_estimate , branch_length_estimate ]
		print (current_mapping [parent])
		for child in range (0, len(current_mapping [UA[0][new_row_count]])) :
			if len(current_mapping [ parent ] [ child ] ) > 2 :
				print ( current_mapping [ parent ] [ child ] )
				current_estimates [ parent ] [ child ] -= max ( current_estimates [ current_mapping [ parent ] [ child ] ] )
				current_estimates [ parent ] [ child ] = round ( current_estimates [ parent ] [ child ] , 1)

		print ("...CLST :......ascending up tree dist....\n")
		cluster ( UA , UA[0][new_row_count] )



	# update distance_matrix (A,B)
	# make a list of the shortest distances
	# while list is populated, recursively construct
	# cluster ( distance_matrix ) 

	return ;

# Formats the distance matrix in o.1
def format_distance_matrix_output ( data ) :
	formatted = ""
	for row in range (0,len(data)) :
		for col in range (0,len(data)) :
			if row > 0 and col > 0 :
				formatted += str(int(data[row][col]))+"\t"
			else :
				formatted += str(data[row][col])+"\t"
		formatted += "\n"
	return formatted

# master method for conducting a single iteration of UPGMA, also creates amd assembles the output files
def UPGMA ( input_filename ) :
	print ("...UPGMA : entering UPGMA()....")
	with open ( "UPGMA_results_for_("+input_filename+").txt" ,'w' ) as output_file :
		initial_data = build_initial_matrix ( input_filename )
		print ("...UPGMA : checking data....")
		output_file.write( "3.o1:\n" )
		output_file.write( format_distance_matrix_output(initial_data["distance_matrix"]))		
		print ("...UPGMA : conducting clustering....")
		cluster ( initial_data["distance_matrix"] , "")
		output_file.write( "\n" )
		output_file.write( "\n3.o2:\n" )
		output_file.write( optimal_trees[0] )
		output_file.write( "\n" )
		output_file.write( "\n3.o3:\n" )
		if len(optimal_trees) > 1 :
			output_file.write( "YES" )
		else :
			output_file.write( "NO" )
		output_file.write( "\n" )
		output_file.write( "\n3.o4:\n" )
		for tree in range(1,len(optimal_trees)) :
			output_file.write( str(optimal_trees[tree]) )
		output_file.close()
	print ("")

# entry point, also creates amd assembles the output files
for group in range (1,len(sys.argv)) :
	UPGMA ( sys.argv[group] )
	optimal_trees = []



