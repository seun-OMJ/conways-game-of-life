//------------------------------------------
// NAME: OMOJOLA OLUWASEUN
// STUDENT NUMBER:7880480
// COURSE: COMP 2160, SECTION A01
// INSTRUCTOR: MEHDI NIKNAM
// ASSIGNMENT: aasignment 2
//
// REMARKS:this code implements conways game of life
//---------------------------------------------

//--------------------------------------------------------------------------------------------
//HOW THE MAIN CODE WORKS:
//1.) The reads the txt file line by line
//2.) When '*'is the first character of a line it prints out the line and moves to the next line
//3.) The next line is read and the numbers are saved as tokens and converted to 
//integers to reperesemt row and column length
//4.) The code then reads the txt file lines corresponding to the number 
//of rows and saves all lines read in a universe
//5.) Once all the rows have been saved in the universe the universe is then porcessed and checks 
//the changes to be made in each cell by working on a duplicate universe. once all cells
//have been checked the universe is save in a generation struct array and the 
//struct array is checked for a duplicate universe
//---------------------------------------------------------------------------------------------
#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include<string.h>
#define MAX_U 60
#define END_CASE 251

typedef struct Generation{
int arr[MAX_U][MAX_U];//the universe to play the game
int rown;// the length of the row
int coln;// the length of the column
}Gen;
Gen game[END_CASE];//the array to store generations
#define LEN 80
int rowlen;
int collen;
void giveOrTake(int check[MAX_U][MAX_U], int checker,int i, int j);
void checkLife(int orig[MAX_U][MAX_U],int tempo[MAX_U][MAX_U],int rowlen,int collen);
void printArr(int array[MAX_U][MAX_U],int rowlen,int collen);
void copy(int orig[MAX_U][MAX_U],int tempo[MAX_U][MAX_U],int  rowlen,int  collen);
int checkCycle(Gen games[END_CASE], int cycle);
void invariant(int array[MAX_U][MAX_U]);
int main(void){
	char line[LEN];
	Gen arr;
	Gen temp;
	int lineCheck2 = 0;
	int row = 0;
	int store[2];
	int b = 0;
	char *token;
	while(fgets(line, LEN, stdin)!=NULL){
		//reads the file line by line
		if (line[0]=='*'){
			assert(line[0]='*');
//			prints the case header
			row = 0;
			printf("%s", line);
			lineCheck2 = 1;}
			
		else if(lineCheck2==1){
			assert((lineCheck2>0)&&(lineCheck2<2));
		//reads the line with numbers of rows and columns
			lineCheck2++;
			token = strtok(line," ");
			while(token!= NULL){	
				store[b] = atoi(token);
				b++;
				token= strtok(NULL,"");}
			arr.rown = store[0];
			arr.coln = store[1];
			temp.rown = store[0];
			temp.coln = store[1];
			row = 0;
			b = 0;
								
	}
		else if(row<arr.rown){	
//loading the unverse as each line by line from the txt file
		for(int j = 0; j<arr.coln; j++){
			if(line[j]=='X'){
				arr.arr[row][j] = 1;
			}
			else{ 
				arr.arr[row][j] = 0;
			}	}
			row++;
		if(row == arr.rown){
		assert(row==arr.rown);
//once all the lines of rows of the universe have been read in
//this part of the code processes the case
			printf("generation 0:\n");
			printArr(arr.arr,arr.rown,arr.coln);//printing thr original array
			lineCheck2 = 0;//number to check if the rows and column are on that line
			int gen = 0;// number of generations saved
			int ch =0;// result return from function check cycle can halter this value
			while((ch==0) && (gen<END_CASE)){
//this part of the code stores a universe in the generation array, checks rules of the game and checks for a cycle 
				for(int i =0;i<arr.rown; i++){
					for(int j = 0;j<arr.coln;j++){
						game[gen].arr[i][j]=arr.arr[i][j];
}		}
				game[gen].rown = arr.rown;
				game[gen].coln = arr.coln;
				checkLife(arr.arr, temp.arr,arr.rown, arr.coln);
				#ifdef NDEBUG
				ch = checkCycle(game,gen);
				#endif
				gen++;
				if((gen>=END_CASE)||(ch!=0)){
				assert((ch ==1)||(gen>=END_CASE));
//this part of the code prints the universes in the generation array 
					int i = 0;
					#ifdef NDEBUG
					if(gen<10){i=0;}
					else{i=gen-10;}
					#endif
				for(int j=i;j<gen;j++){
					printf("generation: %d\n",j);
					printArr(game[j].arr,game[j].rown,game[j].coln);
				}}
			}}
		}
	}	
	return 0;
}

