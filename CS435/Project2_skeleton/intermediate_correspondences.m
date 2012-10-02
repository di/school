%%
%% intermediate-correspondences.m
%%
%% Computational Photography Project 2
%%
%%
%% Computes the location of the correspondence points in the intermediate shape
%%
%% INPUT
%%	1) im1pts	- N x 2 matrix storing the location of the correspondence points in image1
%%	2) im2pts	- N x 2 matrix storing the location of the correspondence points in image2
%%	3) warp_fraction - [0, 1] parameter that controls the intermediate shape	
%%
%% OUTPUT
%%	1) ipts		- N x 2 matrix storing the intermediate points
%%
function [ipts] = intermediate_correspondences(im1pts, im2pts, warp_fraction)

% compute the intermediate point coordinates (this can be a one liner)

ipts = floor((1-warp_fraction).*im1pts(:,:) + warp_fraction.*im2pts(:,:));

return