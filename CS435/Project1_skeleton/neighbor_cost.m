%%
%% neighbor_cost.m
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
%% Given two neighbors, determines the cost between them
%%
%% INPUT
%%	1) q_x			- X coordinate of point q
%%	2) q_y			- Y coordinate of point q
%%	3) p_x			- X coordinate of point p
%%	4) p_y			- Y coordinate of point p
%%	5) cost_matrix		- N x M x 8 matrix containing the cost of each link
%% 
%% OUTPUT
%%	1) cost 		- Cost between p and q
%%
function [cost] = neighbor_cost(q_x,q_y,p_x,p_y,cost_matrix)
  num = 1;

  %%
  %% Check which neighbor p is and return the corresponding link cost
  %%
  for i=-1:1
    for j=-1:1
      if(((q_x+i)==p_x) && ((q_y+j)==p_y))

	if(num == 1)
	  cost = cost_matrix(q_y,q_x,4);
	elseif(num ==2)	 
	  cost = cost_matrix(q_y,q_x,5);
	elseif(num ==3)	 
	  cost = cost_matrix(q_y,q_x,6);
	elseif(num ==4)	 
	  cost = cost_matrix(q_y,q_x,3);
	elseif(num ==5)	 
	  cost = cost_matrix(q_y,q_x,7);
	elseif(num ==6)	 
	  cost = cost_matrix(q_y,q_x,2);
	elseif(num ==7)	 
	  cost = cost_matrix(q_y,q_x,1);
	elseif(num ==8)	 
	  cost = cost_matrix(q_y,q_x,8);
	else
	  disp('Error points not neighbors');
	  exit;
      end
      num = num + 1;
      end
    end
  end	

