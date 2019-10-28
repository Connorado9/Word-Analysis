Word Analysis
By Connor Humiston
6/21/19
Data Structures

File: "HW2_Connor_Humiston"

Purpose: Read through a text file and output the most common words along with their percents, the total unique words in the file, and the total number of words in the file excluding the 50 most common words in the English language.

Description: This C++ program built in Sublime and run through the command line is passed the top n words the user would like to see output, the name of the file needing analyzed, and the file containing the top 50 most common words in the English language. The file then stores the words in an array of WordItem structures that store the word and the number of occurrences of that word in the file. The top n words are outputted along with the number of times the wordItem array was doubled (starting at 10) to accommodate all the words, the number of unique words in the file (excluding ignore words), and the total number of words in the file (excluding ignore words).

Running: The program can be run by typing ./HW2_Connor_Humiston followed the number of output words desired followed by the file name and the 50 most common words file name. 
	For example:
		./HW2_Connor_Humiston 10 Tom_Sawyer.txt ignoreWords.txt

- Note: the file should be preprocessed to exclude punctuation and capital letters
