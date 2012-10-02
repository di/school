%%
%% project2.m
%%
%% Computational Photography Project 2
%%
%% John Novatnack
%% jmn27@cs.drexel.edu
%%
%% Project 2 main wrapper function
%%
%% See project2_script.m (a wrapper script to automate some of the processes
%% and to make a movie)

function project2(im1_filename, im2_filename, operation, flag1, flag2,flag3, flag4,flag5)

  if(nargin < 3)
    disp('Usage:');
    disp('project2(filename1, filename2, operation, [Flags])');
    disp(' ');
    disp('Valid operations:');
    disp('   get_correspondences');
    disp('       flag1   -  File to write the points from image 1');
    disp('       flag2   -  File to write the points from image 2');
    disp(' ');
    disp('   morph');
    disp('       flag1   -  File containing points from image 1');
    disp('       flag2   -  File containing points from image 2');
    disp('       flag3   -  Warp fraction [0..1]');
    disp('       flag4   -  Dissolve fraction [0..1] ')
    disp('       flag5   -  File name of the output image');

    return;
  end




  %%
  %% Input the correspondences points
  %%
  if(strcmp(operation,'get_correspondences'))
		if nargin~=5,
			fprintf(1,'Example usage: project2(''cpupp.jpg'',''ccow.jpg'',''get_correspondences'',''cpupp_pts.txt'',''ccow_pts.txt'')\n');
			return;
		end
    im1 = imread(im1_filename);
    im2 = imread(im2_filename);
		if size(im1)~=size(im2),
			fprintf(1,'The image sizes should match.\n');
			return;
		end

    [im1pts, im2pts] = get_correspondences(im1,im2);

    save(flag1,'im1pts','-ascii','-double');
    save(flag2,'im2pts','-ascii','-double');
    


  %%
  %% Do the morphing
  %%
  elseif(strcmp(operation,'morph'))
		if nargin~=8,
			fprintf(1,'Example usage: project2(''cpupp.jpg'',''ccow.jpg'',''morph'',''cpupp_pts.txt'',''ccow_pts.txt'',0.8,0.8,''cpuppcow_08.jpg'')\n');
			return;
		end
    %%
    %% Parse the flags
    %%
    im1pts_filename = flag1;
    im2pts_filename = flag2;
    warp_fraction = flag3;
    dissolve_fraction = flag4;
    output_filename = flag5;

    
    %%
    %% Read in the images
    %%
    im1 = imread(im1_filename);
    im2 = imread(im2_filename);
		if size(im1)~=size(im2),
			fprintf(1,'The image sizes should match.\n');
			return;
		end


    %%
    %% Read in the correspondence points
    %%
    im1pts = load(im1pts_filename);
    im2pts = load(im2pts_filename);

    im1pts = double(im1pts);
    im2pts = double(im2pts);


    %%
    %% Do the morph
    %%
    morphed_im = morph(im1,im2,im1pts,im2pts,warp_fraction,dissolve_fraction);

    
    %%
    %% Save the image
    %%
    morphed_im = uint8(morphed_im);
    imwrite(morphed_im,output_filename);

  end

