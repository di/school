% Once you get the correspondences you may automated the process of
% computing intermediate frames as follows
% Don't forget to change the file names and step size and dissolve rate (it
% can be a linear/non-linear function of the warp fraction as long as it is
% [0.0 1.0]) accordingly

step=0.1;
cnt=0;
for i=0:step:1.0,
	project2('human1.jpg','dog1.jpg','morph','human1_pts.txt','dog1_pts.txt',i,i,sprintf('humandog1_%d.jpg',cnt));
	cnt=cnt+1;
end

% Once you have all the intermediate frames computed, you may combine them
% into an avi movie file using the following commands
% change the file names accordingly
nframes=ceil(1.0/step)+1;
M=moviein(nframes);
cnt=0;
for i=0:step:1.0,
	imshow(sprintf('humandog1_%d.jpg',cnt));
	M(:,cnt+1)=getframe;
	pause(0);
	cnt=cnt+1;
end

movie(M);

movie2avi(M,'humandog1_morphing.avi','FPS',2,'COMPRESSION','None');

% You can play the resulting movie in matlab as follows
movie(aviread('humandog1_morphing.avi'));

% To play the movie outside matlab, you need a player that plays an
% uncompressed avi file



