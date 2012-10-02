%%
%% extractmin.m
%%
%% Computational Photography Assignment 1
%%
%% ExtractMin function used for Image Scissors
%%
%% Usage:  [xcoord,ycoord,cost] = extractmin
%%
%% Arguments:   
%%            
%% Returns:
%%         xcoord,ycoord - x, y coordinate of the point with the minimum
%%         cost
%%         cost          - the cost of that point
%%
%% NOTE 1: If xcoord and ycoord are zero then the priority queue is empty
%%
%% NOTE 2: You should have a global array called pq in order for this
%% function to work
%%
%% Author: 
%% Konstantinos Bitsakos
%% Department of Computer Science 
%% University of Maryland, College Park
%% kbits@cs.umd.edu
%%
%% February 2004

function [xcoord,ycoord,cost] = extractmin

global pq
    
    [cost,index]=min(pq(3,:));
    
    if index % the priority queue is NOT empty
        xcoord=pq(1,index);
        ycoord=pq(2,index);
        pq(:,index)=[]; %delete the minimum element
    else
        xcoord=0;
        ycoord=0;
    end
    return
