
#------------------------------------------------------------------------------
# Yasin Aikebaier
# yaikebai
# PA 4
# 
# Makefile for CMPS 101-01 Programming Assignment 4
#
#      make                   makes DigraphProperties
#   
#------------------------------------------------------------------------------

DigraphProperties : DigraphProperties.o Digraph.o List.o
	gcc -o DigraphProperties DigraphProperties.o Digraph.o List.o

DigraphProperties.o : DigraphProperties.c Digraph.h List.h
	gcc -c -std=c99 -Wall DigraphProperties.c

Digraph.o : Digraph.c Digraph.h List.h
	gcc -c -std=c99 -Wall Digraph.c

List.o : List.c List.h
	gcc -c -std=c99 -Wall List.c

clean :
	rm -f DigraphProperties DigraphProperties.o Digraph.o List.o