//-----------------------------------------------------------
//PURPOSE:this function takes a universe and copies it and 
//checks if a cell should be dead or alive
//INPUT PARAMETERS:
//int orig[MAX_U][MAX_U]: the original universe
//int tempo[MAX_U][MAX_U]:the universe to be copied to 
// int rowlen: length of the row
// int collen: length of the column
//OUTPUT PARAMETERS:
// No output parameter
//-------------------------------------------------------------
void checkLife(int orig[MAX_U][MAX_U],int tempo[MAX_U][MAX_U],int rowlen,int collen){
	invariant(orig);
//precondition: check that the arrays have same size meaning that their rows and columns are the same length
			//check that the rows and columns are positive numbers
	assert(sizeof(orig[MAX_U][MAX_U])==sizeof(tempo[MAX_U][MAX_U]));
	assert((rowlen>=0)&&(collen>=0));
	int neighbour; 
	copy(orig, tempo, rowlen, collen);
	for(int i = 0; i< rowlen;i++){
		for(int j = 0; j< collen; j++){
			if((i==0)&&(j==0)){
				neighbour= 0;
				neighbour = orig[i][j+1]+orig[i+1][j]+orig[i+1][j+1];
				giveOrTake(tempo, neighbour, i, j);
			
			}			
			else if((i==0)&&(j==collen-1)){
				neighbour = 0;
				neighbour = orig[i][j-1]+orig[i+1][j-1]+orig[i+1][j];
				giveOrTake(tempo, neighbour,i,j);
				
}
			else if((i!=0)&&(i!= rowlen-1)&&(j!=0)&&(j!=collen-1)){
				neighbour = 0;
				neighbour = orig[i-1][j-1]+orig[i-1][j]+orig[i-1][j+1]+orig[i][j-1]+orig[i][j+1]+orig[i+1][j-1]+orig[i+1][j]+orig[i+1][j+1];
				giveOrTake(tempo, neighbour, i, j);
			
}
			else if((i==rowlen-1)&&(j==0)){
				neighbour = 0;
				neighbour = orig[i-1][j]+orig[i-1][j+1]+orig[i][j+1];
				giveOrTake(tempo, neighbour, i, j);
}
			else if((i==rowlen-1)&&(j==collen-1)){
				neighbour = 0;
				neighbour = orig[i-1][j-1]+orig[i-1][j]+orig[i][j-1];
				giveOrTake(tempo, neighbour, i, j);
}
			else if((i==0)&&(j!=0)&&(j!=collen-1)){
				neighbour = 0;
				neighbour = orig[i][j-1]+orig[i][j+1]+orig[i+1][j-1]+orig[i+1][j]+orig[i+1][j+1];
				giveOrTake(tempo, neighbour, i, j);
} 
			else if((i==rowlen-1)&&(j!=0)&&(j!=collen-1)){
				neighbour = 0;
				neighbour = orig[i][j-1]+orig[i][j+1]+orig[i-1][j-1]+orig[i-1][j]+orig[i-1][j+1];
				giveOrTake(tempo, neighbour, i, j);
}
			else if((j==0)&&(i!=0)&&(i!=rowlen-1)){
				neighbour = 0;
				neighbour = orig[i-1][j]+orig[i+1][j]+orig[i-1][j+1]+orig[i][j+1]+orig[i+1][j+1];
				giveOrTake(tempo, neighbour, i, j);
}
			else{
				neighbour = 0;
				neighbour = orig[i-1][j]+orig[i+1][j]+orig[i-1][j-1]+orig[i][j-1]+orig[i+1][j-1];
				giveOrTake(tempo, neighbour, i, j);
}

}}		copy(tempo, orig, rowlen, collen);
		assert(sizeof(tempo[MAX_U][MAX_U])==sizeof(orig[MAX_U][MAX_U]));
		//postcondition: checks to see if tempo was successfully copied into orig;
		
}



