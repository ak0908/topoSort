// Yasin Aikebaier
// yaikebai
// PA 4
// 
//-----------------------------------------------------------------------------
// DigraphProperties.c
//
// This is a test file for Digraph ADT
//-----------------------------------------------------------------------------


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<ctype.h>
#include "List.h"
#include "Digraph.h"

#define MAX_LEN 100000

int main(int argc, char* argv[]){
	FILE *in, *out;
	char line[MAX_LEN];
	char linehelp[MAX_LEN];  // this will help me terminate program if graph is illegal
	char linehelp2[MAX_LEN];
	char* token;             
	char* tokenhelp;		 // this will help me terminate program if graph is illegal
	char* tokenhelp2;
	char* operation;
	int operand1 = -1;
	int operand2 = -1;
	char s1[1000], s2[1000];
	char* charPtr;
	int v, w;
	int numV;
	char helper[MAX_LEN] ;
    char helper2[MAX_LEN];
	int index;
	int spaceCounter;
	int numE1, numE2;


	if(argc != 3){
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}

	// open files for reading and writing
	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");

	if( in==NULL ){
       printf("Unable to open file %s for reading\n", argv[1]);
       exit(1);
    }
    if( out==NULL ){
       printf("Unable to open file %s for writing\n", argv[2]);
       exit(1);
    }

    // reading the line which contains the numVerteice and edges
    fgets(line, MAX_LEN, in);

    // this block of code is to check if the graph is legal on punctuation
    strcpy(linehelp, line);
    tokenhelp = strtok(linehelp, ",\n\r");
    tokenhelp = strtok(NULL, ",\n\r");

    while(tokenhelp != NULL){
    	    	    	    	         
    	index = 0;
    	spaceCounter = 0;
    	while(tokenhelp[index]){
    		if(isspace(tokenhelp[index])) spaceCounter++;
    		index++;
    		//printf("%s\n", "so far so good");
    	}
    	if (spaceCounter != 2){
    		fprintf(out, "%s", line);
    		fprintf(out, "%s\n", "ERROR");
    		fclose(in);
    		fclose(out);
    		exit(1);
    	}
    	tokenhelp = strtok(NULL, ",\n\r");
    }

    // this block of code is to check if the edge is legal
    strcpy(linehelp2, line);
    tokenhelp2 = strtok(linehelp2, " ,\n\r");

    numV = (int)strtol(tokenhelp2, &charPtr, 10);

    tokenhelp2 = strtok(NULL, " ,\n\r");


    while(tokenhelp2 != NULL){
    	numE1 = (int)strtol(tokenhelp2, &charPtr, 10);
    	tokenhelp2 = strtok(NULL, " ,\n\r");
    	numE2 = (int)strtol(tokenhelp2, &charPtr, 10);
    	if(numE1 <= 0 || numE1 > numV || numE2 <= 0 || numE2 > numV || numE2 == numE1){
    		fprintf(out, "%s", line);
    		fprintf(out, "%s\n", "ERROR");
    		fclose(in);
    		fclose(out);
    		exit(1);
    	}
    	tokenhelp2 = strtok(NULL, " ,\n\r");
    }

    

    token = strtok(line, " ,\r\n");

    numV = (int)strtol(token, &charPtr, 10);

    // checking if the numVertices is legal or not
    if( numV <= 0){
    	fprintf(out, "%d,", numV);
    	token = strtok(NULL, "");
    	fprintf(out, "%s", token);
    	fprintf(out, "%s\n", "ERROR");
    	fclose(out);
    	fclose(in);
    	exit(1);
    }
 
    // create a new Digraph based on numV	
    Digraph G = newDigraph((int)strtol(token, &charPtr, 10));


    token = strtok(NULL, " ,\r\n");

    while(token != NULL){

    	v = (int)strtol(token, &charPtr, 10);
    	token = strtok(NULL, " ,\r\n");
    	w = (int)strtol(token, &charPtr, 10);
    	addEdge(G, v, w);
    	token = strtok(NULL, " ,\r\n");
    }


    // reading the line which contains the operation
    while(fgets(line, MAX_LEN, in) != NULL){
    	strcpy(helper, line);
        strcpy(helper2, line);
        token = strtok(helper2, " \r\n");
        if(token == NULL) goto didNotFollowFormat;
        int operandCount = 0;
        token = strtok(NULL, " \r\n");
        while(token != NULL){
            operandCount++ ;
            token = strtok(NULL, " \r\n");
        }

        if (operandCount > 2) goto didNotFollowFormat;

        token = strtok(line, " \r\n");
        operation = token;
        token = strtok(NULL, " \r\n");
        if(token != NULL) operand1 = (int)strtol(token, &charPtr, 10);
        else operand1 = -1;
        token = strtok(NULL, " \r\n");
        if(token != NULL) operand2 = (int)strtol(token, &charPtr, 10);
        else operand2 = -1;

        if(strncmp(operation, "PrintDigraph", 100) == 0){
            sprintf(s1, "%d", operand1);
            sprintf(s2, "%d", operand2);
            fprintf(out, "%s %s %s\n", "PrintDigraph", operand1==-1?"":s1,operand2==-1?"":s2);
            if(operand2 == -1 && operand1 == -1){
                printDigraph(out, G);
                fprintf(out, "\n");
            }
        	else{
                fprintf(out, "%s\n", "ERROR");
            }
        } 

        else if(strncmp(operation, "GetCountSCC", 100) == 0){
            sprintf(s1, "%d", operand1);
            sprintf(s2, "%d", operand2);
            fprintf(out, "%s %s %s\n", "GetCountSCC", operand1==-1?"":s1,operand2==-1?"":s2);
            if(operand2 == -1 && operand1 == -1){
                fprintf(out, "%d\n", GetCountSCC(G));
            }
            else{
                fprintf(out, "%s\n", "ERROR");
            }   
        }

        else if(strncmp(operation, "GetOrder", 100) == 0){
            sprintf(s1, "%d", operand1);
            sprintf(s2, "%d", operand2);
            fprintf(out, "%s %s %s\n", "GetOrder", operand1==-1?"":s1,operand2==-1?"":s2);
            if(operand2 == -1 && operand1 == -1){
                fprintf(out, "%d\n", getOrder(G));
            }
            else{
                fprintf(out, "%s\n", "ERROR");
            }
        	
        } 

        else if(strncmp(operation, "GetSize", 100) == 0){
            sprintf(s1, "%d", operand1);
            sprintf(s2, "%d", operand2);
            fprintf(out, "%s %s %s\n", "GetSize", operand1==-1?"":s1,operand2==-1?"":s2);
            if(operand2 == -1 && operand1 == -1){
                fprintf(out, "%d\n", getSize(G));
            }
            else{
                fprintf(out, "%s\n", "ERROR");
            }
        } 

        else if(strncmp(operation, "GetOutDegree", 100) == 0){
            if(operandCount != 1) goto didNotFollowFormat;

            if(isLegalVertex(G, operand1)){
                fprintf(out, "%s %d\n", "GetOutDegree", operand1);
                fprintf(out, "%d\n", GetOutDegree(G, operand1));
            }

            else goto didNotFollowFormat;

        } 

        else if(strncmp(operation, "GetNumSCCVertices", 100) == 0){
            if(operandCount != 1) goto didNotFollowFormat;

            if(isLegalVertex(G, operand1)){
                fprintf(out, "%s %d\n", "GetNumSCCVertices", operand1);
                fprintf(out, "%d\n", GetNumSCCVertices(G, operand1));               
            }

            else goto didNotFollowFormat;
        }

        else if(strncmp(operation, "PathExists", 100) == 0){
        	sprintf(s1, "%d", operand1);
        	sprintf(s2, "%d", operand2);
			fprintf(out, "%s %s %s\n", "PathExists", operand1==-1?"":s1,operand2==-1?"":s2);
        	if(isLegalVertex(G, operand1) && isLegalVertex(G, operand2)){
        		fprintf(out, "%s\n", PathExistsRecursive(G, operand1, operand2)==FOUND?"YES":"NO");
        	}
        	else fprintf(out, "%s\n", "ERROR");

        	unvisitAll(G);
        }

        else if(strncmp(operation, "Distance", 100) == 0){
        	sprintf(s1, "%d", operand1);
        	sprintf(s2, "%d", operand2);
			fprintf(out, "%s %s %s\n", "Distance", operand1==-1?"":s1,operand2==-1?"":s2);
			if(isLegalVertex(G, operand1) && isLegalVertex(G, operand2)){
        		distance(out, G, operand1, operand2);
        	}
            else fprintf(out, "%s\n", "ERROR");
        }

        else if(strncmp(operation, "InSameSCC", 100) == 0){
            if(operandCount != 2) goto didNotFollowFormat;

            if(isLegalVertex(G, operand1) && isLegalVertex(G, operand2)){
                fprintf(out, "%s %d %d\n", "InSameSCC", operand1, operand2);
                InSameSCC(out, G, operand1, operand2);               
            }

            else goto didNotFollowFormat;
        }

        else if(strncmp(operation, "AddEdge", 100) == 0){
        	sprintf(s1, "%d", operand1);
        	sprintf(s2, "%d", operand2);
			fprintf(out, "%s %s %s\n", "AddEdge", operand1==-1?"":s1,operand2==-1?"":s2);
            if(isLegalVertex(G, operand1) && isLegalVertex(G, operand2)){
                fprintf(out, "%d\n", addEdge(G, operand1, operand2));
            }
            else fprintf(out, "%s\n", "ERROR");
        }

        else if(strncmp(operation, "DeleteEdge", 100) == 0){
        	sprintf(s1, "%d", operand1);
        	sprintf(s2, "%d", operand2);
        	fprintf(out, "%s %s %s\n", "DeleteEdge", operand1==-1?"":s1,operand2==-1?"":s2);
            if(isLegalVertex(G, operand1) && isLegalVertex(G, operand2)){
                fprintf(out, "%d\n", deleteEdge(G, operand1, operand2));
            }
            else fprintf(out, "%s\n", "ERROR");
        }

        else if(strncmp(operation, "Acyclic", 100) == 0){
            if(operand1 == 0 || operand2 == 0) goto didNotFollowFormat;
            sprintf(s1, "%d", operand1);
            sprintf(s2, "%d", operand2);
            fprintf(out, "%s %s %s\n", "Acyclic", operand1==-1?"":s1,operand2==-1?"":s2);
            if(operand2 == -1 && operand1 == -1){
                acyclic(out, G);
            }
            else{
                fprintf(out, "%s\n", "ERROR");
            }

        }

        else if(strncmp(operation, "TopoSort", 100) == 0){
            if(operand1 == 0 || operand2 == 0) goto didNotFollowFormat;
            sprintf(s1, "%d", operand1);
            sprintf(s2, "%d", operand2);
            fprintf(out, "%s %s %s\n", "TopoSort", operand1==-1?"":s1,operand2==-1?"":s2);
            if(operand2 == -1 && operand1 == -1){
                topoSort(out, G);
            }
            else{
                fprintf(out, "%s\n", "ERROR");
            }

        }

        else{
            didNotFollowFormat:
            strtok(helper, "\n");
        	fprintf(out, "%s\n", helper);
        	fprintf(out, "%s\n", "ERROR");
        }

    }

    //fprintf(out, "\n");

    fclose(in);
    fclose(out);


    freeDigraph(&G);

}