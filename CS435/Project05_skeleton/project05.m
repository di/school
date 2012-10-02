%%
%% project05.m
%%
%% Wrapper function for Computational Photography Project 0.5
%%
%% Sample execution:
%%	project05('puppy.jpg','gpuppy.jpg','gaussian',10,10)

function project05(input_filename, output_filename, operation, flag1,flag2)
  

  %%
  %%
  if(nargin < 3) 
    disp(sprintf('Usage: project05(input_filename,output_filename,operation,[flag1,flag2])'));
    disp(sprintf(' Operations:'));
    disp(sprintf('   negative - Image negative'));
    disp(sprintf('   color2gray - Color to gray scale'));
    disp(sprintf('   gamma - Gamma correction'));
    disp(sprintf('      flag1 - Gamma value'));
    disp(sprintf('   mean - Mean filter'));
    disp(sprintf('      flag1 - Window size'));
    disp(sprintf('   gaussian - Gaussian filter'));
    disp(sprintf('      flag1 - Standard deviation'));
    disp(sprintf('      flag2 - Window size'));

  %%
  %% Color to gray scale conversion
  %%
  elseif(strcmp(operation,'color2gray'))

    in_img = imread(input_filename);
    out_img = color2gray(in_img);
    imwrite(out_img,output_filename);

  %%
  %% Image Negative 
  %%
  elseif(strcmp(operation,'negative'))

    in_img = imread(input_filename);
    out_img = negative(in_img);
    imwrite(out_img,output_filename);

  %%
  %% Gamma correction
  %%
  elseif(strcmp(operation,'gamma'))

    if(nargin < 4)
      disp(sprintf('Gamma correction usage:'));
      disp(sprintf('    project05(input_filename,output_filename,\''gamma\'',gamma_value)'));
      return;
    end

    in_img = imread(input_filename);
    out_img = gamma_correction(in_img,flag1);
    imwrite(out_img,output_filename);

  %%
  %% Mean filter
  %%
  elseif(strcmp(operation,'mean'))
    
    if(nargin < 4)
      disp(sprintf('Mean filter usage:'));
      disp(sprintf('    project05(input_filename,output_filename,\''mean\'',window size)'));
      return;
    end      


    in_img = imread(input_filename);
    out_img = mean_filter(in_img,flag1);
    imwrite(out_img,output_filename);

  %%
  %% Gaussian filter
  %%
  elseif(strcmp(operation,'gaussian'))

    if(nargin < 5)
      disp(sprintf('Gaussian filter usage:'));
      disp(sprintf('    project05(input_filename,output_filename,\''gaussian\'',standard deviation, window size)'));
      return;
    end      

    in_img = imread(input_filename);
    out_img = gaussian_filter(in_img,flag1,flag2);
    imwrite(out_img,output_filename);

  else
    disp(sprintf('Invalid operation'));

  end
  
	
	 
		  

  
