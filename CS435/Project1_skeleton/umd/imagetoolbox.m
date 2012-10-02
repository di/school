% CMSC 426- Spring 2004
% Problem Set 4
%
% Usage:  finalimage = imagetoolbox(targetim,sourceim,mask)
%
% Arguments:   
%            targetim   - the target image where we will place a part of
%            the source image
%            sourceim   - the source image where the object is located
%            mask       - bitmask that has 1's on the bits that
%
% Returns:
%            finalimage - the final image after the composition
%
% Author: 
% Konstantinos Bitsakos
% Department of Computer Science 
% University of Maryland, College Park
% kbits@cs.umd.edu
%
% February 2004

function finalimage = imagetoolbox(targetim, sourceim, mask)

close all;
clipped=0;
filledmask=imfill(mask,'holes');
%clippedimage: This variable will contain the clipped part of the source
%image

% Clip source image
[SourceSizeY, SourceSizeX, SourceSizeZ]=size(sourceim);

for i=1:SourceSizeZ
    tempim(:,:,i)=double(sourceim(:,:,i)).*filledmask(:,:);
end
tempim=uint8(tempim);
[Y,X]=find(filledmask(:,:)>0);
maxY=max(Y);
maxX=max(X);
minY=min(Y);
minX=min(X);
clippedimage=tempim(minY:maxY,minX:maxX,:);
clippedfilledmask=filledmask(minY:maxY,minX:maxX);
clear tempim;

while 1
    user_entry = menu('Image Toolbox', 'View target image', 'View source image',...
        'View source image clipped', 'Place clipped part on target image','Exit');

    switch user_entry
        case 1
            figure(1), imshow(targetim);              
        case 2
            figure(2), imshow(sourceim);
        case 3
            figure(3), imshow(clippedimage);
        case 4
            disp('Click the upper left corner where the clipped image will be placed')
            figure(1), imshow(targetim);
            [corner_x, corner_y] = ginput(1);
            corner_x=round(corner_x); corner_y=round(corner_y);
            
            finalmask=double(zeros(size(targetim)));
            finalimage2=double(zeros(size(targetim)));
            [maxCY,maxCX,maxCZ]=size(clippedimage);
            finalmask(corner_y:corner_y+maxCY-1,corner_x:corner_x+maxCX-1)=clippedfilledmask(:,:);
            finalimage2(corner_y:corner_y+maxCY-1,corner_x:corner_x+maxCX-1,:)=clippedimage(:,:,:);
            for i=1:size(targetim,3)
                finalimage1(:,:,i)=double(targetim(:,:,i)) .* (~ finalmask(:,:,1)); 
            end
            finalimage=uint8(finalimage1+finalimage2);
            figure(4), imshow(finalimage);
        case 5
            break;
    end
end

