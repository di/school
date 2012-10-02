% CS 480: Computational Photography
% Fall 2006
% Project 3
%
% homographywarp.m
%
% (Inverse) warp and image using a given homography transformation.
%
% function newimg = homographywarp(orgimg, newimgwidth, newimgheight, H)
function newimg = homographywarp(orgimg, newimgwidth, newimgheight, H)

newimg=zeros(newimgheight,newimgwidth,3);

% TODO: Inverse warp orgimg to get the pixel values of newimg
% Don't forget to divide the image coordinates with w (the 3rd coordinate)
% when you convert the homogeneous coordinates back to image coordinates

s = size(orgimg);
height = s(1);
width = s(2);

iH = inv(H);

for y = 1:newimgheight
	for x = 1:newimgwidth
		pixel = [x,y,1]';
		pixel = iH*pixel;
		pixel = pixel/pixel(3);
		xorgimg = pixel(1);
		yorgimg = pixel(2);
		% now do bilinear interpolation
		deltax = xorgimg - floor(xorgimg);
		deltay = yorgimg - floor(yorgimg);
		xx = floor(xorgimg);
		yy = floor(yorgimg);
		R1 = 0; R2 = 0; R3 = 0; R4 = 0;
		G1 = 0; G2 = 0; G3 = 0; G4 = 0;
		B1 = 0; B2 = 0; B3 = 0; B4 = 0;
		if(xx>0 && yy>0 && xx<width && yy<height)
			R1 = orgimg(yy,xx,1);R2 = orgimg(yy,xx+1,1);R3 = orgimg(yy+1,xx,1);R4 = orgimg(yy+1,xx+1,1);
			G1 = orgimg(yy,xx,2);G2 = orgimg(yy,xx+1,2);G3 = orgimg(yy+1,xx,2);G4 = orgimg(yy+1,xx+1,2);
			B1 = orgimg(yy,xx,3);B2 = orgimg(yy,xx+1,3);B3 = orgimg(yy+1,xx,3);B4 = orgimg(yy+1,xx+1,3);
		end
		newimg(y,x,1)=R1*(1-deltax)*(1-deltay)+R2*deltax*(1-deltay)+R3*(1-deltax)*deltay+R4*deltax*deltay;
		newimg(y,x,2)=G1*(1-deltax)*(1-deltay)+G2*deltax*(1-deltay)+G3*(1-deltax)*deltay+G4*deltax*deltay;
		newimg(y,x,3)=B1*(1-deltax)*(1-deltay)+B2*deltax*(1-deltay)+B3*(1-deltax)*deltay+B4*deltax*deltay;
	end
end
