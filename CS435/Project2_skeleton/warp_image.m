%%
%% warp_image.m
%%
%% Computational Photography Project 2
%%
%%
%% Warps an image to an intermediate shape that may then be cross-dissolved
%%
%% INPUT
%%	1) im1			- R x C x 3 image
%%	2) im1pts		- Correspondence points in image 1
%%	3) intermediate_pts  	- Correspondence points in the intermediate image
%%	4) triangles		- The triangulation of the correspondence points
%%
%% OUTPUT
%% 	1) warpped_img		- R x C x 3 warpped image
function [warpped_img] = warp_image(im1,im1pts,intermediate_pts, triangles)

  intermediate_pts = double(intermediate_pts);
  im1 = double(im1);

  %%
  %% Create an empty output image
  %%
  warpped_img = zeros(size(im1));
  


  %%
  %% Loop through each pixel in the output image
  %%
  [rows,columns,c] = size(im1);
  for i=1:rows
    for j=1:columns


			% FILL IN THE FOLLOWING STEPS %

      %%
      %% Find out which triangle the point is in
      %% Use tsearch (a matlab built-in function)          
        tri = tsearch(im1pts(:,1),im1pts(:,2),triangles,i,j);

      %%
      %% Determine the Barycentric coordinates of the point
      %% Fill in and use barycentric.m
                
        barycentric_coord = abs(barycentric([intermediate_pts(triangles(tri,1),1),intermediate_pts(triangles(tri,2),1), intermediate_pts(triangles(tri,3),1)],[intermediate_pts(triangles(tri,1),2),intermediate_pts(triangles(tri,2),2), intermediate_pts(triangles(tri,3),2)], i, j));

      %%
      %% Determine the corresponding pixel location in the original image using
      %% the barycentric coordiantes
      %%

        corresponding_pixel = barycentric_coord(1).*[i,j] + barycentric_coord(2).*[i,j] + barycentric_coord(3).*[i,j];
        
      %%
      %% Store the results.  
			%% Find the pixel intensity using bilinear interpolation 
      %% Fill in and use bilinear_interp.m
      
        warpped_img(i,j,:) = bilinear_interp(im1, corresponding_pixel(1), corresponding_pixel(2));

    end
  end


      
