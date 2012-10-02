% CS 480: Computational Photography
% Fall 2006
% Project 3
%
% draw3dbox.m
%
% Draw the 3D scene as a box using the 3D planes and their textures

% function [] = draw3Dbox(ceil3, floor3, left3, right3, back3, ...
% 	ceilimg, floorimg, leftimg, rightimg, backimg);

function [] = draw3Dbox(ceil3, floor3, left3, right3, back3, ...
	ceilimg, floorimg, leftimg, rightimg, backimg);

figure(3);
title('3D fly around');
cameratoolbar('Show');
hold on;

%imagesc(floorimg)

% draw floor plane
% Specify the plane with the X, Y, Z spans with another sample point at the
% middle
floorX=[floor3(1,1) (floor3(2,1)-floor3(1,1))/2+floor3(1,1) floor3(2,1);
				floor3(4,1) (floor3(3,1)-floor3(4,1))/2+floor3(4,1) floor3(3,1)];
floorY=[floor3(1,2) (floor3(2,2)-floor3(1,2))/2+floor3(1,2) floor3(2,2);
				floor3(4,2) (floor3(3,2)-floor3(4,2))/2+floor3(4,2) floor3(3,2)];
floorZ=[floor3(1,3) (floor3(2,3)-floor3(1,3))/2+floor3(1,3) floor3(2,3);
				floor3(4,3) (floor3(3,3)-floor3(4,3))/2+floor3(4,3) floor3(3,3)];
warp(floorX,-floorY,floorZ,floorimg);

% draw ceiling plane
ceilX=[ceil3(1,1) (ceil3(2,1)-ceil3(1,1))/2+ceil3(1,1) ceil3(2,1);
			 ceil3(4,1) (ceil3(3,1)-ceil3(4,1))/2+ceil3(4,1) ceil3(3,1)];
ceilY=[ceil3(1,2) (ceil3(2,2)-ceil3(1,2))/2+ceil3(1,2) ceil3(2,2);
			 ceil3(4,2) (ceil3(3,2)-ceil3(4,2))/2+ceil3(4,2) ceil3(3,2)];
ceilZ=[ceil3(1,3) (ceil3(2,3)-ceil3(1,3))/2+ceil3(1,3) ceil3(2,3);
			 ceil3(4,3) (ceil3(3,3)-ceil3(4,3))/2+ceil3(4,3) ceil3(3,3)];
warp(ceilX,-ceilY,ceilZ,ceilimg);

% draw back plane
backX=[back3(1,1) (back3(2,1)-back3(1,1))/2+back3(1,1) back3(2,1);
			 back3(4,1) (back3(3,1)-back3(4,1))/2+back3(4,1) back3(3,1)];
backY=[back3(1,2) (back3(2,2)-back3(1,2))/2+back3(1,2) back3(2,2);
			 back3(4,2) (back3(3,2)-back3(4,2))/2+back3(4,2) back3(3,2)];
backZ=[back3(1,3) (back3(2,3)-back3(1,3))/2+back3(1,3) back3(2,3);
			 back3(4,3) (back3(3,3)-back3(4,3))/2+back3(4,3) back3(3,3)];
warp(backX,-backY,backZ,backimg);

% draw left plane
leftX=[left3(1,1) (left3(2,1)-left3(1,1))/2+left3(1,1) left3(2,1);
			 left3(4,1) (left3(3,1)-left3(4,1))/2+left3(4,1) left3(3,1)];
leftY=[left3(1,2) (left3(2,2)-left3(1,2))/2+left3(1,2) left3(2,2);
			 left3(4,2) (left3(3,2)-left3(4,2))/2+left3(4,2) left3(3,2)];
leftZ=[left3(1,3) (left3(2,3)-left3(1,3))/2+left3(1,3) left3(2,3);
			 left3(4,3) (left3(3,3)-left3(4,3))/2+left3(4,3) left3(3,3)];
warp(leftX,-leftY,leftZ,leftimg);

% draw right plane
rightX=[right3(1,1) (right3(2,1)-right3(1,1))/2+right3(1,1) right3(2,1);
			  right3(4,1) (right3(3,1)-right3(4,1))/2+right3(4,1) right3(3,1)];
rightY=[right3(1,2) (right3(2,2)-right3(1,2))/2+right3(1,2) right3(2,2);
			  right3(4,2) (right3(3,2)-right3(4,2))/2+right3(4,2) right3(3,2)];
rightZ=[right3(1,3) (right3(2,3)-right3(1,3))/2+right3(1,3) right3(2,3);
				right3(4,3) (right3(3,3)-right3(4,3))/2+right3(4,3) right3(3,3)];
warp(rightX,-rightY,rightZ,rightimg);


axis equal;
axis vis3d;
axis off;
camproj('perspective');

