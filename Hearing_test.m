%Hearing Test for frequencies
%sweeps a range of frequencies from START to MAX with STEP size.
%writes frequencies the user cannot hear to hearing_test.txt

START = 8000;
STEP = 500;
MAX = 18000;
fs = 48000; %sampling frequency
T = 3; %seconds to play
a = 5; %amplitude
sec = 3;
cannot_hear = [];

fprintf('starting hearing test\n');
for n = START:STEP:MAX
        pause(sec);
        fprintf('sound test for %d Hz begin\n',n)
        t = 0:(1/fs):T;
        y = a*sin(2*pi*n*t);
        sound(y, fs)
        
        %prompting
        prompt = 'Can you hear this? (y/n) \n';
        
        pause(sec);
        usr_input = input(prompt,'s');
        if(strcmp(usr_input,'y')) 
            
        else 
            cannot_hear = [cannot_hear n];
        end
end


fileID = fopen('hearing_test.txt', 'w'); 
for i=1:length(cannot_hear)
   fprintf(fileID, '%d\n', cannot_hear(i)); 
end
fclose(fileID);

