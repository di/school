% CS 480: Computational Photography
% Fall 2006
% Project 3
%
% function [] = project3(img_file, flength)
function [] = project3(img_file, flength)

if nargin == 1,
	flength=500;
	fprintf(1,'Using the default focal length (500 pixels)\n');
end

img=double(imread(img_file))./255;

% Run the GUI in Figure 1
figure(1);
[vx,vy,irx,iry,orx,ory]=TIP_GUI(img);

% Find the cube faces and compute the expanded image
[bim,bim_alpha,vx,vy,ceilrx,ceilry,floorrx,floorry,...
    leftrx,leftry,rightrx,rightry,backrx,backry] = ...
    TIP_get5rects(img,vx,vy,irx,iry,orx,ory);

% display the expanded image
figure(2);
imshow(bim);

% Draw the Vanishing Point and the 4 faces on the image
figure(2);
hold on;
plot(vx,vy,'w*');
plot([ceilrx ceilrx(1)], [ceilry ceilry(1)], 'y-');
plot([floorrx floorrx(1)], [floorry floorry(1)], 'm-');
plot([leftrx leftrx(1)], [leftry leftry(1)], 'c-');
plot([rightrx rightrx(1)], [rightry rightry(1)], 'g-');
hold off;

% TODO: Implement get3dplanes.m
% Compute the 3D coordinates of the corner points of each surface of the box
% Note that the image coordinates computed above, namely, ceilrx, ceilry,
% floorrx ... store the image coordinates of the corner points of each face
% clockwise (upper-left, upper-right, lower-right,lower-left).
% Print them out to make sure you understand how they are stored! Also note
% that the top left of the image is (0,0).
% Here, you will need the focal length of the camera. If you don't know it
% just use the default value 500, or extract it from the EXIF information
% (details in get3dplanes.m).

[ceil3, floor3, left3, right3, back3] = ...
	get3dplanes(vx, vy, ceilrx, ceilry, floorrx, floorry, ...
	leftrx, leftry, rightrx, rightry, backrx, backry, flength);

% TODO: Implement gettexture.m
% Compute the texture for each surface of the box
% See explanation in gettexture.m for details (read it carefully).
[ceilimg, floorimg, leftimg, rightimg, backimg] = ...
	gettexture(bim, ceil3, floor3, left3, right3, back3, ceilrx, ceilry, ...
	floorrx, floorry, leftrx, leftry, rightrx, rightry, backrx, backry);


% Render the 3D box 
draw3dbox(ceil3, floor3, left3, right3, back3, ceilimg, floorimg, leftimg, rightimg, backimg);


