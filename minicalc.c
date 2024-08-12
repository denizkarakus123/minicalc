#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

//function to find the gcd of two numbers from https://www.geeksforgeeks.org/program-to-find-gcd-or-hcf-of-two-numbers 
//based on euclidian algorithm for gcd of two numbers where we subtract the smaller one from the bigger one recursively
//until one of the numbers is zero and we return the other number
int gcd(int a, int b){
	if (b == 0){
		return a;
	}
	//here we're basically doing the same thing as explained above, except we're optimizing it by using modulo
	return gcd(b, a%b);
}




bool areAnagrams(char *word_1, char *word_2) {
	//initialize count array to hold index of all the letters of the alphabet
	int count[26] = {0}; 
    	int i;
    	
	//iterate through the word until we reach the end character
    	for (i = 0; word_1[i] != '\0'; i++) {
		//subtract 'a' from the letter because we're using ASCII values 
		//add one to count at the index where the letter occurs 
        	count[word_1[i] - 'a']++;
    	}
    	for (i = 0; word_2[i] != '\0'; i++) {
		//here subtract one from the indez where the letter occurs because if both letters
		//have the same letters the value at that index should be zero
        	count[word_2[i] - 'a']--;
    	}
    	for (i = 0; i < 26; i++) {
        	if (count[i] != 0) {
			//this means one word had a different letter than the other
            		return false;
        	}
    	}
    	return true;
}

bool allLowerCase(char *str) {
    	for (int i = 0; str[i] != '\0'; i++) {
		//ASCII value has to be between lowercase letters of alphabet
        	if (str[i] < 'a' || str[i] > 'z') {
            		return false; 
		}
    	}
    	return true; 
}



int main(int argc, char *argv[]){
	if (argc<2){
		fprintf(stderr, "Error: At least one command-line argument is required.\n");
		return 1;
	}


	char *operation = argv[1];
	char *endptr; //to be used to detect error four
	if (strcmp(operation, "+") == 0){
		if (argc != 4 ){
			fprintf(stderr, "Error: Addition requires exactly two arguments.\n");
			return 3;
		}
		else{

			long num_1 = strtol(argv[2], &endptr, 10);
			//if successfully converted to a long, then the end pointer should be pointing to '\0'
			if (*endptr != '\0'){
				fprintf(stderr, "Error: operands must be of correct type.\n");
				return 4;
			}
			long num_2 = strtol(argv[3], &endptr, 10);
			//if successfully converted to a long, then the end pointer should be pointing to '\0'
			if (*endptr != '\0'){
                                fprintf(stderr, "Error: operands must be of correct type.\n");
                                return 4;
                        }

			printf("%ld\n", num_1 + num_2);
		}
	}


	else if (strcmp(operation, "gcd") == 0){
		if (argc < 4){
			fprintf(stderr, "Error: GCD operation requires at least two arguments.\n");
			return 3;
		}
		else{
			long result = strtol(argv[2], &endptr, 10);
			if (*endptr != '\0'){
                                fprintf(stderr, "Error: operands must be of correct type.\n");
                                return 4;
                        }
			if (result <= 0){
				fprintf(stderr, "Error: All inputs for GCD must be greater than zero.\n");
				return 7;
			}
			result = (int)result;
			//iterate through each command line argument to see if they're positive numbers
			for (int i = 3; i<argc; i++){
				int num = strtol(argv[i], &endptr, 10);
				if (*endptr != '\0'){
                                	fprintf(stderr, "Error: operands must be of correct type.\n");
                                	return 4;
                        	}
				if (num <= 0){
					fprintf(stderr, "Error: All inputs for GCD must be greater than zero.\n");
					return 7;
				}
				num = (int)num;
				//use the gcd of the last two numbers as the new number with the next command line arg
				result = gcd(result, num);
			}

			printf("%ld\n", result);
		}
	}



	else if (strcmp(operation, "sqrt") == 0){
		if (argc != 3){
			fprintf(stderr, "Error: sqrt operation needs exactly one argument.\n");
			return 3;
		}
		
		double num = strtod(argv[2], &endptr);
		if (*endptr != '\0'){
                                fprintf(stderr, "Error: operands must be of correct type.\n");
                                return 4;
                        }

		if (num < 0){
			fprintf(stderr, "Error: Square root requires a nonnegative argument.\n");
			return 5;
		}

		else{
			double squareRoot = sqrt(num);
			printf("%f\n", squareRoot);
		}
	}

	else if (strcmp(operation, "anagram") == 0){
		if (argc != 4){
			fprintf(stderr, "Error: Anagram requires exactly two arguments.\n");
			return 3;
		}
		if (!allLowerCase(argv[2]) || !allLowerCase(argv[3])){
			fprintf(stderr, "Error: Anagram inputs must consist only of lowercase letters.\n");
			return 6;
		}


		if (areAnagrams(argv[2], argv[3])) {
            		printf("true\n");
        	} 
		else {
            		printf("false\n");
        	}
	}
	else{
		fprintf(stderr, "Error: The first command-line argument must specify one of the allowed operations.\n");
		return 2;
	}

	return 0;
}