//-----------------------------------------------------------
//PURPOSE:this function checks if a cell should be dead or alive
//INPUT PARAMETER: 
//int check[][]: the universe to be checked
//int checker: the number of neighbours surrounding a cell
//int i: the row index of the cell to be checked
//int j: the column index of the cell to be checked
//OUTPUT PARAMETER:
// no output parameter
//-------------------------------------------------------------
void giveOrTake(int check[MAX_U][MAX_U], int checker, int i, int j){
	invariant(check);
	//preconditions: check that integer values are not negative
	assert((checker>=0)&&(i>=0)&&(j>=0));
	if((checker<2)||(checker>3)){
		check[i][j] = 0;}
	else if((check[i][j]==0)&&(checker == 3)){
		check[i][j]=1;}
	else if(check[i][j] == 1){
	assert(check[i][j]== 1);
		check[i][j]=1;}
//postconition: check that the cell has the correct value
assert((check[i][j]==0)||(check[i][j]==1));
}
//-----------------------------------------------------------------
//PURPOSE: this method copies a universe into an empty universe
//INPUT PARAMETERS:
//int orig[MAX_U][MAX_U]: the original array to be copied
//int tempo[MAX_U][MAX_U]: the array to be copied to
//int rowlen: the length of the row of the universe
//int collen: the length of the column of the universe
//OUTPUT PARAMETER:
//no output parameter
//-----------------------------------------------------------
void copy(int orig[MAX_U][MAX_U],int tempo[MAX_U][MAX_U], int rowlen, int collen){		
//precondition: check that the arrays have same size meaning that their rows and columns are the same length
//check that the rows and columns are positive numbers
	assert(sizeof(orig[MAX_U][MAX_U])==sizeof(tempo[MAX_U][MAX_U]));
	assert((rowlen>=0)&&(collen>=0));
	for(int i= 0; i<rowlen;i++){
		for(int j =0;j<collen;j++){
			tempo[i][j] = orig[i][j];
			//post condition: to check that all elements in both universes are the same
			assert(tempo[i][j]==orig[i][j]);
			invariant(tempo);
}}
//
}
//-------------------------------------------------------------------------------
//PURPOSE: this function prints out the universe and also 
//prints out the boundary lines
//INPUT PARAMETERS:
//int arr[MAX_U][MAX_U]:the universe to be printed
//int rowlen: the length of row of the universe
//int collen: the length of column of the universe
//OUTPUT PARAMETERS:
//no output parameter
//-------------------------------------------------------------------------------
void printArr(int array[MAX_U][MAX_U],int rowlen,int collen){
	invariant(array);
	//preconditions: check that the array is not empty and that the integers are not negative
	assert(array!=NULL);
	assert((rowlen>=0)&&(collen>=0));
	int x,i,j;
	int boundary = collen+2;
	for(x = 0; x<boundary; x++){
		if ((x==0)||(x==boundary-1)){
			printf("+");}
		else{
			printf("-"); }
}
	printf("\n");
	for( i = 0; i<rowlen;i++){
		printf("|");
		for( j=0; j<collen; j++){

			if(array[i][j]==0){
				printf(".");}
			else{
				printf("*");}		
}
		printf("|\n");
}
	for( x = 0; x<boundary;x++){
		if((x==0)||(x==boundary-1)){
			printf("+");}
		else{
			printf("-");}
		
}	//postcondition:check that all elements int the array is printedby checking that all the indices were reached
	assert((x==boundary)&&(i==rowlen)&&(j==collen));
	printf("\n");
}
//------------------------------------------------------------------------------
//PURPOSE:this function checks if any 2 universes are the same
//INPUT PARAMETERS:
//Gen games[END_CASE]: this array stores generations of universes
//int Cycle: this is the present occupied length of the generation array
//OUTPUT PARAMETER:
//int result: resturns 0 if no 2 universes are the same otherwise retruns 1
//-----------------------------------------------------------------------------
int checkCycle(Gen games[END_CASE], int cycle){
	//precondition: to check that cycle is greater than 0 and games array isnt empty
	assert((games!=NULL)&&(cycle>0));
	
	int result = 0;
	int i = 0;
	int arrChecker = 0;
	while((result==0)&&(i<cycle)){
	
		for(int row = 0;row<games[cycle].rown;row++){
			for(int col = 0;col<games[cycle].coln;col++){
				if(games[i].arr[row][col]!=games[cycle].arr[row][col]){
					assert(i!=cycle);
					col = games[cycle].coln;
					row = games[cycle].rown;
					arrChecker = 1;
}

}

}		
		if(arrChecker == 0){
			assert(arrChecker==0);
			printf("cycle spotted in generation %d and %d\n", i, cycle);
			result = 1;}
		i++;
		arrChecker=0;	}
	//postconditions: to check that result is either 1 or 0(true=1 && false=0)
	assert((result>=0)&&(result<=1));
	return result;
}
void invariant(int array[MAX_U][MAX_U]){
	assert(array!=NULL);
	assert(MAX_U>=0);
}




















