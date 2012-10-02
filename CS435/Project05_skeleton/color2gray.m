%%
%% color2gray.m
%%
%% Converts a color image stored in a N x M x 3 matrix, to a 
%% gray-scale image stored in a N x M matrix.
%%
%%

function [gray_img] = color2gray(color_img)

  %%
  %% Create the matrix which will store the gray-scale image
  %% 

  gray_img = zeros(size(color_img,1),size(color_img,2));

  %%
  %% Create the gray-scale image, by average the color
  %% intensities at each pixel
  %% 
  
  for i = 1:size(color_img,1),
      for j = 1:size(color_img,2),
          gray_img(i,j) = (uint16(color_img(i,j,1)) + uint16(color_img(i,j,2)) + uint16(color_img(i,j,3)))/3;
      end
  end
    
  %%
  %% Convert gray_img to a matrix containing doubles from 0 to 1
  %% 
  
  gray_img = gray_img./255;