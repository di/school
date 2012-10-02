%%
%% bilinear_interp.m
%%
%% Computational Photography Project 2
%%
%%
%% Determine the value of a subpixel using bilinear interpolation
%%
%% INPUT
%%	1) im1		-  N x M x 3 matrix containing an image
%%	2) x,y		-  Floating point subpixel we wish to know the value of
%% OUTPUT
%%	1) pixel_value  -  1 x 3 vector with the R,G,B values at (x,y)
%% 
function [pixel_value] = bilinear_interp(im1, x, y)

% compute the bilinearly interpolated pixel value (see slide; do not use
% matlab built-in functions (you can do so only after you implement it
% yourself))

i = floor(x);
j = floor(y);

a = x - i;
b = y - j;

i_offset = 1.0;
j_offset = 1.0;
imSize = size(im1);

if (i == imSize(2))
    i_offset = 0.0;
end
if (j == imSize(1))
    j_offset = 0.0;
end
if (i == 0)
    i = 1;
end
if (j == imSize(1))
    j = 1;
end

pixel_value = ((1-a)*(1-b)).*im1(i,j,:) + (a*(1-b)).*im1(i+i_offset,j,:) + (a*b).*im1(i+i_offset,j+j_offset,:) + ((1-a)*b).*im1(i,j+j_offset);