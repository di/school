%%
%% composite.m
%%
%% Computational Photography Assignment 1
%%
%% John Novatnack
%% jmn27@cs.drexel.edu
%%
%% INPUT:
%%	1) target_img 		- Image to place to cut
%%	2) cut_img		- Image to place ontop of the target
%%	3) mask			- Mask of the cut_img
%%	4) scale		- Scale to apply to the cut_img
%%	5) t_x			- Translation in the x direction
%%	6) t_y			- Translation in the y direction
%%
%% OUTPUT:
%%	1) out_img		- The composited image
%%
function [out_img] = composite(target_img,cut_img,mask,scale,t_x,t_y)

  target_img = double(target_img);
  cut_img  = double(cut_img);
  mask = double(mask);

  %%
  %%
  %% Apply the mask to the cut_img
  %%
  %%

  

  %%
  %%
  %% Scale the cut_img
  %% (hint: imresize)
  %%



  %%
  %%
  %% Translate the cut_img
  %% (hint: position point in binary image processing lecture)
  %%
 
  

  %%
  %%
  %% Create the composite
  %%
