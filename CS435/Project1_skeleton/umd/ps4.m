% CMSC 426- Spring 2004
% Problem Set 4
%
% Usage:  mask = ps4(im)
%
% Arguments:   
%            im     - image to be processed.
%
% Returns:
%            mask    - wire mask of the image
%
% Author: 
% Konstantinos Bitsakos
% Department of Computer Science 
% University of Maryland, College Park
% kbits@cs.umd.edu
%
% February 2004

function mask = ps4(im)

[Size_y,Size_x,Size_z]=size(im);

%%%%%%%%%%%%%%%%%%%%%%
% PREPROCESSING STEP %
%%%%%%%%%%%%%%%%%%%%%%
im2=filterimage(im);

iterations=double(1); % The number of pixel pairs, so far
%pixelpairs: A 4xN array containing the seed and end coordinates (x first y
%second
wiremask=zeros(Size_y,Size_x); %A YSize*XSize*Iterations array containing the wire mask

%Select the initial seed point
close all;
figure(1), imshow(im);

disp('Click the seed point');
[s_x, s_y] = ginput(1);
s_x=round(s_x); s_y=round(s_y);
    
figure(1); hold on;
plot(s_x, s_y, 'rx');

pixelpairs(1,1)=s_x;
pixelpairs(2,1)=s_y;

while 1
    user_entry = menu('Choose a function', 'Select a new point', 'Undo last point',...
        'Close wire', 'Print current wire','Exit');

    switch user_entry
        case 1
            disp('Click the new point')
            figure(1);
            [e_x, e_y] = ginput(1);
            e_x=round(e_x); e_y=round(e_y);
            figure(1); hold on;
            plot(e_x,e_y, 'bo');
            
            pixelpairs(3,iterations)=e_x;
            pixelpairs(4,iterations)=e_y;
            pixelpairs(1,iterations+1)=e_x;
            pixelpairs(2,iterations+1)=e_y;

            disp('Finding new wire segment');
            
            wiremask(:,:,iterations)=scissor(im2,pixelpairs(1,iterations),...
                pixelpairs(2,iterations), pixelpairs(3,iterations),pixelpairs(4,iterations));

            iterations=iterations+1;
                        
        case 2
            disp('Undo');
            if iterations > 1
                iterations=iterations-1;
                % Mark the point green
                figure(1); hold on;
                plot(pixelpairs(3,iterations),pixelpairs(4,iterations), 'go');
            end
        case 3
            disp('Finishing wire');

            pixelpairs(3,iterations)=pixelpairs(1,1);
            pixelpairs(4,iterations)=pixelpairs(2,1);

            wiremask(:,:,iterations)=scissor(im2,pixelpairs(1,iterations),...
                pixelpairs(2,iterations), pixelpairs(3,iterations),pixelpairs(4,iterations));
            
            iterations = iterations+1;
        case 4
            wire=zeros(Size_y,Size_x);
            
            for i=1:iterations-1
                wire(:,:) =wire(:,:) | wiremask(:,:,i);
            end

            if length(size(im)) == 3
                imbw = double(rgb2gray(im));
            else
                imbw = double(im);
            end
            maxval = max(imbw(:));
            minval = min(imbw(:));
            wirethick = imfilter(wire, fspecial('average', 3)) > 0;
            W = double(wirethick).*maxval + double(~wirethick).*minval;
            Wcomplement =  double(wirethick).*minval + double(~wirethick).*maxval;
            imwire = (cat(3, max(W,imbw), min(Wcomplement,imbw), min(Wcomplement,imbw))-minval)./maxval; 
           
            figure(2), imagesc(imwire);
            axis equal;
            axis off;          
        case 5
            break;
    end
end

for i=1:iterations-1
    wire(:,:) =wire(:,:) | wiremask(:,:,i);
end
mask=wire;
return