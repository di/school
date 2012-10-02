% CS 480: Computational Photography
% Fall 2006
% Project 3
%
% get3dplanes.m
% 
% Compute the 3D coordinates of the corner points of the 5 rectangles
%
%function [ceil3, floor3, left3, right3, back3] = ...
%	get3dplanes(vx, vy, ceilrx, ceilry, floorrx, floorry, ...
% leftrx, leftry, rightrx, rightry, backrx, backry)

function [ceil3, floor3, left3, right3, back3] = ...
	get3dplanes(vx, vy, ceilrx, ceilry, floorrx, floorry, ...
	leftrx, leftry, rightrx, rightry, backrx, backry, flength)

% TODO:
%	1. The width and height ratio of the back plane directly tells you the aspect
%	ratio of the box, so specifying the 3D height gives you the 3D width
% 2. The back plane's height is related to the depth of the box (see lecture
% slide: Depth of Box), so specifying the 3D height gives you the 3D depth
% 3. In order to use the above (2) relationship, you need to know the focal
% length in pixels. There are two alternative ways to do this
%		- Just guess it (For the example image sjerome.jpg, use focal length
%		500 pixels)
%		- Extract the true focal length from the EXIF data embedded in the image
%			For this, you can use http://vision.bc.edu/~dmartin/software/Exif.tgz
%			(David Martin's C and mex code for extracting data)
%			You'll need to compile the exif function with the command mex exif.c.
%			Use the exifFocalLength.m function to get the camera focal length in
%			pixels from an image file.
% 4. Once you compute the 3D width, height, and depth of the box, you can
% compute the 3D coordinates of all corners points of the 5 surfaces (you
% may set the origin to be the left bottom corner of the floor surface, 3D X
% axis aligned to the horizontal axis of the image, the 3D Y axis
% aligned to the depth axis of the box, and the 3D Z axis aligned to the
% height axis of the box).
% 5. Store the 3D coordinates for each surface in clockwise order, i.e.
% floor3(1,:)=[? ? ?],.... floor3(4,:)=[0 0 0];
% NOTE: When you compute these 3D coordinates, don't forget to account for
% the fact that the surfaces are not exactly aligned with the box (see
% Figure 2; you notice that the front end of the surfaces are not aligned).
% You need to adjust the depth coordinates of front points of each surface
% accordingly using the 2D image coordinates to get proper results.

% Also, first compute the 3D coordinates for the back plane since those can
% be reused in other surfaces.

bHeight = floorry(1)-ceilry(3);
cHeight = floorry(3)-ceilry(1);
backDepth = floor(flength*(cHeight/bHeight));

back3(1,:) = [ceilrx(1) ceilry(1) backDepth];
back3(2,:) = [ceilrx(2) ceilry(2) backDepth];
back3(3,:) = [floorrx(3) floorry(3) backDepth];
back3(4,:) = [floorrx(4) floorry(4) backDepth];

ceil3(1,:) = [ceilrx(1) ceilry(1) 0];
ceil3(2,:) = [ceilrx(2) ceilry(2) 0];
ceil3(3,:) = back3(2,:);
ceil3(4,:) = back3(1,:);

floor3(1,:) = back3(4,:);
floor3(2,:) = back3(3,:);
floor3(3,:) = [floorrx(3) floorry(3) 0];
floor3(4,:) = [floorrx(4) floorry(4) 0];

left3(1,:) = [leftrx(1) leftry(1) 0];
left3(2,:) = back3(1,:);
left3(3,:) = back3(4,:);
left3(4,:) = [leftrx(4) leftry(4) 0];

right3(1,:) = back3(2,:);
right3(2,:) = [rightrx(2) rightry(2) 0];
right3(3,:) = [rightrx(3) rightry(3) 0];
right3(4,:) = back3(3,:);
