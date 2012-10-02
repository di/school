%%
%% neighbors.m
%%
%% Computational Photography Assignment 1
%%
%% John Novatnack
%% jmn27@cs.drexel.edu
%%
%% Adapted from skeleton code by:
%%
%% 	Konstantinos Bitsakos
%% 	Department of Computer Science 
%% 	University of Maryland, College Park
%% 	kbits@cs.umd.edu
%%
%% Further reference on Intelligent Scissors:
%%	"Intelligent Scissors for Image Composition", E. Mortensen and W. Barret
%%	SIGGRAPH 1995.
%%
%%
%% Given a point returns the x, y coordinates of each point in the neighborhood
%%
%% INPUT
%%	1) p_x		- X coordinate of the point
%%	2) p_y		- Y coordinate of the point
%%
%% 
%% OUTPUT
%%	1) 8 x 2	- Matrix containing the x,y coordinates of the eight neighbors
%%			 
function [neighbors_matrix] = neighbors(p_x,p_y) 
  neighbors_matrix = zeros(8,2);

  current_point = 1;

  for i=-1:1
    for j=-1:1
      
      if(~((i==0)&&(j==0)))
	neighbors_matrix(current_point,1) = p_x + i;
	neighbors_matrix(current_point,2) = p_y + j;
	
	current_point = current_point + 1;
      end
    end
  end
	
