%%
%% gamma_correction.m
%%
%% Computes the gamma corrected version of an input image
%%
%% Inputs:
%%	in_img		- N x M x 3 matrix representing a color image
%%	gamma		- gamma value
%%
%% Outputs:
%%	out_img		- N x M x 3 matrix representing the output image
%%
function out_img = gamma_correction(in_img,gamma)

out_img = 255 * (double(in_img)/255).^gamma;