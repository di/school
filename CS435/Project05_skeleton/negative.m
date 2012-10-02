%%
%% negative.m
%%
%% Computes the negative of a black and white image stored in a N x M matrix
%%

function [negative_img] = negative(in_img)
  
  %%
  %% Normalize the intensities of the input images to be between 0 and 1
  %%
  
  in_img = double(in_img)./255;
  
  %%
  %% Compute the negative image
  %%

  negative_img = 1-in_img;