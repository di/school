% CS 480: Computational Photography
% Fall 2006
% Project 3
%
% gettexture.m
% 
% Get the texture images for each surface of the box by computing the
% homography matrix and (inverse) warping the corresponding region in the
% expanded image
%
%function [ceilimg, floorimg, leftimg, rightimg, backimg] = ...
%	gettexture(bim, ceil3, floor3, left3, right3, back3, ceilrx, ceilry, ...
%	floorrx, floorry, leftrx, leftry, rightrx, rightry, backrx, backry);

function [ceilimg, floorimg, leftimg, rightimg, backimg] = ...
	gettexture(bim, ceil3, floor3, left3, right3, back3, ceilrx, ceilry, ...
	floorrx, floorry, leftrx, leftry, rightrx, rightry, backrx, backry);

% TODO:
% For each face, 
% 1. Compute the homography transformation by specifying appropriate
% 3-vector homogeneous coordinates (note that each surface is a plane, and
% thus only 2 of the 3D coordinates are relevant, so build the target
% coordinates matrix (3x4 with 1's at the bottom row) carefully. The source
% image coordinates can be computed from floorrx, ... (again, note how they
% are stored -- they are different from the floor3 etc.)
% 2. Inverse warp each image region using the computed homography --
% implement this as homographywarp.m


% Here's an sample for the left side of the example image
% Note that for the left side, we use the depth as the horizontal axis of
% the newly computed image and the height as the vertical axis of the newly
% computed image. Also note that you need to adjust the coordinates since
% the 3D coordinates of the front end (left end on the plane) are not 0.
% Stare at Figure 2 get a better idea of what this is doing.
% The image size does not have to be exactly the size of the 3D plane since
% we will texture map it with a matlab function called warp which will
% automatically stretch it. In order to reduce computation time, here we are
% using a fixed width 500.
fixedwidth=500;

%%%%%%%%%%%%%%%%%% left -------------------------------------
srccorners=[leftrx(1) leftrx(2) leftrx(3) leftrx(4);
				leftry(1) leftry(2) leftry(3) leftry(4);
				1 1 1 1];
% for the left plane, the depth is the horizontal axis!
left3dwidth=abs(left3(2,2)-left3(1,2));
% for the left plane, the height is the vertical axis!
left3dheight=abs(left3(4,3)-left3(1,3));
leftimgwidth=fixedwidth;
leftimgheight=floor(leftimgwidth*left3dheight/left3dwidth);
targetcorners=[0 leftimgwidth leftimgwidth 0;
					0 0 leftimgheight leftimgheight;
					1 1 1 1];
% Compute the Homography matrix.
leftH=homography2d(srccorners,targetcorners);

% Warp the image using the Homography matrix.
leftimg=homographywarp(bim,leftimgwidth,leftimgheight,leftH);

% TODO: Implement the rest!

%%%%%%%%%%%%%%%%%%% ceilimg -----------------------------------
srccorners=[ceilrx(1) ceilrx(2) ceilrx(3) ceilrx(4);
				ceilry(1) ceilry(2) ceilry(3) ceilry(4);
				1 1 1 1];
% for the left plane, the depth is the horizontal axis!
ceil3dwidth=abs(ceil3(2,2)-ceil3(1,2));
% for the ceil plane, the height is the vertical axis!
ceil3dheight=abs(ceil3(4,3)-ceil3(1,3));

ceilimgwidth=fixedwidth;
ceilimgheight=floor(ceilimgwidth*ceil3dheight/ceil3dwidth);
targetcorners=[0 ceilimgwidth ceilimgwidth 0;
					0 0 ceilimgheight ceilimgheight;
					1 1 1 1];

% Compute the Homography matrix.
ceilH=homography2d(srccorners,targetcorners);

% Warp the image using the Homography matrix.
ceilimg=homographywarp(bim,ceilimgwidth,ceilimgheight,ceilH);

%%%%%%%%%%%%%%%%%%% floor ----------------------------------------
srccorners=[floorrx(1) floorrx(2) floorrx(3) floorrx(4);
				floorry(1) floorry(2) floorry(3) floorry(4);
				1 1 1 1];
% for the left plane, the depth is the horizontal axis!
floor3dwidth=abs(floor3(2,2)-floor3(1,2));
% for the floor plane, the height is the vertical axis!
floor3dheight=abs(floor3(4,3)-floor3(1,3));

floorimgwidth=fixedwidth;
floorimgheight=floor(floorimgwidth*floor3dheight/floor3dwidth);
targetcorners=[0 floorimgwidth floorimgwidth 0;
					0 0 floorimgheight floorimgheight;
					1 1 1 1];

% Compute the Homography matrix.
floorH=homography2d(srccorners,targetcorners);

% Warp the image using the Homography matrix.
floorimg=homographywarp(bim,floorimgwidth,floorimgheight,floorH);

%%%%%%%%%%%%%%%%%%%%%% right -------------------------------------           
srccorners=[rightrx(1) rightrx(2) rightrx(3) rightrx(4);
				rightry(1) rightry(2) rightry(3) rightry(4);
				1 1 1 1];
% for the left plane, the depth is the horizontal axis!
right3dwidth=abs(right3(2,2)-right3(1,2));
% for the right plane, the height is the vertical axis!
right3dheight=abs(right3(4,3)-right3(1,3));

rightimgwidth=fixedwidth;
rightimgheight=floor(rightimgwidth*right3dheight/right3dwidth);
targetcorners=[0 rightimgwidth rightimgwidth 0;
					0 0 rightimgheight rightimgheight;
					1 1 1 1];

% Compute the Homography matrix.
rightH=homography2d(srccorners,targetcorners);

% Warp the image using the Homography matrix.
rightimg=homographywarp(bim,rightimgwidth,rightimgheight,rightH);

%%%%%%%%%%%%%%%%%%%%%%%% back ------------------------------------
srccorners=[backrx(1) backrx(2) backrx(3) backrx(4);
				backry(1) backry(2) backry(3) backry(4);
				1 1 1 1];
% for the left plane, the depth is the horizontal axis!
back3dwidth=abs(back3(2,2)-back3(1,2));
% for the back plane, the height is the vertical axis!
back3dheight=abs(back3(4,3)-back3(1,3));

backimgwidth=fixedwidth;
backimgheight=floor(backimgwidth*back3dheight/back3dwidth);
targetcorners=[0 backimgwidth backimgwidth 0;
					0 0 backimgheight backimgheight;
					1 1 1 1];

% Compute the Homography matrix.
backH=homography2d(srccorners,targetcorners);

% Warp the image using the Homography matrix.
backimg=homographywarp(bim,backimgwidth,backimgheight,backH);

